.intel_syntax noprefix

.global my_write
.global my_exit

my_write:
    ret

my_exit:
    mov rax, 60
    // rdi exit code
    syscall
