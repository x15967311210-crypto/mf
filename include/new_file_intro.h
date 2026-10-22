#ifndef NEW_FILE_INTRO_H
#define NEW_FILE_INTRO_H

#include "types.h"

#include "constants/new_file_intro.h"
#include "constants/game_state.h"

extern const u16** sLocationTextPointers[LANGUAGE_COUNT];
extern u16** sMessageTextPointers[LANGUAGE_COUNT];

boolu32 IntroHandler(void);
boolu32 NewFileIntroHandler(void);
boolu32 unk_87920(void);
u8 NewFileIntroLandingOnBslSetupOam(IntroLandingOnBslOamType type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void NewFileIntroLandingOnBslVblank(void);
boolu32 NewFileIntroLandingOnBsl(void);
u8 NewFileIntroGetPositionAndSlotOfOamByType_2(IntroLandingOnBslOamType type, s16* pXPosition, s16* pYPosition);

#endif /* NEW_FILE_INTRO_H */
