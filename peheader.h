/* PE HEADER STRUCTS
 * This Header file includes struct for replicating a PE Binary header.
 * Not all of the struct fields are getting used, the whole header still needs to be read.
 */

#ifndef PE_HEADER_STRUCTS
#define PE_HEADER_STRUCTS

#include <stdint.h>

typedef struct {
    uint16_t e_magic;     // "MZ" 0x5a4d in little-endian
    uint16_t e_cblp;      // bytes on last page of file
    uint16_t e_cp;        // pages in file
    uint16_t e_crlc;      // relocations
    uint16_t e_cparhdr;   // size of header in paragraphs
    uint16_t e_minalloc;  // minimum extra paragraphs needed
    uint16_t e_maxalloc;  // maximum extra paragraphs needed
    uint16_t e_ss;        // initial (relative) SS value
    uint16_t e_sp;        // initial SP value
    uint16_t e_csum;      // checksum
    uint16_t e_ip;        // initial IP value
    uint16_t e_cs;        // initial (relative) CS value
    uint16_t e_lfarlc;    // file address of relocation table
    uint16_t e_ovno;      // overlay number
    uint16_t e_res[4];    // reserved
    uint16_t e_oemid;     // OEM identifier
    uint16_t e_oeminfo;   // OEM information
    uint16_t e_res2[10];  // reserved
    uint32_t e_lfanew;    // offset to COFF header
} DosHeader;

typedef struct {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp; // Compilation Time
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics; // https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#characteristics
} CoffHeader;

typedef struct {
    uint16_t Magic;
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitalizedData;
    uint32_t SizeOfUninitalizedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint64_t ImageBase;
} OptionalHeader;

typedef struct{
    char Name[8];
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
} SectionHeader;
#endif
