data
  array: .word 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
  
.globl main

.text
main:
  la	$a0, array	# load array's address to $a0
  li	$a1, 3		# set k=3 to $a1
  jal	swap		# call swap
  li	$a1, 4		# set k=4 to $a1
  jal	swap		# call swap
  li	$v0, 10		# exit to OS
  syscall		# end of main
  
swap:
  addi	$sp, $sp, -12	# allocate 3 words' space on stack
  sw	$s2, 8($sp)	# save $s2 to ($sp+8)
  sw	$s1, 4($sp)	# save $s1 to ($sp+4)
  sw	$s0, 0($sp)	# save $s0 to ($sp)
    
  sll	$s2, $a1, 2	# calc. k's offset(left shift 2 times = x4)
  add	$s2, $a0, $s2 	# calc. k's address
  lw	$s0, 0($s2)	# save k's valute to $s0
  lw	$s1, 4($s2)	# save (k+1)'s valute to $s1
  sw	$s1, 0($s2)	# save $s1 to k's address
  sw	$s0, 4($s2)	# save $s0 to (k+1)'s address
    
  lw	$s0, 0($sp)	# restore $s0 from ($sp)
  lw	$s1, 4($sp)	# restore $s1 from ($sp+4)
  lw	$s2, 8($sp)	# restore $s2 from ($sp+8)
  addi	$sp, $sp, 12	# release 3 words' space on stack

  jr    $ra		# return to main
