# COMP1521 18s2 Week 04 Lab
# Compute factorials, iterative function


### Global data

   .data
msg1:
   .asciiz "n  = "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function
   .text
   .globl main
main:
   #  set up stack frame
   sw    $fp, -4($sp)       # push $fp onto stack
   la    $fp, -4($sp)       # set up $fp for this function
   sw    $ra, -4($fp)       # save return address
   sw    $s0, -8($fp)       # save $s0 to use as ... int n;
   addi  $sp, $sp, -12      # reset $sp to last pushed item

   #  code for main()
   li    $s0, 0             # n = 0;
   
   la    $a0, msg1
   li    $v0, 4
   syscall                  # printf("n  = ");

## ... rest of code for main() goes here ...
   li 	 $v0, 5
   syscall					
   add	 $s0, $v0, $zero	# scanf("%d", &n)

   add	 $a0, $s0, $zero	# store n in $a0 as argument
   jal 	 fac
   add	 $s1, $v0, $zero	# $a0 = fac(n)

   la 	 $a0, msg2
   li	 $v0, 4
   syscall

   add	 $a0, $s1, $zero	# $a0 = fac(n)
   li	 $v0, 1
   syscall					# printf(fac(n))
 
   la    $a0, eol
   li    $v0, 4
   syscall                  # printf("\n");

   # clean up stack frame
   lw    $s0, -8($fp)       # restore $s0 value
   lw    $ra, -4($fp)       # restore $ra for return
   la    $sp, 4($fp)        # restore $sp (remove stack frame)
   lw    $fp, ($fp)          # restore $fp (remove stack frame)

   li    $v0, 0
   jr    $ra                # return 0

# fac() function

fac:
   # setup stack frame

## ... code for prologue goes here ...
   sw	 $fp, -4($sp)		# push $fp onto the stack
   la 	 $fp, -4($sp)		# move $fp to the new frame start
   sw 	 $ra, -8($sp)		# store $ra
   sw 	 $s0, -12($sp)		# store $s0
   addi	 $sp, $sp, -16 		# move $sp to the end of the fram

   # code for fac()

## ... code for fac() goes here ...
   li 	 $s1, 1				# i = 1
   li 	 $s2, 1				# prod = 1

for1:
   bgt 	 $s1, $s0, exitfor1
   mult	 $s2, $s1			# prod * i
   mflo	 $s2				# prod = prod * i
   addi	 $s1, $s1, 1		# i++
   j for1

exitfor1:
   add	 $v0, $s2, $zero

   # clean up stack frame

## ... code for epilogue goes here ...
   lw	 $s0, -8($fp)		# restore the value of $s0
   lw	 $ra, -4($fp)		# restore the value of $ra
   la	 $sp, 4($fp)		# move $sp to end of previous frame
   lw	 $fp, ($fp)			# move $fp to start of previous frame
   jr	 $ra				# return to previous execution point in main
