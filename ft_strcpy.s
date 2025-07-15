global ft_strcpy

section .text

ft_strcpy:
    mov rax, rdi

.copy:
    mov dl, byte [rsi]
    mov byte [rdi], dl
    inc rsi
    inc rdi
    test dl, dl
    jne .copy
    ret