# COMP1521 18s2 Week 05 Lab
#
# Matrix data

   .data
N: .word  2
M: .word  2
P: .word  2
A: .word  1, 2, 3, 4
B: .word  5, 6, 7, 8
C: .space 16

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
	sw	$s3, -12($sp)
	sw	$s4, -16($sp)
	sw	$s5, -20($sp)
	sw	$s6, -24($sp)
	sw	$s7, -28($sp)
	addi	$sp, $sp, -28

	# implement above C code
	lw	$t2, 4($fp)			# $t2 = &C[0][0]
	li	$t9, 4				# $t9 = 4 -> size of memory block
	mul	$s7, $a2, $t9			# $s7 = 4*p -> to move down a column
	li	$s3, 0				# r = 0
forR:
	bge	$s3, $a0, endforR		# if(r >= n) goto endforR
	li	$s4, 0				# c = 0
forC:
	bge	$s4, $a2, endforC		# if(c >= p) goto endforC
	li	$s5, 0				# i = 0
	li	$s6, 0				# sum = 0
	mul	$t3, $s3, $a1
	mul	$t3, $t3, $t9			# $t3 = r*m*4 -> offset to beginning of row r
	lw	$t0, 12($fp)			# $t0 = &A[0][0]
	add	$t0, $t0, $t3			# $t0 = &A[r][0]
	mul	$t3, $s4, $t9			# $t3 = c*4 -> offset to beginning of column c
	lw	$t1, 8($fp)			# $t1 = &B[0][0]
	add	$t1, $t1, $t3			# $t1 = &B[0][c]
dotProd:
	bge	$s5, $a1, enddotProd		# if(i >= m) goto enddotProd
	lw	$t5, ($t0)			# $t5 = A[r][i]
	lw	$t6, ($t1)			# $t6 = B[i][c]
	mul	$t3, $t5, $t6			# $t3 = A[r][i]*B[i][c]
	add	$s6, $s6, $t3			# sum += A[r][i]*B[i][c]
	addi	$t0, $t0, 4			# $t0 = &A[r][i] + 4 -> move to the next column in the row
	add	$t1, $t1, $s7			# $t1 = &B[c][i] + 4*p -> move to the next row in the column
	addi	$s5, $s5, 1			# i += 1
	j	dotProd
enddotProd:
	sw	$s6, ($t2)			# C[r][c] = sum
	addi	$t2, $t2, 4			# $t2 = &C[r][c] + 4 -> next position in matrix
	addi	$s4, $s4, 1			# c += 1
	j	forC
endforC:
	addi	$s3, $s3, 1			# r += 1
	j	forR
endforR:

	# clean up stack and return
	la	$sp, 4($fp)
	lw	$ra, -4($fp)
	lw	$s3, -8($fp)
	lw	$s4, -12($fp)
	lw	$s5, -16($fp)
	lw	$s6, -20($fp)
	lw	$s7, -24($fp)
	lw	$fp, ($fp)
	jr	$ra
