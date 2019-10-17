.data
 sir :.asciiz "aaabbcdddee"
.text
j main

verif:
 seq $a0, $a1, $v0
 jr $ra
 
maxim:
 addi $s3, $s3, 1
 j continua
 
creste:
 addi $s3, $s3, 1
 sub $t0, $s4, $s3
 bltz $t0, maxim
continua:
 jr $ra

unu:
 li $s3, 1
 jr $ra

main:
 la $s0, sir
 lb $s1, ($s0)
 addi $s0, $s0, 1
 lb $s2, ($s0)
 li $s3, 1
 li $s4, 1
 
for: beqz $s2, iesire_for
 move $a0, $s1
 move $a1, $s2
 jal verif
 subi $v0, $v0, 1
 bgezal $v0, creste
 bltzal $v0, unu
 move $s1, $s2
 addi $s0, $s0, 1
 lb $s2, ($s0)
 j for
 
iesire_for:
 
li $v0, 10
syscall