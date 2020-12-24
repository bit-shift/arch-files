# Keegan Gyoery z5197058
# 
# COMP1521 18s1 -- Assignment 1 -- Worm on a Plane!
#
# Base code by Jashank Jeremy and Wael Alghamdi
# Tweaked (severely) by John Shepherd
#
# Set your tabstop to 8 to make the formatting decent

# Requires:
#  - [no external symbols]

# Provides:
	.globl	wormCol
	.globl	wormRow
	.globl	grid
	.globl	randSeed

	.globl	main
	.globl	clearGrid
	.globl	drawGrid
	.globl	initWorm
	.globl	onGrid
	.globl	overlaps
	.globl	moveWorm
	.globl	addWormToGrid
	.globl	giveUp
	.globl	intValue
	.globl	delay
	.globl	seedRand
	.globl	randValue

	# Let me use $at, please.
	.set	noat

# The following notation is used to suggest places in
# the program, where you might like to add debugging code
#
# If you see e.g. putc('a'), replace by the three lines
# below, with each x replaced by 'a'
#
# print out a single character
# define putc(x)
# 	addi	$a0, $0, x
# 	addiu	$v0, $0, 11
# 	syscall
# 
# print out a word-sized int
# define putw(x)
# 	add 	$a0, $0, x
# 	addiu	$v0, $0, 1
# 	syscall

####################################
# .DATA
	.data

	.align 4
wormCol:	.space	40 * 4
	.align 4
wormRow:	.space	40 * 4
	.align 4
grid:		.space	20 * 40 * 1

randSeed:	.word	0

main__0:	.asciiz "Invalid Length (4..20)"
main__1:	.asciiz "Invalid # Moves (0..99)"
main__2:	.asciiz "Invalid Rand Seed (0..Big)"
main__3:	.asciiz "Iteration "
main__4:	.asciiz "Blocked!\n"

	# ANSI escape sequence for 'clear-screen'
main__clear:	.asciiz "\033[H\033[2J"
# main__clear:	.asciiz "__showpage__\n" # for debugging

giveUp__0:	.asciiz "Usage: "
giveUp__1:	.asciiz " Length #Moves Seed\n"


####################################
# .TEXT <main>
	.text
main:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4
# Uses: 	$a0, $a1, $v0, $s0, $s1, $s2, $s3, $s4
# Clobbers:	$a0, $a1

# Locals:
#	- `argc' in $s0
#	- `argv' in $s1
#	- `length' in $s2
#	- `ntimes' in $s3
#	- `i' in $s4

# Structure:
#	main
#	-> [prologue]
#	-> main_seed
#	  -> main_seed_t
#	  -> main_seed_end
#	-> main_seed_phi
#	-> main_i_init
#	-> main_i_cond
#	   -> main_i_step
#	-> main_i_end
#	-> [epilogue]
#	-> main_giveup_0
#	 | main_giveup_1
#	 | main_giveup_2
#	 | main_giveup_3
#	   -> main_giveup_common

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	sw	$s2, -20($sp)
	sw	$s3, -24($sp)
	sw	$s4, -28($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -28

	# save argc, argv
	add	$s0, $0, $a0
	add	$s1, $0, $a1

	# if (argc < 3) giveUp(argv[0],NULL);
	slti	$at, $s0, 4
	bne	$at, $0, main_giveup_0

	# length = intValue(argv[1]);
	addi	$a0, $s1, 4	# 1 * sizeof(word)
	lw	$a0, ($a0)	# (char *)$a0 = *(char **)$a0
	jal	intValue

	# if (length < 4 || length >= 40)
	#     giveUp(argv[0], "Invalid Length");
	# $at <- (length < 4) ? 1 : 0
	slti	$at, $v0, 4
	bne	$at, $0, main_giveup_1
	# $at <- (length < 40) ? 1 : 0
	slti	$at, $v0, 40
	beq	$at, $0, main_giveup_1
	# ... okay, save length
	add	$s2, $0, $v0

	# ntimes = intValue(argv[2]);
	addi	$a0, $s1, 8	# 2 * sizeof(word)
	lw	$a0, ($a0)
	jal	intValue

	# if (ntimes < 0 || ntimes >= 100)
	#     giveUp(argv[0], "Invalid # Iterations");
	# $at <- (ntimes < 0) ? 1 : 0
	slti	$at, $v0, 0
	bne	$at, $0, main_giveup_2
	# $at <- (ntimes < 100) ? 1 : 0
	slti	$at, $v0, 100
	beq	$at, $0, main_giveup_2
	# ... okay, save ntimes
	add	$s3, $0, $v0

main_seed:
	# seed = intValue(argv[3]);
	add	$a0, $s1, 12	# 3 * sizeof(word)
	lw	$a0, ($a0)
	jal	intValue

	# if (seed < 0) giveUp(argv[0], "Invalid Rand Seed");
	# $at <- (seed < 0) ? 1 : 0
	slt	$at, $v0, $0
	bne	$at, $0, main_giveup_3

main_seed_phi:
	add	$a0, $0, $v0
	jal	seedRand

	# start worm roughly in middle of grid

	# startCol: initial X-coord of head (X = column)
	# int startCol = 40/2 - length/2;
	addi	$s4, $0, 2
	addi	$a0, $0, 40
	div	$a0, $s4
	mflo	$a0
	# length/2
	div	$s2, $s4
	mflo	$s4
	# 40/2 - length/2
	sub	$a0, $a0, $s4

	# startRow: initial Y-coord of head (Y = row)
	# startRow = 20/2;
	addi	$s4, $0, 2
	addi	$a1, $0, 20
	div	$a1, $s4
	mflo	$a1

	# initWorm($a0=startCol, $a1=startRow, $a2=length)
	add	$a2, $0, $s2
	jal	initWorm

main_i_init:
	# int i = 0;
	add	$s4, $0, $0
main_i_cond:
	# i <= ntimes  ->  ntimes >= i  ->  !(ntimes < i)
	#   ->  $at <- (ntimes < i) ? 1 : 0
	slt	$at, $s3, $s4
	bne	$at, $0, main_i_end

	# clearGrid();
	jal	clearGrid

	# addWormToGrid($a0=length);
	add	$a0, $0, $s2
	jal	addWormToGrid

	# printf(CLEAR)
	la	$a0, main__clear
	addiu	$v0, $0, 4	# print_string
	syscall

	# printf("Iteration ")
	la	$a0, main__3
	addiu	$v0, $0, 4	# print_string
	syscall

	# printf("%d",i)
	add	$a0, $0, $s4
	addiu	$v0, $0, 1	# print_int
	syscall

	# putchar('\n')
	addi	$a0, $0, 0x0a
	addiu	$v0, $0, 11	# print_char
	syscall

	# drawGrid();
	jal	drawGrid

	# Debugging? print worm pos as (r1,c1) (r2,c2) ...

	# if (!moveWorm(length)) {...break}
	add	$a0, $0, $s2
	jal	moveWorm
	bne	$v0, $0, main_moveWorm_phi

	# printf("Blocked!\n")
	la	$a0, main__4
	addiu	$v0, $0, 4	# print_string
	syscall

	# break;
	j	main_i_end

main_moveWorm_phi:
	addi	$a0, $0, 1
	jal	delay

main_i_step:
	addi	$s4, $s4, 1
	j	main_i_cond
main_i_end:

	# exit (EXIT_SUCCESS)
	# ... let's return from main with `EXIT_SUCCESS' instead.
	addi	$v0, $0, 0	# EXIT_SUCCESS

main__post:
	# tear down stack frame
	lw	$s4, -24($fp)
	lw	$s3, -20($fp)
	lw	$s2, -16($fp)
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

main_giveup_0:
	add	$a1, $0, $0	# NULL
	j	main_giveup_common
main_giveup_1:
	la	$a1, main__0	# "Invalid Length"
	j	main_giveup_common
main_giveup_2:
	la	$a1, main__1	# "Invalid # Iterations"
	j	main_giveup_common
main_giveup_3:
	la	$a1, main__2	# "Invalid Rand Seed"
	# fall through
main_giveup_common:
	# giveUp ($a0=argv[0], $a1)
	lw	$a0, ($s1)	# argv[0]
	jal	giveUp	# never returns


####################################
# clearGrid() ... set all grid[][] elements to '.'
# .TEXT <clearGrid>
	.text
clearGrid:

# Frame:	$fp, $ra, $s0, $s1
# Uses: 	$s0, $s1, $t0, $t1, $t2
# Clobbers:	$t0, $t1, $t2

# Locals:
#	- `row' in $s0
#	- `col' in $s1
#	- 'size' in $t0
#	- `&grid[row][col]' in $t1
#	- '.' in $t2

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)					
	la	$fp, -4($sp)					
	addiu	$sp, $sp, -16					

	# code for function
	la	$t1, grid			# $t1 = &grid[0][0] 
	addi	$t2, $0, '.'			# $t2 = '.' 
	li	$s0, 20				# row = 20
	li	$s1, 40				# col = 40
	mul	$t0, $s0, $s1			# $t0 = row*col
	add	$t0, $t1, $t0			# $t0 = &grid[20][40]
forClear:
	bge	$t1, $t0, endforClear		# if(*grid[row][col] > &grid[20][40]) goto endforClear
	sb	$t2, ($t1)			# grid[row][col] = '.'
	addi	$t1, $t1, 1			# $t1 = &grid[row][col] + 1
	j	forClear
endforClear:

	# tear down stack frame
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# drawGrid() ... display current grid[][] matrix
# .TEXT <drawGrid>
	.text
drawGrid:

# Frame:	$fp, $ra, $s0, $s1
# Uses: 	$a0, $s0, $s1, $t1, $v0
#Clobbers:	$a0, $t1, $v0

# Locals:
#	- 'char' in $a0
#	- `row' in $s0
#	- `col' in $s1
#	- `&grid[row][col]' in $t1
#	- '11' in $v0

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -16
	
	# code for function
	la	$t1, grid			# $t1 = &grid[0][0] 
	li	$v0, 11				# $v0 =  11
	li	$s0, 0				# row = 0
forDrawR:					
	bge	$s0, 20, endforDrawR		# if(row >= 20) goto endforDrawR		
	li	$s1, 0				# col = 0
forDrawC:
	bge	$s1, 40, endforDrawC		# if(col >= 40) goto endforDrawC 
	lb	$a0, ($t1)			# $a0 = grid[row][col]
	syscall					# printf("%c", grid[row][col])
	addi	$t1, $t1, 1			# $t1 = &grid[row][col] + 1
	addi	$s1, $s1, 1			# col += 1
	j	forDrawC			
endforDrawC:
	addi	$a0, $0, '\n'			# $a0 = '\n' 
	syscall					# printf("\n")
	addi	$s0, $s0, 1			# row += 1
	j	forDrawR
endforDrawR:

	# tear down stack frame
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# initWorm(col,row,len) ... set the wormCol[] and wormRow[]
#    arrays for a worm with head at (row,col) and body segements
#    on the same row and heading to the right (higher col values)
# .TEXT <initWorm>
	.text
initWorm:

# Frame:	$fp, $ra
# Uses: 	$a0, $a1, $a2, $t0, $t1, $t2, $t3
# Clobbers:	$t0, $t1, $t2, $t3

# Locals:
#	- `col' in $a0
#	- `row' in $a1
#	- `len' in $a2
#	- `newCol' in $t0
#	- `nsegs' in $t1
#	- '&wormCol[nsegs]' in $t2
#	- '&wormRow[nsegs]' in $t3

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# code for function
	addi	$t0, $a0, 1			# newCol = col + 1
	li	$t1, 1				# nsegs = 1
	la	$t2, wormCol			# $t2 = &wormCol[0]
	la	$t3, wormRow			# $t3 = &wormRow[0]
	sw	$a0, ($t2)			# wormCol[0] = col
	sw	$a1, ($t3)			# wormRow[0] = row
forInit:
	bge	$t1, $a2, endforInit		# if(nsegs >= len) goto endforInit
	beq	$t0, 40, endforInit		# if(newCol == 40) goto endforInit
	addi	$t2, $t2, 4			# $t2 = &wormCol[nsegs] + 4
	addi	$t3, $t3, 4			# $t3 = &wormRow[nsegs] + 4
	sw	$t0, ($t2)			# wormCol[nsegs] = newCol
	sw	$a1, ($t3)			# wormRow[nsegs] = row
	addi	$t0, $t0, 1			# newCol += 1
	addi	$t1, $t1, 1			# nsegs += 1
	j	forInit
endforInit:

	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# ongrid(col,row) ... checks whether (row,col)
#    is a valid coordinate for the grid[][] matrix
# .TEXT <onGrid>
	.text
onGrid:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7, $t0, $t1, $t8
# Uses: 	$a0, $a1, $v0
# Clobbers:	$v0

# Locals:
#	- `col' in $a0
#	- `row' in $a1
#	- 'return' in $v0

# Code:

	# set up stack frame
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
	sw	$t0, -44($sp)
	sw	$t1, -48($sp)
	sw	$t8, -52($sp)
	addi	$sp, $sp, -52

	# code for function
	bltz	$a0, returnOnGrid		# if(col < 0) return 0
	bltz	$a1, returnOnGrid		# if(row < 0) return 0
	bge	$a0, 40, returnOnGrid		# if(col >= 40) return 0
	bge	$a1, 20, returnOnGrid		# if(row >= 20) return 0
	li	$v0, 1				# return 1
	j	returnF
returnOnGrid:
	li	$v0, 0				# return 0
returnF:

	# tear down stack frame
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
	lw	$t0, -40($fp)
	lw	$t1, -44($fp)
	lw	$t8, -48($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# overlaps(r,c,len) ... checks whether (r,c) holds a body segment
# .TEXT <overlaps>
	.text
overlaps:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7, $t0, $t1, $t8
# Uses: 	$a0, $a1, $a2, $t0, $t1, $t3, $t4, $t6, $v0
# Clobbers:	$t3, $t4, $t6, $v0

# Locals:
#	- `col' in $a0
#	- `row' in $a1
#	- `len' in $a2
#	- '&wormCol[i]' in $t0
#	- '&wormRow[i]' in $t1
#	- 'wormCol[i]' in $t3
#	- 'wormRow[i]' in $t4
#	- `i' in $t6
# 	- 'return' in $v0

# Code:

	# set up stack frame
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
	sw	$t0, -44($sp)
	sw	$t1, -48($sp)
	sw	$t8, -52($sp)
	addi	$sp, $sp, -52

	# code for function
	li	$t6, 0				# i = 0
	la	$t0, wormCol			# $t0 = &wormCol[0]
	la	$t1, wormRow			# $t1 = &wormRow[0]
	li	$v0, 0				# $v0 = 0
forOverlaps:					
	bge	$t6, $a2, endforOverlaps	# if(i >= len) goto endforOverlaps
	lw	$t3, ($t0)			# $t3 = wormCol[i]
	lw	$t4, ($t1)			# $t4 = wormRow[i]
	bne	$a0, $t3, endifOverlaps		# if(wormCol[i] != col) goto endifOverlaps
	bne	$a1, $t4, endifOverlaps		# if(wormRow[i] != row) goto endifOverlaps
	li	$v0, 1				# $v0 = 1
	j	endforOverlaps
endifOverlaps:
	addi	$t0, $t0, 4			# $t0 = &wormCol[i] + 4
	addi	$t1, $t1, 4			# $t1 = &wormRow[i] + 4
	addi	$t6, $t6, 1			# i += 1
	j	forOverlaps

endforOverlaps:

	# tear down stack frame
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
	lw	$t0, -40($fp)
	lw	$t1, -44($fp)
	lw	$t8, -48($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# moveWorm() ... work out new location for head
#         and then move body segments to follow
# updates wormRow[] and wormCol[] arrays

# (col,row) coords of possible places for segments
# done as global data; putting on stack is too messy
	.data
	.align 4
possibleCol: .space 8 * 4	# sizeof(word)
possibleRow: .space 8 * 4	# sizeof(word)

# .TEXT <moveWorm>
	.text
moveWorm:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7
# Uses: 	$s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7, $t0, $t1, $t2, $t3
# Clobbers:	$t0, $t1, $t2, $t3

# Locals:
#	- `col' in $s0
#	- `row' in $s1
#	- `len' in $s2
#	- `dx' in $s3
#	- `dy' in $s4
#	- `n' in $s7
#	- `i' in $t0
#	- tmp in $t1
#	- tmp in $t2
#	- tmp in $t3
# 	- `&possibleCol[0]' in $s5
#	- `&possibleRow[0]' in $s6

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	sw	$s2, -20($sp)
	sw	$s3, -24($sp)
	sw	$s4, -28($sp)
	sw	$s5, -32($sp)
	sw	$s6, -36($sp)
	sw	$s7, -40($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -40

	# code for function
	add	$s2, $a0, $0			# $s2 = len
	li	$s7, 0				# n = 0
	la	$s5, possibleCol		# $s5 = &possibleCol[0]
	la	$s6, possibleRow		# $s6 = &possibleRow[0]	
	li	$s3, -1				# dx = -1
	addi	$t0, $s2, -1			# i = len - 1 
fordx:
	bgt	$s3, 1 endfordx			# if(dx > 1) goto endfordx
	li	$s4, -1				# dy = -1
fordy:
	bgt	$s4, 1, endfordy		# if(dy > 1) goto endfordy
	lw	$s0, wormCol			# col = wormCol[0]
	lw	$s1, wormRow			# row = wormRow[0]
	add	$s0, $s0, $s3			# col = wormCol[0] + dx
	add	$s1, $s1, $s4			# row = wormRow[0] + dy
	add	$a0, $s0, $0			# $a0 = col
	add	$a1, $s1, $0			# $a1 = row
	add	$a2, $s2, $0			# $a2 = len
	jal	overlaps			# overlaps(col, row, len)
	add	$v1, $v0, $0			# $v1 = overlaps(col, row, len)
	jal	onGrid				# onGrid(col, row)
	bnez	$v1, endifMove			# if(overlaps(col, row, len) goto endifMove
	bne	$v0, 1, endifMove		# if(!onGrid(col, row)) goto endifMove
	sw	$s0, ($s5)			# possibleCol[n] = col
	sw	$s1, ($s6)			# possibleRow[n] = row
	addi	$s5, $s5, 4			# $s5 = &possibleCol[0] + 4
	addi	$s6, $s6, 4			# $s6 = &possibleRow[0] + 4
	addi	$s7, $s7, 1			# n += 1
endifMove:
	addi	$s4, $s4, 1			# dy += 1
	j	fordy			
endfordy:			
	add	$s3, $s3, 1			# dx += 1
	j	fordx
endfordx:
	beqz	$s7, return0Move		# if(n == 0) goto retrun0Move
	la	$s0, wormCol			# col = &wormCol[0]
	la	$s1, wormRow			# row = &wormRow[0]
	mul	$t1, $t0, 4			# $t1 = i*4 = offset
	add	$s0, $s0, $t1			# col = &wormCol[i]
	add	$s1, $s1, $t1			# row = &wormRow[i]
forMoveWorm:
	beqz	$t0, endforMoveWorm		# if(i == 0) goto endforMoveWorm
	lw	$t8, -4($s0)			# $t8 = wormCol[i-1] 
	sw	$t8, ($s0)			# wormCol[i] = wormCol[i-1]
	lw	$t8, -4($s1)			# $t8 = wormRow[i-1]
	sw	$t8, ($s1)			# wormCol[i] = wormRow[i-1]
	addi	$t0, $t0, -1			# i -= 1
	addi	$s0, $s0, -4			# $s0 = &wormCol[i]
	addi	$s1, $s1, -4			# $s1 = &wormRow[i]
	j	forMoveWorm
endforMoveWorm:
	add	$a0, $s7, $0			# $a0 = n
	jal	randValue			# randValue(n)
	add	$t0, $v0, $0			# i = randValue(n)
	mul	$t1, $t0, 4			# $t1 = i*4 = offset
	la	$s5, possibleCol		# $s5 = &possibleCol[0] 
	la	$s6, possibleRow		# $s6 = &possibleRow[0]
	add	$s5, $s5, $t1			# $s5 = &possibleCol[i]
	add	$s6, $s6, $t1			# $s6 = &possibleRow[i]
	lw	$t8, ($s5)			# $t8 = possibleCol[i]
	sw	$t8, wormCol			# wormCol[0] = possibleCol[i]
	lw	$t8, ($s6)			# $t8 = possibleRow[i]
	sw	$t8, wormRow			# wormRow[0] = possibleRow[i]
	li	$v0, 1				# return 1
	j	return1Move
return0Move:
	li	$v0, 0				# return 0
return1Move:

	# tear down stack frame
	lw	$s7, -36($fp)
	lw	$s6, -32($fp)
	lw	$s5, -28($fp)
	lw	$s4, -24($fp)
	lw	$s3, -20($fp)
	lw	$s2, -16($fp)
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# addWormTogrid(N) ... add N worm segments to grid[][] matrix
#    0'th segment is head, located at (wormRow[0],wormCol[0])
#    i'th segment located at (wormRow[i],wormCol[i]), for i > 0
# .TEXT <addWormToGrid>
	.text
addWormToGrid:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3
# Uses: 	$a0, $s0, $s1, $s2, $s3, $t0, $t2, $t3, $t4, $t5, $t6, $t7
# Clobbers:	$t0, $t2, $t3, $t4, $t5, $t6, $t7

# Locals:
#	- `len' in $a0
#	- `&wormCol[i]' in $s0
#	- `&wormRow[i]' in $s1
#	- 'col' in $s2
#	- 'row' in $s3
#	- `i' in $t0
#	- 'row offset' in $t2
#	- 'col and row offset' in $t3
#	- 'o' in $t4
#	- '@' in $t5
#	- '40' in $t6
#	- `grid[row][col]' in $t7

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$s0, -12($sp)
	sw	$s1, -16($sp)
	sw	$s2, -20($sp)
	sw	$s3, -24($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -24

	# code for function
	addi	$t5, $0, '@'			# $t5 = '@' -> head character
	addi	$t4, $0, 'o'			# $t4 = 'o' -> body character
	la	$s0, wormCol			# $s0 = &wormCol[0]
	la	$s1, wormRow			# $s1 = &wormRow[0]
	li	$t6, 40				# $t6 = 40 
	li	$t0, 0				# i = 0

forAddWorm:
	bge	$t0, $a0, endforAddWorm		# if(i >= len) goto endforAddWorm
	la	$t7, grid			# $t7 = &grid[0][0] 
	lw	$s2, ($s0)			# col = wormCol[i]
	lw	$s3, ($s1)			# row = wormRow[i]
	mul	$t2, $s3, $t6			# $t2 = row*40 = row offset
	add	$t3, $t2, $s2			# $t3 = row*40 + col = row and col offset
	add	$t7, $t7, $t3			# $t7 = &grid[row][col]
	bgt	$t0, 0, storeBody		# if(i > 0) goto storeBody
	sb	$t5, ($t7)			# grid[row][col] = '@'
	j	continueAddWorm			# Don't store body if stored head 
storeBody:
	sb	$t4, ($t7)			# grid[row][col] = 'o'
continueAddWorm:
	addi	$s0, $s0, 4			# $s0 = &wormCol[i] + 4
	addi	$s1, $s1, 4			# $s1 = &wormRow[i] + 4
	addi	$t0, $t0, 1			# i += 1
	j	forAddWorm
	
endforAddWorm:

	# tear down stack frame
	lw	$s3, -20($fp)
	lw	$s2, -16($fp)
	lw	$s1, -12($fp)
	lw	$s0, -8($fp)
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# giveUp(msg) ... print error message and exit
# .TEXT <giveUp>
	.text
giveUp:

# Frame:	frameless; divergent
# Uses: 	$a0, $a1
# Clobbers:	$s0, $s1

# Locals:
#	- `progName' in $a0/$s0
#	- `errmsg' in $a1/$s1

# Code:
	add	$s0, $0, $a0
	add	$s1, $0, $a1

	# if (errmsg != NULL) printf("%s\n",errmsg);
	beq	$s1, $0, giveUp_usage

	# puts $a0
	add	$a0, $0, $s1
	addiu	$v0, $0, 4	# print_string
	syscall

	# putchar '\n'
	add	$a0, $0, 0x0a
	addiu	$v0, $0, 11	# print_char
	syscall

giveUp_usage:
	# printf("Usage: %s #Segments #Moves Seed\n", progName);
	la	$a0, giveUp__0
	addiu	$v0, $0, 4	# print_string
	syscall

	add	$a0, $0, $s0
	addiu	$v0, $0, 4	# print_string
	syscall

	la	$a0, giveUp__1
	addiu	$v0, $0, 4	# print_string
	syscall

	# exit(EXIT_FAILURE);
	addi	$a0, $0, 1 # EXIT_FAILURE
	addiu	$v0, $0, 17	# exit2
	syscall
	# doesn't return


####################################
# intValue(str) ... convert string of digits to int value
# .TEXT <intValue>
	.text
intValue:

# Frame:	$fp, $ra
# Uses: 	$t0, $t1, $t2, $t3, $t4, $t5
# Clobbers:	$t0, $t1, $t2, $t3, $t4, $t5

# Locals:
#	- `s' in $t0
#	- `*s' in $t1
#	- `val' in $v0
#	- various temporaries in $t2

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# int val = 0;
	add	$v0, $0, $0

	# register various useful values
	addi	$t2, $0, 0x20 # ' '
	addi	$t3, $0, 0x30 # '0'
	addi	$t4, $0, 0x39 # '9'
	addi	$t5, $0, 10

	# for (char *s = str; *s != '\0'; s++) {
intValue_s_init:
	# char *s = str;
	add	$t0, $0, $a0
intValue_s_cond:
	# *s != '\0'
	lb	$t1, ($t0)
	beq	$t1, $0, intValue_s_end

	# if (*s == ' ') continue; # ignore spaces
	beq	$t1, $t2, intValue_s_step

	# if (*s < '0' || *s > '9') return -1;
	blt	$t1, $t3, intValue_isndigit
	bgt	$t1, $t4, intValue_isndigit

	# val = val * 10
	mult	$v0, $t5
	mflo	$v0

	# val = val + (*s - '0');
	sub	$t1, $t1, $t3
	add	$v0, $v0, $t1

intValue_s_step:
	# s = s + 1
	addi	$t0, $t0, 1	# sizeof(byte)
	j	intValue_s_cond
intValue_s_end:

intValue__post:
	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra

intValue_isndigit:
	# return -1
	addi	$v0, $0, -1
	j	intValue__post


####################################
# delay(N) ... waste some time; larger N wastes more time
#                            makes the animation believable
# .TEXT <delay>
	.text
delay:

# Frame:	$fp, $ra
# Uses: 	$a0, $t0, $t1, $t2
# Clobbers:	$t0, $t1, $t2

# Locals:
#	- `n' in $a0
#	- `i' in $t0
#	- `j' in $t1
#	- 'k' in $t2

# Code:
	# set up stack frame
	sw	$fp, -4($sp)				
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# code for function
	li	$t0, 0				# i = 0
for1:
	bge	$t0, $a0, endfor1		# if(i >= n) goto endfor1
	li	$t1, 0				# j = 0
for2:
	bge	$t1, 20000, endfor2		# if(j >= 20000) goto endfor2
	li	$t2, 0				# k = 0
	addi	$t2, $t2, 1			# k += 1
	addi	$t1, $t1, 1			# j += 1
	j	for2
endfor2:
	addi	$t0, $t0, 1			# i += 1
	j	for1
endfor1:
	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# seedRand(Seed) ... seed the random number generator
# .TEXT <seedRand>
	.text
seedRand:

# Frame:	$fp, $ra
# Uses: 	$a0
# Clobbers:	[none]

# Locals:
#	- `seed' in $a0

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -8

	# randSeed <- $a0
	sw	$a0, randSeed

seedRand__post:
	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$fp, ($fp)
	jr	$ra


####################################
# randValue(n) ... generate random value in range 0..n-1
# .TEXT <randValue>
	.text
randValue:

# Frame:	$fp, $ra
# Uses: 	$a0
# Clobbers:	$t0, $t1

# Locals:	[none]
#	- `n' in $a0

# Structure:
#	rand
#	-> [prologue]
#       no intermediate control structures
#	-> [epilogue]

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	sw	$ra, -8($sp)
	sw	$t8, -12($sp)
	la	$fp, -4($sp)
	addiu	$sp, $sp, -12

	# $t0 <- randSeed
	lw	$t0, randSeed
	# $t1 <- 1103515245 (magic)
	li	$t1, 0x41c64e6d

	# $t0 <- randSeed * 1103515245
	mult	$t0, $t1
	mflo	$t0

	# $t0 <- $t0 + 12345 (more magic)
	addi	$t0, $t0, 0x3039

	# $t0 <- $t0 & RAND_MAX
	and	$t0, $t0, 0x7fffffff

	# randSeed <- $t0
	sw	$t0, randSeed

	# return (randSeed % n)
	div	$t0, $a0
	mfhi	$v0

rand__post:
	# tear down stack frame
	lw	$ra, -4($fp)
	la	$sp, 4($fp)
	lw	$t8, -8($fp)
	lw	$fp, ($fp)
	jr	$ra
