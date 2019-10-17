.data
 x:.word 10
 y:.word 11
 z:.word 12
.text
main:
 la $t0, x
 lw $t1, 4($t0)
 li $t2, 14
 la $t1, 8($t0)
 sh $t2, x+8
 li $v0, 10
 syscall