/*
 * hack/include/hack/text_tables.h — HACK=1 message-banner text overlay.
 *
 * HACK-008d2 / D-013.  src/text.c includes this header only under HACK=1 and
 * uses its per-area message-id lists in TextDrawMessageBanner for stage 4/5
 * (the message-banner sprite).  The generated u16 text blocks and pointer
 * lists live in the ignored hack/gen/text_tables.h; this shim is the stable
 * injection point.
 *
 * Text is split from content_tables.h/scroll_tables.h so the generated text
 * blocks are defined in exactly one translation unit.  Do not edit src/data or
 * the vanilla sMessageTextPointers to add hack content.
 */
#ifndef HACK_TEXT_TABLES_H
#define HACK_TEXT_TABLES_H

/* HACK-008d2: generated from hack/content/text/messages.json through
 * tools/preproc.  The header is ignored generated output;
 * `make content-tables` creates it before a HACK build. */
#if defined(__has_include)
#if __has_include("../../gen/text_tables.h")
#include "../../gen/text_tables.h"
#else
#error "missing hack/gen/text_tables.h; run make content-tables"
#endif
#else
#include "../../gen/text_tables.h"
#endif

#endif /* HACK_TEXT_TABLES_H */
