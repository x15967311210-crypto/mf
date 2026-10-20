#include "data/audio.h"
#include "gba.h"
#include "macros.h"

#include "audio.h"
#include "audio/track_internal.h"

#include "constants/audio_engine.h"

const u16 sUnk_a5278[128] = {
    0x2c, 0x9d, 0x107, 0x16b, 0x1ca, 0x223, 0x277, 0x2c7, 0x312, 0x358, 0x39b, 0x3da, 0x2c, 0x9d, 0x107, 0x16b,
    0x1ca, 0x223, 0x277, 0x2c7, 0x312, 0x358, 0x39b, 0x3da, 0x2c, 0x9d, 0x107, 0x16b, 0x1ca, 0x223, 0x277, 0x2c7,
    0x312, 0x358, 0x39b, 0x3da, 0x2c, 0x9d, 0x107, 0x16b, 0x1ca, 0x223, 0x277, 0x2c7, 0x312, 0x358, 0x39b, 0x3da,
    0x416, 0x44e, 0x483, 0x4b6, 0x4e5, 0x511, 0x53c, 0x563, 0x589, 0x5ac, 0x5ce, 0x5ed, 0x60b, 0x627, 0x642, 0x65b,
    0x672, 0x689, 0x69e, 0x6b2, 0x6c4, 0x6d6, 0x6e7, 0x6f7, 0x706, 0x714, 0x721, 0x72d, 0x739, 0x744, 0x74f, 0x759,
    0x762, 0x76b, 0x773, 0x77b, 0x783, 0x789, 0x790, 0x797, 0x79d, 0x7a2, 0x7a7, 0x7ac, 0x7b1, 0x7b6, 0x7ba, 0x7be,
    0x7c1, 0x7c5, 0x7c8, 0x7cb, 0x7ce, 0x7d1, 0x7d4, 0x7d6, 0x7d9, 0x7db, 0x7dd, 0x7df, 0x7e1, 0x7e2, 0x7e4, 0x7e6,
    0x7e7, 0x7e9, 0x7ea, 0x7eb, 0x7ec, 0x7ed, 0x7ee, 0x7ef, 0x7f0, 0x7f1, 0x7f2, 0x7f3, 0x7f4, 0x7f4, 0x7f5, 0x7f6
};

const u8 sClockTable[49] = {
    0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x1c, 0x1e, 0x20, 0x24, 0x28, 0x2a, 0x2c,
    0x30, 0x34, 0x36, 0x38, 0x3c, 0x40, 0x42, 0x44, 0x48, 0x4c, 0x4e, 0x50, 0x54, 0x58, 0x5a, 0x5c,
    0x60
};

const u8 sNoiseTable[60] = {
    0xd7, 0xd6, 0xd5, 0xd4, 0xc7, 0xc6, 0xc5, 0xc4, 0xb7, 0xb6, 0xb5, 0xb4, 0xa7, 0xa6, 0xa5, 0xa4, 0x97, 0x96, 0x95, 0x94,
    0x87, 0x86, 0x85, 0x84, 0x77, 0x76, 0x75, 0x74, 0x67, 0x66, 0x65, 0x64, 0x57, 0x56, 0x55, 0x54, 0x47, 0x46, 0x45, 0x44,
    0x37, 0x36, 0x35, 0x34, 0x27, 0x26, 0x25, 0x24, 0x17, 0x16, 0x15, 0x14, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00
};

const u8 sCgb3Vol[16] = {
    0x0, 0x0,
    0x60, 0x60, 0x60, 0x60,
    0x40, 0x40, 0x40, 0x40,
    0x80, 0x80, 0x80, 0x80,
    0x20, 0x20
};

const u8 sUnk_a53f5[19] = {
    0x0, 0x20, 0x16, 0x10, 0xd, 0xb, 0xa, 0x8,
    0x8, 0xa, 0xb, 0xd, 0x10, 0x16, 0x20, 0x0,
    0x0, 0x0, 0x0,
};


const u32 sNativeSampleRate[SOUND_MODE_FREQ_END] = {
    0,
    SAMPLES_PER_SECOND(96), SAMPLES_PER_SECOND(132), SAMPLES_PER_SECOND(176),
    SAMPLES_PER_SECOND(224), SAMPLES_PER_SECOND(264), SAMPLES_PER_SECOND(304),
    SAMPLES_PER_SECOND(352), SAMPLES_PER_SECOND(448), SAMPLES_PER_SECOND(528),
    SAMPLES_PER_SECOND(608), SAMPLES_PER_SECOND(672), SAMPLES_PER_SECOND(704)
};

const u32 sMusicPitchData[SOUND_MODE_FREQ_END] = {
    0x0,
    0xB6DEB, 0x85002, 0x63C01,
    0x4E5FF, 0x42801, 0x39C02,
    0x31E00, 0x272FF, 0x21400,
    0x1CE01, 0x1A1FF, 0x18F00
};

const u16 sPcmSamplesPerVBlankTable[SOUND_MODE_FREQ_END] = {
    0,             // unk1          // unk2
    96, 132, 176,  // 6, 8.25, 11   // 16.00, 11.6363, 8.7272
    224, 264, 304, // 14, 16.5, 19  // 6.8571, 5.8181, 5.0526
    352, 448, 528, // 22, 28, 33    // 4.3636, 3.4286, 2.9090
    608, 672, 704, // 38, 42, 44    // 2.5263, 2.2857, 2.1818
};

const u8 sArray_a548a[512] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};

void* const sDma1ControlPointer = REG_DMA1_CNT;
const u32 sDma1ControlValue = C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_DEST_FIXED, 4);
static const u16 sAudio_a5694 = DMA_ENABLE | DMA_START_SPECIAL | DMA_REPEAT | DMA_32BIT;
static const u16 sAudio_a5696 = DMA_ENABLE | DMA_INTR_ENABLE | DMA_START_SPECIAL | DMA_REPEAT | DMA_32BIT;

const MusicFunc_T sMusicCommandFunctionPointers[30] = {
    [FINE - FINE] = Music_EmptyCommand,
    [GOTO - FINE] = (MusicFunc_T)unk_4a3c, // AudioCommand_Goto
    [PATT - FINE] = (MusicFunc_T)unk_4a7c, // AudioCommand_PatternPlay
    [PEND - FINE] = AudioCommand_PatternEnd,
    [REPT - FINE] = AudioCommand_Repeat,
    [5] = Music_EmptyCommand,
    [6] = Music_EmptyCommand,
    [7] = Music_EmptyCommand,
    [MEMACC - FINE] = Music_EmptyCommand,
    [PRIO - FINE] = AudioCommand_Priority,
    [TEMPO - FINE] = Music_EmptyCommand,
    [KEYSH - FINE] = AudioCommand_KeyShift,
    [VOICE - FINE] = Music_EmptyCommand,
    [VOL - FINE] = AudioCommand_Volume,
    [PAN - FINE] = AudioCommand_PanPot,
    [BEND - FINE] = AudioCommand_PitchBend,
    [BENDR - FINE] = AudioCommand_BendRange,
    [LFOS - FINE] = AudioCommand_LfoSpeed,
    [LFODL - FINE] = AudioCommand_LfoDelay,
    [MOD - FINE] = AudioCommand_ModulationDepth,
    [MODT - FINE] = AudioCommand_ModulationType,
    [21] = Music_EmptyCommand,
    [22] = Music_EmptyCommand,
    [TUNE - FINE] = AudioCommand_Tune,
    [24] = Music_EmptyCommand,
    [25] = Music_EmptyCommand,
    [26] = Music_EmptyCommand,
    [27] = Music_EmptyCommand,
    [XCMD - FINE] = AudioCommand_ExtendCommand,
    [EOT - FINE] = AudioCommand_EndOfTie
};

/* BEGIN GENERATED by tools/shift/gen_blob_tables.py: sBlob_a5710_a8cdc */
extern const u8 DirectSoundData_080AA488[];
extern const u8 DirectSoundData_080AA84C[];
extern const u8 DirectSoundData_080AA9B0[];
extern const u8 DirectSoundData_080AB22C[];
extern const u8 DirectSoundData_080ABA4C[];
extern const u8 DirectSoundData_080AC340[];
extern const u8 DirectSoundData_080ACA18[];
extern const u8 DirectSoundData_080AD784[];
extern const u8 DirectSoundData_080AE354[];
extern const u8 DirectSoundData_080AEBD0[];
extern const u8 DirectSoundData_080AEE10[];
extern const u8 DirectSoundData_080AF6B8[];
extern const u8 DirectSoundData_080AFED0[];
extern const u8 DirectSoundData_080B0310[];
extern const u8 DirectSoundData_080B0E50[];
extern const u8 DirectSoundData_080B3148[];
extern const u8 DirectSoundData_080B3910[];
extern const u8 DirectSoundData_080B4520[];
extern const u8 DirectSoundData_080B51D0[];
extern const u8 DirectSoundData_080B5750[];
extern const u8 DirectSoundData_080B5BC8[];
extern const u8 DirectSoundData_080B60A4[];
extern const u8 DirectSoundData_080B6A84[];
extern const u8 DirectSoundData_080B7054[];
extern const u8 DirectSoundData_080B75BC[];
extern const u8 DirectSoundData_080B7A14[];
extern const u8 DirectSoundData_080B83C0[];
extern const u8 DirectSoundData_080B8B88[];
extern const u8 DirectSoundData_080BA2C0[];
extern const u8 DirectSoundData_080BA964[];
extern const u8 DirectSoundData_080BBB78[];
extern const u8 DirectSoundData_080BD1B0[];
extern const u8 DirectSoundData_080BDB48[];
extern const u8 DirectSoundData_080BE5B8[];
extern const u8 DirectSoundData_080BF78C[];
extern const u8 DirectSoundData_080C857C[];
extern const u8 DirectSoundData_080C9288[];
extern const u8 DirectSoundData_080C9BE4[];
extern const u8 DirectSoundData_080CA0BC[];
extern const u8 DirectSoundData_080CACAC[];
extern const u8 DirectSoundData_080CCD9C[];
extern const u8 DirectSoundData_080CEE3C[];
extern const u8 DirectSoundData_080CF140[];
extern const u8 DirectSoundData_080D05B8[];
extern const u8 DirectSoundData_080D0BF4[];
extern const u8 DirectSoundData_080D1414[];
extern const u8 DirectSoundData_080D1CB4[];
extern const u8 DirectSoundData_080D1F1C[];
extern const u8 DirectSoundData_080D2924[];
extern const u8 DirectSoundData_080D3598[];
extern const u8 DirectSoundData_080D3694[];
extern const u8 DirectSoundData_080D4204[];
extern const u8 DirectSoundData_080D468C[];
extern const u8 DirectSoundData_080D4CB4[];
extern const u8 DirectSoundData_080D5304[];
extern const u8 DirectSoundData_080D55D0[];
extern const u8 DirectSoundData_080D5A40[];
extern const u8 DirectSoundData_080D5BB8[];
extern const u8 DirectSoundData_080D5E5C[];
extern const u8 DirectSoundData_080D5ECC[];
extern const u8 DirectSoundData_080D73C8[];
extern const u8 DirectSoundData_080D767C[];
extern const u8 DirectSoundData_080D8528[];
extern const u8 DirectSoundData_080DABEC[];
extern const u8 DirectSoundData_080DCB7C[];
extern const u8 DirectSoundData_080E1DAC[];
extern const u8 DirectSoundData_080E45AC[];
extern const u8 DirectSoundData_080E6FBC[];
extern const u8 DirectSoundData_080E7880[];
extern const u8 DirectSoundData_080E84E8[];
extern const u8 DirectSoundData_080EA434[];
extern const u8 DirectSoundData_080EA74C[];
extern const u8 DirectSoundData_080EADF4[];
extern const u8 DirectSoundData_080EBEFC[];
extern const u8 DirectSoundData_080ED67C[];
extern const u8 DirectSoundData_080EDB54[];
extern const u8 DirectSoundData_080EE514[];
extern const u8 DirectSoundData_080EF02C[];
extern const u8 DirectSoundData_080EF660[];
extern const u8 DirectSoundData_080F0CB0[];
extern const u8 DirectSoundData_080F32C8[];
extern const u8 DirectSoundData_080F3AFC[];
extern const u8 DirectSoundData_080F4548[];
extern const u8 DirectSoundData_080F5F80[];
extern const u8 DirectSoundData_080F6FF0[];
extern const u8 DirectSoundData_080F79E0[];
extern const u8 DirectSoundData_080F9A28[];
extern const u8 DirectSoundData_08119D40[];
extern const u8 DirectSoundData_0811A384[];
extern const u8 DirectSoundData_0811A4B4[];
extern const u8 DirectSoundData_0811A6B8[];
extern const u8 DirectSoundData_0811AB98[];
extern const u8 DirectSoundData_0811ACB0[];
extern const u8 DirectSoundData_0811AE5C[];
extern const u8 DirectSoundData_0811B124[];
extern const u8 DirectSoundData_0811B3A4[];
extern const u8 DirectSoundData_0811B760[];
extern const u8 DirectSoundData_0811B8B0[];
extern const u8 DirectSoundData_0811BB74[];
extern const u8 DirectSoundData_0811BF4C[];
extern const u8 DirectSoundData_0811C188[];
extern const u8 DirectSoundData_0811C3E0[];
extern const u8 DirectSoundData_0811C930[];
extern const u8 DirectSoundData_0811CBA8[];
extern const u8 DirectSoundData_0811D098[];
extern const u8 DirectSoundData_0811D960[];
extern const u8 DirectSoundData_0811E1BC[];
extern const u8 DirectSoundData_0811EA04[];
extern const u8 DirectSoundData_0811EE04[];
extern const u8 DirectSoundData_0811F228[];
extern const u8 DirectSoundData_0811F868[];
extern const u8 DirectSoundData_0811FA88[];
extern const u8 DirectSoundData_0811FE08[];
extern const u8 DirectSoundData_08120188[];
extern const u8 DirectSoundData_08120508[];
extern const u8 DirectSoundData_08120888[];
extern const u8 DirectSoundData_08120C08[];
extern const u8 DirectSoundData_08120F88[];
extern const u8 DirectSoundData_081220C8[];
extern const u8 DirectSoundData_081225A8[];
extern const u8 DirectSoundData_08123394[];
extern const u8 DirectSoundData_08123CA0[];
extern const u8 DirectSoundData_08124188[];
extern const u8 DirectSoundData_0812466C[];
extern const u8 DirectSoundData_08124BFC[];
extern const u8 DirectSoundData_081250B0[];
extern const u8 DirectSoundData_08125B24[];
extern const u8 DirectSoundData_08126574[];
extern const u8 DirectSoundData_08126E38[];
extern const u8 DirectSoundData_08127B24[];
extern const u8 DirectSoundData_08128634[];
extern const u8 DirectSoundData_08128C80[];
extern const u8 DirectSoundData_08128D40[];
extern const u8 DirectSoundData_0812A328[];
extern const u8 DirectSoundData_0812B1C0[];
extern const u8 DirectSoundData_0812B614[];
extern const u8 DirectSoundData_0812BF0C[];
extern const u8 DirectSoundData_0812C4F8[];
extern const u8 DirectSoundData_0812C6D4[];
extern const u8 DirectSoundData_0812CCA8[];
extern const u8 DirectSoundData_0812CE14[];
extern const u8 DirectSoundData_0812D244[];
extern const u8 DirectSoundData_0812D674[];
extern const u8 DirectSoundData_0812DAA4[];
extern const u8 DirectSoundData_0812DE34[];
extern const u8 DirectSoundData_0812E540[];
extern const u8 DirectSoundData_0812E970[];
extern const u8 DirectSoundData_0812F11C[];
extern const u8 DirectSoundData_0812F8C4[];
extern const u8 DirectSoundData_0812FDDC[];
extern const u8 DirectSoundData_08130750[];
extern const u8 DirectSoundData_08131124[];
extern const u8 DirectSoundData_081314F8[];
extern const u8 DirectSoundData_081319E8[];
extern const u8 DirectSoundData_081324F8[];
extern const u8 DirectSoundData_081346B8[];
extern const u8 DirectSoundData_08137008[];
extern const u8 DirectSoundData_08139068[];
extern const u8 DirectSoundData_0813B7A8[];
extern const u8 DirectSoundData_0813D1D8[];
extern const u8 DirectSoundData_0813F868[];
extern const u8 DirectSoundData_0813FA88[];
extern const u8 DirectSoundData_0813FE08[];
extern const u8 DirectSoundData_08140188[];
extern const u8 DirectSoundData_08140458[];
extern const u8 DirectSoundData_08140728[];
extern const u8 DirectSoundData_081409F8[];
extern const u8 DirectSoundData_08140CC8[];
extern const u8 DirectSoundData_08141238[];
extern const u8 DirectSoundData_081415B8[];
extern const u8 DirectSoundData_08141A98[];
extern const u8 DirectSoundData_08142A78[];
extern const u8 DirectSoundData_08142DF8[];
extern const u8 DirectSoundData_08143C28[];
extern const u8 DirectSoundData_08143FCC[];
extern const u8 DirectSoundData_081441EC[];
extern const u8 DirectSoundData_0814439C[];
extern const u8 DirectSoundData_081448B0[];
extern const u8 DirectSoundData_08145230[];
extern const u8 DirectSoundData_081455D4[];
extern const u8 DirectSoundData_081459B0[];
extern const u8 DirectSoundData_08145DF0[];
extern const u8 DirectSoundData_08145F50[];
extern const u8 DirectSoundData_08146D20[];
extern const u8 DirectSoundData_08147DB0[];
extern const u8 DirectSoundData_08148B4C[];
extern const u8 DirectSoundData_0814A838[];
extern const u8 DirectSoundData_0814B818[];
extern const u8 DirectSoundData_0814C7F8[];
extern const u8 DirectSoundData_0814D468[];
extern const u8 DirectSoundData_0814D868[];
extern const u8 DirectSoundData_0814DEA8[];
extern const u8 DirectSoundData_0814E270[];
extern const u8 DirectSoundData_0814E890[];
extern const u8 DirectSoundData_0814EF74[];
extern const u8 DirectSoundData_0814F4D4[];
extern const u8 DirectSoundData_0814F72C[];
extern const u8 DirectSoundData_0814F958[];
extern const u8 DirectSoundData_0814FD38[];
extern const u8 DirectSoundData_081502D4[];
extern const u8 DirectSoundData_081506AC[];
extern const u8 DirectSoundData_08150A2C[];
extern const u8 DirectSoundData_08150CFC[];
extern const u8 DirectSoundData_081510BC[];
extern const u8 DirectSoundData_0815129C[];
extern const u8 DirectSoundData_081516CC[];
extern const u8 DirectSoundData_081520D4[];
extern const u8 DirectSoundData_081523A4[];
extern const u8 DirectSoundData_08152FB0[];
extern const u8 DirectSoundData_08153B50[];
extern const u8 DirectSoundData_08153CC0[];
extern const u8 DirectSoundData_08154528[];
extern const u8 DirectSoundData_08155038[];
extern const u8 DirectSoundData_08155B48[];
extern const u8 DirectSoundData_08155E18[];
extern const u8 DirectSoundData_081560E8[];
extern const u8 DirectSoundData_081563B8[];
extern const u8 DirectSoundData_08156688[];
extern const u8 DirectSoundData_08157928[];
extern const u8 DirectSoundData_08157BF8[];
extern const u8 DirectSoundData_08158790[];
extern const u8 DirectSoundData_081590A4[];
extern const u8 DirectSoundData_0815A974[];
extern const u8 DirectSoundData_0815B2B4[];
extern const u8 DirectSoundData_0815B844[];
extern const u8 DirectSoundData_0815D064[];
extern const u8 DirectSoundData_0815E514[];
extern const u8 DirectSoundData_0815F5A4[];
extern const u8 DirectSoundData_0815FD84[];
extern const u8 DirectSoundData_0815FFA4[];
extern const u8 DirectSoundData_08160730[];
extern const u8 DirectSoundData_08161A48[];
extern const u8 DirectSoundData_08162228[];
extern const u8 DirectSoundData_081644C8[];
extern const u8 DirectSoundData_0816602C[];
extern const u8 DirectSoundData_08167BBC[];
extern const u8 DirectSoundData_08168D90[];
extern const u8 DirectSoundData_0816ABE0[];
extern const u8 DirectSoundData_0816C350[];
extern const u8 DirectSoundData_0816E250[];
extern const u8 DirectSoundData_0816F428[];
extern const u8 DirectSoundData_081706C8[];
extern const u8 DirectSoundData_081721A8[];
extern const u8 DirectSoundData_08175F98[];
extern const u8 DirectSoundData_08176DB8[];
extern const u8 DirectSoundData_08177558[];
extern const u8 DirectSoundData_08177A38[];
extern const u8 DirectSoundData_081783A8[];
extern const u8 DirectSoundData_08178D10[];
extern const u8 DirectSoundData_08179738[];
extern const u8 DirectSoundData_0817A198[];
extern const u8 DirectSoundData_0817B310[];
extern const u8 DirectSoundData_0817DE70[];
extern const u8 DirectSoundData_0817EFB0[];
extern const u8 DirectSoundData_08180460[];
extern const u8 DirectSoundData_081830F8[];
extern const u8 DirectSoundData_08186F98[];
extern const u8 DirectSoundData_08187B14[];
extern const u8 DirectSoundData_08188BD0[];
extern const u8 DirectSoundData_081899A0[];
extern const u8 DirectSoundData_0818B530[];
extern const u8 DirectSoundData_0818C930[];
extern const u8 DirectSoundData_0818D9C0[];
extern const u8 DirectSoundData_0818E8F0[];
extern const u8 DirectSoundData_0818F980[];
extern const u8 DirectSoundData_0818FCEC[];
extern const u8 DirectSoundData_0819029C[];
extern const u8 DirectSoundData_08190488[];
extern const u8 DirectSoundData_08190AB4[];
extern const u8 DirectSoundData_08190D18[];
extern const u8 DirectSoundData_081913E0[];
extern const u8 DirectSoundData_081919E0[];
extern const u8 DirectSoundData_08192424[];
extern const u8 DirectSoundData_081937EC[];
extern const u8 DirectSoundData_08193EC4[];
extern const u8 DirectSoundData_0819496C[];
extern const u8 DirectSoundData_08194FD8[];
extern const u8 DirectSoundData_08195670[];
extern const u8 DirectSoundData_08195EBC[];
extern const u8 DirectSoundData_08196984[];
extern const u8 DirectSoundData_08197268[];
extern const u8 DirectSoundData_08197CC0[];
extern const u8 DirectSoundData_08197E88[];
extern const u8 DirectSoundData_08198684[];
extern const u8 DirectSoundData_08199414[];
extern const u8 DirectSoundData_0819A0B0[];
extern const u8 DirectSoundData_0819C754[];
extern const u8 DirectSoundData_0819CAF0[];
extern const u8 DirectSoundData_0819D3C8[];
extern const u8 DirectSoundData_0819DAC0[];
extern const u8 DirectSoundData_0819E524[];
extern const u8 DirectSoundData_0819E958[];
extern const u8 DirectSoundData_0819EE6C[];
extern const u8 DirectSoundData_0819FEBC[];
extern const u8 DirectSoundData_081A064C[];
extern const u8 DirectSoundData_081A23FC[];
extern const u8 DirectSoundData_081A28F8[];
extern const u8 DirectSoundData_081A2DF4[];
extern const u8 DirectSoundData_081A32F0[];
extern const u8 DirectSoundData_081A37EC[];
extern const u8 DirectSoundData_081A43D0[];
extern const u8 DirectSoundData_081A4AC0[];
extern const u8 DirectSoundData_081A5090[];
extern const u8 DirectSoundData_081A5434[];
extern const u8 DirectSoundData_081A5E40[];
extern const u8 DirectSoundData_081A6AFC[];
extern const u8 DirectSoundData_081AB0B0[];
extern const u8 DirectSoundData_081AB320[];
extern const u8 DirectSoundData_081ABA98[];
extern const u8 DirectSoundData_081AD364[];
extern const u8 DirectSoundData_081AEF28[];
extern const u8 DirectSoundData_081B0958[];
extern const u8 DirectSoundData_081B0FCC[];
extern const u8 DirectSoundData_081B17A0[];
extern const u8 DirectSoundData_081B1DA4[];
extern const u8 DirectSoundData_081B28E0[];
extern const u8 DirectSoundData_081B5230[];
extern const u8 DirectSoundData_081B7E84[];
extern const u8 DirectSoundData_081B808C[];
extern const u8 DirectSoundData_081B8548[];
extern const u8 DirectSoundData_081B87F4[];
extern const u8 DirectSoundData_081B8FDC[];
extern const u8 DirectSoundData_081BB0CC[];
extern const u8 DirectSoundData_081BB470[];
extern const u8 DirectSoundData_081BE070[];
extern const u8 DirectSoundData_081BE190[];
extern const u8 DirectSoundData_081BEB4C[];
extern const u8 DirectSoundData_081BF2E8[];
extern const u8 DirectSoundData_081BF9A8[];
extern const u8 DirectSoundData_081BFC48[];
extern const u8 DirectSoundData_081BFFB8[];
extern const u8 DirectSoundData_081C07F8[];
extern const u8 DirectSoundData_081C1120[];
extern const u8 DirectSoundData_081C12E8[];
extern const u8 DirectSoundData_081C166C[];
extern const u8 DirectSoundData_081C1B40[];
extern const u8 DirectSoundData_081C258C[];
extern const u8 DirectSoundData_081C3004[];
extern const u8 DirectSoundData_081C3704[];
extern const u8 DirectSoundData_081C3E08[];
extern const u8 DirectSoundData_081C4714[];
extern const u8 DirectSoundData_081C490C[];
extern const u8 DirectSoundData_081C4E74[];
extern const u8 DirectSoundData_081C6480[];
extern const u8 DirectSoundData_081C781C[];
extern const u8 DirectSoundData_081CDC5C[];
extern const u8 DirectSoundData_081D2ECC[];
extern const u8 DirectSoundData_081D387C[];
extern const u8 DirectSoundData_081D43A0[];
extern const u8 DirectSoundData_081D5D58[];
extern const u8 DirectSoundData_081D7994[];
extern const u8 DirectSoundData_081E06F4[];
extern const u8 DirectSoundData_081E17E4[];
extern const u8 DirectSoundData_081E3114[];
extern const u8 DirectSoundData_081E37C8[];
extern const u8 DirectSoundData_081E4238[];
extern const u8 DirectSoundData_081E6620[];
extern const u8 DirectSoundData_081E70F8[];
extern const u8 DirectSoundData_081ECDBC[];
extern const u8 DirectSoundData_081EF770[];
extern const u8 DirectSoundData_081F1F3C[];
extern const u8 DirectSoundData_081F43A0[];
extern const u8 DirectSoundData_081F6830[];
extern const u8 DirectSoundData_081F8B80[];
extern const u8 DirectSoundData_081FB34C[];
extern const u8 DirectSoundData_081FDB98[];
extern const u8 DirectSoundData_0820037C[];
extern const u8 DirectSoundData_082027B8[];
extern const u8 DirectSoundData_08204F48[];
extern const u8 DirectSoundData_08207CD8[];
extern const u8 DirectSoundData_0820A158[];
extern const u8 DirectSoundData_0820C53C[];
extern const u8 DirectSoundData_0820E5D8[];
extern const u8 DirectSoundData_0821073C[];
extern const u8 DirectSoundData_08212B70[];
extern const u8 DirectSoundData_08215298[];
extern const u8 DirectSoundData_0821E0EC[];
extern const u8 DirectSoundData_08228B64[];
extern const u8 DirectSoundData_0822DF60[];
extern const u8 DirectSoundData_08234300[];
extern const u8 DirectSoundData_08236BE0[];
extern const u8 DirectSoundData_0823C1F8[];
extern const u8 DirectSoundData_0823FACC[];
extern const u8 DirectSoundData_082438E4[];
extern const u8 DirectSoundData_082466E0[];

struct Blob_a5710_a8cdcVoice {
    u8 instrumentType;
    u8 pitch;
    u8 unk_2;
    u8 unk_3;
    const u32* pSample;
    const u32* envelope;
};

struct Blob_a5710_a8cdc {
    struct Blob_a5710_a8cdcVoice records[1135];
    u8 tail[152];
};

static const struct Blob_a5710_a8cdc sBlob_a5710_a8cdc = {
    {
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AA488), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AA84C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AA9B0), (const u32*)0xA5B4A5FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AB22C), (const u32*)0xFF00FF },
        { 0x0, 0x35, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ABA4C), (const u32*)0xE855E8FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AC340), (const u32*)0xFF00FF },
        { 0x0, 0x38, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ABA4C), (const u32*)0xE855E8FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3A, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ABA4C), (const u32*)0xE855E8FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ACA18), (const u32*)0xCC0CFAFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ABA4C), (const u32*)0xE855E8FF },
        { 0x0, 0x3D, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ABA4C), (const u32*)0xE855E8FF },
        { 0x0, 0x36, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AD784), (const u32*)0xF24DF9FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AE354), (const u32*)0xA54DC3FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AD784), (const u32*)0xF24DE2FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x5A, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AD784), (const u32*)0x7F80D8FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AEBD0), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ACA18), (const u32*)0xCC19F6FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AC340), (const u32*)0x1900FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AEE10), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AF6B8), (const u32*)0xCFAFF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AFED0), (const u32*)0xBC00BCFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3148), (const u32*)0xF280F9FF },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x4040400 },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x4040400 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x1040200 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0xF0000 },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x6060600 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3910), (const u32*)0xF9B4F925 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3910), (const u32*)0xA59AC3FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B4520), (const u32*)0xA54DC3FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x6060600 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B51D0), (const u32*)0xE24DE2FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B5750), (const u32*)0xE24DE2FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B5BC8), (const u32*)0xE24DE2FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B60A4), (const u32*)0xE24DE2FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B6A84), (const u32*)0xE24DE2FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x60D0602 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B7054), (const u32*)0xF24DBC40 },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x1050200 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xBC4DF9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3910), (const u32*)0xF9B4F925 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B75BC), (const u32*)0xE24DE2FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[14]), (const u32*)0x0 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B7A14), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xF2B4FC1A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xF24DE2FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xBC4DF9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xF2B4FC1A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3910), (const u32*)0xF9B4F925 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B83C0), (const u32*)0xFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BD1B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA2C0), (const u32*)0x7FFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA964), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xFF0013 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BBB78), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BD1B0), (const u32*)0xA580FCFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BDB48), (const u32*)0xDA7BFE0F },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x5090300 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BE5B8), (const u32*)0xFF0008 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BF78C), (const u32*)0xFF0008 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080C857C), (const u32*)0xFD33F208 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B75BC), (const u32*)0xE24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080C9288), (const u32*)0xF24DE2FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x1040200 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080C9BE4), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CA0BC), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B83C0), (const u32*)0xFF0040 },
        { 0x40, 0x0, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[126]), (const u32*)((u32)&sBlob_a5710_a8cdc.records[1132]) },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xFF0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0x7FFF0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CACAC), (const u32*)0xF24DFD0A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CACAC), (const u32*)0xFFF225 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0502 },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x1030600 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xBC4DF9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ABA4C), (const u32*)0xE855E8FF },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x6050606 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x6050605 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B6A84), (const u32*)0xE24DE2FF },
        { 0x0, 0x37, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AA84C), (const u32*)0xFF00FF },
        { 0x0, 0x4A, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AE354), (const u32*)0xA54DC3FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[113]), (const u32*)0x0 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x7010600 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CCD9C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CEE3C), (const u32*)0xF919F913 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CEE3C), (const u32*)0xF24DE2FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x1040200 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x1040200 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CF140), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BBB78), (const u32*)0xF9FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CF140), (const u32*)0xEB4DEBFF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xA54DC3FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D05B8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D0BF4), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D1414), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D1CB4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D1F1C), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D2924), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3598), (const u32*)0xA5FF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3598), (const u32*)0xBCFF0080 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3694), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D4204), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3694), (const u32*)0xC3E7C355 },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[163]), (const u32*)0x0 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D468C), (const u32*)0xFF00FF },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0xF0000 },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D4CB4), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5304), (const u32*)0xA54DC340 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D55D0), (const u32*)0x73FF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5A40), (const u32*)0x73FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5BB8), (const u32*)0x73FF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D4204), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D767C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D8528), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080DABEC), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5E5C), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5ECC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D73C8), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xF9CEF933 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080DCB7C), (const u32*)0xA5FF0040 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080E1DAC), (const u32*)0x7FFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080E45AC), (const u32*)0x7FFF00FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080E6FBC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080E7880), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EBEFC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080E84E8), (const u32*)0xF980FDFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080E84E8), (const u32*)0xF980FD08 },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[170]), (const u32*)0x0 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EA434), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3910), (const u32*)0xA54DC3FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ED67C), (const u32*)0x7FFF0080 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xBC4DF9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EA74C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EADF4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xFF0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BDB48), (const u32*)0xDA7BFE0F },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EDB54), (const u32*)0xF29A00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xF29A0008 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EE514), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EF02C), (const u32*)0xA5FF00FF },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x90100 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EF660), (const u32*)0xFF0025 },
        { 0xB, 0x3C, 0x0, 0x0, (const u32*)((u32)(u8*)&sBlob_a5710_a8cdc+0x359C), (const u32*)0x10F0001 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F0CB0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EDB54), (const u32*)0xF29A0008 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xBC4DF9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA964), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080EA434), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA964), (const u32*)0x7F3395FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x1040200 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F32C8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F3AFC), (const u32*)0xFF00FF },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x6090600 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA2C0), (const u32*)0x7FFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xA54DC3FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xA54DC3FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xE2B4F9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xF2B4FC1A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xA5FFA5FF },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x90100 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080C9BE4), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CA0BC), (const u32*)0xF24DE2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B83C0), (const u32*)0xFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xFF00FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0xA, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D468C), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xD8FF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x2070200 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA964), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xBC4DF9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xF980F9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3598), (const u32*)0xF94DF2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F4548), (const u32*)0xD819F9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BDB48), (const u32*)0xDA7BFE0F },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ACA18), (const u32*)0xEB0CFAFF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F5F80), (const u32*)0xE24DE2FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F6FF0), (const u32*)0xF94DC3FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3910), (const u32*)0xD84DC3FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xA5FF7F40 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x6070600 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080DABEC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D8528), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B83C0), (const u32*)0xFDCEFD40 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F79E0), (const u32*)0x7FFF0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xF2CEFDFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CACAC), (const u32*)0xA5FF7FFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5ECC), (const u32*)0xFD19FDFF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F79E0), (const u32*)0xFF0033 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0x7FFF0040 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0x7FFF0008 },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)sArray_a548a+0xD6), (const u32*)0x0 },
        { 0x9, 0x3C, 0x0, 0x0, (const u32*)0x3, (const u32*)0x1040200 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xBC4DF9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA2C0), (const u32*)0x7FFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xF2B4FC1A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B3910), (const u32*)0xF9B4F925 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xF2B4F2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xEB9AFCFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xBCB4FC25 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xBCB4FC40 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xE2B4E2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xD8CED8FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D2924), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3598), (const u32*)0xD8FF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080CACAC), (const u32*)0xD8FF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0xF980F9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F4548), (const u32*)0xD819F9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080BA964), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xD8FF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080F9A28), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08119D40), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811A384), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811A4B4), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811A6B8), (const u32*)0xB400FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811AB98), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811ACB0), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811ACB0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811AE5C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811B124), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811A384), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811AB98), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811B3A4), (const u32*)0xEBFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811B760), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811B8B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811BB74), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811BF4C), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811C188), (const u32*)0xE70025 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811C3E0), (const u32*)0x800013 },
        { 0x3, 0x3C, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[1145]), (const u32*)0xF0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x60A0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811C930), (const u32*)0xBCCE00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811C930), (const u32*)0xADFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D098), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D098), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D960), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EA04), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xE2FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xD8FF0040 },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F228), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F868), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FA88), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FE08), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120188), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120508), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120888), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120C08), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120F88), (const u32*)0xB40040 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081220C8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCCCE0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08123394), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xCCFF0025 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08123CA0), (const u32*)0xB40025 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08124188), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xA580000D },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812466C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08124BFC), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xCE0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08125B24), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126574), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126E38), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F228), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08127B24), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128C80), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812A328), (const u32*)0x7FB400FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B1C0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811BB74), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B614), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xFF0040 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812C4F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xA5CE00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x60A0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xA0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812C6D4), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812CCA8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812CE14), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812D244), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812D674), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812DAA4), (const u32*)0xE2FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812DE34), (const u32*)0xE2FF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E540), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xE2CE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812F11C), (const u32*)0xD8FF00FF },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812F8C4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812FDDC), (const u32*)0x673CFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812FDDC), (const u32*)0xCC673CFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812FDDC), (const u32*)0x7F803CFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E540), (const u32*)0xFF000B },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E540), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xCE0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812F11C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812DAA4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812DE34), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812FDDC), (const u32*)0xE73CFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E540), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08131124), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081314F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081319E8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126574), (const u32*)0xD8FF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081324F8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081346B8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08137008), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08139068), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813B7A8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813D1D8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F868), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FA88), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FE08), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120188), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120508), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813F868), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813FA88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813FE08), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120888), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120C08), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F868), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FA88), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FE08), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120188), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120508), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120888), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120C08), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x20F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140CC8), (const u32*)0xE2FF000A },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08141238), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081415B8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08141A98), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08142A78), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08142DF8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08143C28), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08143FCC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811C3E0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B614), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08141238), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811A6B8), (const u32*)0xB400FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812F8C4), (const u32*)0xA5FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xD8FF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081441EC), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811AB98), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814439C), (const u32*)0xE7000F },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081448B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F868), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FA88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FE08), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120188), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120508), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081220C8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145230), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081455D4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F228), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xF400FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF0080 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50D0001 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140CC8), (const u32*)0xFF000D },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814439C), (const u32*)0xF2FF000F },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08123CA0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814439C), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xE70040 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x30F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081459B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811BB74), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145DF0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145F50), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08146D20), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x30F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08147DB0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081220C8), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F228), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08148B4C), (const u32*)0xF40080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812FDDC), (const u32*)0xE73C40 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814A838), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814A838), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814B818), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814C7F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814D468), (const u32*)0xB4A50B },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814D868), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814D868), (const u32*)0xFF0080 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814DEA8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814E270), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814DEA8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814E890), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811BB74), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814EF74), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xCCFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xD8CE0025 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081441EC), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814F4D4), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D960), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B614), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812F8C4), (const u32*)0xA5FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D960), (const u32*)0xD8FF0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xD8E700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814F72C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811AB98), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814F958), (const u32*)0xE70080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D960), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xD8FF00FF },
        { 0x3, 0x3C, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[1145]), (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814F958), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812F8C4), (const u32*)0xE2CE001A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814FD38), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D960), (const u32*)0xEBCE000F },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081502D4), (const u32*)0xEBCE000F },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081506AC), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081459B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08150A2C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081455D4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08150CFC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B1C0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081510BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815129C), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081516CC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081520D4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081523A4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128C80), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08152FB0), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814439C), (const u32*)0xE7000F },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08153B50), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08153CC0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08154528), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08155038), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120F88), (const u32*)0xB40040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08155B48), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08155E18), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081560E8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081563B8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08155B48), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08155E18), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081563B8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08156688), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08157928), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F228), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F228), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E540), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812D244), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812D674), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812D674), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08157BF8), (const u32*)0xD8FF0033 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08158790), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x20F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCCCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCCCE0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08142DF8), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140CC8), (const u32*)0xE2CE000A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811BB74), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814439C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812CCA8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812C6D4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140CC8), (const u32*)0xE2FF000A },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081590A4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815A974), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815A974), (const u32*)0xFF0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812A328), (const u32*)0x7FB400FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B1C0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811AE5C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xA5CE00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B614), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812FDDC), (const u32*)0xE73CFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815B2B4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xFF00FF },
        { 0x3, 0x3C, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[1145]), (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xFF0040 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812C4F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xE2CE00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815B844), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815D064), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5E5C), (const u32*)0x7FCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5E5C), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xCCCE0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128C80), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xA5CE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815E514), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815F5A4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815A974), (const u32*)0xFF0033 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081441EC), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814F4D4), (const u32*)0xE700FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128C80), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815FD84), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081459B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08150A2C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814E890), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08142DF8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814D468), (const u32*)0xB4A5FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815FFA4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140CC8), (const u32*)0xFF000D },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145F50), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140CC8), (const u32*)0xFF000A },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F868), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FA88), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811FE08), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120188), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120508), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813F868), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813FA88), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0813FE08), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120888), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120C08), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815E514), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08160730), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x60A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08161A48), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08120F88), (const u32*)0xB40040 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811C3E0), (const u32*)0x800013 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08162228), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081644C8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08150CFC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xFF0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811EE04), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D960), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081502D4), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0816602C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126574), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08167BBC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815F5A4), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815D064), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08168D90), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0816ABE0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0816C350), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0816E250), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815E514), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08161A48), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815FFA4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814EF74), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811AE5C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812B1C0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812A328), (const u32*)0x7FB400FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0x7FB400FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xA5CE00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF0080 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50D0001 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x20F0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0816F428), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081706C8), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081721A8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCCCE0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08147DB0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08175F98), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08176DB8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08177558), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145230), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08177A38), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145230), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145DF0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081783A8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xA5CE00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x60A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081220C8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081721A8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCCCE0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xE700FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D098), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xD8FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811D098), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08178D10), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x60A0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815F5A4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08153CC0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCE0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145230), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08179738), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08176DB8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08177558), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812DAA4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812C6D4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x20F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081225A8), (const u32*)0xCE0080 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xB400FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08146D20), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x30F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0817A198), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0817B310), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0817B310), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0817DE70), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081448B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0817EFB0), (const u32*)0xF40040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812BF0C), (const u32*)0xA5CE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140188), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140458), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081409F8), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50F0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x60A0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814439C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08180460), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08180460), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081830F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08186F98), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081220C8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0815F5A4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126574), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126E38), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126574), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08187B14), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0816602C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814A838), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814A838), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140CC8), (const u32*)0xFF000D },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08180460), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08180460), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08188BD0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0812E970), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08125B24), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08157BF8), (const u32*)0xDA00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50D0001 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811F228), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08125B24), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081830F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128634), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811E1BC), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081899A0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0817EFB0), (const u32*)0xF40040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0818B530), (const u32*)0xE70040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145F50), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08157BF8), (const u32*)0xDA00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50D0001 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x50D0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08140728), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811CBA8), (const u32*)0xFF00FF },
        { 0x20, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08130750), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0811A6B8), (const u32*)0xB400FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x60A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0818C930), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08186F98), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08145230), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08128D40), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0814C7F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0818D9C0), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x40A0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08167BBC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126574), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08126E38), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08187B14), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081250B0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0818E8F0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0818F980), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0818FCEC), (const u32*)0xCE00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819029C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08190488), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08190AB4), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08190D18), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081913E0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081919E0), (const u32*)0xFF00FF },
        { 0x8, 0x40, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08192424), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AA488), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AA84C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AEBD0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AA9B0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AB22C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ABA4C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AC340), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AD784), (const u32*)0xF740 },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AE354), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080ACA18), (const u32*)0x52F7FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080AEE10), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x8, 0x3C, 0x0, 0xB0, (const u32*)((u32)DirectSoundData_081937EC), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08193EC4), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0xD0, (const u32*)((u32)DirectSoundData_0819496C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08194FD8), (const u32*)0xFF00FF },
        { 0x80, 0x0, 0x0, 0x0, (const u32*)((u32)&sBlob_a5710_a8cdc.records[911]), (const u32*)0x0 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08195670), (const u32*)0xA500F611 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0x20F0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08195EBC), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08196984), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08197268), (const u32*)0xCE00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08197CC0), (const u32*)0xFF001A },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x70001 },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x70001 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08197E88), (const u32*)0xF5FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08198684), (const u32*)0x29F21A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08199414), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819A0B0), (const u32*)0xFE0A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819C754), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819CAF0), (const u32*)0xCEFEFF },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0xC0603 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819D3C8), (const u32*)0xC600FAFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819DAC0), (const u32*)0xF5FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819E524), (const u32*)0x7F00F5FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819C754), (const u32*)0xFE08 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819A0B0), (const u32*)0xFE16 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819E958), (const u32*)0x1EEFFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819EE6C), (const u32*)0xFE08 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819FEBC), (const u32*)0xE2FA80 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0E50), (const u32*)0x29FEFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A064C), (const u32*)0xFF001A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A23FC), (const u32*)0xF2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A28F8), (const u32*)0xF2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A2DF4), (const u32*)0xF2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A32F0), (const u32*)0xF2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A37EC), (const u32*)0xCEF2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A43D0), (const u32*)0xA4F2FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A4AC0), (const u32*)0xFCFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A5090), (const u32*)0x1E7FFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A5434), (const u32*)0x52A5FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A5E40), (const u32*)0xA4B8FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0xF0000 },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819CAF0), (const u32*)0xDA00FEFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A37EC), (const u32*)0xCEF225 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081A6AFC), (const u32*)0xFF0040 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819DAC0), (const u32*)0xFAFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081AB0B0), (const u32*)0x52DAFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081AB320), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081ABA98), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081AD364), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081AEF28), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B0958), (const u32*)0xEFFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B0FCC), (const u32*)0xE9FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819FEBC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B17A0), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08195670), (const u32*)0xFF0016 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3598), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D5E5C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080D3694), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080C9BE4), (const u32*)0xFF000C },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B0310), (const u32*)0xC6FF000C },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_080B8B88), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0x40606 },
        { 0x2, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0x40606 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08195670), (const u32*)0xE900F60A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B1DA4), (const u32*)0xC6FF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B28E0), (const u32*)0xC6FF000A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B5230), (const u32*)0xC6FF000A },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0x500 },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x0, (const u32*)0x500 },
        { 0x3, 0x3C, 0x0, 0x0, (const u32*)((u32)(u8*)&sBlob_a5710_a8cdc+0x35BC), (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B7E84), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B808C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B8548), (const u32*)0xFF000A },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B87F4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081B8FDC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BB0CC), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BB470), (const u32*)0xFF000A },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BE070), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BE190), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BEB4C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BF2E8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BF9A8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BFC48), (const u32*)0xFF00FF },
        { 0x1, 0x3C, 0x0, 0x0, (const u32*)0x2, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BB470), (const u32*)0xDA0F },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081BFFB8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C07F8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C1120), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C12E8), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C166C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C1B40), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C258C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C3004), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C3704), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C3E08), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C4714), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C490C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C4E74), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C6480), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081C781C), (const u32*)0xFF00FF },
        { 0x4, 0x3C, 0x0, 0x0, (const u32*)0x1, (const u32*)0xF0000 },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081CDC5C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081D2ECC), (const u32*)0x8BC6FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081D387C), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081D43A0), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081D5D58), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0819CAF0), (const u32*)0xDA00FE0C },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081D7994), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08197CC0), (const u32*)0xA4ECFF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081E06F4), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081E17E4), (const u32*)0xFF000C },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081E3114), (const u32*)0xDA00FE0C },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081E37C8), (const u32*)0xDA7BFE0F },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081E4238), (const u32*)0xFF00FF },
        { 0x0, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081E6620), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081E70F8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081ECDBC), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081EF770), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081F1F3C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081F43A0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081F6830), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081F8B80), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081FB34C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_081FDB98), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0820037C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_082027B8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08204F48), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08207CD8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0820A158), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0820C53C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0820E5D8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0821073C), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08212B70), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08215298), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0821E0EC), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08228B64), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0822DF60), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08234300), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_08236BE0), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0823C1F8), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_0823FACC), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_082438E4), (const u32*)0xFF00FF },
        { 0x8, 0x3C, 0x0, 0x0, (const u32*)((u32)DirectSoundData_082466E0), (const u32*)0xFF00FF },
    },
    {
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x00, 0x11, 0x23, 0x56, 0x89, 0xAC, 0xDE, 0xEF, 0xFF, 0xEE, 0xDC, 0xA9,
        0x86, 0x53, 0x21, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0x23, 0x45, 0x67, 0x89,
        0x23, 0x45, 0x67, 0x89, 0x23, 0x45, 0x67, 0x89, 0x23, 0x45, 0x67, 0x89,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x23, 0x44, 0x56, 0x67, 0x78,
        0x87, 0x76, 0x65, 0x44, 0x32, 0x11, 0x00, 0x00,
    },
};
typedef char sBlob_a5710_a8cdc_record_size_check[sizeof(sBlob_a5710_a8cdc.records[0]) == 12 ? 1 : -1];
typedef char sBlob_a5710_a8cdc_records_size_check[sizeof(sBlob_a5710_a8cdc.records) == 13620 ? 1 : -1];
typedef char sBlob_a5710_a8cdc_tail_size_check[sizeof(sBlob_a5710_a8cdc.tail) == 152 ? 1 : -1];
typedef char sBlob_a5710_a8cdc_size_check[sizeof(sBlob_a5710_a8cdc) == 13772 ? 1 : -1];
/* END GENERATED: sBlob_a5710_a8cdc */
