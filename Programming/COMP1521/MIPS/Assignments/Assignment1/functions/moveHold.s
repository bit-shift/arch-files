### TODO: Your code goes here
         li      $s7, 0                          # n  
         add     $s2, $a0, $0                    # s2 = len
         la      $s0, wormCol                    # t0 = wormCol[0]
         la      $s1, wormRow                    # t1 = wormRow[0]
         la      $s5, possibleCol                # t2 = col, t3 = row
         la      $s6, possibleRow                #    
         li      $s3, -1                         # dx 
         li      $s4, -1                         # dy 
         lw      $t0, ($s0)                      #    
         lw      $t1, ($s1)
 
 fordx:
         bgt     $s3, 1, endfordx
         li      $s4, -1
 fordy:
         bgt     $s4, 1, endfordy
         add     $t2, $t0, $s3
         add     $t3, $t1, $s4
         li      $a0, 10                         # col in a0
         li      $a1, 20                         # row in a1
         #add    $a2, $s2, $0                    # len in a2
         #jal    overlaps
         #add    $v1, $v0, $0                    # result of overlaps in v1, 1 if overlap, 0 if all good
         jal     onGrid                          # result of onGrid is in v0, 1 if all good
         #bnez   $v1, endifMove                  # overlap not 0, escape
         bne     $v0, 1, endifMove               # onGrid not 1, escape
         lw      $t2, ($s5)
         lw      $t3, ($s6)
         addi    $s7, $s7, 1
         addi    $s5, $s5, 4
         addi    $s6, $s6, 4
 endifMove:
         addi    $s4, $s4, 1
         j       fordy
 endfordy:
         addi    $s3, $s3, 1
         j       fordx
 endfordx:
         beqz    $s7, return0Move
         add     $a0, $s7, $0
         li      $v0, 1
         syscall
         addi    $t7, $0, 4                      # store 4 in a register
         mul     $t5, $s2, $t7                   # store 4*len in t5
         addi    $t5, $t5, -4                    # set t5 = (len-1)*4
         add     $s0, $s0, $t5                   # set wormCol pointer to end
         add     $s1, $s1, $t5                   # set wormRow pointer to end
         add     $t6, $s2, $0                    # t6 = i = len
         addi    $t6, $t6, -1                    # i = len - 1
 forMoveWorm:
         bgez    $t6, endforMoveWorm
		 lw      $t8, -4($s0)                    # get wormCol[i-1]
         sw      $t8, ($s0)                      # put wormCol[i-1] into wormCol[i]
         lw      $t9, -4($s1)                    # get wormRow[i-1]
         sw      $t9, ($s1)                      # put wormRow[i-1] into wormRow[i]
         addi    $t6, $t6, -1                    # i--
         addi    $s0, $s0, -4                    # move pointer to wormCol back 4 bytes
         addi    $s1, $s1, -4                    # move pointer to wormRow back 4 bytes
         j       forMoveWorm
 endforMoveWorm:
         add     $a0, $s7, $0
         jal     randValue
         add     $t6, $v0, $0
         mul     $t6, $t6, $t7
         la      $s5, possibleCol                # t2 = col, t3 = row
         la      $s6, possibleRow                #
         add     $s5, $s5, $t6
         add     $s6, $s5, $t6
         la      $s0, wormCol
         la      $s1, wormRow
         lw      $t8, ($s5)
         sw      $t8, ($s0)
         lw      $t9, ($s6)
         sw      $t9, ($s1)
         li      $v0, 1
         j       returnMove
 return0Move:
         li      $v0, 0
 returnMove:

