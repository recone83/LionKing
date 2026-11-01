use strict;
use warnings;
use FindBin;
use File::Spec;
use File::Temp qw(tempdir);

chdir File::Spec->catdir($FindBin::Bin, '..') or die "Cannot enter workspace: $!";
open my $binary, '<:raw', 'bin/obj1_code.bin' or die "Cannot read code object: $!";
local $/;
my $code = <$binary>;
close $binary or die "Cannot close code object: $!";
my @calls = (
    [0x14, 0x84], [0x19, 0x70], [0x1e, 0x740], [0x23, 0xb70],
    [0x2d, 0x2210], [0x32, 0x8a7f], [0x37, 0x8d18], [0x46, 0x3677],
    [0x4b, 0x864c], [0x50, 0x46b0], [0x5a, 0x1f0],
);
for my $call (@calls) {
    my ($offset, $target) = @$call;
    die "Main binary call mismatch at $offset\n"
        unless substr($code, $offset, 1) eq "\xe8"
        && $offset + 5 + unpack('l<', substr($code, $offset + 1, 4)) == $target;
}
for my $literal (
    [0x28, 'b804000000'],
    [0x3c, 'b4ff31d2882596730100'],
    [0x55, 'b811000000'],
) {
    die "Main binary argument/flag mismatch\n"
        unless substr($code, $literal->[0], length($literal->[1]) / 2)
            eq pack('H*', $literal->[1]);
}
my $dir = tempdir(CLEANUP => 1);
my $harness = File::Spec->catfile($dir, 'check_main.c');
my $executable = File::Spec->catfile($dir, 'check_main');
my $main = File::Spec->rel2abs('src/engine/main.c');
open my $file, '>', $harness or die "Cannot write $harness: $!";
print {$file} <<"C" or die "Cannot write $harness: $!";
#include <assert.h>
#include <stdio.h>

unsigned char DAT_00017396;
#include "$main"

static unsigned int step;
static void expect(unsigned int expected) { assert(step++ == expected); }
void FUN_00000084(void) { expect(0); }
void FUN_00000070(void) { expect(1); }
void FUN_00000740(void) { expect(2); }
void FUN_00000b70(void) { expect(3); }
void FUN_00002210(unsigned int offset) { expect(4); assert(offset == 4); }
void audio_config_parse_settings(void) { expect(5); }
void audio_config_initialize_backend(void) { expect(6); }
void FUN_00003677(void) {
  expect(7);
  assert(DAT_00017396 == 0xff);
  DAT_00017396 = 0;
}
void FUN_0000864c(void) { expect(8); assert(DAT_00017396 == 0); }
void FUN_000046b0(void) { expect(9); }
void FUN_000001f0(unsigned int offset) { expect(10); assert(offset == 0x11); }

int main(void) {
  game_main();
  assert(step == 11);
  puts("PASS: main call order, data offsets and joystick flag");
  return 0;
}
C
close $file or die "Cannot close $harness: $!";
system('cc', '-std=c99', '-Wall', '-Wextra', '-Werror', $harness, '-o', $executable) == 0
    or die "Cannot compile main test harness (cc required)\n";
system($executable) == 0 or die "Main reconstruction test failed\n";
