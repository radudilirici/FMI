.data
	s :.asciiz "aaabbcdddee"
.text
main:
	la $s0, s
	li $s1, 0
	lb $a0, ($s0)
	while: beqz $a0 exit
		move $a1, $s0
		jal nr_aparitii
		blt $v0, $s1, continue
			move $s1, $v0
		continue:
		lb $a0, ($s0)
		addi $s0, $s0, 1
		j while
		
	
	nr_aparitii:
		li $v0, 0
		lb $t1, ($a1)
		while_eq: bne $a0, $t1, end_while_eq
			addi $v0, $v0, 1
			addi $a1, $a1, 1
			lb $t1, ($a1)
		end_while_eq:
			jr $ra
		
	exit:
		li $v0, 10
		syscall