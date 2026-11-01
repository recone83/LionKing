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
print "/* Generated from checksum-verified original DS data; do not edit. */\n";
print "#include \"engine/animation_data.h\"\n";
print "const unsigned char animation_level6_bank_list[188] = {\n";
my @banks = unpack 'C*', substr($data, 0xe3d0, 188);
while (@banks) {
    my @row = splice @banks, 0, 16;
    print '    ', join(', ', map { sprintf '0x%02x', $_ } @row), ",\n";
}
print "};\n";
print "const unsigned char animation_emitter_data[ANIMATION_EMITTER_SIZE] = {\n";
my @emitter = unpack 'C*', substr($data, 0xe48c, 0x16728 - 0xe48c);
while (@emitter) {
    my @row = splice @emitter, 0, 16;
    print '    ', join(', ', map { sprintf '0x%02x', $_ } @row), ",\n";
}
print "};\n";
print "const unsigned char animation_idle_data[ANIMATION_IDLE_SIZE] = {\n";
my @bytes = unpack 'C*', $bytes;
while (@bytes) {
    my @row = splice @bytes, 0, 16;
    print '    ', join(', ', map { sprintf '0x%02x', $_ } @row), ",\n";
}
print "};\n";
print "const unsigned char animation_falling_data[ANIMATION_FALLING_SIZE] = {\n";
my @falling = unpack 'C*', substr($data, 0xe4b4, 0x1675a - 0xe4b4);
while (@falling) {
    my @row = splice @falling, 0, 16;
    print '    ', join(', ', map { sprintf '0x%02x', $_ } @row), ",\n";
}
print "};\n";
print <<'FALLING';
int animation_falling_initialize(ANIMATION_PROGRAM *program)
{
    return animation_program_initialize(program, animation_falling_data,
        ANIMATION_FALLING_SIZE, ANIMATION_FALLING_BASE, ANIMATION_FALLING_START,
        animation_falling_data, ANIMATION_FALLING_SIZE, ANIMATION_FALLING_BASE);
}
FALLING
print <<'TIMED';
int animation_timed_initialize(ANIMATION_PROGRAM *program)
{
    return animation_program_initialize(program, animation_falling_data,
        ANIMATION_FALLING_SIZE, ANIMATION_FALLING_BASE, ANIMATION_TIMED_START,
        animation_falling_data, ANIMATION_FALLING_SIZE, ANIMATION_FALLING_BASE);
}
TIMED
print <<'NATIVE';
int animation_movement_initialize(ANIMATION_PROGRAM *program)
{
    return animation_program_initialize(program, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, ANIMATION_MOVEMENT_START,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE);
}
NATIVE
print "const unsigned char animation_idle_script[ANIMATION_IDLE_SCRIPT_SIZE] = {\n";
print '    ', join(', ', map { sprintf '0x%02x', $_ }
    unpack('C*', substr($data, 0x5f84, 22))), "\n};\n";
print "const unsigned char animation_movement_data[ANIMATION_MOVEMENT_SIZE] = {\n";
@bytes = unpack 'C*', substr($data, 0x3252, 0xfc44 - 0x3252);
while (@bytes) {
    my @row = splice @bytes, 0, 16;
    print '    ', join(', ', map { sprintf '0x%02x', $_ } @row), ",\n";
}
print "};\n";
