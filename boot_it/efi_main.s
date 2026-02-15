BITS 64
DEFAULT REL

%define EFI_SUCCESS 0

; Offsets based on UEFI spec
%define EFI_SYSTEM_TABLE_ConOut 64
%define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_OutputString 8

SECTION .text
GLOBAL efi_main

efi_main:
    ; RCX = ImageHandle
    ; RDX = EFI_SYSTEM_TABLE*

    push rbp
    mov rbp, rsp
    sub rsp, 32                ; shadow space (MS ABI)

    ; Load ConOut from SystemTable
    mov rax, [rdx + EFI_SYSTEM_TABLE_ConOut]

    ; Call ConOut->OutputString(ConOut, L"Hello UEFI\r\n")
    lea rdx, [rel hello_str]   ; CHAR16*
    mov rcx, rax               ; This pointer
    mov rax, [rax + EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_OutputString]
    call rax

    ; return EFI_SUCCESS
    xor eax, eax

    leave
    ret

SECTION .data
hello_str:
    dw 'H','e','l','l','o',' ','U','E','F','I',13,10,0
