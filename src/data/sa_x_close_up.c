#include "data/sa_x_close_up.h"
#include "macros.h"
#include "oam.h"

const u16 sSaXCloseUpPal[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette.pal");
const u16 sSaXCloseUpPalGrayscale[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette_grayscale.pal");
const u32 sSaXCloseUpGfx[4472] = INCBIN_U32("data/sa_x_close_up/graphics.gfx.lz");
const u32 sSaXCloseUpTileTable1[294] = INCBIN_U32("data/sa_x_close_up/first.tt.lz");
const u32 sSaXCloseUpTileTable2[305] = INCBIN_U32("data/sa_x_close_up/second.tt.lz");

const u8 sSaXCloseUpDurations[2] = { 25, 60 };

static const u8 sBlob_73421e_prefix[0xC6FA] = INCBIN_U8("data/Blob_73421e_prefix.bin");

static const struct FrameData sSaXCloseUpAnimFrames[38] = {
    [0] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB39C),
        .timer = 1
    },
    [1] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB3AA),
        .timer = 1
    },
    [2] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB3B8),
        .timer = 2
    },
    [3] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB3D2),
        .timer = 2
    },
    [4] = FRAME_DATA_TERMINATOR,
    [5] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB3F8),
        .timer = 4
    },
    [6] = FRAME_DATA_TERMINATOR,
    [7] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB3D2),
        .timer = 2
    },
    [8] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB3B8),
        .timer = 2
    },
    [9] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB3AA),
        .timer = 1
    },
    [10] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB39C),
        .timer = 1
    },
    [11] = FRAME_DATA_TERMINATOR,
    [12] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB412),
        .timer = 1
    },
    [13] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB42C),
        .timer = 1
    },
    [14] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB43A),
        .timer = 2
    },
    [15] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB454),
        .timer = 2
    },
    [16] = FRAME_DATA_TERMINATOR,
    [17] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB47A),
        .timer = 4
    },
    [18] = FRAME_DATA_TERMINATOR,
    [19] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB454),
        .timer = 2
    },
    [20] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB43A),
        .timer = 2
    },
    [21] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB42C),
        .timer = 1
    },
    [22] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB412),
        .timer = 1
    },
    [23] = FRAME_DATA_TERMINATOR,
    [24] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB4BA),
        .timer = 4
    },
    [25] = FRAME_DATA_TERMINATOR,
    [26] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB4C8),
        .timer = 4
    },
    [27] = FRAME_DATA_TERMINATOR,
    [28] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB4D6),
        .timer = 4
    },
    [29] = FRAME_DATA_TERMINATOR,
    [30] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB4E4),
        .timer = 4
    },
    [31] = FRAME_DATA_TERMINATOR,
    [32] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB4F2),
        .timer = 4
    },
    [33] = FRAME_DATA_TERMINATOR,
    [34] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB500),
        .timer = 4
    },
    [35] = FRAME_DATA_TERMINATOR,
    [36] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB50E),
        .timer = 4
    },
    [37] = FRAME_DATA_TERMINATOR
};

static const struct FrameData sSaXCloseUpFrameData[88] = {
    [0] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB51C),
        .timer = 14
    },
    [1] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC4C8),
        .timer = 14
    },
    [2] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC4D0),
        .timer = 14
    },
    [3] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC4C8),
        .timer = 14
    },
    [4] = FRAME_DATA_TERMINATOR,
    [5] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB51C),
        .timer = 8
    },
    [6] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB524),
        .timer = 4
    },
    [7] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB52C),
        .timer = 4
    },
    [8] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB534),
        .timer = 8
    },
    [9] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB53C),
        .timer = 5
    },
    [10] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB54A),
        .timer = 5
    },
    [11] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB558),
        .timer = 5
    },
    [12] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB534),
        .timer = 30
    },
    [13] = FRAME_DATA_TERMINATOR,
    [14] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB574),
        .timer = 4
    },
    [15] = FRAME_DATA_TERMINATOR,
    [16] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB612),
        .timer = 4
    },
    [17] = FRAME_DATA_TERMINATOR,
    [18] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB6B0),
        .timer = 4
    },
    [19] = FRAME_DATA_TERMINATOR,
    [20] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xBD86),
        .timer = 8
    },
    [21] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xBE2A),
        .timer = 8
    },
    [22] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xBECE),
        .timer = 8
    },
    [23] = FRAME_DATA_TERMINATOR,
    [24] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xBF72),
        .timer = 8
    },
    [25] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC016),
        .timer = 8
    },
    [26] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC0BA),
        .timer = 8
    },
    [27] = FRAME_DATA_TERMINATOR,
    [28] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC15E),
        .timer = 8
    },
    [29] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC202),
        .timer = 8
    },
    [30] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC2A6),
        .timer = 8
    },
    [31] = FRAME_DATA_TERMINATOR,
    [32] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB79A),
        .timer = 8
    },
    [33] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB7A2),
        .timer = 8
    },
    [34] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB7AA),
        .timer = 8
    },
    [35] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB7A2),
        .timer = 4
    },
    [36] = FRAME_DATA_TERMINATOR,
    [37] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB7B2),
        .timer = 4
    },
    [38] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB7BA),
        .timer = 4
    },
    [39] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB7B2),
        .timer = 4
    },
    [40] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xB7BA),
        .timer = 20
    },
    [41] = FRAME_DATA_TERMINATOR,
    [42] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC34A),
        .timer = 4
    },
    [43] = FRAME_DATA_TERMINATOR,
    [44] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC352),
        .timer = 4
    },
    [45] = FRAME_DATA_TERMINATOR,
    [46] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC360),
        .timer = 4
    },
    [47] = FRAME_DATA_TERMINATOR,
    [48] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC36E),
        .timer = 4
    },
    [49] = FRAME_DATA_TERMINATOR,
    [50] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC37C),
        .timer = 4
    },
    [51] = FRAME_DATA_TERMINATOR,
    [52] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC38A),
        .timer = 4
    },
    [53] = FRAME_DATA_TERMINATOR,
    [54] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC398),
        .timer = 4
    },
    [55] = FRAME_DATA_TERMINATOR,
    [56] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC3A6),
        .timer = 4
    },
    [57] = FRAME_DATA_TERMINATOR,
    [58] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC3B4),
        .timer = 4
    },
    [59] = FRAME_DATA_TERMINATOR,
    [60] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC3C8),
        .timer = 4
    },
    [61] = FRAME_DATA_TERMINATOR,
    [62] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC3DC),
        .timer = 4
    },
    [63] = FRAME_DATA_TERMINATOR,
    [64] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC3F0),
        .timer = 4
    },
    [65] = FRAME_DATA_TERMINATOR,
    [66] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC404),
        .timer = 4
    },
    [67] = FRAME_DATA_TERMINATOR,
    [68] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC418),
        .timer = 4
    },
    [69] = FRAME_DATA_TERMINATOR,
    [70] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC42C),
        .timer = 4
    },
    [71] = FRAME_DATA_TERMINATOR,
    [72] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC434),
        .timer = 4
    },
    [73] = FRAME_DATA_TERMINATOR,
    [74] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC448),
        .timer = 4
    },
    [75] = FRAME_DATA_TERMINATOR,
    [76] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC45C),
        .timer = 4
    },
    [77] = FRAME_DATA_TERMINATOR,
    [78] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC470),
        .timer = 4
    },
    [79] = FRAME_DATA_TERMINATOR,
    [80] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC484),
        .timer = 4
    },
    [81] = FRAME_DATA_TERMINATOR,
    [82] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC498),
        .timer = 4
    },
    [83] = FRAME_DATA_TERMINATOR,
    [84] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC4AC),
        .timer = 4
    },
    [85] = FRAME_DATA_TERMINATOR,
    [86] = {
        .pFrame = (const u16*)((u8*)sBlob_73421e_prefix + 0xC4BA),
        .timer = 4
    },
    [87] = FRAME_DATA_TERMINATOR
};

static const u8 sBlob_73421e_after[0x6B98] = INCBIN_U8("data/Blob_73421e_after.bin");
