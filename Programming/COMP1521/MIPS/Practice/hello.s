# MIPS Hello World printout
# Keegan Gyoery z5197058
# 2018-3-13

		.data
msg:	.asciiz "Hello, World!\n"

		.text
		.globl main

main:
		la $a0, msg
		li $v0, 4
		syscall
		jr $ra
