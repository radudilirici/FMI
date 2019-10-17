.data
 v :.word 4, -7, 3, 7, 9, -3, 0, 10, -100
 n :.word 9
.text
main:
 lw $t2, n
 li $t1, 4
 mulou $t2, $t1, $t2
 li $t1, 0
for:
 bge $t1, $t2, iesire #if i>=n exit
 lw $t3, v($t1)
 bgtz $t3, adauga
 b urm
 adauga:
  add $t0, $t0, $t3 #t0 == suma
 urm:
  addi $t1, $t1, 4
 j for
iesire:
 li $v0, 10
 syscall