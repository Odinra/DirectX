#include "SaveXFile.h"
#include <d3dx9xof.h>
#include <initguid.h>
#include <rmxfguid.h>
#include <iostream>
//This defines the GUID of the template
//that is it saving the data to.
DEFINE_GUID(GUID_HIGHSCORE, 
0xc93d8550, 0xe663, 0x47b9, 0xb4, 0xb0, 0x7e, 0x68, 0x2e, 0x9b, 0x1f, 0xf4);
//This structure is for getting  the data
//from the main.cpp file and saving it to
//the x file.
struct high_score
{
	char userInitial[4];
	int highScore;
	char dateAccomplished[11];
};

high_score scoreDataSave[11];

//This random variable is for accumulating the index
//for the structures so it can save the next data
//onto the next array of structures.
int b = 0;

void saveXFile(char username[], int score,char date[], int index)
{

	LPD3DXFILE File = NULL;
	if(FAILED(D3DXFileCreate(&File)))
		return;

	LPD3DXFILESAVEOBJECT saveObject = NULL;
	File->CreateSaveObject("FastestTimes.x", D3DXF_FILESAVE_TOFILE, D3DXF_FILEFORMAT_TEXT, &saveObject);

	char *szTempData = "xof 0302txt 0032\n\ntemplate HIGH_SCORE{\n<C93D8550-E663-47B9-B4B0-7E682E9B1FF4>\nSTRING UserInitials;\nDWORD TimeAchieved;\nSTRING DateAchieved;\n[...]\n}";
	if(FAILED(File->RegisterTemplates(szTempData, strlen(szTempData))))
	{
		File->Release();
		return;
	}

	LPD3DXFILESAVEDATA ppObj;

	sprintf_s(scoreDataSave[b].userInitial, "%s", username);
	scoreDataSave[b].highScore = score;
	sprintf_s(scoreDataSave[b].dateAccomplished, "%s", date);
	b++;
	char objectName[9];
	//I did a for loop so it will save the data
	//into the structures and then save them to
	//the x file.
	for(int i = 0; i < index; i++)
	{
		sprintf_s(objectName, "Player%i", i+1);
		saveObject->AddDataObject(GUID_HIGHSCORE, objectName, NULL, sizeof(high_score), &scoreDataSave[i], &ppObj);
	}
	saveObject->Save();
	saveObject->Release();
}