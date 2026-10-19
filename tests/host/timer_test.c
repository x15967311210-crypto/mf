/*
 * Host-side unit tests for the in-game timer in src/in_game_timer.c.
 *
 * The real engine function is linked in by the Makefile's host-test target:
 *
 *   cc ... tests/host/timer_test.c src/in_game_timer.c -Wl,--gc-sections ...
 *
 * Only the timer fixture globals are defined here.  No GBA I/O, ROM data, or
 * emulator is involved.
 */

#include "test.h"

#include "structs/in_game_timer.h"

struct InGameTimer gInGameTimer;
u8 gMaxInGameTimeFlag;

static void set_time(u8 hours, u8 minutes, u8 seconds, u8 frames)
{
    gInGameTimer.hours = hours;
    gInGameTimer.minutes = minutes;
    gInGameTimer.seconds = seconds;
    gInGameTimer.frames = frames;
    gMaxInGameTimeFlag = FALSE;
}

static void check_time(u8 hours, u8 minutes, u8 seconds, u8 frames)
{
    CHECK_EQ(gInGameTimer.hours, hours);
    CHECK_EQ(gInGameTimer.minutes, minutes);
    CHECK_EQ(gInGameTimer.seconds, seconds);
    CHECK_EQ(gInGameTimer.frames, frames);
}

/* ------------------------------------------------------------------ */
/* Flag behavior and normal frame/second/minute rolling.               */
/* ------------------------------------------------------------------ */

static void test_max_time_flag_freezes_timer(void)
{
    u8 i;

    CHECK_EQ(SIMULATED_FPS, 64);
    set_time(12, 34, 56, 63);
    gMaxInGameTimeFlag = TRUE;

    for (i = 0; i < 4; i++)
        InGameTimerUpdate();

    check_time(12, 34, 56, 63);
    CHECK_EQ(gMaxInGameTimeFlag, TRUE);
}

static void test_frame_increment(void)
{
    set_time(0, 0, 0, 0);
    InGameTimerUpdate();
    check_time(0, 0, 0, 1);

    /* 63 frames done; the next tick completes one second. */
    set_time(0, 0, 0, 63);
    InGameTimerUpdate();
    check_time(0, 0, 1, 0);
}

static void test_seconds_boundary(void)
{
    set_time(0, 0, 59, 63);
    InGameTimerUpdate();
    check_time(0, 1, 0, 0);
}

static void test_minutes_boundary(void)
{
    /*
     * Real engine behavior: the hour-rollover path also executes the
     * in-loop frames++ in src/in_game_timer.c, so the carry is one frame
     * past a pure total-frames decomposition.  Assert the actual carry.
     */
    set_time(0, 59, 59, 63);
    InGameTimerUpdate();
    check_time(1, 0, 0, 1);
}

static void test_hours_boundary_caps(void)
{
    set_time(99, 59, 59, 63);
    InGameTimerUpdate();

    check_time(99, 59, 59, 59);
    CHECK_EQ(gMaxInGameTimeFlag, TRUE);
    CHECK_TRUE(gInGameTimer.hours <= 99);
}

/* ------------------------------------------------------------------ */
/* Long tick sequence against a total-frames reference model.          */
/* ------------------------------------------------------------------ */

static void test_long_sequence_matches_total_frames_model(void)
{
    u32 ticks = 100000;
    u32 total;
    struct InGameTimer expected;
    u32 i;

    set_time(0, 0, 0, 0);
    for (i = 0; i < ticks; i++)
        InGameTimerUpdate();

    /* Decompose tick count into 64 fps, 60 seconds, 60 minutes. */
    total = ticks;
    expected.frames = total % SIMULATED_FPS;
    total /= SIMULATED_FPS;
    expected.seconds = total % 60;
    total /= 60;
    expected.minutes = total % 60;
    total /= 60;
    expected.hours = total % 100;

    check_time(expected.hours, expected.minutes,
               expected.seconds, expected.frames);
    CHECK_EQ(expected.hours, 0);
    CHECK_EQ(expected.minutes, 26);
    CHECK_EQ(expected.seconds, 2);
    CHECK_EQ(expected.frames, 32);
    CHECK_EQ(gMaxInGameTimeFlag, FALSE);
}

/* ------------------------------------------------------------------ */
/* The cap must be sticky, not a wrapping counter.                     */
/* ------------------------------------------------------------------ */

static void test_cap_does_not_wrap(void)
{
    u8 i;

    set_time(99, 59, 59, 63);
    InGameTimerUpdate();
    check_time(99, 59, 59, 59);
    CHECK_EQ(gMaxInGameTimeFlag, TRUE);

    for (i = 0; i < 8; i++)
        InGameTimerUpdate();

    check_time(99, 59, 59, 59);
    CHECK_EQ(gMaxInGameTimeFlag, TRUE);
}

int main(void)
{
    test_max_time_flag_freezes_timer();
    test_frame_increment();
    test_seconds_boundary();
    test_minutes_boundary();
    test_hours_boundary_caps();
    test_long_sequence_matches_total_frames_model();
    test_cap_does_not_wrap();

    if (g_host_test_failures != 0)
        return host_test_finish();

    printf("timer-test: %d/%d passed\n",
           g_host_test_checks, g_host_test_checks);
    return 0;
}
