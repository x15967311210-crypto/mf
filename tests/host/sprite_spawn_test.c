/*
 * Host-side unit tests for sprite spawning in src/sprite.c.
 *
 * The real engine functions are linked in by the Makefile's host-test target:
 *
 *   cc ... tests/host/sprite_spawn_test.c src/sprite.c -Wl,--gc-sections ...
 *
 * Only the fixture globals below are defined here; the spawn code itself is
 * the engine implementation.  No GBA I/O, ROM data, or emulator is involved.
 *
 * NOTE: the actual SpriteSpawnPrimary() takes an explicit spriteId/gfxRow and
 * stores them verbatim.  The spriteset-slot lookup (low slots derive an id,
 * 0x80 means hidden, values > 0x10 index gSpritesetSpriteIds/GfxSlots) lives
 * in SpriteInitPrimary().  This file covers both so the spriteset expectations
 * are tested against the function that really implements them.
 */

#include "test.h"

#include "sprite.h"

#include <string.h>

/* Fixtures normally supplied by the GBA linker script / globals. */
struct SpriteData gSpriteData[MAX_AMOUNT_OF_SPRITES];
u8 gSpriteDrawOrder[MAX_AMOUNT_OF_SPRITES];
u8 gSpritesetSpriteIds[MAX_AMOUNT_OF_SPRITE_TYPES];
u8 gSpritesetSpriteGfxSlots[MAX_AMOUNT_OF_SPRITE_TYPES];

#define PRIMARY_BASE_STATUS \
    (SPRITE_STATUS_EXISTS | SPRITE_STATUS_ONSCREEN | SPRITE_STATUS_NOT_DRAWN)
#define SECONDARY_BASE_STATUS PRIMARY_BASE_STATUS

static void reset_fixtures(void)
{
    memset(gSpriteData, 0, sizeof(gSpriteData));
    memset(gSpriteDrawOrder, 0, sizeof(gSpriteDrawOrder));
    memset(gSpritesetSpriteIds, 0, sizeof(gSpritesetSpriteIds));
    memset(gSpritesetSpriteGfxSlots, 0, sizeof(gSpritesetSpriteGfxSlots));
}

/* A deterministic, non-zero spriteset table so table lookups are visible. */
static void set_spriteset_table(void)
{
    u8 i;

    for (i = 0; i < MAX_AMOUNT_OF_SPRITE_TYPES; i++)
    {
        gSpritesetSpriteIds[i] = 0x40 + i;
        gSpritesetSpriteGfxSlots[i] = 0x10 + i;
    }
}

static void check_position(const struct SpriteData *sprite, u16 y, u16 x)
{
    u16 expected[2] = { y, x };

    CHECK_MEMEQ(&sprite->yPosition, expected, sizeof(expected));
}

static void check_common_reset_fields(const struct SpriteData *sprite)
{
    CHECK_EQ(sprite->bgPriority, 2);
    CHECK_EQ(sprite->drawOrder, 4);
    CHECK_EQ(sprite->pose, 0);
    CHECK_EQ(sprite->health, 0);
    CHECK_EQ(sprite->invincibilityStunFlashTimer, 0);
    CHECK_EQ(sprite->work0, 0);
    CHECK_EQ(sprite->paletteRow, 0);
    CHECK_EQ(sprite->frozenPaletteRowOffset, 0);
    CHECK_EQ(sprite->ignoreSamusCollisionTimer, 1);
    CHECK_EQ(sprite->freezeTimer, 0);
    CHECK_EQ(sprite->numberOfXToForm, 1);
}

/* ------------------------------------------------------------------ */
/* SpriteSpawnPrimary: direct field initialization.                    */
/* ------------------------------------------------------------------ */

static void test_spawn_primary_basic(void)
{
    const struct SpriteData *sprite;
    u8 slot;

    reset_fixtures();
    slot = SpriteSpawnPrimary(4, 6, 0, 5, 3, 5, 0);
    sprite = &gSpriteData[0];

    CHECK_EQ(slot, 0);
    CHECK_TRUE(slot < MAX_AMOUNT_OF_SPRITES);
    CHECK_EQ(sprite->status, PRIMARY_BASE_STATUS);
    CHECK_EQ(sprite->properties, 0);
    CHECK_EQ(sprite->spriteId, 4);
    CHECK_EQ(sprite->spritesetGfxSlot, 0);
    CHECK_EQ(sprite->spritesetSlotAndProperties, 5);
    CHECK_EQ(sprite->roomSlot, 6);
    check_position(sprite, 3, 5);
    check_common_reset_fields(sprite);
    CHECK_EQ(sprite->primarySpriteRamSlot, 0);
    CHECK_EQ(gSpriteData[1].status, 0);
}

static void test_spawn_primary_status_bits(void)
{
    const struct SpriteData *sprite;
    u8 slot;

    reset_fixtures();
    slot = SpriteSpawnPrimary(0x12, 7, 1, 0x85, 0x1234, 0x2345,
                              SPRITE_STATUS_HIDDEN);
    sprite = &gSpriteData[0];

    CHECK_EQ(slot, 0);
    CHECK_EQ(sprite->status, PRIMARY_BASE_STATUS | SPRITE_STATUS_HIDDEN);
    CHECK_EQ(sprite->properties, 0);
    CHECK_EQ(sprite->spriteId, 0x12);
    CHECK_EQ(sprite->spritesetGfxSlot, 1);
    /* SpawnPrimary stores the spriteset slot verbatim; see InitPrimary. */
    CHECK_EQ(sprite->spritesetSlotAndProperties, 0x85);
    CHECK_EQ(sprite->roomSlot, 7);
    check_position(sprite, 0x1234, 0x2345);
    check_common_reset_fields(sprite);
    CHECK_EQ(sprite->primarySpriteRamSlot, 0);
}

static void test_spawn_primary_high_spriteset_slot(void)
{
    const struct SpriteData *sprite;
    u8 slot;

    /* SpriteSpawnPrimary uses its explicit id/gfx arguments, not the table. */
    reset_fixtures();
    set_spriteset_table();
    slot = SpriteSpawnPrimary(0x33, 2, 0x44, 0x11, 10, 20, 0);
    sprite = &gSpriteData[0];

    CHECK_EQ(slot, 0);
    CHECK_EQ(sprite->spriteId, 0x33);
    CHECK_EQ(sprite->spritesetGfxSlot, 0x44);
    CHECK_EQ(sprite->spritesetSlotAndProperties, 0x11);
    CHECK_EQ(sprite->roomSlot, 2);
}

static void test_spawn_primary_first_free_and_full(void)
{
    u8 i;
    u8 slot;

    reset_fixtures();
    gSpriteData[0].status = SPRITE_STATUS_EXISTS;
    gSpriteData[0].spriteId = 0x77;

    slot = SpriteSpawnPrimary(4, 1, 0, 5, 1, 1, 0);
    CHECK_EQ(slot, 1);
    CHECK_EQ(gSpriteData[0].spriteId, 0x77);
    CHECK_EQ(gSpriteData[1].spriteId, 4);

    reset_fixtures();
    for (i = 0; i < MAX_AMOUNT_OF_SPRITES; i++)
        gSpriteData[i].status = SPRITE_STATUS_EXISTS;

    slot = SpriteSpawnPrimary(4, 1, 0, 5, 1, 1, 0);
    CHECK_EQ(slot, UCHAR_MAX);
}

/* ------------------------------------------------------------------ */
/* SpriteInitPrimary: spriteset slot decoding and block positioning.   */
/* ------------------------------------------------------------------ */

static void test_init_primary_low_slot_position(void)
{
    const struct SpriteData *sprite;

    reset_fixtures();
    set_spriteset_table();
    SpriteInitPrimary(0x05, 3, 5, 6);
    sprite = &gSpriteData[0];

    CHECK_EQ(sprite->status, SPRITE_STATUS_EXISTS);
    CHECK_EQ(sprite->properties, 0);
    CHECK_EQ(sprite->spriteId, 4);
    CHECK_EQ(sprite->spritesetGfxSlot, 0);
    CHECK_EQ(sprite->spritesetSlotAndProperties, 5);
    CHECK_EQ(sprite->roomSlot, 6);
    /* BLOCK_TO_SUB_PIXEL(3) + BLOCK_SIZE, BLOCK_TO_SUB_PIXEL(5) + HALF_BLOCK_SIZE */
    CHECK_EQ(sprite->yPosition, 256);
    CHECK_EQ(sprite->xPosition, 352);
    check_common_reset_fields(sprite);
    CHECK_EQ(sprite->primarySpriteRamSlot, 0);
}

static void test_init_primary_hidden_bit(void)
{
    const struct SpriteData *sprite;

    reset_fixtures();
    set_spriteset_table();
    SpriteInitPrimary(0x85, 3, 5, 6);
    sprite = &gSpriteData[0];

    CHECK_EQ(sprite->status,
             SPRITE_STATUS_EXISTS | SPRITE_STATUS_HIDDEN);
    CHECK_EQ(sprite->spriteId, 4);
    CHECK_EQ(sprite->spritesetGfxSlot, 0);
    CHECK_EQ(sprite->spritesetSlotAndProperties, 5);
    CHECK_EQ(sprite->roomSlot, 6);
}

static void test_init_primary_spriteset_table(void)
{
    const struct SpriteData *sprite;

    /* 0x11 -> (0x11 - 1) % 16 == 0. */
    reset_fixtures();
    set_spriteset_table();
    SpriteInitPrimary(0x11, 1, 2, 3);
    sprite = &gSpriteData[0];

    CHECK_EQ(sprite->status, SPRITE_STATUS_EXISTS);
    CHECK_EQ(sprite->spriteId, gSpritesetSpriteIds[0]);
    CHECK_EQ(sprite->spriteId, 0x40);
    CHECK_EQ(sprite->spritesetGfxSlot, gSpritesetSpriteGfxSlots[0]);
    CHECK_EQ(sprite->spritesetGfxSlot, 0x10);
    CHECK_EQ(sprite->spritesetSlotAndProperties, 0x11);

    /* 0x1F -> (0x1F - 1) % 16 == 14 (last in-bounds table index). */
    reset_fixtures();
    set_spriteset_table();
    SpriteInitPrimary(0x1F, 1, 2, 3);
    sprite = &gSpriteData[0];

    CHECK_EQ(sprite->spriteId, gSpritesetSpriteIds[14]);
    CHECK_EQ(sprite->spriteId, 0x4E);
    CHECK_EQ(sprite->spritesetGfxSlot, gSpritesetSpriteGfxSlots[14]);
    CHECK_EQ(sprite->spritesetGfxSlot, 0x1E);
    CHECK_EQ(sprite->spritesetSlotAndProperties, 0x1F);
}

/* ------------------------------------------------------------------ */
/* SpriteSpawnSecondary: fields, status flags, and slot scan.          */
/* ------------------------------------------------------------------ */

static void test_spawn_secondary_basic(void)
{
    const struct SpriteData *sprite;
    u8 slot;

    reset_fixtures();
    slot = SpriteSpawnSecondary(0x23, 9, 6, 7, 0x1234, 0x2345,
                                SPRITE_STATUS_HIDDEN);
    sprite = &gSpriteData[0];

    CHECK_EQ(slot, 0);
    CHECK_TRUE(slot < MAX_AMOUNT_OF_SPRITES);
    CHECK_EQ(sprite->status,
             SECONDARY_BASE_STATUS | SPRITE_STATUS_HIDDEN);
    CHECK_EQ(sprite->properties, SP_SECONDARY_SPRITE);
    CHECK_TRUE((sprite->properties & SP_SECONDARY_SPRITE) != 0);
    CHECK_EQ(sprite->spritesetSlotAndProperties, UCHAR_MAX);
    CHECK_EQ(sprite->primarySpriteRamSlot, 7);
    CHECK_EQ(sprite->spriteId, 0x23);
    CHECK_EQ(sprite->spritesetGfxSlot, 6);
    CHECK_EQ(sprite->roomSlot, 9);
    check_position(sprite, 0x1234, 0x2345);
    check_common_reset_fields(sprite);
    CHECK_EQ(gSpriteData[1].status, 0);
}

static void test_spawn_secondary_first_free_and_full(void)
{
    u8 i;
    u8 slot;

    reset_fixtures();
    gSpriteData[0].status = SPRITE_STATUS_EXISTS;
    gSpriteData[0].spriteId = 0x77;

    slot = SpriteSpawnSecondary(0x23, 1, 2, 0, 3, 4, 0);
    CHECK_EQ(slot, 1);
    CHECK_EQ(gSpriteData[0].spriteId, 0x77);
    CHECK_EQ(gSpriteData[1].spriteId, 0x23);
    CHECK_EQ(gSpriteData[1].properties, SP_SECONDARY_SPRITE);

    reset_fixtures();
    for (i = 0; i < MAX_AMOUNT_OF_SPRITES; i++)
        gSpriteData[i].status = SPRITE_STATUS_EXISTS;

    slot = SpriteSpawnSecondary(0x23, 1, 2, 0, 3, 4, 0);
    CHECK_EQ(slot, UCHAR_MAX);
}

/* ------------------------------------------------------------------ */
/* Mixed sequence: slots advance and earlier sprites stay intact.      */
/* ------------------------------------------------------------------ */

static void test_mixed_spawn_sequence(void)
{
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;

    reset_fixtures();

    first = SpriteSpawnPrimary(4, 1, 0, 0x05, 3, 5, 0);
    second = SpriteSpawnSecondary(0x23, 2, 6, 0, 0x1234, 0x2345, 0);
    third = SpriteSpawnPrimary(5, 3, 1, 0x11, 7, 9, 0);
    fourth = SpriteSpawnSecondary(0x24, 4, 7, 2, 0x3456, 0x4567, 0);

    CHECK_EQ(first, 0);
    CHECK_EQ(second, 1);
    CHECK_EQ(third, 2);
    CHECK_EQ(fourth, 3);

    CHECK_EQ(gSpriteData[0].status, PRIMARY_BASE_STATUS);
    CHECK_EQ(gSpriteData[1].status, SECONDARY_BASE_STATUS);
    CHECK_EQ(gSpriteData[2].status, PRIMARY_BASE_STATUS);
    CHECK_EQ(gSpriteData[3].status, SECONDARY_BASE_STATUS);

    CHECK_EQ(gSpriteData[0].spriteId, 4);
    CHECK_EQ(gSpriteData[1].spriteId, 0x23);
    CHECK_EQ(gSpriteData[2].spriteId, 5);
    CHECK_EQ(gSpriteData[3].spriteId, 0x24);

    CHECK_EQ(gSpriteData[0].roomSlot, 1);
    CHECK_EQ(gSpriteData[1].roomSlot, 2);
    CHECK_EQ(gSpriteData[2].roomSlot, 3);
    CHECK_EQ(gSpriteData[3].roomSlot, 4);

    CHECK_EQ(gSpriteData[0].properties, 0);
    CHECK_EQ(gSpriteData[1].properties, SP_SECONDARY_SPRITE);
    CHECK_EQ(gSpriteData[2].properties, 0);
    CHECK_EQ(gSpriteData[3].properties, SP_SECONDARY_SPRITE);

    CHECK_EQ(gSpriteData[0].spritesetSlotAndProperties, 0x05);
    CHECK_EQ(gSpriteData[1].spritesetSlotAndProperties, UCHAR_MAX);
    CHECK_EQ(gSpriteData[2].spritesetSlotAndProperties, 0x11);
    CHECK_EQ(gSpriteData[3].spritesetSlotAndProperties, UCHAR_MAX);

    CHECK_EQ(gSpriteData[0].primarySpriteRamSlot, 0);
    CHECK_EQ(gSpriteData[1].primarySpriteRamSlot, 0);
    CHECK_EQ(gSpriteData[2].primarySpriteRamSlot, 2);
    CHECK_EQ(gSpriteData[3].primarySpriteRamSlot, 2);

    check_position(&gSpriteData[0], 3, 5);
    check_position(&gSpriteData[1], 0x1234, 0x2345);
    check_position(&gSpriteData[2], 7, 9);
    check_position(&gSpriteData[3], 0x3456, 0x4567);

    CHECK_EQ(gSpriteData[4].status, 0);
}

int main(void)
{
    test_spawn_primary_basic();
    test_spawn_primary_status_bits();
    test_spawn_primary_high_spriteset_slot();
    test_spawn_primary_first_free_and_full();
    test_init_primary_low_slot_position();
    test_init_primary_hidden_bit();
    test_init_primary_spriteset_table();
    test_spawn_secondary_basic();
    test_spawn_secondary_first_free_and_full();
    test_mixed_spawn_sequence();

    if (g_host_test_failures != 0)
        return host_test_finish();

    printf("sprite-spawn-test: %d/%d passed\n",
           g_host_test_checks, g_host_test_checks);
    return 0;
}
