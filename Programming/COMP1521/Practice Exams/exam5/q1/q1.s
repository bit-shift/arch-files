# COMP1521 Practice Prac Exam #1
# (int dp, int n) dotProd(int *a1, int n1, int *a2, int n2)

   .text
   .globl dotProd

# params: a1=$a0, n1=$a1, a2=$a2, n2=$a3
dotProd:
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
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...

   # add code for your dotProd function here
   li	$t0, 0
   li	$t1, 0
   bge	$a1, $a3, else
   add	$t3, $a1, $0
   j	endif
else:
   add	$t3, $a3, $0
endif:
for:
   bge	$t0, $t3, endfor
   lw	$t5, ($a0)
   lw	$t6, ($a2)
   mul	$t7, $t5, $t6
   add	$t1, $t1, $t7
   addi	$t0, $t0, 1
   addi	$a0, $a0, 4
   addi	$a2, $a2, 4
   j	for

endfor:
   add	$v0, $t1, $0
   add	$v1, $t3, $0


# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

