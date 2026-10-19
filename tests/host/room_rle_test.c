/*
 * Host-side unit tests for RoomRleDecompress() from src/room.c.
 *
 * The real implementation is linked in by the Makefile's host-test target:
 *
 *   cc ... tests/host/room_rle_test.c src/room.c -Wl,--gc-sections ...
 *
 * -ffunction-sections/-fdata-sections plus --gc-sections keep unrelated room
 * code and its GBA globals out of the final binary.  Nothing here emulates
 * GBA I/O or depends on ROM data; every vector below is synthetic.
 */

#include "test.h"

#include "room.h"

#include <string.h>

#define OUT_SIZE 64
#define FILL_BYTE 0xCC

static u8 sOut[OUT_SIZE];

static void reset_output(void)
{
    memset(sOut, FILL_BYTE, sizeof(sOut));
}

/* ------------------------------------------------------------------ */
/* Type 0: the first source byte selects the decompressed size.        */
/* ------------------------------------------------------------------ */

static void test_type0_size_codes(void)
{
    static const u8 codes[] = { 0x00, 0x01, 0x02, 0x03, 0x7F };
    static const u32 expected_sizes[] = {
        0x800, 0x1000, 0x1000, 0x2000, 0x2000
    };
    size_t i;

    for (i = 0; i < sizeof(codes); i++)
    {
        /* type0 size, then two valid two-byte 8-bit passes. */
        u8 src[] = {
            codes[i],
            0x01, 0x02, 'A', 'B', 0x00,
            0x01, 0x02, 'C', 'D', 0x00
        };
        static const u8 expected[] = { 'A', 'C', 'B', 'D' };
        u32 result;

        reset_output();
        result = RoomRleDecompress(0, src, sOut);

        CHECK_EQ(result, expected_sizes[i]);
        CHECK_MEMEQ(sOut, expected, sizeof(expected));
        CHECK_EQ(sOut[4], FILL_BYTE);
    }
}

/* ------------------------------------------------------------------ */
/* Type 1: no header; two passes interleave into dst[0], dst[2], ...   */
/* ------------------------------------------------------------------ */

static void test_type1_no_header_interleaved(void)
{
    static const u8 src[] = {
        0x01, 0x02, 'a', 'b', 0x00,
        0x01, 0x02, 'c', 'd', 0x00
    };
    static const u8 expected[] = { 'a', 'c', 'b', 'd' };
    u32 result;

    reset_output();
    result = RoomRleDecompress(1, src, sOut);

    CHECK_EQ(result, 0);
    CHECK_MEMEQ(sOut, expected, sizeof(expected));
    CHECK_EQ(sOut[4], FILL_BYTE);
}

/* ------------------------------------------------------------------ */
/* Type > 1: two source bytes become a 4-byte header, then the passes. */
/* ------------------------------------------------------------------ */

static void test_type2_header_then_interleaved_passes(void)
{
    static const u8 src[] = {
        0x34, 0x12,             /* header: 34 00 12 00 */
        0x01, 0x02, 'A', 'B', 0x00,
        0x01, 0x02, 'C', 'D', 0x00
    };
    static const u8 expected[] = {
        0x34, 0x00, 0x12, 0x00,
        'A', 'C', 'B', 'D'
    };
    u32 result;

    reset_output();
    result = RoomRleDecompress(2, src, sOut);

    CHECK_EQ(result, 0);
    CHECK_MEMEQ(sOut, expected, sizeof(expected));
    CHECK_EQ(sOut[8], FILL_BYTE);
}

/* ------------------------------------------------------------------ */
/* 8-bit pass mode: literal and run controls, both terminated by 0.    */
/* ------------------------------------------------------------------ */

static void test_8bit_literal_and_run(void)
{
    /* pass 1: literal "xyz"; pass 2: run of 3 * 'Q'. */
    static const u8 src[] = {
        0x01, 0x03, 'x', 'y', 'z', 0x00,
        0x01, 0x83, 'Q', 0x00
    };
    static const u8 expected[] = { 'x', 'Q', 'y', 'Q', 'z', 'Q' };
    u32 result;

    reset_output();
    result = RoomRleDecompress(1, src, sOut);

    CHECK_EQ(result, 0);
    CHECK_MEMEQ(sOut, expected, sizeof(expected));
    CHECK_EQ(sOut[6], FILL_BYTE);
}

/* ------------------------------------------------------------------ */
/* 16-bit pass mode: leading non-1 byte, then big-endian 16-bit words. */
/* ------------------------------------------------------------------ */

static void test_16bit_literal_and_run(void)
{
    /*
     * pass 1: 0x0003 literal "xyz"
     * pass 2: 0x8003 run of 3 * 'Q'
     * Each pass starts with the non-1 mode byte (0x00).
     */
    static const u8 src[] = {
        0x00, 0x00, 0x03, 'x', 'y', 'z', 0x00, 0x00,
        0x00, 0x80, 0x03, 'Q', 0x00, 0x00
    };
    static const u8 expected[] = { 'x', 'Q', 'y', 'Q', 'z', 'Q' };
    u32 result;

    reset_output();
    result = RoomRleDecompress(1, src, sOut);

    CHECK_EQ(result, 0);
    CHECK_MEMEQ(sOut, expected, sizeof(expected));
    CHECK_EQ(sOut[6], FILL_BYTE);
}

/* ------------------------------------------------------------------ */
/* Interleaving: pass 2 always starts at dstStart + 1.                 */
/* ------------------------------------------------------------------ */

static void test_pass2_starts_at_dst_plus_one(void)
{
    static const u8 src[] = {
        0x01, 0x03, '1', '2', '3', 0x00,
        0x01, 0x03, 'a', 'b', 'c', 0x00
    };
    static const u8 expected[] = {
        '1', 'a',
        '2', 'b',
        '3', 'c'
    };
    u32 result;

    reset_output();
    result = RoomRleDecompress(1, src, sOut);

    CHECK_EQ(result, 0);
    CHECK_MEMEQ(sOut, expected, sizeof(expected));
    CHECK_EQ(sOut[6], FILL_BYTE);
}

/* ------------------------------------------------------------------ */
/* Regression vector: run + literal mixed in both passes.              */
/* ------------------------------------------------------------------ */

static void test_mixed_run_and_literal_regression(void)
{
    /*
     * pass 1: literal "AB", then run of 2 * 'R'
     * pass 2: run of 2 * 'C', then literal "DEF"
     */
    static const u8 src[] = {
        0x01, 0x02, 'A', 'B', 0x82, 'R', 0x00,
        0x01, 0x82, 'C', 0x03, 'D', 'E', 'F', 0x00
    };
    static const u8 expected[] = {
        'A', 'C',
        'B', 'C',
        'R', 'D',
        'R', 'E',
        FILL_BYTE, 'F'
    };
    u32 result;

    reset_output();
    result = RoomRleDecompress(1, src, sOut);

    CHECK_EQ(result, 0);
    CHECK_MEMEQ(sOut, expected, sizeof(expected));
    CHECK_EQ(sOut[10], FILL_BYTE);
}

int main(void)
{
    test_type0_size_codes();
    test_type1_no_header_interleaved();
    test_type2_header_then_interleaved_passes();
    test_8bit_literal_and_run();
    test_16bit_literal_and_run();
    test_pass2_starts_at_dst_plus_one();
    test_mixed_run_and_literal_regression();

    return host_test_finish();
}
