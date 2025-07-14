li	$t0,5
addi	$t0,$t0,-2

li	$s0,1
li	$s1,1

Loop:
	beq	$t0,$zero,Exit
	add	$s2,$s0,$s1
	move	$s0,$s1
	move	$s1,$s2
	addi	$t0, $t0, -1
	j  Loop
Exit:
	
