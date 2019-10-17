.data

.text
main:
 li $t0, 0x1234
 sll $t2, $t0, 3
 li $v0, 10
 syscall