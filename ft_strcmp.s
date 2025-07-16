global ft_strcmp

section .text

ft_strcmp:
    xor rax, rax
    xor rcx, rcx

.loop:
    mov al, [rdi + rcx]
    mov bl, [rsi + rcx]
    cmp al, bl
    jne .diff
    test al, al
    je .equal
    inc rcx
    jmp .loop

.diff:
    movzx eax, al
    movzx ebx, bl
    sub eax, ebx
    ret

.equal:
    xor eax, eax
    ret
