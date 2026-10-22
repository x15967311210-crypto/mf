/*
 * mGBA API compatibility for harness.c.
 *
 * harness.c was originally written against a newer mGBA that spells the
 * native pixel type `mColor`, has a `mCoreLoadSaveFile()` path helper and a
 * `SAVESTATE_ALL` mask.  The canonical harness build is now mGBA 0.6 (the
 * BizHawk 2.3.0.1 core), where the same concepts are named `color_t`,
 * `mCore->loadSave(VFile*)` and an explicit section mask.
 *
 * This header keeps one harness source buildable against both APIs:
 *
 *   - include it after the mGBA headers (it needs struct mCore);
 *   - use `mColor` as before;
 *   - use `SAVESTATE_ALL` as before;
 *   - call `mf_harness_load_save(core, path)` instead of
 *     `mCoreLoadSaveFile(core, path, false)`.
 *
 * Detection is header-based: newer mGBA ships <mgba-util/image.h>, while 0.6
 * (and 0.7.x) do not.  No ROM data is involved and nothing is loaded here.
 */
#ifndef HARNESS_COMPAT06_H
#define HARNESS_COMPAT06_H

#include <mgba/core/core.h>
#include <mgba/core/serialize.h>
#include <mgba-util/vfs.h>

#include <fcntl.h>
#include <stdarg.h>

#if defined(__has_include)
#if __has_include(<mgba-util/image.h>)
#define MF_HARNESS_NEW_MGBA_API 1
#endif
#endif

#ifdef MF_HARNESS_NEW_MGBA_API
#include <mgba-util/image.h>
#else
/*
 * mGBA 0.6 uses `color_t` from <mgba/core/interface.h>; with COLOR_16_BIT
 * (the BizHawk build) that is a uint16_t, matching the 5-5-5 framebuffer the
 * screen hashes and PPM dumps expect.
 */
typedef color_t mColor;
#endif

/*
 * 0.6 has no SAVESTATE_ALL; "all sections" is the union of the per-section
 * flags.  Newer mGBA defines it itself, so the guard covers both.
 */
#ifndef SAVESTATE_ALL
#define SAVESTATE_ALL \
    (SAVESTATE_SCREENSHOT | SAVESTATE_SAVEDATA | SAVESTATE_CHEATS | \
     SAVESTATE_RTC | SAVESTATE_METADATA)
#endif

/*
 * 0.6 has no `mCoreLoadSaveFile(path, temporary)` helper; the core vtable
 * exposes `loadSave(VFile*)`.  Both load SaveRAM before reset.  The helper
 * returns nonzero on success, like mCoreLoadSaveFile.
 */
static int mf_harness_load_save(struct mCore* core, const char* path) {
#ifdef MF_HARNESS_NEW_MGBA_API
    return mCoreLoadSaveFile(core, path, false);
#else
    struct VFile* vf = VFileOpen(path, O_RDONLY);
    if (!vf) {
        return 0;
    }
    bool ok = core->loadSave(core, vf);
    vf->close(vf);
    return ok ? 1 : 0;
#endif
}

/*
 * mGBA 0.6 has no default logger and no config-driven stdout filter: with no
 * logger installed, mLog() prints every message (including the per-SWI BIOS
 * DEBUG trace) straight to stdout.  Install a silent logger so the harness
 * output stays machine-readable.  Newer mGBA already honours `logToStdout`,
 * so this is a no-op there.
 */
#ifndef MF_HARNESS_NEW_MGBA_API
#include <mgba/core/log.h>

static void mf_harness_quiet_log(
    struct mLogger* logger,
    int category,
    enum mLogLevel level,
    const char* format,
    va_list args
) {
    (void)logger;
    (void)category;
    (void)level;
    (void)format;
    (void)args;
}

static void mf_harness_quiet_logs(void) {
    static struct mLogger logger;
    logger.log = mf_harness_quiet_log;
    logger.filter = NULL;
    mLogSetDefaultLogger(&logger);
}
#else
static void mf_harness_quiet_logs(void) {
}
#endif

#endif /* HARNESS_COMPAT06_H */
