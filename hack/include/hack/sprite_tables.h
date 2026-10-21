/*
 * hack/include/hack/sprite_tables.h — HACK=1 spriteset overlay selection.
 *
 * HACK-008d3 / D-013.  src/sprite.c includes this header only under HACK=1 and
 * uses HACK_AREA_TEST_1_DEFAULT_SPRITESETS to load the AREA_TEST_1 default
 * spriteset instead of the vanilla sSpritesetPointers fallback.  The generated
 * (spriteId, gfxSlot) pair tables live in the ignored hack/gen/sprite_tables.h;
 * this shim is the stable injection point.
 *
 * The room entry's defaultSpriteset is an index into sSpritesetPointers and
 * cannot name a generated table, so the manifest's spritesets table never
 * reaches the engine without this hook.  Do not edit src/data to add hack
 * content.
 */
#ifndef HACK_SPRITE_TABLES_H
#define HACK_SPRITE_TABLES_H

/* HACK-008d3: generated from hack/content/tiled/entry_ledge.room.json.  The
 * header is ignored generated output; `make content-tables` creates it before
 * a HACK build. */
#if defined(__has_include)
#if __has_include("../../gen/sprite_tables.h")
#include "../../gen/sprite_tables.h"
#else
#error "missing hack/gen/sprite_tables.h; run make content-tables"
#endif
#else
#include "../../gen/sprite_tables.h"
#endif

#endif /* HACK_SPRITE_TABLES_H */
