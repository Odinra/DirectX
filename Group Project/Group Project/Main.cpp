#define INITGUID
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#include "d3dUtility.h"
/******************************************************************************
*	Group Project
*	Great Wheels of Destruction (Working Title)
*	Created By:
*	Christopher King
*	Bradley Ward
*	Copyright 2013
******************************************************************************/

//
// Globals
//
HWND mainHWND, hMHighScore, hHighScore;
HINSTANCE hInstance, hNewInstance;
WNDCLASS cw;
int recordPlace = -1;
Audio sound;
IDirect3DDevice9* Device = 0;

char currentDate[11], initials[4];

Terrain* TheTerrain = 0;

//CSOCKET csocket;

d3d::BoundingBox Quarts[4];
bool bCkeckpoints[4], bCkeckpointsAI[4];

int checkPoint = 0, checkPointAI = 0;
std::list<D3DXVECTOR3> m_Waypoints;
std::list<D3DXVECTOR3>::iterator curWaypoint;
bool m_bLooped = true;
bool Finished(){return !(curWaypoint != m_Waypoints.end());}
inline void SetNextWaypoint()
{
	assert(m_Waypoints.size() > 0);

	if(++curWaypoint == m_Waypoints.end())
	{
		if(m_bLooped)
		{
			curWaypoint = m_Waypoints.begin();
		}
	}
}
D3DXVECTOR3 CurrentWaypoint(){ return *curWaypoint;}
//class Path
//{
//private:
//public:
//	
//	
//	
//	
//
//	Path():m_bLooped(true){}
//	D3DXVECTOR3 CurrentWaypoint(){ return *curWaypoint;}
//	
//	inline void SetNextWaypoint();
//	void LoopOn(){m_bLooped=true;}
//	void LoopOff(){m_bLooped=true;}
//	void AddWayPoint(D3DXVECTOR3 new_point);
//	void Set(std::list<D3DXVECTOR3> new_path)
//	{
//		m_Waypoints = new_path;
//		curWaypoint = m_Waypoints.begin();}
//	void Set(const Path& path){m_Waypoints=path.GetPath();curWaypoint = m_Waypoints.begin();}
//
//	void Clear(){m_Waypoints.clear();}
//
//	std::list<D3DXVECTOR3> GetPath()const{return m_Waypoints;}
//};
//
//void Path::AddWayPoint(D3DXVECTOR3 new_point)
//{
//	m_Waypoints.push_back(new_point);
//}
//
//Path* paths;

int LapTimes[3];

int Place = 1;

D3DXVECTOR3 CredPos(0,0,0);

ID3DXSprite* SpriteCredits;
ID3DXSprite* SpriteMap;
ID3DXSprite* spriteRacers[10];
ID3DXSprite* spriteSelector;
ID3DXSprite* spriteTitleScreen;
ID3DXSprite* spriteCountDown;
ID3DXSprite* spritePlaceBanner;
ID3DXSprite* spriteFastestTimes;

LPDIRECT3DTEXTURE9 TexCredits;
LPDIRECT3DTEXTURE9 TexMap;
LPDIRECT3DTEXTURE9 TexRacers;
LPDIRECT3DTEXTURE9 TexSelector;
LPDIRECT3DTEXTURE9 TexTitleScreen;
LPDIRECT3DTEXTURE9 TexCount3;
LPDIRECT3DTEXTURE9 TexCount2;
LPDIRECT3DTEXTURE9 TexCount1;
LPDIRECT3DTEXTURE9 TexCountGo;
LPDIRECT3DTEXTURE9 Tex1stPlace;
LPDIRECT3DTEXTURE9 Tex2ndPlace;
LPDIRECT3DTEXTURE9 TexFinish;
LPDIRECT3DTEXTURE9 TexCar;
LPDIRECT3DTEXTURE9 TexFastestTimes;


// Screen size
int x = GetSystemMetrics(SM_CXSCREEN);
int y = GetSystemMetrics(SM_CYSCREEN);
const int Width  = x;
const int Height = y;

// Initializing a camera object that can not fly
Camera TheCamera(Camera::LANDOBJECT);
Opponent TheOpponent;

// input object for movement
input TheInput;

// Setting color materials
D3DMATERIAL9 mtrlBrown, mtrlTan, mtrlDarkWood, mtrlLightWood, mtrlRed, mtrlWhite, mtrlBlack, mtrlGrey, mtrlYellow, mtrlBuGold, mtrlBlue, mtrlGreen;

// Meshes, vectors, and matrices for creating the box
ID3DXMesh** walls = new ID3DXMesh*[6];
D3DXVECTOR3 wallsPos[6];
D3DXMATRIX objWalls[6];
D3DXMATRIX V;

// Font mesh
ID3DXFont *m_font, *m_font2;

// Camera positioning values
D3DXVECTOR3 camStart(-2095.0f, 0.0f, 322.0f);
D3DXVECTOR3 OppStart(-1736.0f, 58.0f, 115.0f);
D3DXVECTOR3 p, t;

// Double word value for creating a timer
DWORD dwFinalTick, dwInitialTick;

// Double word variable for creating a timer for velocity
// This really isn't used anymore but I never got rid of it so yeah.
DWORD dwVelInitTick, dwVelFinalTick;

// Variables for holding the actual second count because using GetTickCount returns a millisecond
int seconds = 0, countDown = 0;
double dVelSeconds = 0, dTempSeconds = 0;

XFile OpponentX;

// Various character arrays for displaying text strings to the screen
char buffers[50];
char buffers2[150];
char buffers3[250];
char buffers4[250];
char buffers5[250];
char buffers6[250];
char buffers7[250];

// Enumerated data type to determine the current car being used.
enum CarType {Car1 = 0 /*Jimmy & Dan*/, Car2 /*Rico*/, Car3 /*Miguel y Miguelita*/, Car4 /*Jimmy Slicks*/,
	Car5 /*Angry Janitor Bob*/, Car6 /*Nuclear Beakers*/, Car7 /*Flower Power*/, Car8 /*Do$h Diva$*/, Car9 /*Secret #1*/,
	Car10 /*Secret #2*/};

enum GameState {TitleScreen, SinglePlayer, OnlineMultiplayer, Credits, Story, FastestTimes, SplitScreen, GameStart, GamePlay, GameOver};

GameState CurrentGameState = TitleScreen;
GameState NextGameState;

// Enumerated data type to set the current gear so that proper gear data will be loaded when it is needed
enum Gear {gear1, gear2, gear3, gear4, gear5, gear6};

// Movement function that holds all the movement data for cars and a function parameter that takes a enumerated data type to determine car type
void Movement(CarType);
void AI(CarType);

// Car struct
// It contains double variables that hold the acceleration value, reverse value, total revs per minute, revs per millisecond, and the turning angle
struct Car
{
public:
	double dAccelerate, dReverse, dAccelerateMod, dReverseMod, dTurnMod, dTotalRPM;
	double dRevsPerMSec;
	float angle;
	Gear gear;
	int CurrentGear;
	Car()
	{
		dAccelerate = 0;
		dReverse = 0;
		angle = 0;
		dTotalRPM = 0;
		gear = gear1;
		dRevsPerMSec = 0;
	}
};

// Array of objects from the Car struct
Car carAttr[9];
void ResetStats()
{
	checkPoint = 0;
	checkPointAI = 0;
	TheCamera.setPosition(&camStart);
	TheOpponent._pos = OppStart;
	LapTimes[0] = 0;
	LapTimes[1] = 0;
	LapTimes[2] = 0;
	bCkeckpoints[0] = true;
	bCkeckpoints[1] = false;
	bCkeckpoints[2] = false;
	bCkeckpoints[3] = false;
	bCkeckpointsAI[0] = true;
	bCkeckpointsAI[1] = false;
	bCkeckpointsAI[2] = false;
	bCkeckpointsAI[3] = false;
	for(int i = 0; i < 9; i++)
	{
		carAttr[i].angle = 0;
		carAttr[i].dAccelerate = 0;
	}
	TheCamera._look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	TheOpponent._look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}
void AddNewHighScore()
{
	
	bool newRecord = false;
	if(seconds < scoreDataReturn[0].highScore) 
	{
		recordPlace = 0;
		for (int i = 3; i > 0;i--)
		{
			scoreDataReturn[i+1] = scoreDataReturn[i];
		}
		newRecord=true;
	}
	else if(seconds < scoreDataReturn[1].highScore)
	{
		recordPlace = 1;
		for (int i = 3; i > 1;i--)
		{
			scoreDataReturn[i+1] = scoreDataReturn[i];
		}
		newRecord=true;
	}
	else if(seconds < scoreDataReturn[2].highScore)
	{
		recordPlace = 2;
		for (int i = 3; i > 2;i--)
		{
			scoreDataReturn[i+1] = scoreDataReturn[i];
		}
		newRecord=true;
	}
	else if(seconds < scoreDataReturn[3].highScore)
	{
		recordPlace = 3;
		for (int i = 3; i > 3;i--)
		{
			scoreDataReturn[i+1] = scoreDataReturn[i];
		}
		newRecord=true;
	}
	else if(seconds < scoreDataReturn[4].highScore)
	{
		recordPlace = 4;
		newRecord=true;
	}

	if(newRecord)
	{
		dwFinalTick = GetTickCount();
		CurrentGameState = FastestTimes;
		NextGameState = Credits;
		char TempBuff[80] = "Please enter your initials in the format FML. (First Middle Last)";

		hMHighScore = CreateWindowEx(NULL, "WinClass2", "New Track Record!", WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE, Width/2 - 230,Height/2 - 75, 460, 150,	NULL, NULL, hNewInstance,	NULL);

		CreateWindowEx(NULL, "button", "Enter", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 75, 400, 20, hMHighScore, (HMENU)BUT_HighScore, hNewInstance, NULL);

		hHighScore = CreateWindowEx(NULL, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 25, 50, 400, 20, hMHighScore, (HMENU)BOX_HighScore, hNewInstance, NULL);

		HDC hdc = GetDC(hMHighScore);

		::TextOutA(hdc, 25, 20, TempBuff, (int)strlen(TempBuff));
	}

}

void GameFinished()
{
	D3DXMATRIX I;
		D3DXMATRIX i, tripler, grow;

	D3DXMatrixIdentity(&i);
		
	D3DXMatrixIdentity(&I);
	if(TheTerrain)
		TheTerrain->draw(&I, false);



	TheCamera.getViewMatrix(&V);
	Device->SetTransform(D3DTS_VIEW, &V);
	TheCamera.getPosition(&p);
	int height = TheTerrain->getHeight(p.x, p.z);
	p.y = height + 20;
	TheCamera.setPosition(&p);
	TheCamera.getLook(&t);
	renderSkybox(Device, TheCamera);

	D3DCOLOR c = D3DCOLOR_ARGB(255,255,255,255);
	

	D3DXVECTOR3 pos2(Width/2, Height* 3/5, 0), center2(128, 128, 0);
	D3DXVECTOR3 pos(Width/2, Height/5, 0), center(128, 64, 0);
	spritePlaceBanner->Begin(NULL);
	spritePlaceBanner->Draw(TexFinish, NULL, &center, &pos, c);
	if(checkPoint > checkPointAI)
		Place = 1;
	else
		Place = 2;
	if(Place == 1)
		spritePlaceBanner->Draw(Tex1stPlace, NULL, &center2, &pos2, c);
	else if(Place == 2)
		spritePlaceBanner->Draw(Tex2ndPlace, NULL, &center2, &pos2, c);
	
	spritePlaceBanner->End();

	if(TheInput.KeyTest(DIK_RETURN))
	{
		ResetStats();
		CurrentGameState = Credits;
		AddNewHighScore();
	}


}

void countdown(GameState GS)
{

			D3DXMATRIX I;
		D3DXMATRIX i, tripler, grow;

	D3DXMatrixIdentity(&i);
		
	D3DXMatrixIdentity(&I);
	if(TheTerrain)
		TheTerrain->draw(&I, false);



	TheCamera.getViewMatrix(&V);
	Device->SetTransform(D3DTS_VIEW, &V);
	TheCamera.getPosition(&p);
	int height = TheTerrain->getHeight(p.x, p.z);
	p.y = height + 20;
	TheCamera.setPosition(&p);
	TheCamera.getLook(&t);

	D3DXVECTOR3 countpos(Width/2, Height/2, 0), center(100, 100, 0);
	D3DCOLOR c = D3DCOLOR_ARGB(255,255,255,255);


	renderSkybox(Device, TheCamera);
	spriteCountDown->Begin(NULL);
	if(countDown < 2)
		spriteCountDown->Draw(TexCount3, NULL, &center, &countpos, c);	
	else if(countDown < 3)
		spriteCountDown->Draw(TexCount2, NULL, &center, &countpos, c);
	else if(countDown < 4)
		spriteCountDown->Draw(TexCount1, NULL, &center, &countpos, c);
	else if(countDown < 5)
		spriteCountDown->Draw(TexCountGo, NULL, &center, &countpos, c);
	else if(countDown >= 5)
	{
		CurrentGameState = GS;
		countDown = 0;
	}
	spriteCountDown->End();
			
	if(fpuSub(GetTickCount(), dwFinalTick) > 1000)
	{
		countDown = fpuAdd(countDown, 1);
		
		dwInitialTick = dwFinalTick;
		dwFinalTick = GetTickCount();		
	}
}

void DisplayTrackTimes()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect2;
	rect2.left=Width - 200;
	rect2.right=Width;
	rect2.top=0;
	rect2.bottom=rect2.top+20;

	// Displaying the text
	sprintf(buffers, "Lap 1 Time: %i", LapTimes[0]);

	m_font->DrawText(NULL, buffers, 50, &rect2, 0, fontColor );

	rect2.left=Width - 200;
	rect2.right=Width;
	rect2.top=30;
	rect2.bottom=rect2.top+20;

	// Displaying the text
	sprintf(buffers, "Lap 2 Time: %i", LapTimes[1]);

	m_font->DrawText(NULL, buffers, 50, &rect2, 0, fontColor );

	rect2.left=Width - 200;
	rect2.right=Width;
	rect2.top=60;
	rect2.bottom=rect2.top+20;

	// Displaying the text
	sprintf(buffers, "Lap 3 Time: %i", LapTimes[2]);

	m_font->DrawText(NULL, buffers, 50, &rect2, 0, fontColor );
}

// Function to display time
void DisplayTime()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect2;
	rect2.left=2;
	rect2.right=780;
	rect2.top=0;
	rect2.bottom=rect2.top+20;

	// Displaying the text
	sprintf(buffers, "Time: %i seconds", seconds);

	m_font->DrawText(NULL, buffers, 50, &rect2, 0, fontColor );
}

void DisplayPosition()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect1;
	rect1.left=2;
	rect1.right=780;
	rect1.top=40;
	rect1.bottom=rect1.top+20;

	// Displaying the text
	sprintf(buffers2, "X: %f, Y: %f, Z: %f", p.x, p.y, p.z);

	m_font->DrawText(NULL, buffers2, 150, &rect1, 0, fontColor );
}

void DisplaySpeed()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect3;
	rect3.left=2;
	rect3.right=780;
	rect3.top=60;
	rect3.bottom=rect3.top+20;

	// setting the position of font
	RECT rect4;
	rect4.left=2;
	rect4.right=780;
	rect4.top=80;
	rect4.bottom=rect4.top+20;

	double dAccelx10 = 100 * carAttr[0].dAccelerate;

	// Displaying the text
	sprintf(buffers3, "Velocity: %f", dAccelx10);

	m_font->DrawText(NULL, buffers3, 250, &rect3, 0, fontColor );

	// Displaying the text
	sprintf(buffers4, "Velocity: %f", carAttr[0].dReverse);

	m_font->DrawText(NULL, buffers4, 250, &rect4, 0, fontColor );
}

void DisplayDriveTime()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect5;
	rect5.left=2;
	rect5.right=780;
	rect5.top=100;
	rect5.bottom=rect5.top+20;

	// Displaying the text
	sprintf(buffers5, "Time: %f seconds", dVelSeconds);

	m_font->DrawText(NULL, buffers5, 50, &rect5, 0, fontColor );
}

void DisplayRPM()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect6;
	rect6.left=2;
	rect6.right=780;
	rect6.top=120;
	rect6.bottom=rect6.top+20;

	// Displaying the text
	sprintf(buffers7, "%f RPM", carAttr[0].dTotalRPM);

	m_font->DrawText(NULL, buffers7, 50, &rect6, 0, fontColor );
}

void DisplayGears()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect7;
	rect7.left=2;
	rect7.right=780;
	rect7.top=140;
	rect7.bottom=rect7.top+20;

	// Displaying the text
	sprintf(buffers6, "Gear: %i", carAttr[0].CurrentGear);

	m_font->DrawText(NULL, buffers6, 50, &rect7, 0, fontColor );
}

void SetAttributes()
{
	// Jimmy and Dan
	carAttr[0].dAccelerateMod = 0.00001f;
	carAttr[0].dReverseMod = 0.00001f;
	carAttr[0].dTurnMod = .000001f;

	// Rico
	carAttr[1].dAccelerateMod = 0.0000095f;
	carAttr[1].dReverseMod = 0.0000095f;
	carAttr[1].dTurnMod = .0000025f;

	// Miguel y Miguelita
	carAttr[2].dAccelerateMod = 0.000085f;
	carAttr[2].dReverseMod = 0.000085f;
	carAttr[2].dTurnMod = .00000015f;
	
	// Jimmy Slicks
	carAttr[3].dAccelerateMod = 0.000015f;
	carAttr[3].dReverseMod = 0.000015f;
	carAttr[3].dTurnMod = .00000005f;

	// Angry Janitor Bob
	carAttr[4].dAccelerateMod = 0.0000075f;
	carAttr[4].dReverseMod = 0.0000075f;
	carAttr[4].dTurnMod = .0000002f;

	// Albert Beakers
	carAttr[5].dAccelerateMod = 0.0000075f;
	carAttr[5].dReverseMod = 0.0000075f;
	carAttr[5].dTurnMod = .0000003f;

	// Flower Power
	carAttr[6].dAccelerateMod = 0.0000085f;
	carAttr[6].dReverseMod = 0.0000085f;
	carAttr[6].dTurnMod = .0000003f;

	// Do$h Diva$
	carAttr[7].dAccelerateMod = 0.0000125f;
	carAttr[7].dReverseMod = 0.0000125f;
	carAttr[7].dTurnMod = .00000015f;
}

void SetMaterials()
{
	// Setting materials
	mtrlRed = d3d::RED_MTRL;
	mtrlWhite = d3d::WHITE_MTRL;
	mtrlBlack = d3d::BLACK_MTRL;
	mtrlYellow = d3d::YELLOW_MTRL;
	mtrlGreen = d3d::GREEN_MTRL;
	mtrlBlue = d3d::BLUE_MTRL;
}

void quartertrack(D3DXVECTOR3 pos)
{
	if(bCkeckpoints[0])
	{
		if(Quarts[0].isPointInside(pos))
		{
			checkPoint++;
			bCkeckpoints[1] = true;
			bCkeckpoints[0] = false;
		}
	}
	if(bCkeckpoints[1])
	{
		if(Quarts[1].isPointInside(pos))
		{
			checkPoint++;
			bCkeckpoints[2] = true;
			bCkeckpoints[1] = false;
		}
	}
	if(bCkeckpoints[2])
	{
		if(Quarts[2].isPointInside(pos))
		{
			checkPoint++;
			bCkeckpoints[3] = true;
			bCkeckpoints[2] = false;
		}
	}
	if(bCkeckpoints[3])
	{
		if(Quarts[3].isPointInside(pos))
		{
			checkPoint++;
			bCkeckpoints[0] = true;
			bCkeckpoints[3] = false;
		}
	}


}
void quartertrackAI(D3DXVECTOR3 pos)
{
	if(bCkeckpointsAI[0])
	{
		if(Quarts[0].isPointInside(pos))
		{
			checkPointAI++;
			bCkeckpointsAI[1] = true;
			bCkeckpointsAI[0] = false;
		}
	}
	if(bCkeckpointsAI[1])
	{
		if(Quarts[1].isPointInside(pos))
		{
			checkPointAI++;
			bCkeckpointsAI[2] = true;
			bCkeckpointsAI[1] = false;
		}
	}
	if(bCkeckpointsAI[2])
	{
		if(Quarts[2].isPointInside(pos))
		{
			checkPointAI++;
			bCkeckpointsAI[3] = true;
			bCkeckpointsAI[2] = false;
		}
	}
	if(bCkeckpointsAI[3])
	{
		if(Quarts[3].isPointInside(pos))
		{
			checkPointAI++;
			bCkeckpointsAI[0] = true;
			bCkeckpointsAI[3] = false;
		}
	}
}

bool Setup()
{
	time_t curr;
	tm local;
	time(&curr); // get current time_t value
	local=*(localtime(&curr)); // dereference and assign
	sprintf(currentDate, "%i/%i/%i", local.tm_mon+1, local.tm_mday, local.tm_year+1900);

	OpponentX.init(Device, "Car.x");

	D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);

	TheTerrain = new Terrain(Device, "SQTR.raw", 512,512,10,.2f);
	TheTerrain->genTexture(&lightDirection);
	TheTerrain->loadTexture("SQTR.jpg");

	D3DXCreateSprite(Device, &SpriteCredits);
	D3DXCreateSprite(Device, &SpriteMap);
	for (int i = 0; i < 10; i++)
	D3DXCreateSprite(Device, &spriteRacers[i]);
	D3DXCreateSprite(Device, &spriteSelector);
	D3DXCreateSprite(Device, &spriteTitleScreen);
	D3DXCreateSprite(Device, &spriteCountDown);
	D3DXCreateSprite(Device, &spritePlaceBanner);
	D3DXCreateSprite(Device, &spriteFastestTimes);
	
	
	D3DXCreateTextureFromFile(Device, "SQTR.jpg", &TexMap);
	D3DXCreateTextureFromFile(Device, "SQTR.jpg", &TexRacers);
	D3DXCreateTextureFromFile(Device, "Count3.png", &TexCount3);
	D3DXCreateTextureFromFile(Device, "Count2.png", &TexCount2);
	D3DXCreateTextureFromFile(Device, "Count1.png", &TexCount1);
	D3DXCreateTextureFromFile(Device, "CountGO.png", &TexCountGo);
	D3DXCreateTextureFromFile(Device, "1stBanner.png", &Tex1stPlace);
	D3DXCreateTextureFromFile(Device, "2ndBanner.png", &Tex2ndPlace);
	D3DXCreateTextureFromFile(Device, "Finish.png", &TexFinish);
	D3DXCreateTextureFromFile(Device, "Things2.png", &TexCar);
	D3DXCreateTextureFromFile(Device, "Selector1366.png", &TexSelector);
	if(Width == 1920)
	{
		D3DXCreateTextureFromFile(Device, "Credits.png", &TexCredits);
		D3DXCreateTextureFromFile(Device, "TitleScreen1.png", &TexTitleScreen);
		D3DXCreateTextureFromFile(Device, "FastestTimes.png", &TexFastestTimes);
	}
	else if(Width == 1366)
	{
		D3DXCreateTextureFromFile(Device, "Credits1366.png", &TexCredits);
		D3DXCreateTextureFromFile(Device, "TitleScreen1366.png", &TexTitleScreen);
	}
	else if(Width == 1280)
	{
		D3DXCreateTextureFromFile(Device, "Credits1280.png", &TexCredits);
		D3DXCreateTextureFromFile(Device, "TitleScreen1280.png", &TexTitleScreen);
		D3DXCreateTextureFromFile(Device, "FastestTimes1280.png", &TexFastestTimes);
	}

	D3DXCreateFont(Device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );
	D3DXCreateFont(Device, 30, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font2 );

	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	// set blending factors so that alpha component determines transparency
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	SetMaterials();

	bCkeckpoints[0] = true;
	bCkeckpoints[1] = false;
	bCkeckpoints[2] = false;
	bCkeckpoints[3] = false;
	bCkeckpointsAI[0] = true;
	bCkeckpointsAI[1] = false;
	bCkeckpointsAI[2] = false;
	bCkeckpointsAI[3] = false;

	LapTimes[0] = 0;
	LapTimes[1] = 0;
	LapTimes[2] = 0;


	D3DXVECTOR3 temp;
	temp.x = -2300;
	temp.y = 30;
	temp.z = 667;
	Quarts[3]._min = temp;
	temp.x = -1600;
	temp.y = 70;
	temp.z = 781;
	Quarts[3]._max = temp;

	temp.x = 667;
	temp.y = 30;
	temp.z = 1600;
	Quarts[0]._min = temp;
	temp.x = 781;
	temp.y = 70;
	temp.z = 2300;
	Quarts[0]._max = temp;

	temp.x = 1600;
	temp.y = 30;
	temp.z = -781;
	Quarts[1]._min = temp;
	temp.x = 2300;
	temp.y = 70;
	temp.z = -667;
	Quarts[1]._max = temp;

	temp.x = -1600;
	temp.y = 30;
	temp.z = -2300;
	Quarts[2]._min = temp;
	temp.x = -781;
	temp.y = 70;
	temp.z = -667;
	Quarts[2]._max = temp;

	std::list<D3DXVECTOR3> Way, Way2;
	
	//EndStraight
	Way.push_back(D3DXVECTOR3(-2000, 58, 800));
	//corner
	Way.push_back(D3DXVECTOR3(-1650, 58, 1700));
	//beginStraight
	Way.push_back(D3DXVECTOR3(-1100, 58, 1800));
	//EndStraight
	Way.push_back(D3DXVECTOR3(800, 58, 1800));
	//corner
	Way.push_back(D3DXVECTOR3(1650, 58, 1700));
	//beginstraight
	Way.push_back(D3DXVECTOR3(1800, 58, 1100));
	//endstraight
	Way.push_back(D3DXVECTOR3(2000, 58, -800));
	//corner
	Way.push_back(D3DXVECTOR3(1650, 58, -1700));
	//beginstraight
	Way.push_back(D3DXVECTOR3(1100, 58, -1800));
	//endstraight
	Way.push_back(D3DXVECTOR3(-800, 58, -2000));
	//corner
	Way.push_back(D3DXVECTOR3(-1650, 58, -1700));
	//beginstraight
	Way.push_back(D3DXVECTOR3(-1800, 58, -1100));
	//loops
	Way2 = Way;

	m_Waypoints = Way;
	curWaypoint =m_Waypoints.begin();
	//paths->AddWayPoint(D3DXVECTOR3(-2200, 58, 800));
	//paths->AddWayPoint(D3DXVECTOR3(-1600, 58, 1600));
	//paths->AddWayPoint(D3DXVECTOR3(800, 58, 2300));
	//paths->AddWayPoint(D3DXVECTOR3(1600, 58, 1600));
	//paths->AddWayPoint(D3DXVECTOR3(2300, 58, -800));
	//paths->AddWayPoint(D3DXVECTOR3(1600, 58, -1600));
	//paths->AddWayPoint(D3DXVECTOR3(-800, 58, -2300));
	//paths->AddWayPoint(D3DXVECTOR3(-1600, 58, -1600));


	//CreateWorldCube();

	//build skybox
	BuildSkybox(Device);

	SetAttributes();

	TheOpponent.setPosition(&OppStart);

	//
	// set camera
	//
	D3DXVECTOR3 dir(0.0f, -1.0f, 0.0f);
	D3DXVECTOR3 pos(0.0f, 0.0, 0.0f);
	TheCamera.setPosition(&camStart);
	TheCamera.getPosition(&p);
	TheCamera.getLook(&t);
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)Width / (float)Height,
		1.0f,
		10000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	Device->SetRenderState(D3DRS_LIGHTING, true);

	// ambient light
	Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255,255,255));

	return true;
}
void Cleanup()
{
	//for(int z = 0; z < 6; z++)
	//{
	//	walls[z]->Release();
	//}
	TheInput.CleanUpInput();


	d3d::Delete<Terrain*>(TheTerrain);
}
long prevmouseX = 0, prevMouseY = 0;
bool Display(float timeDelta)
{
	if( Device )
	{		

		TheInput.MouseUpdate();
		TheInput.KeyUpdate();
		TheInput.JoyUpdate();

		Device->SetRenderState(D3DRS_LIGHTING, true);
			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
			Device->BeginScene();
			Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			
			char buffersf[80];

		HRESULT hr;

		D3DXVECTOR3 opPos, OpDir;
		
		D3DXVECTOR3 f, lastPos;
		D3DXMATRIX I;
		D3DXMATRIX i, tripler, grow;
		static float SelectorType = 1;
		//titlescreen stuffs
		D3DXVECTOR3 Titlepos, SinglePos(Width * 1/25,Height * 1/5,0),OnlinePos(Width * 1/12,Height * 2/7,0), CreditsPos(Width * 17/100,Height * 35/100,0), StoryPos(Width * 24/100,Height * 43/100,0), TimesPos(Width * 20/100,Height * 53/100,0);
		if(Width == 1920)
		{
			SinglePos.x = Width * 10/100;
			SinglePos.y = Height * 33/100;
		

			OnlinePos.x = Width * 15/100;
			OnlinePos.y = Height * 42/100;
				

			CreditsPos.x = Width * 27/100;
			CreditsPos.y = Height * 55/100;
				

			StoryPos.x = Width * 37/100;
			StoryPos.y = Height * 63/100;
				

			TimesPos.x = Width * 32/100;
			TimesPos.y = Height * 81/100;
			
		}
		else if(Width == 1280)
		{
			SinglePos.x = Width * 5/100;
			SinglePos.y = Height * 33/100;
		

			OnlinePos.x = Width * 8/100;
			OnlinePos.y = Height * 45/100;
				

			CreditsPos.x = Width * 18/100;
			CreditsPos.y = Height * 55/100;
				

			StoryPos.x = Width * 25/100;
			StoryPos.y = Height * 65/100;
				

			TimesPos.x = Width * 20/100;
			TimesPos.y = Height * 85/100;
			
		}
		D3DCOLOR TitleColor = D3DCOLOR_ARGB(255,255,255,255);
		RECT TitleRect;
		long MouseX = TheInput.MouseXTest(), MouseY = TheInput.MouseYTest();
			// set color of font
			D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

			// setting the position of font
			RECT rect2;

			bool asdf = true;	
		switch(CurrentGameState)
		{
		case TitleScreen:
			if(asdf)
			{

			}
			TitleRect.left = 0;
			TitleRect.right = Width;
			TitleRect.top = 0;
			TitleRect.bottom = Height;
			Titlepos.x = 0;
			Titlepos.y = 0;
			Titlepos.z = 1;

			spriteTitleScreen->Begin(NULL);
			hr = spriteTitleScreen->Draw(TexTitleScreen, &TitleRect, NULL, &Titlepos, TitleColor);
			spriteTitleScreen->End();

			if(SelectorType < 2 )
			{
				spriteSelector->Begin(NULL);
				hr = spriteSelector->Draw(TexSelector, NULL, NULL, &SinglePos, TitleColor);
				spriteSelector->End();
				if(fpuSub(GetTickCount(), dwFinalTick) > 100)
				{
					if(TheInput.KeyTest(DIK_RETURN))
					{
						CurrentGameState = GameStart;
						NextGameState = SinglePlayer;
					}
				}
			}
			else if(SelectorType < 3 )
			{
				spriteSelector->Begin(NULL);
				hr = spriteSelector->Draw(TexSelector, NULL, NULL, &OnlinePos, TitleColor);
				spriteSelector->End();
				if(fpuSub(GetTickCount(), dwFinalTick) > 100)
				{
				if(TheInput.KeyTest(DIK_RETURN))
				{
					CurrentGameState = OnlineMultiplayer;
					NextGameState = OnlineMultiplayer;
				}
				}
			}

			else if(SelectorType < 4 )
			{
				spriteSelector->Begin(NULL);
				hr = spriteSelector->Draw(TexSelector, NULL, NULL, &CreditsPos, TitleColor);
				spriteSelector->End();
				if(fpuSub(GetTickCount(), dwFinalTick) > 100)
				{
				if(TheInput.KeyTest(DIK_RETURN))
				{
					CurrentGameState = Credits;
					NextGameState = Credits;
				}
				}
			}
			else if(SelectorType < 5 )
			{
				spriteSelector->Begin(NULL);
				hr = spriteSelector->Draw(TexSelector, NULL, NULL, &StoryPos, TitleColor);
				spriteSelector->End();
				if(fpuSub(GetTickCount(), dwFinalTick) > 100)
				{
				if(TheInput.KeyTest(DIK_RETURN))
				{
					CurrentGameState = Story;
					NextGameState = Story;
				}
				}
			}
			else if(SelectorType <= 6 )
			{
				spriteSelector->Begin(NULL);
				hr = spriteSelector->Draw(TexSelector, NULL, NULL, &TimesPos, TitleColor);
				spriteSelector->End();
				if(fpuSub(GetTickCount(), dwFinalTick) > 100)
				{
				if(TheInput.KeyTest(DIK_RETURN))
				{
					dwFinalTick = GetTickCount();
					CurrentGameState = FastestTimes;
					NextGameState = TitleScreen;
				}
				}
			}
			if(TheInput.KeyTest(DIK_S) || TheInput.KeyTest(DIK_DOWN))
			{
				SelectorType+=.0025;
				if(SelectorType > 6)
					SelectorType = 1;
			}
			if(TheInput.KeyTest(DIK_W) || TheInput.KeyTest(DIK_UP))
			{
				SelectorType-=.0025;
				if(SelectorType < 1)
					SelectorType = 6;
			}
			break;
		case SinglePlayer:

			
			D3DXMatrixIdentity(&i);
		
			D3DXMatrixIdentity(&I);
			D3DXMatrixIdentity(&tripler);
			D3DXMatrixIdentity(&grow);
			if(TheTerrain)
				TheTerrain->draw(&I, false);

			Movement(Car1);
			AI(Car2);

			//TheOpponent.getPosition(&opPos);
			//TheOpponent.getLook(&OpDir);
			Device->SetTexture(0, TexCar);
			D3DXMatrixTranslation(&tripler, TheOpponent._pos.x, TheTerrain->getHeight(TheOpponent._pos.x,TheOpponent._pos.z), TheOpponent._pos.z);
			D3DXMatrixRotationYawPitchRoll(&grow, (carAttr[Car2].angle*1000 * D3DX_PI) + D3DX_PI/2, 0, 0);
			D3DXMatrixMultiply(&tripler, &grow, &tripler);
			D3DXMatrixScaling(&grow, 20,15,20);
			D3DXMatrixMultiply(&tripler, &grow, &tripler);
			Device->SetTransform(D3DTS_WORLD, &tripler);
			OpponentX.Draw();
			TheCamera.getViewMatrix(&V);
			Device->SetTransform(D3DTS_VIEW, &V);
			TheCamera.getPosition(&p);
			TheCamera.setPosition(&p);
			TheCamera.getLook(&t);



			quartertrack(p);

			//DisplayTime();
			//DisplayPosition();
			//DisplaySpeed();
			//DisplayGears();
			DisplayTrackTimes();


			renderSkybox(Device, TheCamera);

			
			if(fpuSub(GetTickCount(), dwFinalTick) > 1000)
			{
				seconds = fpuAdd(seconds, 1);
				if(checkPoint/4 < 1)
					LapTimes[0] = fpuAdd(LapTimes[0], 1);
				else if(checkPoint/4 < 2)
					LapTimes[1] = fpuAdd(LapTimes[1], 1);
				else if(checkPoint/4 < 3)
					LapTimes[2] = fpuAdd(LapTimes[2], 1);
				else 
					CurrentGameState = GameOver;
				dwInitialTick = dwFinalTick;
				dwFinalTick = GetTickCount();

				//countDown = fpuAdd(countDown, 1);
			}
			break;
		case GamePlay:
			break;
		case OnlineMultiplayer:
			break;
		case Credits:
			TitleRect.left = 0;
			TitleRect.right = Width;
			TitleRect.top = 0;
			TitleRect.bottom = 21000;
			SpriteCredits->Begin(NULL);
			SpriteCredits->Draw(TexCredits, &TitleRect, NULL, &CredPos, TitleColor);
			SpriteCredits->End();
			CredPos.y-=.1;
			if(CredPos.y < -6000)
			{
				CurrentGameState = TitleScreen;
				CredPos.y = 0;
			}
			break;
		case Story:
			break;
		case FastestTimes:
			TitleRect.left = 0;
			TitleRect.right = Width;
			TitleRect.top = 0;
			TitleRect.bottom = Height;
			Titlepos.x = 0;
			Titlepos.y = 0;
			Titlepos.z = 0;
			spriteFastestTimes->Begin(NULL);
			spriteFastestTimes->Draw(TexFastestTimes, &TitleRect, NULL, &Titlepos, TitleColor);
			spriteFastestTimes->End();
			

			rect2.left=Width * 18/100;
			rect2.right=rect2.left + 60;
			rect2.top=Height * 25/100;
			rect2.bottom=rect2.top+30;

			// Displaying the text
			sprintf(buffersf, "%s  ", scoreDataReturn[0].userInitial);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );
			
			rect2.left=Width * 38/100;
			rect2.right=rect2.left + 50;
			rect2.top=Height * 25/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%i  ", scoreDataReturn[0].highScore);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 56/100;
			rect2.right=rect2.left + 130;
			rect2.top=Height * 25/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%s  ", scoreDataReturn[0].dateAccomplished);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 18/100;
			rect2.right=rect2.left + 60;
			rect2.top=Height * 33/100;
			rect2.bottom=rect2.top+30;

			// Displaying the text
			sprintf(buffersf, "%s  ", scoreDataReturn[1].userInitial);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );
			
			rect2.left=Width * 38/100;
			rect2.right=rect2.left + 50;
			rect2.top=Height * 33/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%i  ", scoreDataReturn[1].highScore);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 56/100;
			rect2.right=rect2.left + 130;
			rect2.top=Height * 33/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%s  ", scoreDataReturn[1].dateAccomplished);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 18/100;
			rect2.right=rect2.left + 60;
			rect2.top=Height * 41/100;
			rect2.bottom=rect2.top+30;

			// Displaying the text
			sprintf(buffersf, "%s  ", scoreDataReturn[2].userInitial);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );
			
			rect2.left=Width * 38/100;
			rect2.right=rect2.left + 50;
			rect2.top=Height * 41/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%i  ", scoreDataReturn[2].highScore);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 56/100;
			rect2.right=rect2.left + 130;
			rect2.top=Height * 41/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%s  ", scoreDataReturn[2].dateAccomplished);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 18/100;
			rect2.right=rect2.left + 60;
			rect2.top=Height * 49/100;
			rect2.bottom=rect2.top+30;

			// Displaying the text
			sprintf(buffersf, "%s  ", scoreDataReturn[3].userInitial);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );
			
			rect2.left=Width * 38/100;
			rect2.right=rect2.left + 50;
			rect2.top=Height * 49/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%i  ", scoreDataReturn[3].highScore);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 56/100;
			rect2.right=rect2.left + 130;
			rect2.top=Height * 49/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%s  ", scoreDataReturn[3].dateAccomplished);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 18/100;
			rect2.right=rect2.left + 60;
			rect2.top=Height * 57/100;
			rect2.bottom=rect2.top+30;

			// Displaying the text
			sprintf(buffersf, "%s  ", scoreDataReturn[4].userInitial);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );
			
			rect2.left=Width * 38/100;
			rect2.right=rect2.left + 50;
			rect2.top=Height * 57/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%i  ", scoreDataReturn[4].highScore);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );

			rect2.left=Width * 56/100;
			rect2.right=rect2.left + 130;
			rect2.top=Height * 57/100;
			rect2.bottom=rect2.top+30;

			sprintf(buffersf, "%s  ", scoreDataReturn[4].dateAccomplished);
			m_font2->DrawText(NULL, buffersf, 50, &rect2, 0, fontColor );
			if(fpuSub(GetTickCount(), dwFinalTick) > 100)
			{

				if(TheInput.KeyTest(DIK_RETURN))
				{
					CurrentGameState = NextGameState;
					dwFinalTick = GetTickCount();
				}
				
			}

			break;
		case SplitScreen:
			break;
		case GameStart:
			countdown(NextGameState);
			break;
		case GameOver:
			GameFinished();
			break;
		}
		Device->EndScene();
			Device->Present(0, 0, 0, 0);

	}

	return true;
}
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		//::PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case BUT_HighScore:
			{
				GetWindowText(hHighScore, initials ,4);
				sprintf(scoreDataReturn[recordPlace].userInitial,"%s", initials);
				sprintf(scoreDataReturn[recordPlace].dateAccomplished,"%s",currentDate);
				scoreDataReturn[recordPlace].highScore = seconds;

				for(int i = 0; i < 5; i++)
				{
					saveXFile(scoreDataReturn[i].userInitial, scoreDataReturn[i].highScore, scoreDataReturn[i].dateAccomplished, i+1);
				}

				::DestroyWindow(hMHighScore);
			}
			break;
		}

	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
		{
			::DestroyWindow(hwnd);
			::PostQuitMessage(0);
		}
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance, 
	PSTR cmdLine,
	int showCmd)
{

	//saveXFile("CLK", 70, "03/19/13", 1);
	//saveXFile("BRW", 80, "03/19/13", 2);
	//saveXFile("CLK", 90, "03/19/13", 3);
	//saveXFile("BRW", 100, "03/19/13", 4);
	//saveXFile("ASD", 110, "03/19/13", 5);

	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

		cw.style         = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
	cw.lpfnWndProc   = (WNDPROC)d3d::WndProc; 
	cw.cbClsExtra    = 0;
	cw.cbWndExtra    = 0;
	cw.hInstance     = hInstance;
	cw.hIcon         = LoadIcon(0, IDI_APPLICATION);
	cw.hCursor       = LoadCursor(0, IDC_ARROW);
	cw.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	cw.lpszMenuName  = 0;
	cw.lpszClassName = "WinClass2";

	if( !RegisterClass(&cw)) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}

	if(!TheInput.SetupInput(hinstance, mainHWND))
	{
		::MessageBox(0, "TheInput.SetupInput(hinstance, mainHWND) - FAILED", 0, 0);
		return 0;
	}
					

	LoadXFile();
	dwInitialTick = GetTickCount();
	dwFinalTick = dwInitialTick;

	d3d::EnterMsgLoop( Display );


	Cleanup();
	Device->Release();
	return 0;
}
D3DXVECTOR3 Seek(D3DXVECTOR3 TargetPos, CarType car)
{
	D3DXVECTOR3 DesiredVelocity, vec3 = TargetPos - TheOpponent._pos;
	D3DXVec3Normalize(&DesiredVelocity, &vec3);
	vec3 = DesiredVelocity - TheOpponent._look;
	D3DXVec3Normalize(&DesiredVelocity, &vec3);


	return DesiredVelocity;
}

D3DXVECTOR3 FollowPath(CarType car)
{
	D3DXVECTOR3 Distance = CurrentWaypoint() - TheOpponent._pos;
	//Move to the next waypoint uf close enough to to current Target
	if(D3DXVec3LengthSq(&Distance) < 10)
	{
		SetNextWaypoint();
	}
	if(!Finished())
	{
		return Seek(CurrentWaypoint(), car);
	}
}

void AI(CarType car)
{
	bool BoolA = false, BoolD = false, BoolW = false, BoolS = false, BoolSpace = false;
	/*BoolA = true;*/ BoolW = true;
	D3DXVECTOR3 Lookey;
	TheOpponent.getLook(&Lookey);
	D3DXVECTOR3  QWERT;
	QWERT = FollowPath(car);
	quartertrackAI(TheOpponent._pos);
	

	//if( QWERT.x >= Lookey.x + .05  || QWERT.z >= Lookey.z + .05 )
	//{
	//	BoolA = false;
	//	BoolD = true;
	//}
	//else if( QWERT.x <= Lookey.x - .05|| QWERT.z <= Lookey.z - .05)
	//{
	//	BoolD = false;
	//	BoolA = true;
	//}
	//else
 //		BoolD = BoolA = false;
		//if( QWERT.x >= Lookey.x + .05  || QWERT.z >= Lookey.z + .05 )
	//{
	//	BoolA = false;
	//	BoolD = true;
	//}
	//else if( QWERT.x <= Lookey.x - .05|| QWERT.z <= Lookey.z - .05)
	//{
	//	BoolD = false;
	//	BoolA = true;
	//}
	//else
 //		BoolD = BoolA = false;
	TheOpponent._look = QWERT;
	
	
	if(BoolA)
	{
		if(carAttr[car].angle > 0)
			carAttr[car].angle = 0;

		if(carAttr[car].dAccelerate != 0 || carAttr[car].dReverse != 0)
		{
			carAttr[car].angle -= carAttr[car].dTurnMod;
		}

		TheOpponent.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
	}

	if(!BoolA)
	{
		carAttr[car].angle = carAttr[car].angle * .9995f;
		TheOpponent.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
	}

	if(BoolD)
	{
		if(carAttr[car].angle < 0)
			carAttr[car].angle = 0;

		if(carAttr[car].dAccelerate != 0 || carAttr[car].dReverse != 0)
		{
			carAttr[car].angle += carAttr[car].dTurnMod;
		}

		TheOpponent.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
	}

	if(!BoolD)
	{
		carAttr[car].angle = carAttr[car].angle * .9995f;
		TheOpponent.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
	}

	if(BoolW)
	{
		carAttr[car].dReverse = 0;

		D3DXVECTOR3 lastpos, f;
		TheOpponent.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;

		if (carAttr[car].dAccelerate < 10)
		{
			carAttr[car].dAccelerate += carAttr[car].dAccelerateMod;		

			TheOpponent.walk(carAttr[car].dAccelerate);
		}

		else if (carAttr[car].dAccelerate > 10)
		{
			carAttr[car].dAccelerate = 10;
			TheOpponent.walk(carAttr[car].dAccelerate);
		}

		TheOpponent.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
		{
			TheOpponent.setPosition(&lastpos);

			TheOpponent.walk(carAttr[car].dAccelerate * -10);
			carAttr[car].dAccelerate = 0;
		}
		else
			TheOpponent.setPosition(&f);
	}

	if(!BoolW)
	{

		D3DXVECTOR3 lastpos, f;
		TheOpponent.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;

		if(carAttr[car].dAccelerate < .00001)
		{
			carAttr[car].dAccelerate = 0;
		}

		else if(carAttr[car].dAccelerate > .00001)
		{
			carAttr[car].dAccelerate *= .9995f;
			TheOpponent.walk(carAttr[car].dAccelerate);
		}

		TheOpponent.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
		{
			TheOpponent.setPosition(&lastpos);
			TheOpponent.walk(carAttr[car].dAccelerate * -3);
			carAttr[car].dAccelerate = 0;
		}
		else
			TheOpponent.setPosition(&f);
	}

	if(BoolS)
	{
		D3DXVECTOR3 lastpos, f;
		TheOpponent.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;


		carAttr[car].dAccelerate = 0;
		carAttr[car].dReverse -= carAttr[car].dReverseMod;

		if (carAttr[car].dReverse < -.30)
			carAttr[car].dReverse = -.30;

		TheOpponent.walk(carAttr[car].dReverse);

		TheOpponent.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
			TheOpponent.setPosition(&lastpos);
		else
			TheOpponent.setPosition(&f);
	}

	if(!BoolS)
	{
		D3DXVECTOR3 lastpos, f;
		TheOpponent.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;


		if (carAttr[car].dReverse == 0)
			carAttr[car].dReverse = 0;

		carAttr[car].dReverse = carAttr[0].dReverse * .9995f;

		TheOpponent.walk(carAttr[car].dReverse);

		TheOpponent.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
			TheOpponent.setPosition(&lastpos);
		else
			TheOpponent.setPosition(&f);
	}

	if(BoolSpace)
	{
		if(carAttr[car].dAccelerate > 0)
		{
			carAttr[car].dAccelerate = carAttr[car].dAccelerate * .995f;

			if(fpuSub(GetTickCount(), dwFinalTick) > 1)
			{
				dVelSeconds = fpuSub(dVelSeconds, .01);
				dwVelInitTick = dwVelFinalTick;
				dwVelFinalTick = GetTickCount();

				if(dVelSeconds < 0)
					dVelSeconds = 0;

				DisplayDriveTime();
			}

			dTempSeconds = dVelSeconds;
		}

		if(carAttr[car].dReverse > 0)
		{
			carAttr[car].dReverse = carAttr[car].dReverse * .995f;
		}
	}
}

void Movement(CarType car)
{
	long X = TheInput.JoylXTest();
	long Z = (TheInput.JoylZTest() - 32767) * -1;

	if(TheInput.KeyTest(DIK_A))
	{
		if(carAttr[car].angle > 0)
			carAttr[car].angle = 0;

		if(carAttr[car].dAccelerate != 0 || carAttr[car].dReverse != 0)
		{
			carAttr[car].angle -= carAttr[car].dTurnMod;
		}

		TheCamera.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
	}

	if(!(TheInput.KeyTest(DIK_A)))
	{
		carAttr[car].angle = carAttr[0].angle * .9995f;
		TheCamera.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
	}

	if(TheInput.KeyTest(DIK_D))
	{
		if(carAttr[car].angle < 0)
			carAttr[car].angle = 0;

		if(carAttr[car].dAccelerate != 0 || carAttr[car].dReverse != 0)
		{
			carAttr[car].angle += carAttr[car].dTurnMod;
		}

		TheCamera.racingYaw(carAttr[0].angle, carAttr[0].dAccelerate);
	}

	if(!(TheInput.KeyTest(DIK_D)))
	{
		carAttr[car].angle = carAttr[car].angle * .9995f;
		TheCamera.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
	}

	if(TheInput.KeyTest(DIK_W))
	{
		carAttr[car].dReverse = 0;

		D3DXVECTOR3 lastpos, f;
		TheCamera.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;

		if (carAttr[car].dAccelerate < 10)
		{
			carAttr[car].dAccelerate += carAttr[car].dAccelerateMod;		

			TheCamera.walk(carAttr[car].dAccelerate);
		}

		else if (carAttr[car].dAccelerate > 10)
		{
			carAttr[car].dAccelerate = 10;
			TheCamera.walk(carAttr[car].dAccelerate);
		}

		TheCamera.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
		{
			TheCamera.setPosition(&lastpos);

			TheCamera.walk(carAttr[car].dAccelerate * -3);
			carAttr[car].dAccelerate = 0;
		}
		else
			TheCamera.setPosition(&f);
	}

	if(!(TheInput.KeyTest(DIK_W)) && !Z)
	{

		D3DXVECTOR3 lastpos, f;
		TheCamera.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;

		if(carAttr[car].dAccelerate < .00001)
		{
			carAttr[car].dAccelerate = 0;
		}

		else if(carAttr[car].dAccelerate > .00001)
		{
			carAttr[car].dAccelerate *= .9995f;
			TheCamera.walk(carAttr[car].dAccelerate);
		}

		TheCamera.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
		{
			TheCamera.setPosition(&lastpos);
			TheCamera.walk(carAttr[car].dAccelerate * -3);
			carAttr[car].dAccelerate = 0;
		}
		else
			TheCamera.setPosition(&f);
	}

	if(TheInput.KeyTest(DIK_S))
	{
		D3DXVECTOR3 lastpos, f;
		TheCamera.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;


		carAttr[car].dAccelerate = 0;
		carAttr[car].dReverse -= carAttr[car].dReverseMod;

		if (carAttr[car].dReverse < -.30)
			carAttr[car].dReverse = -.30;

		TheCamera.walk(carAttr[car].dReverse);

		TheCamera.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
			TheCamera.setPosition(&lastpos);
		else
			TheCamera.setPosition(&f);
	}

	if(!(TheInput.KeyTest(DIK_S)) && !Z)
	{
		D3DXVECTOR3 lastpos, f;
		TheCamera.getPosition(&lastpos);
		float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
		lastpos.y = height + 20.0f;


		if (carAttr[car].dReverse == 0)
			carAttr[car].dReverse = 0;

		carAttr[car].dReverse = carAttr[0].dReverse * .9995f;

		TheCamera.walk(carAttr[car].dReverse);

		TheCamera.getPosition(&f);
		height = TheTerrain->getHeight(f.x, f.z);

		f.y = height + 20.0f;
		if (f.y != lastpos.y )
			TheCamera.setPosition(&lastpos);
		else
			TheCamera.setPosition(&f);
	}

	if(TheInput.KeyTest(DIK_SPACE))
	{
		if(carAttr[car].dAccelerate > 0)
		{
			carAttr[car].dAccelerate = carAttr[car].dAccelerate * .995f;

			if(fpuSub(GetTickCount(), dwFinalTick) > 1)
			{
				dVelSeconds = fpuSub(dVelSeconds, .01);
				dwVelInitTick = dwVelFinalTick;
				dwVelFinalTick = GetTickCount();

				if(dVelSeconds < 0)
					dVelSeconds = 0;

				DisplayDriveTime();
			}

			dTempSeconds = dVelSeconds;
		}

		if(carAttr[car].dReverse > 0)
		{
			carAttr[car].dReverse = carAttr[0].dReverse * .995f;
		}
	}

	if(X)
	{
		{
			if(carAttr[car].dAccelerate != 0 || carAttr[car].dReverse != 0)
			{
				carAttr[car].angle += carAttr[car].dTurnMod * X / 50;
			}
			TheCamera.racingYaw(carAttr[car].angle, carAttr[car].dAccelerate);
		}
	}	

	if(Z)
	{
		if (Z > 0)
		{

			carAttr[car].dReverse = 0;

			D3DXVECTOR3 lastpos, f;
			TheCamera.getPosition(&lastpos);
			float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
			lastpos.y = height + 20.0f;

			if (carAttr[car].dAccelerate < 10)
			{
				carAttr[car].dAccelerate += carAttr[car].dAccelerateMod * Z / 20000;		

				TheCamera.walk(carAttr[car].dAccelerate);
			}

			else if (carAttr[car].dAccelerate > 10)
			{
				carAttr[car].dAccelerate = 10;
				TheCamera.walk(carAttr[car].dAccelerate);
			}

			TheCamera.getPosition(&f);
			height = TheTerrain->getHeight(f.x, f.z);

			f.y = height + 20.0f;
			if (f.y != lastpos.y )
			{
				TheCamera.setPosition(&lastpos);

				TheCamera.walk(carAttr[car].dAccelerate * -3);
				carAttr[car].dAccelerate = 0;
			}
			else
				TheCamera.setPosition(&f);
		}
		else if (Z < 0)
		{
			if(carAttr[car].dAccelerate > 0)
			{
				carAttr[car].dAccelerate = carAttr[car].dAccelerate * .995f;

				if(fpuSub(GetTickCount(), dwFinalTick) > 1)
				{
					dVelSeconds = fpuSub(dVelSeconds, .01);
					dwVelInitTick = dwVelFinalTick;
					dwVelFinalTick = GetTickCount();

					if(dVelSeconds < 0)
						dVelSeconds = 0;

					DisplayDriveTime();
				}

				dTempSeconds = dVelSeconds;
			}

			if  (carAttr[car].dAccelerate < 0.0001)
			{
				D3DXVECTOR3 lastpos, f;
				TheCamera.getPosition(&lastpos);
				float height = TheTerrain->getHeight(lastpos.x, lastpos.z);
				lastpos.y = height + 20.0f;
				carAttr[car].dReverse -= carAttr[car].dReverseMod;

				if (carAttr[car].dReverse < -.30)
					carAttr[car].dReverse = -.30;

				TheCamera.walk(carAttr[car].dReverse);

				TheCamera.getPosition(&f);
				height = TheTerrain->getHeight(f.x, f.z);

				f.y = height + 20.0f;
				if (f.y != lastpos.y )
					TheCamera.setPosition(&lastpos);
				else
					TheCamera.setPosition(&f);
			}
		}
	}
}