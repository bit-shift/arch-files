# Header Comment
# Keegan Gyoery z5197058
# 2018-xx-xx

        .data
eol:    .asciiz "\n"

        .text
        .globl main

main:
	li		$a0, 10
	jal		delay
	li		$v0, 0
	jr		$ra

delay:
	sw		$fp, -4($sp)
	sw		$ra, -8($sp)
	la		$fp, -4($sp)
	addi	$sp, $sp, -12

	li		$t0, 0

for:
	bgt		$t0, $a0, endfor
	addi	$t0, $t0, 1
	j for

endfor:
	li		$v0, 0

	lw		$ra, -4($fp)
	la		$sp, 4($fp)
	lw		$fp, ($fp)		
	jr		$ra
