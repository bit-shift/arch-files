        la      $s0, wormCol
         lw      $t0, ($s0)
         la      $s1, wormRow
         lw      $t1, ($s1)
         add     $s2, $a2, $0
         li      $t7, 0
 
 for:
         bge     $t7, 10, endfor
         li      $v0, 1
         add     $a0, $t0, $0
         syscall
         li      $v0, 11
         addi    $a0, $0, ' ' 
         syscall
         li      $v0, 1
         add     $a0, $t1, $0
         syscall
         li      $v0, 11
         addi    $a0, $0, ' ' 
         syscall
         add     $a0, $t0, $0
         add     $a1, $t1, $0
         add     $a2, $s2, $0
         jal     onGrid
         add     $a0, $v0, $0
         li      $v0, 1
         syscall
         li      $v0, 11
         addi    $a0, $0, ' ' 
         syscall
         addi    $s0, $s0, 4
         addi    $s1, $s1, 4
         lw      $t0, ($s0)
         lw      $t1, ($s1)
         addi    $t7, $t7, 1
         j       for 
 endfor:
         li      $v0, 1


		 add     $a0, $v0, $0
         li      $v0, 1
         syscall
         li      $v0, 11
         addi    $a0, $0, ' '
         syscall

