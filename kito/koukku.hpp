#pragma once

#ifndef koukku_
#define koukku_
#include "pch.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
namespace hook //a VERY basic namespace to do the most basic things!
{
#ifdef MINHOOK_LIBRARY
	inline void hook_error(MH_STATUS s) {
		MessageBoxA(NULL, std::format("Fatal error: {}", MH_StatusToString(s)).c_str(), "Hook error!", MB_ICONERROR);
#ifdef _ERR_EXISTS
		__err::error(std::string("hook_error:\n") + MH_StatusToString(s));
#endif

	}
	template <typename T>
	struct hookobj
	{

		hookobj() = default;
		//hookobj(const hookobj&) = delete;
		hookobj(const auto org, const LPVOID detour/*, const LPVOID target = (LPVOID)org*/, const bool enabled = true) : pTarget((LPVOID)org), pDetour(detour), orgFnc(reinterpret_cast<T*>((DWORD)org))
		{
			init(reinterpret_cast<T*>(org), detour, enabled);
		}
		~hookobj()
		{
			release();
		}
		bool init(auto org, const LPVOID detour/*, const LPVOID target = (LPVOID)org*/, const bool enabled = true)
		{
			pTarget = (LPVOID)org;
			pDetour = detour;
			orgFnc = reinterpret_cast<T*>((DWORD)org);
			if (ok = (pTarget && pDetour), !ok) {
				return ok;
			}
#pragma warning(suppress : 26812)
			MH_STATUS status = MH_CreateHook(pTarget, pDetour, &(LPVOID&)orgFnc);
			if (ok = (status == MH_OK), !ok) {
				hook_error(status);

				return false;
			}
			if (!enabled)
				return true;

			if (status = enable(), status != MH_OK) {
				hook_error(status);


				return false;
			}
			return 1;
		}bool release() {
			if (ok = (pTarget), !ok) {
				return false;
			}
#pragma warning(suppress : 26812)
			MH_STATUS status;
			if (status = disable(), status != MH_OK) {
				hook_error(status);
				return false;
			}

			status = MH_RemoveHook(pTarget);
			if (ok = (status == MH_OK), !ok) {
				hook_error(status);
				return false;
			}
			pTarget = pDetour = 0;
			return 1;
		}
		MH_STATUS enable() {
			if (!pTarget)
				return MH_ERROR_NOT_INITIALIZED;
			return MH_EnableHook(pTarget);
		}
		MH_STATUS disable() {
			if (!pTarget)
				return MH_ERROR_NOT_INITIALIZED;
			return MH_DisableHook(pTarget);
		}
		template<typename ... Args>
		auto call(const Args... args) {
			return orgFnc(args...);
		}


	private:
		bool ok = false;
		LPVOID pTarget = 0;
		LPVOID pDetour = 0;
		T* orgFnc = 0;
	};
#else
#error "MinHook library doesn't exist"
#endif


	void nop(std::uintptr_t address);
	void write_addr(void* addr, const char* bytes, size_t len);
	void write_addr(void* addr, void* bytes, size_t len);

	void write_addr(std::uintptr_t addr, const char* bytes, size_t len);
	void memcopy(void* dst, void* src, size_t len);

	void get_bytes(void* addr, size_t len, BYTE* buffer);

	std::uintptr_t find_pattern(std::string moduleName, std::string pattern);
	std::uintptr_t find_pattern(DWORD start_address, DWORD end_address, std::string pattern);


};

#endif