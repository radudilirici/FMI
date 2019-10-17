.data
	s :.asciiz "sir123"
	
.text
main:
	la $t0, s
	
	for:
		lb $t1, ($t0)
		beqz $t1, end_for
		sb $t1, ($sp)
		subi $sp, $sp, 1
		addi $t0, $t0, 1
		j for
	end_for:
		addi $sp, $sp, 1
	
	while:
		lb $t1, ($sp)
		beqz $t1, end_while
		move $a0, $t1
		li $v0, 11
		syscall
		addi $sp, $sp, 1
		j while
	end_while:
	
	li $v0, 10
	syscall