global ft_strcmp

section .text

ft_strcmp:
    xor rax, rax
    xor rcx, rcx

.loop:
    mov al, [rdi + rcx]
    mov dl, [rsi + rcx]         ; rdx is caller-saved, unlike rbx
    cmp al, dl
    jne .diff
    test al, al
    je .equal
    inc rcx
    jmp .loop

.diff:
    movzx eax, al
    movzx edx, dl
    sub eax, edx
    ret

.equal:
    xor eax, eax
    ret
