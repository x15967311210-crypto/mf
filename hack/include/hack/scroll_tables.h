/*
 * hack/include/hack/scroll_tables.h — HACK=1 scroll overlay selection.
 *
 * HACK-008d1 / D-013.  src/scroll.c includes this header only when HACK=1 and
 * uses HACK_AREA_TEST_1_SCROLLS for the AREA_TEST_1 entry of
 * sAreaScrollPointers.  The generated scroll blocks, terminator and pointer
 * list live in the ignored hack/gen/scroll_tables.h; this shim is the stable
 * injection point.
 *
 * Scrolls are split from content_tables.h (room/door/spriteset tables) so that
 * each generated object is defined in exactly one translation unit.  Do not
 * edit src/data to add hack content.
 */
#ifndef HACK_SCROLL_TABLES_H
#define HACK_SCROLL_TABLES_H

/* HACK-008d1: generated from hack/content/tiled/entry_ledge.room.json plus the
 * converter's scrolls.bin.  The header is ignored generated output;
 * `make content-tables` creates it before a HACK build. */
#if defined(__has_include)
#if __has_include("../../gen/scroll_tables.h")
#include "../../gen/scroll_tables.h"
#else
#error "missing hack/gen/scroll_tables.h; run make content-tables"
#endif
#else
#include "../../gen/scroll_tables.h"
#endif

#endif /* HACK_SCROLL_TABLES_H */
