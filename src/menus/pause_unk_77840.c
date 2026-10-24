#include "globals.h"

#include "audio_wrappers.h"
#include "dma.h"

/**
 * @brief 77840 | 43C | Pause-screen map download / OAM state machine
 *
 * Ported from the decomp.me scratch mJ7q3 by biosp4rk (100% match).
 */
void unk_77840(u8 arg0)
{
    s32 var_r6;

    var_r6 = 0;

    switch (PAUSE_SCREEN_DATA.unk_1)
    {
        case 0:
            var_r6 = 5;
            DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_1 = 8;
            break;

        case 3:
            var_r6 = 1;
            PAUSE_SCREEN_DATA.oam[0xD].currentAnimationFrame = 9;
            PAUSE_SCREEN_DATA.oam[0xE].currentAnimationFrame = 9;
            DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_1 = 4;
            break;

        case 4:
            if (arg0 == 1)
            {
                var_r6 = 2;
                PAUSE_SCREEN_DATA.dispcnt ^= DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 5;
            }
            else if (arg0 == 3)
            {
                var_r6 = 2;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 6;
            }
            else if (arg0 == 5)
            {
                var_r6 = 3;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 6;
            }
            break;

        case 5:
            if (arg0 == 2)
            {
                var_r6 = 1;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 4;
                SoundPlay(0x203);
            }
            else if (arg0 == 3)
            {
                PAUSE_SCREEN_DATA.unk_1 = 7;
            }
            break;

        case 6:
            if (arg0 == 4)
            {
                var_r6 = 1;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = 4;
            }
            break;

        case 7:
            if (arg0 == 4)
            {
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = 5;
            }
            break;

        case 8:
            if (arg0 == 2)
            {
                var_r6 = 4;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 9;
                SoundPlay(0x203);
            }
            else if (arg0 == 3 || arg0 == 5)
            {
                var_r6 = 6;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 0xB;
            }
            break;

        case 9:
            if (arg0 == 1)
            {
                var_r6 = 5;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 8;
            }
            else if (arg0 == 3)
            {
                var_r6 = 6;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 0xA;
            }
            else if (arg0 == 5)
            {
                var_r6 = 6;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 0xA;
            }
            break;

        case 10:
            if (arg0 == 4)
            {
                var_r6 = 4;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = 9;
            }
            break;

        case 11:
            if (arg0 == 4)
            {
                var_r6 = 5;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = 8;
            }
            break;
    }

    switch (var_r6)
    {
        case 1:
            PAUSE_SCREEN_DATA.oam[0xD].oamId = 0x59;
            PAUSE_SCREEN_DATA.oam[0xD].priority = 2;
            PAUSE_SCREEN_DATA.oam[0xD].objMode = 0;
            PAUSE_SCREEN_DATA.oam[0xE].oamId = 0x5C;
            PAUSE_SCREEN_DATA.oam[0xE].priority = 2;
            PAUSE_SCREEN_DATA.oam[0xE].objMode = 1;

            PAUSE_SCREEN_DATA.oam[0xD].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[0xD].yPosition = 0x84;
            PAUSE_SCREEN_DATA.oam[0xE].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[0xE].yPosition = 0x84;
            PAUSE_SCREEN_DATA.oam[0xC].xPosition = 0x1C;
            break;

        case 2:
            PAUSE_SCREEN_DATA.oam[0xD].oamId = 0;
            PAUSE_SCREEN_DATA.oam[0xE].oamId = 0;
            PAUSE_SCREEN_DATA.oam[0xC].xPosition = -0x64;
            break;

        case 3:
            PAUSE_SCREEN_DATA.oam[0xD].oamId = 0;
            PAUSE_SCREEN_DATA.oam[0xE].oamId = 0;
            break;

        case 4:
            PAUSE_SCREEN_DATA.oam[0xD].oamId = 0x59;
            PAUSE_SCREEN_DATA.oam[0xD].priority = 2;
            PAUSE_SCREEN_DATA.oam[0xD].objMode = 0;
            PAUSE_SCREEN_DATA.oam[0xE].oamId = 0x5C;
            PAUSE_SCREEN_DATA.oam[0xE].priority = 2;
            PAUSE_SCREEN_DATA.oam[0xE].objMode = 1;

            PAUSE_SCREEN_DATA.oam[0xD].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[0xD].yPosition = 0x84;
            PAUSE_SCREEN_DATA.oam[0xE].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[0xE].yPosition = 0x84;

            PAUSE_SCREEN_DATA.oam[0xD].currentAnimationFrame = 9;
            PAUSE_SCREEN_DATA.oam[0xE].currentAnimationFrame = 9;
            PAUSE_SCREEN_DATA.oam[0xD].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[0xE].animationDurationCounter = 0;
            break;

        case 5:
            PAUSE_SCREEN_DATA.oam[0xE].oamId = 0;

            PAUSE_SCREEN_DATA.oam[0xD].oamId = 0x34;
            PAUSE_SCREEN_DATA.oam[0xD].xPosition = 0xCA;
            PAUSE_SCREEN_DATA.oam[0xD].yPosition = 0x8E;
            PAUSE_SCREEN_DATA.oam[0xD].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.oam[0xD].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[0xD].priority = 2;
            PAUSE_SCREEN_DATA.oam[0xD].objMode = 0;
            break;

        case 6:
            PAUSE_SCREEN_DATA.oam[0xE].oamId = 0;
            PAUSE_SCREEN_DATA.oam[0xD].oamId = 0;
            break;
    }
}
