
#ifndef __audioH_
#define __audioH_

#include <d3dx9.h>
#include <xact3.h>
#include <string>


class Audio
{
public:
	HRESULT PrepareXACT();
	VOID CleanupXACT();
	VOID AudioUpdate();
	VOID AudioPlay(PCSTR filename);
	
	struct AUDIO_STATE
	{
    IXACT3Engine* pEngine;
    IXACT3WaveBank* pWaveBank;
    IXACT3SoundBank* pSoundBank;
    XACTINDEX iZap;

    VOID* pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
    VOID* pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
	};

	AUDIO_STATE g_audioState;

};

#endif

