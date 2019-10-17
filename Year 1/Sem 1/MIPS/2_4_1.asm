.data
 x:.word 11
 y:.word 3
.text
main:
 lw $t1, x
 lw $t2, y
 div $t0, $t1, $t2
 rem $t1, $t2, $t1
 mulou $t3, $t0, $t1
 li $v0, 10
 syscall