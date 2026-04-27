#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "peheader.h"

int main(int argc, char *argv[]){

    if (argc !=2) {
        printf("Usage: peloader [PE Binary]\n");
        return 1;
    }

    FILE *pefile = fopen(argv[1], "rb");
    if (pefile == NULL) {
        perror(argv[1]);
        return 1;
    }

    DosHeader dos;
    if (!fread(&dos,sizeof(dos), 1, pefile)) {
        fprintf(stderr, "File too small\n");
        fclose(pefile);
        return 1;
    }
    if (dos.e_magic == 0x5a4d) {
        printf("DOS Magic:  OK (MZ)\n");
        printf("PE Offset:  0x%x\n\n", dos.e_lfanew);
    } else {
        fprintf(stderr, "Not a PE File. \n");
        fclose(pefile);
        return 1;
    }
    /* COFF Header processing  */
    uint32_t pe_sig;
    CoffHeader coffheader;
    /* Seeking to the COFF Header Offset */
    if (fseek(pefile, dos.e_lfanew, SEEK_SET)) {
        perror("fseek");
        fclose(pefile);
        return 1;
    }
    /* The PE Signature is a 2 Byte "one of", not included in the Struct */
    if (!fread(&pe_sig, 4, 1, pefile)){
        fprintf(stderr, "PE Signature could not be read from the File.\n");
        fclose(pefile);
        return 1;
    }
    if (pe_sig != 0x00004550) {
        fprintf(stderr,"Not a valid PE signature.\n");
        fclose(pefile);
        return 1;
    }

    /* Initalizing the coffheader with the correct file pointer */
    if (!fread(&coffheader, sizeof(coffheader), 1, pefile)) {
        fprintf(stderr,"Failed to read COFF Header.\n");
        fclose(pefile);
        return 1;
    }

    switch (coffheader.Machine) {
        case 0x014C: printf("Machine:   Intel i386\n"); break;
        case 0x8664: printf("Machine:   AMD64\n"); break;
        case 0x0200: printf("Machine:   Intel Itanium\n"); break;
        default: printf("Machine:   Unknown Architecture\n"); break;
    }

    printf("Sections:    %u\n", coffheader.NumberOfSections);
    printf("Timestamp:   %u\n", coffheader.TimeDateStamp);
    printf("OptHdr size: %u bytes\n", coffheader.SizeOfOptionalHeader);
    printf("Characteristics: 0x%04x\n", coffheader.Characteristics);
    fclose(pefile);
    return 0;
}
