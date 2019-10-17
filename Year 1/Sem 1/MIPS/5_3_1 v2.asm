.data
	a1 :.word 1
	a2 :.word 2
.text
main:
	lw $s1, a1
	lw $s2, a2
	li, $s0, 0 # i
	
	for: beq $s0, 5, iesire_for
		move $a0, $s1
		move $a1, $s2
		jal an
		move $s1, $s2
		move $s2, $v0
		addi $s0, $s0, 1
		j for
	iesire_for:
		j exit
	
	an:
		move $t0, $a0
		move $t1, $a1
		mulou $t3, $t0, 3
		add $t3, $t3, $t1
		move $v0, $t3
		jr $ra
	
	exit:
	move $a0, $s2
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall