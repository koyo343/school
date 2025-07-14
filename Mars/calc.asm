addi	$s1,$zero,11
addi	$s2,$zero,7
addi	$s3,$zero,8
add	$t1,$s1,$s2

sub	$t1,$s1,$s2
addi	$t1,$t1,1

add	$t1,$s1,$s3
add	$t2,$s1,$s2
sub	$t1,$t1,$t2
addi	$t1,$t1,5

and	$t1,$s1,$s2
or	$t1,$t1,$s3
sll	$t1,$t1,2