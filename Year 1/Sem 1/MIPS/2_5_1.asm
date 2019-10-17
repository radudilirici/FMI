.data
 x:.word 1
 y:.word 0
 z:.word 1
 w:.word 1
 
.text
main:
 lw $t1, x
 lw $t2, y
 lw $t3, z
 lw $t4, w
 or $t1, $t1, $t2
 xori $t3, $t3, 1
 and $t1, $t1, $t3
 xor $t5, $t1, $t4
 li $v0, 10
 syscall