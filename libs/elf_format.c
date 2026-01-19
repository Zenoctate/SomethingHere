#include "elf_format.h"

void setELF64Header(word type, word machine, Qword entry_point, Qword prog_off, Qword sect_off, word ph_num, word sh_num, Dword flags, byte ABI, word shstrndx) {
    elf64_header.magicNUM = {0x7f, 0x45, 0x4c, 0x46};
    elf64_header.arch_bit = 2;
    elf64_header.endian = 1;
    elf64_header.elf_version = 1;
    // elf64_header.ABI = ABI;
    elf64_header.ABI_version = 0;
    elf64_header.unused = {0};
    // elf64_header.e_type = type;
    // elf64_header.e_machine = machine;
    elf64_header.e_version = 1;
    // elf64_header.e_entry = entry_point;
    // elf64_header.e_phoff = prog_off;
    // elf64_header.e_shoff = sect_off;
    // elf64_header.e_flags = flags;
    elf64_header.e_ehsize = 0x40;
    elf64_header.e_phentsize = 0x36;
    // elf64_header.e_phnum = ph_num;
    elf64_header.e_shentsize = 0x40;
    // elf64_header.e_shnum = sh_num;
    // elf64_header.e_shstrndx = shstrndx;
}

struct ELF64_PROG_HEADER createProgHeader(Dword type, Dword flags, Qword offset, Qword vaddr, Qword paddr, Qword filesz, Qword memsz, Qword align) {
    ELF64_PROG_HEADER out;
    out.p_type = type;
    out.p_flags = flags;
    out.p_offset = offset;
    out.p_vaddr = vaddr;
    out.p_paddr = paddr;
    out.p_filesz = filesz;
    out.p_memsz = memsz;
    out.p_align = align;
    return out;
}

struct ELF64_SECT_HEADER createSectHeader(Dword name, Dword type, Qword flags, Qword addr, Qword offset, Qword size, Dword link, Dword info, Qword addralign, Qword entsize) {
    ELF64_SECT_HEADER out;
    out.sh_name = name;
    out.sh_type = type;
    out.sh_flags = flags;
    out.sh_addr = addr;
    out.sh_offset = offset;
    out.sh_size = size;
    out.sh_paddr = link;
    out.sh_memsz = info;
    out.sh_addralign = addralign;
    out.sh_entsize = entsize;
    return out;
}

int makeELF64File(ELF64_PROG_HEADER ph[], word phnum, ELF64_SECT_HEADER sh[], word shnum) {
    
}