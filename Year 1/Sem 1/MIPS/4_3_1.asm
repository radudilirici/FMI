.data

.text
main:
 beq $t1, 7, sapte
 beq $t2, 7, sapte
 beq $t3, 7, sapte
 beq $t4, 7, sapte
 beq $t5, 7, sapte
 li $t0, 0
 b iesire

sapte:
 li $t0, 1
 b iesire
iesire:
 li $v0, 10
 syscall