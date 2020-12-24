# COMP1521 Practice Prac Exam #1
# int rmOdd(int *src, int n, int*dest)

   .text
   .globl rmOdd

# params: src=$a0, n=$a1, dest=$a2
rmOdd:
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

   # add code for your rmOdd function here
   li	$t0, 0 #i
   li	$t1, 0 #j
   li	$t9, 2

for:	
   bge	$t0, $a1, endfor
   lw	$t2, ($a0)
   rem	$t3, $t2, $t9
   bnez	$t3, endif
   sw	$t2, ($a2)
   addi	$a2, $a2, 4
   addi	$t1, $t1, 1
endif:
   addi	$a0, $a0, 4
   addi	$t0, $t0, 1
   j	for
endfor:
   add	$v0, $t1, $0


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

