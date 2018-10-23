#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "channel.h"
#include "desktop.h"
#include "font.h"
#include "glyph.h"
#include "image.h"
#include "input.h"
#include "music.h"
#include "pixmap.h"
#include "renderer.h"
#include "screen.h"
#include "sound.h"

String SDLError();
String MixerError();

// Not to be exported
void InitGame();
void FinishGame();
void HandleEvents();

#endif // GAME_MAIN_H
