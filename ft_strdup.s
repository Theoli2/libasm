global ft_strdup
extern ft_strlen
extern ft_strcpy
extern malloc

section .text

ft_strdup:
    push rdi

    call ft_strlen
    add rax, 1
    mov rdi, rax

    call malloc wrt ..plt
    test rax, rax
    je .return_null

    mov rdi, rax
    pop rsi
    call ft_strcpy

    ret

.return_null:
    pop rsi
    xor rax, rax
    ret
