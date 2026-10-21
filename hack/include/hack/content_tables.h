/*
 * hack/include/hack/content_tables.h — HACK=1 content overlay selection.
 *
 * HACK-008c1 / D-013 scaffold.  src/room.c includes this header only when
 * HACK=1 and uses the macros below for the AREA_TEST_1 entries of
 * sAreaDoorPointers and sAreaRoomEntryPointers.  No other baseline table is
 * hookable this way: the overlay owns its tables, the baseline owns src/data.
 *
 * The overlay is empty for HACK-008c1, so both macros name the baseline
 * tables and the hack ROM is byte-identical to mf_us.gba.  HACK-008c2 replaces
 * these two defaults with the generated tables under hack/gen/ (declared
 * extern here); that is the stable injection point.  Do not edit src/data to
 * add hack content.
 */
#ifndef HACK_CONTENT_TABLES_H
#define HACK_CONTENT_TABLES_H

/* HACK-008c2: generated from hack/content/rooms/entry_ledge.  The header is
 * ignored generated output; `make content-tables` creates it before a HACK
 * build.  Keep this include as the only generated-content injection point. */
#if defined(__has_include)
#if __has_include("../../gen/content_tables.h")
#include "../../gen/content_tables.h"
#else
#error "missing hack/gen/content_tables.h; run make content-tables"
#endif
#else
#include "../../gen/content_tables.h"
#endif

#define HACK_AREA_TEST_1_DOORS HackTest1Doors
#define HACK_AREA_TEST_1_ROOM_ENTRIES HackTest1RoomEntries

#endif /* HACK_CONTENT_TABLES_H */
