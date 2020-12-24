# Header Comment
# Keegan Gyoery z5197058
# 2018-xx-xx

        .data
msg1:	.asciiz "First lines result: "
msg2:	.asciiz "Second lines result: "
eol:    .asciiz "\n"

        .text
        .globl main

main:
	add		$t1, $0, $0
	lui		$t1, 0x4321
	ori		$t1, $t1, 0x8765
	la		$a0, msg1
	li		$v0, 4
	syscall
	la		$a0, eol
	syscall
	add		$a0, $t1, $0
	li		$v0, 1
	syscall
