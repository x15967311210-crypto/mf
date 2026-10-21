/*
 * hack/include/hack/tileset_tables.h — HACK=1 blockout tileset selection.
 *
 * BUG-023.  src/room.c includes this header only under HACK=1 and selects
 * HackTest1TilesetEntry for AREA_TEST_1 instead of the room entry's
 * sTilesetEntries index.  The generated tables live in the ignored
 * hack/gen/tileset_tables.h; this shim is the stable injection point.
 *
 * The generated palette keeps the authored colours in pPalette row 2, which
 * RoomLoadTileset copies to global PALRAM row 4; the tilemap therefore uses
 * palette bank 4.  Do not edit src/data to add hack tileset content.
 */
#ifndef HACK_TILESET_TABLES_H
#define HACK_TILESET_TABLES_H

/* BUG-023: generated from hack/content/tiled/blockout_tileset.png.  The header
 * is ignored generated output; `make content-tables` creates it before a HACK
 * build. */
#if defined(__has_include)
#if __has_include("../../gen/tileset_tables.h")
#include "../../gen/tileset_tables.h"
#else
#error "missing hack/gen/tileset_tables.h; run make content-tables"
#endif
#else
#include "../../gen/tileset_tables.h"
#endif

#endif /* HACK_TILESET_TABLES_H */
