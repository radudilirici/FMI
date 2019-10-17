.data
 x:.word 17
 y:.word 26
.text
main:
 lw $t1, x
 lw $t2, y
 sub $t3, $t1, $t2
 blt $t3, 0, minus
 j iesire
minus:
 mulo $t3, $t3, -1
iesire:
 li $v0, 10
 syscall