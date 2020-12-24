# COMP1521 Practice Prac Exam #1
# int lowerfy(char *src, char *dest)

   .text
   .globl lowerfy

# params: src=$a0, dest=$a1
lowerfy:
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

   # add code for your lowerfy function here
   li	$t1, 0
   li	$t2, '\0'
for:
   lb	$t3, ($a0)
   beq	$t3, $t2, endfor

   blt	$t3, 'A', endif
   bgt	$t3, 'Z', endif
   addi	$t3, $t3, 'a'
   addi	$t3, $t3, -'A'
   addi	$t1, $t1, 1
endif:
   sb	$t3, ($a1)
   addi	$a0, $a0, 1
   addi	$a1, $a1, 1
   j	for
endfor:
   sb	$t2, ($a1)
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

