#include "LoadXFile.h"
#include <d3dx9xof.h>
#include <initguid.h>
#include <rmxftmpl.h>
#include <rmxfguid.h>
#include <iostream>
//This defines the GUID of the template
//that is it loading the data from. 
DEFINE_GUID(GUID_HIGHSCORE, 
0xc93d8550, 0xe663, 0x47b9, 0xb4, 0xb0, 0x7e, 0x68, 0x2e, 0x9b, 0x1f, 0xf4);
//This structure is for storing the data
//that are in the x file.
struct high_score
{
	char userInitial[3];
	int highScore;
	char dateAccomplished[10];
};
high_score* scoreData[11] = {NULL};

//This structure is for returning the data
//that was stored in the other structure
//to the main.cpp file because for some reason
//the functions would not return them directly
//but it will work if i store it into another structure.
high_score_return scoreDataReturn[11] = {NULL};

//This is a function prototype for extracting data
//from the x file.
void ExtractData(LPD3DXFILEDATA dataObject);
//This random variable is for accumulating the index
//for the structures so it can save the next data
//onto the next array of structures.
int a = 0;
char* GetInitial(int index)
{
	return scoreDataReturn[index].userInitial;
}

int GetScore(int index)
{
	return scoreDataReturn[index].highScore;
}

char* GetDate(int index)
{
	return scoreDataReturn[index].dateAccomplished;
}

void LoadXFile()
{
	LPD3DXFILE File = NULL;
	LPD3DXFILEENUMOBJECT EnumObject = NULL;
	LPD3DXFILEDATA dataObject = NULL;
	if(FAILED(D3DXFileCreate(&File)))
		return;

	char *szTempData = "xof 0302txt 0032\n\ntemplate HIGH_SCORE{\n<C93D8550-E663-47B9-B4B0-7E682E9B1FF4>\nSTRING UserInitials;\nDWORD GameScore;\nSTRING DateAchieved;\n[...]\n}";
	if(FAILED(File->RegisterTemplates(szTempData, strlen(szTempData))))
	{
		File->Release();
		return;
	}

	if(FAILED(File->CreateEnumObject("newscore.x",D3DXF_FILELOAD_FROMFILE,&EnumObject)))
		return;

	SIZE_T childNum = 0;

	EnumObject->GetChildren(&childNum);

	for(SIZE_T i = 0; i < childNum; i++)
	{
		EnumObject->GetChild(i,&dataObject);
		ExtractData(dataObject);
		dataObject->Release();
	}
	a = 0;
	EnumObject->Release();
	File->Release();
}
//This function is for extracting the data from the x file
//and store the values into the structure that was made.
void ExtractData(LPD3DXFILEDATA dataObject)
{
	LPD3DXFILEDATA subDataObject = NULL;
	GUID pType;
	SIZE_T dwSize = 0;
	char *pName = NULL;

	if(!dataObject)
		return;

	dataObject->GetType(&pType);
	dataObject->GetName(NULL,&dwSize);
	if(dwSize)
	{
		if((pName = new char[dwSize]) != NULL)
		{
			dataObject->GetName(pName, &dwSize);
		}
	}
	if(pType == GUID_HIGHSCORE)
	{
		SIZE_T dataSize = 0;
		dataObject->Lock(&dataSize, (const void**)&scoreData[a]);
		sprintf_s(scoreDataReturn[a].userInitial, "%s", scoreData[a]->userInitial);
		scoreDataReturn[a].highScore = scoreData[a]->highScore;
		sprintf_s(scoreDataReturn[a].dateAccomplished, "%s", scoreData[a]->dateAccomplished);
		a++;
		dataObject->Unlock();
	}

}