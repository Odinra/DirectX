#include "audio.h"

//Globals


IXACT3Engine* g_pAudioEngine;
IXACT3WaveBank* g_pWaveBank;
IXACT3SoundBank* g_pSoundBank;

VOID* g_pWaveBankData;
VOID* g_pSoundBankData;

//Audio Setup
HRESULT AudioSetup()
{
	HRESULT hr;
	HANDLE hFile;
	HANDLE hMapFile;
	DWORD dwFileSize;
	DWORD dwBytesRead;

	//Audio Engine
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if(FAILED(hr))
		return hr;
	hr = XACT3CreateEngine(0,&g_pAudioEngine);
	if(FAILED(hr))
		return hr;
	//Initialize XACT
	XACT_RUNTIME_PARAMETERS xrParams = {0};
	hr = g_pAudioEngine->Initialize(&xrParams);
	if(FAILED(hr))
		return hr;


	//Wave Bank
	//Create a handle to teh wave bank file
	hFile= CreateFile("Win/Wave Bank.xwb",GENERIC_READ,FILE_SHARE_READ,NULL, OPEN_EXISTING,0,NULL);

	//get the file size
	dwFileSize = GetFileSize(hFile,NULL);
	if(dwFileSize==-1)
		return E_FAIL;
	//create a memory mapped file handle
	hMapFile = CreateFileMapping(hFile,NULL,PAGE_READONLY,0,dwFileSize,NULL);
	if(!hMapFile)
		return E_FAIL;
	//get a pointer to the file data in memory
	g_pWaveBankData = MapViewOfFile(hMapFile,FILE_MAP_READ,0,0,0);
	if(!g_pWaveBankData)
		return E_FAIL;
	//create the wave bank
	hr = g_pAudioEngine->CreateInMemoryWaveBank(g_pWaveBankData,dwFileSize,0,0,&g_pWaveBank);
	if(FAILED(hr))
		return hr;

	//close file handles
	CloseHandle(hFile);
	CloseHandle(hMapFile);


	//SoundBank
	//create a handle to sound bank file
	hFile = CreateFile("Win/Sound Bank.xsb",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;
	dwFileSize = GetFileSize(hFile,NULL);
	if(dwFileSize ==-1)
		return E_FAIL;
	//allocate memory for sound bank data
	g_pSoundBankData = new BYTE[dwFileSize];
	if(!g_pSoundBankData)
		return E_FAIL;
	//read teh sound bank data into memory
	if(ReadFile(hFile,g_pSoundBankData,dwFileSize,
		&dwBytesRead,NULL)==0)
		return E_FAIL;
	//create the sound bank
	hr= g_pAudioEngine->CreateSoundBank(g_pSoundBankData,dwFileSize,0,0,&g_pSoundBank);
	if(FAILED(hr))
		return E_FAIL;
	//close file hnadle
	CloseHandle(hFile);
	return S_OK;
}
//Audio update
void AudioUpdate()
{
	if(g_pAudioEngine)
		g_pAudioEngine->DoWork();
}
//Audio Cleanup
VOID AudioCleanup()
{
	if(g_pAudioEngine)
	{
		g_pAudioEngine->ShutDown();
		g_pAudioEngine->Release();
	}
	if(g_pSoundBankData)
	{
		delete[] g_pSoundBankData;
		g_pSoundBankData = NULL;
	}
	if(g_pWaveBankData)
	{
		UnmapViewOfFile(g_pWaveBankData);
		g_pWaveBankData = NULL;
	}
	CoUninitialize();
}
//Play Sound
void AudioPlay(PCSTR filename)
{
	XACTINDEX index = g_pSoundBank->GetCueIndex(filename);
	g_pSoundBank->Play(index,0,1,NULL);
}
//Stop Sound
void AudioStop(PCSTR filename)
{
	XACTINDEX index = g_pSoundBank->GetCueIndex(filename);
	g_pSoundBank->Stop(index, 0);
}