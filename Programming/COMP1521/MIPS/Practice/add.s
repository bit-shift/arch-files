# Header Comment
# Keegan Gyoery z5197058
# 2018-xx-xx

        .data
str1:	.asciiz "Please enter an integer: "
str2:	.asciiz "The sum of the two integers is: "
eol:	.asciiz "\n"

        .text
        .globl main

main:
		la $a0, str1
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		add $t0, $v0, $0
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		add $t1, $v0, $0
		add $t2, $t0, $t1
		la $a0, str2
		li $v0, 4
		syscall
		add $a0, $t2, $0
		li $v0, 1
		syscall
		la $a0, eol
		li $v0, 4
		syscall
		jr $ra		
