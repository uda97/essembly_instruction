add     $t0, $s1, $s2
add     $t1, $s3, $s4
sub	    $s0, $t0, $t1
addi	$s2, $s1, 2
add     $s1, $s2, $t0
addi	$s2, $s1, -2
addi	$s2, $s1, -4
lw		$t0, 32($s3)
addi    $s3, $s3, 1
sw		$t0, 48($s3)


