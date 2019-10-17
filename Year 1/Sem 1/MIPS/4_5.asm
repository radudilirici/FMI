.data
 string1 :.asciiz "Nr de elemente:\n"
 string2 :.asciiz "Elementele:\n"
 meniu :.asciiz "\n1. Suma elementelor\n2. Ultimul element\n3. Elementele mai mari decat n\n4. Iesire din program\n"
 suma :.asciiz "\nSuma:\n"
 ultimul :.asciiz "\nUltimul element:\n"
 mari :.asciiz "\nElemente mai mari decat n:\n"
 enter :.asciiz "\n"
 n :.word 0
 elem :.space 64
 
.text
main:

 li $v0, 4
 la $a0, string1
 syscall
 
 li $v0, 5
 syscall
 sw $v0, n
 
 lw $t1, n
 la $t2, elem
 
 li $v0, 4
 la $a0, string2
 syscall
 
 for: beq $t0, $t1, iesire_for
  li $v0, 5
  syscall
  sw $v0, ($t2)
  addi $t2, $t2, 4
  addi $t0, $t0, 1
  b for
 
 iesire_for:
 li $t0, 0
 li $t1, 0
 li $t2, 0
 
 switch:
  li $v0, 4
  la $a0, meniu
  syscall
  
  li $v0, 5
  syscall
  move $t0, $v0 #in t0 retinem optiunea
  
  beq $t0, 1, unu
  beq $t0, 2, doi
  beq $t0, 3, trei
  beq $t0, 4, exit
  b switch #default
  
  unu:
   li $t0, 0
   lw $t1, n
   la $t2, elem
   li $t3, 0 #suma
   for_unu: bge $t0, $t1, iesire_unu
    lw $t4, ($t2)
    add $t3, $t3, $t4
    addi $t2, $t2, 4
    addi $t0, $t0, 1
    b for_unu
    
  iesire_unu:
   li $v0, 4
   la $a0, suma
   syscall
   li $v0, 1
   move $a0, $t3
   syscall
   li $v0, 4
   la $a0, enter
   syscall
   b switch
    
   doi:
    li $t0, 1
    lw $t1, n
    la $t2, elem
    for_doi: bge $t0, $t1, iesire_doi
     addi $t0, $t0, 1
     addi $t2, $t2, 4
     b for_doi
     
   iesire_doi:
    li $v0, 4
    la $a0, ultimul
    syscall
    li $v0, 1
    lw $a0, ($t2)
    syscall
    li $v0, 4
    la $a0, enter
    syscall
    b switch
    
   trei:
    li $t0, 0
    lw $t1, n
    la $t2, elem
    li $v0, 4
    la $a0, mari
    syscall
    for_trei: bge $t0, $t1, iesire_trei
     lw $t3, ($t2)
     ble $t3, $t1, urm
      li $v0, 1
      move $a0, $t3
      syscall
      li $v0, 11
      li $a0, 32 #afisam un space
      syscall
     urm:
     addi $t0, $t0, 1
     addi $t2, $t2, 4
     b for_trei
     
    iesire_trei:
     li $v0, 4
     la $a0, enter
     syscall
     b switch
  
 exit:
 li $v0, 10
 syscall