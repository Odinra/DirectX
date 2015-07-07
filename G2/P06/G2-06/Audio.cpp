#include "audio.h"

HRESULT Audio::PrepareXACT()
{
	HRESULT hr;

	HANDLE hFile;
	DWORD dwFileSize;
	DWORD dwBytesRead;
	HANDLE hMapFile;

	hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );  // COINIT_APARTMENTTHREADED will work too
	if(FAILED(hr))
		return hr;

	hr = XACT3CreateEngine( 0, &g_audioState.pEngine );

	if( FAILED( hr ) || g_audioState.pEngine == NULL )
		return hr;

	// Initialize & create the XACT runtime 
	XACT_RUNTIME_PARAMETERS xrParams = {0};
	xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	hr = g_audioState.pEngine->Initialize( &xrParams );
	if( FAILED( hr ) )
		return hr;

	// Create an "in memory" XACT wave bank file using memory mapped file IO
	// Memory mapped files tend to be the fastest for most situations assuming you 
	// have enough virtual address space for a full map of the file
	// hr = E_FAIL; // assume failure
	hFile = CreateFile( "Win\\Wave Bank.xwb", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	if( hFile == INVALID_HANDLE_VALUE )
		return E_FAIL;


	dwFileSize = GetFileSize( hFile, NULL );
	if( dwFileSize == -1 )
		return E_FAIL;


	hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
	if( !hMapFile )
		return E_FAIL;

	g_audioState.pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
	if( !g_audioState.pbWaveBank )
		return E_FAIL;

	hr = g_audioState.pEngine->CreateInMemoryWaveBank( g_audioState.pbWaveBank, dwFileSize, 0,
		0, &g_audioState.pWaveBank );
	if(FAILED(hr))
		return hr;

	CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle


	CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle



	// Read and register the sound bank file with XACT.  Do not use memory mapped file IO because the 
	// memory needs to be read/write and the working set of sound banks are small.

	hFile = CreateFile( "Win\\Sound Bank.xsb", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
		return E_FAIL;

	dwFileSize = GetFileSize( hFile, NULL );
	if( dwFileSize == -1 )
		return E_FAIL;

	// Allocate the data here and free the data when recieving the sound bank destroyed notification
	g_audioState.pbSoundBank = new BYTE[dwFileSize];
	if( !g_audioState.pbSoundBank )
		return E_FAIL;

	if(  ReadFile( hFile, g_audioState.pbSoundBank, dwFileSize, &dwBytesRead, NULL ) == 0 )
		return E_FAIL;


	hr = g_audioState.pEngine->CreateSoundBank( g_audioState.pbSoundBank, dwFileSize, 0,
		0, &g_audioState.pSoundBank );
	if( FAILED( hr ) )
		return E_FAIL; // CleanupXACT() will cleanup state before exiting

	CloseHandle( hFile );
	return S_OK;
}

VOID Audio::AudioUpdate()
{
	if(g_audioState.pEngine)
		g_audioState.pEngine->DoWork();
}

VOID Audio::AudioPlay(PCSTR filename)
{
	XACTINDEX index = g_audioState.pSoundBank->GetCueIndex(filename);
	g_audioState.pSoundBank->Play(index, 0, 0, NULL);
}

VOID Audio::CleanupXACT()
{
	// Shutdown XACT
	//
	// Note that pEngine->ShutDown is synchronous and will take some time to complete 
	// if there are still playing cues.  Also pEngine->ShutDown() is generally only 
	// called when a game exits and is not the preferred method of changing audio 
	// resources. To know when it is safe to free wave/sound bank data without 
	// shutting down the XACT engine, use the XACTNOTIFICATIONTYPE_SOUNDBANKDESTROYED 
	// or XACTNOTIFICATIONTYPE_WAVEBANKDESTROYED notifications 
	if( g_audioState.pEngine )
	{
		g_audioState.pEngine->ShutDown();
		g_audioState.pEngine->Release();
	}

	if( g_audioState.pbSoundBank )
	{
		delete[] g_audioState.pbSoundBank;
		g_audioState.pbSoundBank = NULL;
	}
	// After pEngine->ShutDown() returns it is safe to release memory mapped files
	if( g_audioState.pbWaveBank )
	{
		UnmapViewOfFile( g_audioState.pbWaveBank );
		g_audioState.pbWaveBank = NULL;
	}
	CoUninitialize();
}


