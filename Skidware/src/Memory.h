#pragma once
#include <cstdint>

class Memory
{
public:
	Memory() = default;
	~Memory() = default;

	char* FindPattern(uintptr_t pModuleBaseAddress, const char* szSignature, size_t nSelectResultIndex = 0);

	template <typename T = char*>
	char* GetAddress(char* addr, uintptr_t offset = NULL) {
		auto adr = *(int32_t*)(addr)+addr + 4 + offset;
		return adr;
	}

	template <typename T>
	T ReadVirtualMemory(uintptr_t src)
	{
		return *(T*)(src);
	}

	template <typename T>
	void WriteVirtualMemory(uintptr_t src, T buffer)
	{
		*(T*)(src) = buffer;
	}
};