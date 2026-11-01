use strict;
use warnings;
use FindBin;
use File::Spec;
use File::Path qw(make_path);

chdir File::Spec->catdir($FindBin::Bin, '..') or die "Cannot enter workspace: $!";
my $check_only = @ARGV == 1 && $ARGV[0] eq '--check';
die "Usage: perl tools/split_pseudocode.pl [--check]\n"
    if @ARGV && !$check_only;

sub read_text {
    my ($path) = @_;
    open my $file, '<:raw', $path or die "Cannot read $path: $!";
    local $/;
    return <$file>;
}

sub write_text {
    my ($path, $text) = @_;
    open my $file, '>:raw', $path or die "Cannot write $path: $!";
    print {$file} $text or die "Cannot write $path: $!";
    close $file or die "Cannot close $path: $!";
}

my (@renames, %forward, %reverse, %destinations);
my @rows = split /\n/, read_text('libs/RENAMES.tsv');
die "Invalid rename manifest header\n"
    unless shift(@rows) eq "original_symbol\tcurrent_symbol\tmodule";
for my $row (@rows) {
    next unless length $row;
    my ($old, $new, $module) = split /\t/, $row, -1;
    die "Invalid manifest row: $row\n"
        unless defined $module && $old =~ /^FUN_[0-9a-f]{8}$/
        && $new =~ /^[a-z][a-z0-9_]+$/
        && $module =~ m{^(?:libs|engine)/[a-z_]+\.c$};
    die "Duplicate rename: $row\n" if exists $forward{$old} || exists $reverse{$new};
    $forward{$old} = $new;
    $reverse{$new} = $old;
    $destinations{$old} = $module;
    push @renames, [$old, $new, $module];
}

sub original_names {
    my ($text) = @_;
    $text =~ s/\b([A-Za-z_][A-Za-z0-9_]*)\b/exists $reverse{$1} ? $reverse{$1} : $1/ge;
    return $text;
}

sub definitions {
    my ($text) = @_;
    my %result;
    while ($text =~ /^([^\n;{}]*\b((?:thunk_)?FUN_[0-9a-f]{8}|[a-z][a-z0-9_]+)\([^\n;{}]*\)\n(?:\s*\n)*\{.*?^\})/msg) {
        my ($body, $symbol) = ($1, $2);
        my ($start, $end) = ($-[1], $+[1]);
        next unless $symbol =~ /^(?:thunk_)?FUN_[0-9a-f]{8}$/ || exists $reverse{$symbol};
        my $original = $reverse{$symbol} // $symbol;
        die "Duplicate definition $original\n" if exists $result{$original};
        $result{$original} = {
            body => $body, start => $start, end => $end,
            line => 1 + (substr($text, 0, $start) =~ tr/\n//),
            symbol => $symbol,
        };
    }
    return \%result;
}

my $backup = read_text('pseiudo.c.backup');
my $source = definitions($backup);
die "Expected 750 backup definitions, got " . scalar(keys %$source) . "\n"
    unless keys(%$source) == 750;

my @paths = ('pseiudo.c', sort(glob('libs/*.c')), sort(glob('engine/*.c')));
my %texts = map { $_ => read_text($_) } @paths;

sub validate {
    my ($files, $renamed) = @_;
    my (%owners, %counts);
    for my $path (sort keys %$files) {
        my $defs = definitions($files->{$path});
        $counts{$path} = scalar keys %$defs;
        for my $old (keys %$defs) {
            die "Unknown definition $old in $path\n" unless exists $source->{$old};
            die "Overlapping definition $old\n" if exists $owners{$old};
            $owners{$old} = $path;
            die "Changed signature/body for $old in $path\n"
                unless original_names($defs->{$old}{body}) eq $source->{$old}{body};
            if ($renamed && exists $forward{$old}) {
                die "Incorrect symbol/owner for $old\n"
                    unless $defs->{$old}{symbol} eq $forward{$old}
                    && $path eq $destinations{$old};
            }
        }
    }
    for my $old (keys %$source) {
        die "Missing definition $old\n" unless exists $owners{$old};
    }
    if ($renamed) {
        for my $path (keys %$files) {
            my $text = $files->{$path};
            $text =~ s{/\*.*?\*/|//[^\n]*}{}gs;
            for my $old (keys %forward) {
                die "Stale reference $old in $path\n" if $text =~ /\b\Q$old\E\b/;
            }
        }
        for my $path (keys %$files) {
            next if $path eq 'pseiudo.c';
            die "Module not included: $path\n"
                unless $files->{'pseiudo.c'} =~ /^#include "\Q$path\E"$/m;
        }
    }
    return (\%owners, \%counts);
}

validate(\%texts, 0);
unless ($check_only) {
    for my $rename (@renames) {
        my ($old, $new, $module) = @$rename;
        my $defs = definitions($texts{'pseiudo.c'});
        next unless exists $defs->{$old};
        my $def = $defs->{$old};
        my $start = $def->{start};
        my $prefix = substr($texts{'pseiudo.c'}, 0, $start);
        if ($prefix =~ /((?:\n|^[ \t]*\/\/[^\n]*\n)+)\z/m) {
            $start = $-[1];
        }
        my $chunk = substr($texts{'pseiudo.c'}, $start, $def->{end} - $start, '');
        $texts{$module} //= "/* Extracted pseudocode; not yet compilable. */\n";
        my $address = hex(substr($old, 4)) + 0x10000;
        $texts{$module} .= sprintf(
            "\n/* Backup line %d; original %s; code address 0x%x. */\n%s\n",
            $source->{$old}{line}, $old, $address, $chunk
        );
    }
    for my $path (keys %texts) {
        $texts{$path} =~ s{(/\* Backup line \d+; original )([a-z][a-z0-9_]+)(;)}
            {$1 . ($reverse{$2} // $2) . $3}ge;
        $texts{$path} =~ s{(/\*.*?\*/|//[^\n]*)|\b([A-Za-z_][A-Za-z0-9_]*)\b}
            {defined $1 ? $1 : ($forward{$2} // $2)}gse;
    }
    for my $path (sort keys %texts) {
        next if $path eq 'pseiudo.c';
        next if $texts{'pseiudo.c'} =~ /^#include "\Q$path\E"$/m;
        $texts{'pseiudo.c'} =~ s/(#include "libs\/libc_conio\.c"\n)/$1#include "$path"\n/
            or die "Cannot find module include anchor\n";
    }
}

my ($owners, $counts) = validate(\%texts, 1);
my $inventory = "source_line\tsymbol\tgroup\tsource_address\tnormalized_address\tcurrent_symbol\tmodule\n";
for my $old (sort { $source->{$a}{line} <=> $source->{$b}{line} } keys %$owners) {
    my $path = $owners->{$old};
    next if $path eq 'pseiudo.c';
    my ($group) = $path =~ m{/([^/]+)\.c$};
    my ($offset) = $old =~ /([0-9a-f]{8})$/;
    $inventory .= join("\t", $source->{$old}{line}, $old, $group,
        "0x$offset", sprintf('0x%x', hex($offset) + 0x10000),
        $forward{$old} // $old, $path) . "\n";
}

if ($check_only) {
    die "Function inventory is out of date\n"
        unless read_text('libs/FUNCTIONS.tsv') eq $inventory;
} else {
    make_path('engine');
    for my $path (sort keys %texts) {
        write_text($path, $texts{$path}) unless -e $path && read_text($path) eq $texts{$path};
    }
    write_text('libs/FUNCTIONS.tsv', $inventory);
}
print "PASS: 750 definitions, no loss/overlap, unchanged signatures/bodies after reverse renaming.\n";
print "$_: $counts->{$_} definitions\n" for sort keys %$counts;
