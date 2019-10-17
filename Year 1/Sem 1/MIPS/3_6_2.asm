.data
 var1 :.word 16
 var2 :.word 31
 var3 :.word 0
.text
 lw $t1, var1
 lw $t2, var2
 li $t3, 16
 div $t2, $t3
 mflo $t2
 mulou $t1, $t1, 8
 sub $t3, $t1, $t2
 sw $t3, var3
 li $v0, 10
 syscall