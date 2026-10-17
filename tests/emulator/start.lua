-- mGBA Lua Start/file-select scenario.
--
-- Fallback for a frontend-only environment; the C harness in harness.c is the
-- preferred runner.  Hold Start for 6 frames every 60 frames starting at frame
-- 600.  Success latches at the first frame after the first Start where
-- DISPCNT != 0, gMainGameMode == 7 and gSubGameMode1 >= 1.
--
-- Run with:
--   SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy mgba -l start.lua rom.gba

local FRAMES = 1200
local START_FIRST_FRAME = 600
local START_PERIOD = 60
local START_HOLD = 6
local START_KEY = 8 -- 1 << GBA_KEY_START

local DISPCNT = 0x04000000
local MAIN_MODE = 0x03000BDE
local SUB_MODE1 = 0x03000BE0
local SUB_MODE2 = 0x03000BE2

local latched = false
local latch_frame = -1
for i = 0, FRAMES - 1 do
    local pressed = i >= START_FIRST_FRAME
        and ((i - START_FIRST_FRAME) % START_PERIOD) < START_HOLD
    emu:setKeys(pressed and START_KEY or 0)
    emu:runFrame()
    if i >= START_FIRST_FRAME and not latched then
        local dispcnt = emu:read16(DISPCNT)
        local main_mode = emu:read16(MAIN_MODE)
        local sub1 = emu:read16(SUB_MODE1)
        if dispcnt ~= 0 and main_mode == 7 and sub1 >= 1 then
            latched = true
            latch_frame = i
        end
    end
end

local dispcnt = emu:read16(DISPCNT)
local main_mode = emu:read16(MAIN_MODE)
local sub1 = emu:read16(SUB_MODE1)
local sub2 = emu:read16(SUB_MODE2)
print(string.format(
    "START frames=%d dispcnt=0x%04X main=%d sub1=%d sub2=%d latched=%s latch_frame=%d",
    FRAMES, dispcnt, main_mode, sub1, sub2, tostring(latched), latch_frame
))

if not latched then
    print("FAIL: start/file-select: no frame after Start had " ..
        "DISPCNT ~= 0 && main == 7 && sub1 >= 1")
    os.exit(1)
end
print("PASS: start/file-select")
