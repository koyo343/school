.data
const0: .byte -2

.text
li	$s0, 7
li	$s1, 9
li	$s2, -9

sub	$t0, $s0, $s1
add	$t1, $s0, $s2

slt	$t2, $s0, $s2
sltu	$t3, $s0, $s2

la	$t8, const0
lb	$t4, 0($t8)
lbu	$t5, 0($t8)

li	$v0, 10		# exit to OS
syscall			# end of main


