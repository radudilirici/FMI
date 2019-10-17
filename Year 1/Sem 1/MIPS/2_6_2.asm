.data

.text
main:
 li $t0, 0x12345678
 ror $t1, $t0, 5
 li $v0, 10
 syscall