# COMP1521 17s2 Final Exam
# void colSum(m, N, a)

   .text
   .globl colSum

# params: m=$a0, N=$a1, a=$a2
colSum:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   addi $sp, $sp, -4
   sw   $s4, ($sp)
   addi $sp, $sp, -4
   sw   $s5, ($sp)
   # if you need to save more than six $s? registers
   # add extra code here to save them on the stack

# suggestion for local variables (based on C code):
# m=#s0, N=$s1, a=$s2, row=$s3, col=$s4, sum=$s5

   # add code for your colSum function here
   li	$t0, 0
   li	$t1, 0
   li	$t3, 0
   li	$t9, 4
   mul	$t8, $t9, $a1

forcol:
   bge	$t1, $a1, endforcol
   li	$t3, 0
   add	$t2, $a0, $0
   mul	$t4, $t1, $t9
   add	$t2, $t2, $t4
forrow:
   bge	$t0, $a1, endforrow
   lw	$t7, ($t2)
   add	$t3, $t3, $t7
   addi	$t0, $t0, 1
   add	$t2, $t2, $t8
   j	forrow
endforrow:
   sw	$t3, ($a2)
   add	$a2, $a2, $t9
   addi	$t1, $t1, 1
   j	forcol
endforcol:
   

# epilogue
   # if you saved more than six $s? registers
   # add extra code here to restore them
   lw   $s5, ($sp)
   addi $sp, $sp, 4
   lw   $s4, ($sp)
   addi $sp, $sp, 4
   lw   $s3, ($sp)
   addi $sp, $sp, 4
   lw   $s2, ($sp)
   addi $sp, $sp, 4
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

