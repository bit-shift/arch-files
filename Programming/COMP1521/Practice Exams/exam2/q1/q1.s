# COMP1521 Practice Prac Exam #1
# int everyKth(int *src, int n, int k, int*dest)

   .text
   .globl everyKth

# params: src=$a0, n=$a1, k=$a2, dest=$a3
everyKth:
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

   # add code for your everyKth function here
   li	$t0, 0
   li	$t1, 0
   li	$t8, 4
   mul	$t9, $a2, $t8 
for:
   bge	$t0, $a1, endfor
   lw	$t2, ($a0)
   sw	$t2, ($a3)
   add	$a0, $a0, $t9
   addi	$a3, $a3, 4
   add 	$t0, $t0, $a2
   addi	$t1, $t1, 1
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

