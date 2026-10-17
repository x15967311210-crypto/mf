#ifndef TEXT_H
#define TEXT_H

#include "types.h"

u32 TextGetCharacterWidth(u16 idx);
void TextDrawCharacter(u16 charId, u32* dst, u8 width, u8 indent, u8 color);
void TextDrawCharacterPauseDebug(u16 charId, u32* dst, u8 color);
void TextDrawLocationText(u8 locationText, u8 gfxSlot);
void TextDrawMessageBanner(u8 messageId, u8 gfxSlot, u8 stage);
void TextDisplayMessage(u8 gfxSlot, u8 stage);
void TextClearGraphics(u8 action);

/* Code pointers held by sBlob_79c170_79c27c (asm/disasm_0x08079afc.s). */
void unk_7bde0(void);
void NavigationConversationUpdateXParasitePopUp(void);
void NavigationConversationClearPopUpGraphics(void);

#endif /* TEXT_H */
