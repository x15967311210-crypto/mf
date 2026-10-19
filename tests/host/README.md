# Host-side unit tests

Fast, deterministic tests that compile real engine C with the host compiler.
They need no GBA toolchain, no baserom, no `data/` directory, and no emulator.

```sh
make host-test
```

The target compiles `tests/host/room_rle_test.c` together with the real
`src/room.c` and links with `-ffunction-sections -fdata-sections
-Wl,--gc-sections`.  The linker drops every unrelated room function (and its
GBA/global references), so only `RoomRleDecompress` from the engine ends up in
the binary.  The implementation is never copied or re-implemented here.

The binary is written to `tests/host/bin/room_rle_test` (git-ignored) and run
immediately.  A successful run exits 0 and prints:

```
host-test: N/N passed
```

## Coverage

`room_rle_test.c` covers `RoomRleDecompress` with synthetic vectors only:

- type 0 size codes (`0 -> 0x800`, `1/2 -> 0x1000`, other -> `0x2000`);
- type 1: no header, two interleaved passes;
- type >1: two source bytes become a 4-byte header before the passes;
- 8-bit pass mode: literal and run controls with the `0x00` terminator;
- 16-bit pass mode: big-endian literal/run controls with `0x0000`;
- pass 2 starts at `dstStart + 1`;
- a combined run/literal regression vector.

## Scope

This is a quick pre-check for pure algorithms, not a replacement for the
emulator/behavior suite (`make -f Makefile.shift smoke`, `test`, `audit`).
Tests must stay synthetic: do not add GBA I/O, globals, ROM addresses, or
copyrighted data.

## Adding a test

1. Include `test.h` and the real engine header (for example `room.h`).
2. Use `CHECK_TRUE`, `CHECK_EQ`, or `CHECK_MEMEQ`; failures report
   `file:line` and the expression.
3. Call the check functions from `main` and return `host_test_finish()`.
4. If the test needs another engine file, extend the `host-test` recipe in the
   top-level `Makefile` rather than copying engine code.
