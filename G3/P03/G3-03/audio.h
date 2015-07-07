#ifndef AUDIO_H
#define AUDIO_H
#include <xact3.h>
HRESULT AudioSetup();
void AudioUpdate();
void AudioCleanup();
void AudioPlay(PCSTR soundName);
void AudioStop(PCSTR soundName);
#endif