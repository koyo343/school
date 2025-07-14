.data
size:	.word 9
input:	.float 0.0, 1.2, 2.5, 1.1, 2.1, 3.1, 2.1, 3.1, 0.0
filter:	.float 0.0, 1.0, 2.0, 1.0, 2.0, 0.0, 2.0, 0.0, 1.0
output:	.float 0.0	# initialize to zero.

msg:	.asciiz	"output: "

.text
main:
la	$t0, input
lwc1	$f1, 0($t0)		# inpuit data
la	$t1, filter
lwc1	$f2, 0($t1)		# filter
la	$t3, size
lw	$s0, 0($t3)		# set size
l.s	$f4, output		# initialize $f4
li	$s1, 0			# initialize loop-counter

Loop:
  beq $s1, $s0, Exit # if (loop-counter == size) then exit
  mul.s $f3, $f1, $f2
  add.s $f4, $f3, $f4
  addi $t0, $t0, 4
  lwc1 $f1, 0($t0)
  addi $t1, $t1, 4
  lwc1 $f2, 0($t1)
  addi $s1, $s1, 1
  j    Loop
  
Exit:
la	$t4, output
swc1	$f4, 0($t4)	# save the result

la	$a0, msg	# address of ASCII string
li	$v0, 4		# print string
syscall

mov.s	$f12, $f4	# argument
li	$v0, 2		# print float
syscall

li	$v0, 10		# exit to OS
syscall			# end of main




