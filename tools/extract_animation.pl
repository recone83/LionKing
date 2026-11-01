#!/usr/bin/env perl
use strict;
use warnings;
use Digest::SHA qw(sha256_hex);

die "Usage: perl tools/extract_animation.pl bin/obj2_data.bin\n" unless @ARGV == 1;
open my $file, '<:raw', $ARGV[0] or die "Cannot read $ARGV[0]: $!\n";
local $/;
my $data = <$file>;
close $file or die "Cannot close $ARGV[0]: $!\n";
die "Original data dump checksum mismatch\n"
    unless sha256_hex($data) eq
        '3e8e0b247c00a95dfb9a3353745cb76bf1df1acb5337e62dd0de0cac25d2d634';
my $bytes = substr($data, 0x6531, 0x8048 - 0x6531);
print "/* Generated from original DS:0x6531..0x8048; do not edit. */\n";
print "#include \"engine/animation_data.h\"\n";
print "const unsigned char animation_idle_data[ANIMATION_IDLE_SIZE] = {\n";
my @bytes = unpack 'C*', $bytes;
while (@bytes) {
    my @row = splice @bytes, 0, 16;
    print '    ', join(', ', map { sprintf '0x%02x', $_ } @row), ",\n";
}
print "};\n";
print "const unsigned char animation_idle_script[ANIMATION_IDLE_SCRIPT_SIZE] = {\n";
print '    ', join(', ', map { sprintf '0x%02x', $_ }
    unpack('C*', substr($data, 0x5f84, 22))), "\n};\n";
