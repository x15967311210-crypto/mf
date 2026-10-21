# How to add dialogue / message-banner text

Hack-owned text uses the repository charmap through `tools/preproc`'s
`INCTEXT` path. Do not write a second encoder and do not edit the vanilla
message tables.

## 1. Write the text source

Create or extend a C file under `hack/content/text/`:

```c
#include "constants/text.h"

const u16 sHackTextSilentAtrium[] = INCTEXT(
    "SILENT ATRIUM{NEW_LINE}"
    "THE SIGNAL IS WEAK"
);
```

Proven mappings are uppercase/lowercase letters, space, `{NEW_LINE}`,
`{WIDTH(n)}`, `{INDENT(n)}` and the terminator; unknown glyphs (digits,
punctuation) are hard errors until they are proven against the text blob. See
`charmap.txt` and `docs/content-pipeline.md`.

## 2. Register the text ID

Add a `text` entry to `hack/content/ids.yaml` with an `area` and a note that
states the intended `message_id` and source file. Then:

```sh
python3 tools/content/gen_ids.py --write
python3 tools/content/gen_ids.py --check
```

`TEXT_*` IDs are global; the in-area `message_id` is separate.

## 3. Map the message

`hack/content/text/messages.json` (`mf-hack.text-messages/v1`) maps
`(area, message_id, text_id)` to the source file and the `literal` index:

```json
{"schema": "mf-hack.text-messages/v1",
 "areas": [{"area": "AREA_TEST_1", "messages": [
   {"text_id": "TEXT_ENTRY_LEDGE_SIGNAL", "message_id": 2,
    "source": "golden_path.c", "literal": 0}]}]}
```

`message_id` must be 0..21 (the message banner clamps at 21 and adds 21 to index
the vanilla table). `literal` selects one `INCTEXT` block in the source file.
`message_id` is **the banner spawn's record index (`roomSlot`)**, not its
spriteset slot; Entry Ledge's `signal_banner` is spriteset slot 5 but spawn
record 2, so its `message_id` is 2.

## 4. Place the banner

Add a `spawns` object with `sprite_id: PSPRITE_MESSAGE_BANNER`, the desired
`spriteset` and `slot`, and a `properties` value. The spawn order in the room
data is the `roomSlot`; changing spawn order changes `message_id`, so keep
`messages.json` in sync. The banner text is drawn when the banner runs its
popup; the HACK text hook is gated on `gCurrentArea == AREA_TEST_1`.

## 5. Generate and validate

```sh
python3 tools/content/gen_text_tables.py --self-check
make content-tables-check content-check
make hack-build
make hack-liveness-check
```

`gen_text_tables.py` runs the real `tools/preproc` and emits
`hack/gen/text_tables.h` (one `u16` block per TEXT id, a `[message_id]` pointer
list). `hack-liveness-check` proves the banner's `roomSlot` is the authored id
(2), not `UCHAR_MAX`.

## Pitfalls

- `MessageBannerInit` used to overwrite an offscreen banner's `roomSlot` with
  `UCHAR_MAX`, which made `TextDrawMessageBanner` draw vanilla text index 42
  (BUG-022). The HACK hook now preserves the authored id for `AREA_TEST_1`.
- The vanilla path uses `index = messageId`, clamps at 21, then adds 21; the
  vanilla table needs entries 0..42. The HACK table is indexed directly by
  `message_id` and must have `HACK_AREA_TEST_1_TEXT_COUNT` entries (22).
- Do not reuse a vanilla pointer or message index; keep IDs in `ids.yaml`.
- One `literal` per `INCTEXT` block; add a new block rather than reusing text.
- Text IDs and the message id are different namespaces; `TEXT_*` is global,
  `message_id` is per area.
