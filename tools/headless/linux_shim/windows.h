#ifndef MF_LINUX_WINDOWS_SHIM_H
#define MF_LINUX_WINDOWS_SHIM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cdecl
#define __cdecl
#endif

typedef void* HMODULE;
typedef void* FARPROC;
typedef unsigned long DWORD;

HMODULE LoadLibraryA(const char* path);
FARPROC GetProcAddress(HMODULE module, const char* name);
int FreeLibrary(HMODULE module);
DWORD GetLastError(void);
int CreateDirectoryA(const char* path, void* security);

#ifdef __cplusplus
}
#endif

#endif
