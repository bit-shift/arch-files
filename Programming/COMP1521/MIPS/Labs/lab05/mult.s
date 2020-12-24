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
