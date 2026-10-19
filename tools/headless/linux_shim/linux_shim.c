/*
 * Minimal Windows API shim so mf_bizhawk_dll.c can be linked against the
 * native mGBA 0.6 Biz* wrapper on Linux/WSL.
 */
#include <windows.h>

#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

extern void* BizCreate(const void* bios, const void* rom, int length,
    const void* dbinfo, int skipbios);
extern void BizReset(void* ctx);
extern int BizAdvance(void* ctx, uint16_t keys, uint32_t* vbuff, int* nsamp,
    int16_t* sbuff, int64_t time, int16_t gyrox, int16_t gyroy, int16_t gyroz,
    uint8_t luma);
extern void BizDestroy(void* ctx);
extern void BizGetMemoryAreas(void* ctx, void* dst);
extern void BizPutSaveRam(void* ctx, const void* data, int size);
extern void BizGetRegisters(void* ctx, int* dest);
extern uint8_t BizReadBus(void* ctx, uint32_t addr);

HMODULE LoadLibraryA(const char* path) {
    (void) path;
    return (HMODULE) 1;
}

FARPROC GetProcAddress(HMODULE module, const char* name) {
    (void) module;
    if (!strcmp(name, "BizCreate")) return (FARPROC) BizCreate;
    if (!strcmp(name, "BizReset")) return (FARPROC) BizReset;
    if (!strcmp(name, "BizAdvance")) return (FARPROC) BizAdvance;
    if (!strcmp(name, "BizDestroy")) return (FARPROC) BizDestroy;
    if (!strcmp(name, "BizGetMemoryAreas")) return (FARPROC) BizGetMemoryAreas;
    if (!strcmp(name, "BizPutSaveRam")) return (FARPROC) BizPutSaveRam;
    if (!strcmp(name, "BizGetRegisters")) return (FARPROC) BizGetRegisters;
    if (!strcmp(name, "BizReadBus")) return (FARPROC) BizReadBus;
    return NULL;
}

int FreeLibrary(HMODULE module) {
    (void) module;
    return 1;
}

DWORD GetLastError(void) {
    return 0;
}

int CreateDirectoryA(const char* path, void* security) {
    (void) security;
    return mkdir(path, 0755);
}
