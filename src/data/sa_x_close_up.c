#include "data/sa_x_close_up.h"
#include "macros.h"
#include "oam.h"

const u16 sSaXCloseUpPal[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette.pal");
const u16 sSaXCloseUpPalGrayscale[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette_grayscale.pal");
const u32 sSaXCloseUpGfx[4472] = INCBIN_U32("data/sa_x_close_up/graphics.gfx.lz");
const u32 sSaXCloseUpTileTable1[294] = INCBIN_U32("data/sa_x_close_up/first.tt.lz");
const u32 sSaXCloseUpTileTable2[305] = INCBIN_U32("data/sa_x_close_up/second.tt.lz");

const u8 sSaXCloseUpDurations[2] = { 25, 60 };

static const u8 sBlob_73421e_before[0xC89A] = INCBIN_U8("data/Blob_73421e_before.bin");

static const struct FrameData sSaXCloseUpFrameData[74] = {
    [0] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB574),
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR,
    [2] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB612),
        .timer = 4
    },
    [3] = FRAME_DATA_TERMINATOR,
    [4] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB6B0),
        .timer = 4
    },
    [5] = FRAME_DATA_TERMINATOR,
    [6] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xBD86),
        .timer = 8
    },
    [7] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xBE2A),
        .timer = 8
    },
    [8] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xBECE),
        .timer = 8
    },
    [9] = FRAME_DATA_TERMINATOR,
    [10] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xBF72),
        .timer = 8
    },
    [11] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC016),
        .timer = 8
    },
    [12] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC0BA),
        .timer = 8
    },
    [13] = FRAME_DATA_TERMINATOR,
    [14] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC15E),
        .timer = 8
    },
    [15] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC202),
        .timer = 8
    },
    [16] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC2A6),
        .timer = 8
    },
    [17] = FRAME_DATA_TERMINATOR,
    [18] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB79A),
        .timer = 8
    },
    [19] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB7A2),
        .timer = 8
    },
    [20] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB7AA),
        .timer = 8
    },
    [21] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB7A2),
        .timer = 4
    },
    [22] = FRAME_DATA_TERMINATOR,
    [23] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB7B2),
        .timer = 4
    },
    [24] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB7BA),
        .timer = 4
    },
    [25] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB7B2),
        .timer = 4
    },
    [26] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xB7BA),
        .timer = 20
    },
    [27] = FRAME_DATA_TERMINATOR,
    [28] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC34A),
        .timer = 4
    },
    [29] = FRAME_DATA_TERMINATOR,
    [30] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC352),
        .timer = 4
    },
    [31] = FRAME_DATA_TERMINATOR,
    [32] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC360),
        .timer = 4
    },
    [33] = FRAME_DATA_TERMINATOR,
    [34] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC36E),
        .timer = 4
    },
    [35] = FRAME_DATA_TERMINATOR,
    [36] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC37C),
        .timer = 4
    },
    [37] = FRAME_DATA_TERMINATOR,
    [38] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC38A),
        .timer = 4
    },
    [39] = FRAME_DATA_TERMINATOR,
    [40] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC398),
        .timer = 4
    },
    [41] = FRAME_DATA_TERMINATOR,
    [42] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC3A6),
        .timer = 4
    },
    [43] = FRAME_DATA_TERMINATOR,
    [44] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC3B4),
        .timer = 4
    },
    [45] = FRAME_DATA_TERMINATOR,
    [46] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC3C8),
        .timer = 4
    },
    [47] = FRAME_DATA_TERMINATOR,
    [48] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC3DC),
        .timer = 4
    },
    [49] = FRAME_DATA_TERMINATOR,
    [50] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC3F0),
        .timer = 4
    },
    [51] = FRAME_DATA_TERMINATOR,
    [52] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC404),
        .timer = 4
    },
    [53] = FRAME_DATA_TERMINATOR,
    [54] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC418),
        .timer = 4
    },
    [55] = FRAME_DATA_TERMINATOR,
    [56] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC42C),
        .timer = 4
    },
    [57] = FRAME_DATA_TERMINATOR,
    [58] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC434),
        .timer = 4
    },
    [59] = FRAME_DATA_TERMINATOR,
    [60] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC448),
        .timer = 4
    },
    [61] = FRAME_DATA_TERMINATOR,
    [62] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC45C),
        .timer = 4
    },
    [63] = FRAME_DATA_TERMINATOR,
    [64] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC470),
        .timer = 4
    },
    [65] = FRAME_DATA_TERMINATOR,
    [66] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC484),
        .timer = 4
    },
    [67] = FRAME_DATA_TERMINATOR,
    [68] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC498),
        .timer = 4
    },
    [69] = FRAME_DATA_TERMINATOR,
    [70] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC4AC),
        .timer = 4
    },
    [71] = FRAME_DATA_TERMINATOR,
    [72] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_before + 0xC4BA),
        .timer = 4
    },
    [73] = FRAME_DATA_TERMINATOR
};

static const u8 sBlob_73421e_after[0x6B98] = INCBIN_U8("data/Blob_73421e_after.bin");
