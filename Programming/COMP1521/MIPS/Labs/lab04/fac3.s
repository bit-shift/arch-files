# COMP1521 18s2 Week 04 Lab
# Compute factorials, recursive function


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
   li	 $v0, 5
   syscall
   add	 $s0, $v0, $zero	# scanf("%d", &n)

   add	 $a0, $s0, $zero	# set up n as argument to fac
   jal	 fac
   add	 $s1, $v0, $zero	# $s2 = fac(n)

   la	 $a0, msg2
   li	 $v0, 4
   syscall					# printf("n! = ")

   add	 $a0, $s1, $zero
   li	 $v0, 1
   syscall					# printf(fac(n)

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
   # set up stack frame

## ... code for prologue goes here ...
   sw	 $fp, -4($sp)		# store previous frame pointer at the top of the new frame
   la	 $fp, -4($sp)		# set new frame pointer position
   sw	 $ra, -8($sp)		# store the return address in the stack
   sw	 $a0, -12($sp)		# store the argument of the function on the stack
   addi	 $sp, $sp, -16		# decrement the stack pointer

   # code for fac()

## ... code for fac() goes here ...
   lw	 $v0, -8($fp)		# load the argument into $v0
   bgt	 $v0, 1, recursive	# if n > 1 goto recursion section
   li	 $v0, 1				# set $v0 = 1 for return
   j	 end				# jump to the end section to return and remove the stack frame

recursive:
   lw	 $v1, -8($fp)		# load the argument to the function into $v1
   addi	 $v0, $v1, -1		# load the argument - 1 into $v0
   add	 $a0, $v0, $zero	# load "n - 1" into $a0
   jal	 fac				# call fac(n-1)
   lw	 $v1, -8($fp)		# load the argument of the previous function from the stack into $v1
   mul	 $v0, $v0, $v1		# n*(n-1) and store in $v0 to return

end:

   # clean up stack frame

## ... code for epilogue goes here ...
   lw	 $ra, -4($fp)		# restore the return address
   la	 $sp, 4($fp)		# reset the stack pointer to the previous frame
   lw	 $fp, ($fp)			# reset the frame pointer to the previous frame
   jr	 $ra				# return to called address
