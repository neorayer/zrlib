#include <windows.h>
#include "zr_mem.h"
#include "zr_logger.h"

inline byte * zr_memmem(const byte* haystack, size_t hl, const byte* needle,
		size_t nl) {
	int i;
	if (nl>hl)
		return 0;
	for (i=hl-nl+1; i; --i) {
		if ((haystack[0] != needle[0]) || (haystack[2] != needle[2])) {
			++haystack;
			continue;
		}
		if (!memcmp(haystack, needle, nl))
			return (byte *)haystack;
		++haystack;
	}
	return 0;
}

int zr_memscan_count(HANDLE procHandle, DWORD maxAddr, byte key[], long keyLen) {
	int res = 0;

	int bufLen = 0x01;
	byte * buf = new byte[bufLen];
	SIZE_T rlen = 0;
	MEMORY_BASIC_INFORMATION mi;
	long miLen = sizeof(mi);

	PBYTE beginAddr = 0;

	zr_log_debug_ec(0, "zr_memscan_count...");
	for (;; beginAddr = (PBYTE)(mi.BaseAddress) + mi.RegionSize) {
		DWORD lReturn = VirtualQueryEx(procHandle, beginAddr, &mi, miLen);
		if (lReturn != miLen)
			break;

		if (MEM_COMMIT != mi.State) {
			continue;
		}
		if ((DWORD)mi.BaseAddress > maxAddr) {
			break;
		}
		delete buf;
		buf = new byte[mi.RegionSize];
		bufLen = mi.RegionSize;
		if (ReadProcessMemory(procHandle, mi.BaseAddress, buf, bufLen, &rlen)) {
			if (zr_memmem(buf, rlen, key, keyLen)) {
				zr_log_debug_ec(0, "found key at %8X", mi.BaseAddress);
				res ++;
			}
		}
	}
	delete buf;
	zr_log_debug_ec(0, "Scan Over");
	return res;
}

PVOID zr_memscan_baseaddr(HANDLE procHandle,  PVOID _beginAddr, DWORD maxAddr, byte key[],
		long keyLen) {
	PVOID res = 0;

	SIZE_T bufLen = 0x01;
	byte * buf = new byte[bufLen];
	SIZE_T rlen = 0;
	MEMORY_BASIC_INFORMATION mi;
	long miLen = sizeof(mi);

	PBYTE beginAddr = (PBYTE)_beginAddr;

	zr_log_debug_ec(0, "zr_memscan_baseaddr...");
	for (;; beginAddr = (PBYTE)(mi.BaseAddress) + mi.RegionSize) {
		DWORD lReturn = VirtualQueryEx(procHandle, beginAddr, &mi, miLen);
		if (lReturn != miLen) {
			zr_log_debug_ec(GetLastError(), "VirtualQueryEx Error");
			break;
		}

		if (MEM_COMMIT != mi.State) {
			continue;
		}
		if ((DWORD)mi.BaseAddress > maxAddr) {
			break;
		}
		
		delete buf;
		bufLen = mi.RegionSize;
		buf = new byte[bufLen];
		if (ReadProcessMemory(procHandle, mi.BaseAddress, buf, bufLen, &rlen)) {
			if (zr_memmem(buf, rlen, key, keyLen)) {
				res = mi.BaseAddress;
				zr_log_debug_ec(0, "found key at %8X", res);
				break;
			}
		}
	}
	delete buf;
	return res;
}


PVOID zr_memscan_addr(HANDLE procHandle, DWORD maxAddr, byte key[], long keyLen) {
	PVOID res = 0;

	int bufLen = 0x1000000;
	byte * buf = new byte[bufLen];
	SIZE_T rlen = 0;
	MEMORY_BASIC_INFORMATION mi;
	long miLen = sizeof(mi);

	PBYTE beginAddr = 0;

	zr_log_debug_ec(0, "zr_memscan_addr...");
	for (;; beginAddr = (PBYTE)(mi.BaseAddress) + mi.RegionSize) {
		//zr_log_debug_ec(0, "searching... %8X", beginAddr);
		DWORD lReturn = VirtualQueryEx(procHandle, beginAddr, &mi, miLen);
		if (lReturn != miLen) {
			zr_log_debug_ec(GetLastError(), "VirtualQueryEx Error");
			break;
		}

		if (MEM_COMMIT != mi.State) {
			continue;
		}
		if ((DWORD)mi.BaseAddress > maxAddr) {
			break;
		}
		delete buf;
		buf = new byte[mi.RegionSize];
		bufLen = mi.RegionSize;
		if (ReadProcessMemory(procHandle, mi.BaseAddress, buf, bufLen, &rlen)) {
			byte * pos = zr_memmem(buf, rlen, key, keyLen);
			if (pos) {
				res = (PBYTE)mi.BaseAddress + ((PBYTE)pos - (PBYTE)buf);
				zr_log_debug_ec(0, "found key, B_Addr=%8X, keyAddr=%8X",mi.BaseAddress, res);
				break;
			}
		}
	}
	delete buf;
	return res;
}
