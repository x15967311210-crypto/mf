#ifndef PAUSE_SCREEN_MAP_DATA_H
#define PAUSE_SCREEN_MAP_DATA_H

#include "types.h"
#include "gba/memory.h"
#include "oam.h"

extern const u8 sMinimapTilesGfx[32 * 14 * TILE_SIZE];

/* 0x79bec0: the pause-screen OAM table, 154 pointers to animation frame data.
   The storage is the generated pointer blob in src/menus/pause_screen_map.c
   (sBlob_79bec0_79c128); this name is a zero-size alias for the same address,
   typed the way PauseScreenProcessOam indexes it. */
extern const struct FrameData* const sUnk_79bec0[154];

#endif /* PAUSE_SCREEN_MAP_DATA_H */
