-- mGBA Lua boot smoke.
--
-- Runs 600 frames and verifies that the main loop is alive.  The frame counter
-- and DISPCNT shadow are fixed IWRAM addresses from linker.ld (D-002): they stay
-- valid across the shiftable ROM refactor.
--
-- Run with:
--   SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy mgba -l boot_smoke.lua rom.gba

local FRAMES = 600
local FRAME_COUNTER = 0x03000002
local DISPCNT_SHADOW = 0x03000008

local start = emu:currentFrame()
for _ = 1, FRAMES do
    emu:runFrame()
end
local elapsed = emu:currentFrame() - start
local counter = emu:read16(FRAME_COUNTER)
local dispcnt = emu:read16(DISPCNT_SHADOW)

print(string.format(
    "BOOT frames=%d frame_counter=%d dispcnt=0x%04X",
    elapsed, counter, dispcnt
))

if elapsed < FRAMES then
    print("FAIL: emulator did not advance the requested frames")
    os.exit(1)
end
if counter == 0 then
    print("FAIL: frame counter did not advance")
    os.exit(1)
end
if dispcnt == 0 then
    print("FAIL: DISPCNT shadow was not initialized")
    os.exit(1)
end
print("PASS: boot smoke")
