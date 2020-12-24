# COMP1521 18s2 Week 05 Lab
#
# Matrix data #2

   .data
N: .word  3
M: .word  2
P: .word  4
A: .word  1, 2, 3, 4, 5, 6
B: .word  8, 7, 6, 5, 4, 3, 2, 1
C: .space 48

# COMP1521 18s1 Week 05 Lab
#
# Main program to drive matrix multiplication
# Assumes that labels N,M,P,A,B,C exist, and
# refer to appropriate objects/values
   .data
labelA:
   .asciiz "A:\n"
labelB:
   .asciiz "\nB:\n"
labelC:
   .asciiz "\nC:\n"

   .text
   .globl main
main:
   # set up stack frame for main()
   sw   $fp, -4($sp)
   la   $fp, -4($sp)
   sw   $ra, -4($fp)
   addi $sp, $sp, -8

   # print matrix A
   la   $a0, labelA
   li   $v0, 4
   syscall
   lw   $a0, N
   lw   $a1, M
   la   $a2, A
   jal  printMatrix

   # print matrix B
   la   $a0, labelB
   li   $v0, 4
   syscall
   lw   $a0, M
   lw   $a1, P
   la   $a2, B
   jal  printMatrix

   # multiply C = A x B
   lw   $a0, N             # matrix dimensions in $a?
   lw   $a1, M
   lw   $a2, P
   addi $sp, $sp, -4       # matrix addresses on stack
   la   $t0, A
   sw   $t0, ($sp)         # push(&A)
   addi $sp, $sp, -4
   la   $t0, B
   sw   $t0, ($sp)         # push(&B)
   addi $sp, $sp, -4
   la   $t0, C
   sw   $t0, ($sp)         # push(&C)
   jal  multMatrices
   nop
   addi $sp, $sp, 12       # clean args off stack

   # print matrix C
   la   $a0, labelC
   li   $v0, 4
   syscall
   lw   $a0, N
   lw   $a1, P
   la   $a2, C
   jal  printMatrix

   # return 0 and clean up stack
   li   $v0, 0
   lw   $ra, -4($fp)
   la   $sp, 4($fp)
   lw   $fp, ($fp)
   jr   $ra

# COMP1521 18s1 Week 05 Lab
#
# void printMatrix(int nrows, int ncols, int m[nrows][ncols])
# {
#    for (int r = 0; r < nrows; r++) {
#       for (int c = 0; c < ncols; c++) {
#          printf(" %3d", m[r][c]);
#       }
#       printf("\n");
#    }
# }

   .text
   .globl printMatrix
printMatrix:
   # register usage:
   # nrows is $s0, ncols is $s1, r is $s2, c is $s3

   # set up stack frame for printMatrix()
   sw   $fp, -4($sp)
   la   $fp, -4($sp)
   sw   $ra, -4($fp)
   sw   $s0, -8($fp)
   sw   $s1, -12($fp)
   sw   $s2, -16($fp)
   sw   $s3, -20($fp)
   addi $sp, $sp, -24

   # set up registers
   move $s0, $a0
   move $s1, $a1
   
   # for r in 0..nrows-1
   li   $s2, 0
print_loop1:
   bge  $s2, $s0, print_end1
   # for c in 0..ncols-1
   li   $s3, 0
print_loop2:
   bge  $s3, $s1, print_end2
   # get m[r][c]
   li   $t1, 4            # sizeof(int)
   mul  $t0, $s2, $s1
   mul  $t0, $t0, $t1     # offset of start of row r
   mul  $t1, $s3, $t1     # offset of col c within row
   add  $t0, $t0, $t1     # offset from start of matrix
   add  $t0, $t0, $a2
   lw   $a0, ($t0)        # a0 = m[r][c]
   li   $v0, 1
   syscall                # printf("%d", a0)
   li   $a0, ' '
   li   $v0, 11
   syscall                # putchar(' ')
   addi $s3, $s3, 1       # c++
   j    print_loop2
print_end2:
   li   $a0, '\n'         # putchar('\n')
   li   $v0, 11
   syscall
   addi $s2, $s2, 1       # r++
   j    print_loop1
print_end1:

   # clean up stack and return
   lw   $ra, -4($fp)
   lw   $s0, -8($fp)
   lw   $s1, -12($fp)
   lw   $s2, -16($fp)
   lw   $s3, -20($fp)
   la   $sp, 4($fp)
   lw   $fp, ($fp)
   jr   $ra

# COMP1521 18s1 Week 05 Lab
#
# void multMatrices(int n, int m, int p,
#                   int A[n][m], int B[m][p], int C[n][p])
# {
#    for (int r = 0; r < n; r++) {
#       for (int c = 0; c < p; c++) {
#          int sum = 0;
#          for (int i = 0; i < m; i++) {
#             sum += A[r][i] * B[i][c];
#          }
#          C[r][c] = sum;
#       }
#    }
# }

   .text
   .globl multMatrices
multMatrices:
# possible register usage:
# n is $s0, m is $s1, p is $s2,
# r is $s3, c is $s4, i is $s5, sum is $s6
# $a0 = N, $a1 = M, $a2, = P

	# set up stack frame for multMatrices()
	sw	$fp, -4($sp)
	la	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	sw	$s2, -20($sp)
	sw	$s3, -24($sp)
	sw	$s4, -28($sp)
	sw	$s5, -32($sp)
	sw	$s6, -36($sp)
	sw	$s7, -40($sp)
	addi	$sp, $sp, -40
	# implement above C code
	lw	$t0, 12($fp)				# &A
	lw	$t1, 8($fp)			# &B
	lw	$t2, 4($fp)			# &C
	li	$t9, 4
	add	$s0, $a0, $0
	add	$s1, $a1, $0
	add	$s2, $a2, $0
	mul	$s7, $s2, $t9			# 4*p
	li	$s3, 0
forR:
	bge	$s3, $s0, endforR
	li	$s4, 0
forC:	
	bge	$s4, $s2, endforC
	li	$s5, 0
	li	$s6, 0
	mul	$t3, $s3, $s1
	mul	$t4, $t3, $t9
	lw	$t0, 12($fp)
	add	$t0, $t0, $t4
	mul	$t3, $s4, $t9
	lw	$t1, 8($fp)
	add	$t1, $t1, $t3
dotProd:
	bge	$s5, $s1, enddotProd
	lw	$t5, ($t0)
	lw	$t6, ($t1)
	mul	$t8, $t5, $t6
	add	$s6, $s6, $t8
	addi	$t0, $t0, 4
	add	$t1, $t1, $s7
	addi	$s5, $s5, 1
	j	dotProd

enddotProd:
	sw	$s6, ($t2)
	addi	$t2, $t2, 4
	addi	$s4, $s4, 1
	j	forC

endforC:
	addi	$s3, $s3, 1
	j	forR

endforR:

	# clean up stack and return
	la	$sp, 4($fp)
	lw	$ra, -4($fp)
	lw	$s0, -8($fp)
	lw	$s1, -12($fp)
	lw	$s2, -16($fp)
	lw	$s3, -20($fp)
	lw	$s4, -24($fp)
	lw	$s5, -28($fp)
	lw	$s6, -32($fp)
	lw	$s7, -36($fp)
	lw	$fp, ($fp)
	jr	$ra
