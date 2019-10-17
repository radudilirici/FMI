.data
 a1: .word 1
 a2: .word 2
.text
j main

a_n:
 move $t0, $a0
 move $t1, $a1
 mulou $t0, $t0, 3
 add $t0, $t0, $t1
 move $v0, $t0
 jr $ra

main:
 lw $s1, a1
 lw $s2, a2
 li $s0, 0
 
for: beq $s0, 5, iesire_for
 move $a0, $s1
 move $a1, $s2
 jal a_n
 move $s1, $s2
 move $s2, $v0
 addi $s0, $s0, 1
 j for
 
iesire_for:
 li $v0, 10
 syscall