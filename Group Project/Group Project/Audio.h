// Audio Header File for Great Wheels of Destruction
// This is a header file that has a class for initializing and utilizing XACT for loading and playing music and sounds ingame.

// START OF HEADER
#ifndef __audioH_
#define __audioH_

#include <d3dx9.h>
#include <xact3.h>
#include <string>

// Class definition
class Audio
{
	// Public functions
public:
	// Result handle for the function that initializes XACT
	HRESULT PrepareXACT();
	// Function for cleaning up XACT when exiting the game
	VOID CleanupXACT();
	// Function for updating new audio data
	VOID AudioUpdate();
	// Function for playing a specific audio file with a parameter for the filename
	VOID AudioPlay(PCSTR filename);
	
	// A structure that holds data for the audio state
	struct AUDIO_STATE
	{
		// A pointer variable to the XACT engine
		IXACT3Engine* pEngine;
		// A pointer variable to access the Wave Bank of the XACT audio file
		IXACT3WaveBank* pWaveBank;
		// A pointer variable to access the Sound Bank of the XACT audio file
		IXACT3SoundBank* pSoundBank;
		// The index of the XACT audio file which contains the list of cues
		XACTINDEX iZap;

		VOID* pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
		VOID* pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
	};

	// An object of the audio state structure previously defined
	AUDIO_STATE g_audioState;

};

// END OF HEADER
#endif

