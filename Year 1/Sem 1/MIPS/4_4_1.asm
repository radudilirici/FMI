.data
 sir :.asciiz "Sir de lungime 19.."
 x :.word 7
.text
main:
 #t0 = lungimea
 #t1 = i
 lw $t2, sir
if: #if t2 != NULL
 beqz $t2, iesire
 while: #while t2 != NULL
  srl $t2, $t2, 8 #fiecare caracter ocupa 2 spatii in hexa
  addi $t0, $t0, 1
  beqz $t2, urm
  b while
  urm: #trecem la urmatoarea memorie
   li $t3, 4
   div $t0, $t3
   mfhi $t3
   bgtz $t3, iesire #trebuie sa shiftam de exact 4 ori pana sa trecem la urmatoarea memorie
   
   addi $t1, $t1, 4
   lw $t2, sir($t1)
   b if
  
iesire:
 li $v0, 10
 syscall