# Header Comment
# Keegan Gyoery z5197058
# 2018-xx-xx

        .data
eol:    .asciiz "\n"

        .text
        .globl main

main:
    li	$a0, 5
    jal delay

delay:
# Code:
    # set up stack frame
    sw      $fp, -4($sp)
    sw      $ra, -8($sp)
    la      $fp, -4($sp)
    addi	$sp, $sp, -8

### TODO: your code goes here
    li		$t0, 0
for1:
    bgt     $t0, $a0, endfor1
    addi    $t0, $t0, 1
    j       for1
endfor1:
    # tear down stack frame
    lw      $ra, -4($fp)
    la      $sp, 4($fp)
    lw      $fp, ($fp)
    jr      $ra
