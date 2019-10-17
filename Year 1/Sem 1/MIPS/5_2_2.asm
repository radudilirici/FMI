.data
 s :.asciiz "sirris"
 
.text
main:
 la $t0, s

for:
 lb $t1, ($t0)
 beqz $t1, end_for
 sb $t1, ($sp)
 subi $sp, $sp, 1
 addi $t0, $t0, 1
 b for
end_for:

la $t0, s
addi $sp, $sp, 1

verif: #vom retine in $t3 daca e sau nu palindrom
 lb $t1, ($t0)
 lb $t2, ($sp)
 beqz $t1, este
 bne $t1, $t2, nu_e
 addi $sp, $sp, 1
 addi $t0, $t0, 1
 b verif
 
este:
 li $t3, 1
 b exit

nu_e:
 li $t3, 0
 b exit

exit:
 li $v0, 10
 syscall