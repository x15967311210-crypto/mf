-- mGBA Lua boot smoke.
--
-- Runs 600 frames and verifies that the main loop is alive.  The frame counter
-- and mode words are fixed IWRAM addresses from linker.ld (D-002), so they stay
-- valid across the shiftable ROM refactor.
--
-- Run with:
--   SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy mgba -l boot_smoke.lua rom.gba

local FRAMES = 600
local FRAME_COUNTER = 0x03000002
local CURRENT_AREA = 0x0300002C
local MAIN_MODE = 0x03000BDE
local SUB_MODE = 0x03000BE0

local start = emu:currentFrame()
for _ = 1, FRAMES do
    emu:runFrame()
end
local elapsed = emu:currentFrame() - start
local counter = emu:read16(FRAME_COUNTER)
local area = emu:read8(CURRENT_AREA)
local main_mode = emu:read8(MAIN_MODE)
local sub_mode = emu:read16(SUB_MODE)

print(string.format(
    "BOOT frames=%d frame_counter=%d area=%d main_mode=%d sub_mode=0x%04X",
    elapsed, counter, area, main_mode, sub_mode
))

if elapsed < FRAMES then
    print("FAIL: emulator did not advance the requested frames")
    os.exit(1)
end
if counter < math.floor(FRAMES * 3 / 4) then
    print("FAIL: frame counter is below the liveness floor")
    os.exit(1)
end
print("PASS: boot smoke")
