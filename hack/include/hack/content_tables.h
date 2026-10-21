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

/* AREA_TEST_1 has 12 baseline doors and 4 baseline room entries. */
#define HACK_AREA_TEST_1_DOORS sTest1Doors
#define HACK_AREA_TEST_1_ROOM_ENTRIES sTest1RoomEntries

#endif /* HACK_CONTENT_TABLES_H */
