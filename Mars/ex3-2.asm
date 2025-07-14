.data

# Enter any floating point number you like.
input:	.float 10.0	# fahrenheit temperature

const0:	.word 32
const1:	.float 0.5555555	#5.0 / 9.0

.text
l.s	$f2, input	#f2 = 10.0

# celsius = (fahrenheit - 32.0) * 5.0 / 9.0
l.s	$f4, const0	#f4 = 32
cvt.s.w	$f4, $f4	# convert integer to single precision
l.s	$f6, const1	# $f6 = 5.0 / 9.0
sub.s	$f0, $f2, $f4	# $f0 = (fahrenheit - 32.0)
mul.s	$f0, $f0, $f6	# $f0 = (fahrenheit - 32.0) * 5.0 / 9.0

li	$v0, 10		# exit to OS
syscall			# end of main


