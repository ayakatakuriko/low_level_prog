section .text

exit:
    mov rax, 60
    xor rdi, rdi
    syscall

string_length:
    ;引数をrdiから受け取る
    xor rax, rax
.loop:
    cmp byte [rdi+rax], 0
    je .end
    inc rax
    jmp .loop
.end:
    ret

print_string:
    ;引数をrdiから受け取る
    xor rax, rax
    call string_length ;raxに文字列の長さが入る
    mov rdx, rax ;文字列のバイト数
    inc rdx
    mov rsi, rdi;文字列のアドレス
    mov rdi, 1;stdoutのディスクリプタ
    mov rax, 1; 'writeのsyscall'
    syscall
    ret


print_char:
    ;引数をrdiから受け取る
    push rdi ;rdi内には文字コードが入っている。writeでほしいのはアドレスなので、スタックに積むことでアドレスを得る。
    mov rdi, rsp; 書き込むデータの場所
    call string_length
    pop rdi
    ret

print_newline:
    mov rdi, 10
    jmp print_char


print_uint:
    mov r9 10
    xor r10, r10
.loop:
    xor rax, rax
    mov rdx, rdi ;divはrax:rdxをOPで割る
    div r9
    mov rdi, rax ;rdiに商を格納
    add rdx, 0x30 ;文字コードに変換しておく
    push rdx; あまりをpush
    inc r10
    cmp rax, 0
    je .end1
    jmp .loop
.end1:
    pop rdi
    dec r10
    call print_char
    cmp r10, 0
    ja .end1
    ret


print_int:
    xor rax, rax
    cmp rdi 0
    jge .print ;rdiが正の数だった
    neg rdi ;rdiの符号を反転
    push rdi
    mov rdi 45 ;-をプリント
    call print_char
    pop rdi
.print:
    jmp print_uint

string_equals:
    xor rax, rax
    ret


read_char:
    mov rdi, 0
    mov rdx, 1
    syscall
    com rax, -1
    je .zero
    mv rdi, rsi
    call print_char
    jmp .end
.zero:
    mv rdi, 0
    call print_uint
.end:
    ret

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret


string_copy:
    ret
