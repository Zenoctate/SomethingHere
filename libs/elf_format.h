#ifndef ELF_FORMAT
#define ELF_FORMAT

#include "defs.h"

struct __attribute__((packed)) ELF64_HEADER {
    byte        magicNUM[4];    // = {0x7f, 0x45, 0x4c, 0x46}
    byte        arch_bit;       // = 2 (64-bit)
    byte        endian;         // = 1 (little endian)
    byte        elf_version;    // = 1
    byte        ABI;            // Default Linux 0x03
    byte        ABI_version;    // = 0
    byte        unused[7];      // = {0}
    word        e_type;
    word        e_machine;      // 0x32 (IA-64); 0x3E (AMD x86_64)
    Dword       e_version;      // = 1
    Qword       e_entry;
    Qword       e_phoff;        // Typically 0x40 or equal to e_ehsize
    Qword       e_shoff;
    Dword       e_flags;
    word        e_ehsize;       // = 0x40 (64-bit)
    word        e_phentsize;    // = 0x36 (64-bit)
    word        e_phnum;
    word        e_shentsize;    // = 0x40 (64-bit)
    word        e_shnum;
    word        e_shstrndx;
} elf64_header;

struct __attribute__((packed)) ELF64_PROG_HEADER {
    Dword       p_type;
    Dword       p_flags;
    Qword       p_offset;
    Qword       p_vaddr;
    Qword       p_paddr;
    Qword       p_filesz;
    Qword       p_memsz;
    Qword       p_align;
};

struct __attribute__((packed)) ELF64_SECT_HEADER {
    Dword       sh_name;
    Dword       sh_type;
    Qword       sh_flags;
    Qword       sh_addr;
    Qword       sh_offset;
    Qword       sh_size;
    Dword       sh_link;
    Dword       sh_info;
    Qword       sh_addralign;
    Qword       sh_entsize;
};

void setELF64Header(word type, word machine, Qword entry_point, Qword prog_off, Qword sect_off, word ph_num, word sh_num, Dword flags, byte ABI, word shstrndx);

struct ELF64_PROG_HEADER createProgHeader(Dword type, Dword flags, Qword offset, Qword vaddr, Qword paddr, Qword filesz, Qword memsz, Qword align);
struct ELF64_SECT_HEADER createSectHeader(Dword name, Dword type, Qword flags, Qword addr, Qword offset, Qword size, Dword link, Dword info, Qword addralign, Qword entsize);

int makeELF64File(ELF64_PROG_HEADER ph[], word phnum, ELF64_SECT_HEADER sh[], word shnum);

// struct __attribute__((packed)) ELF32_HEADER {
//     byte magicNUM[4] = {0x45, 0x4c, 0x46, 0x00};
//     short int version;
// } elf_header;

// struct __attribute__((packed)) ELF32_PROG_HEADER {

// }

// // Not useful much
// struct __attribute__((packed)) ELF32_SECT_HEADER {

// }

#endif