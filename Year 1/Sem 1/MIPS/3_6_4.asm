.data
 x :.word 5
.text
main:
 lw $t1, x
 mulou $t2, $t1, $t1
 mulou $t2, $t2, 2
 mulo $t1, $t1, -4
 addi $t0, $t1, 12
 add $t0, $t2, $t0
 sw $t0, x+4
 li $v0, 10
 syscall