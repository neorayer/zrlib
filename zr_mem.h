#ifndef ZR_MEM_H_
#define ZR_MEM_H_

inline byte * zr_memmem(const byte* haystack, size_t hl, const byte* needle, size_t nl);
int zr_memscan_count(HANDLE procHandle, DWORD maxAddr, byte key[], long keyLen);
PVOID zr_memscan_baseaddr(HANDLE procHandle, PVOID beginAddr, DWORD maxAddr, byte key[], long keyLen);
PVOID zr_memscan_addr(HANDLE procHandle, DWORD maxAddr, byte key[],long keyLen);

#endif /*ZR_MEM_H_*/
