#include "base.h"
//
// Globals
//

float avatarYaw;
HWND hMHighScore, hHighScore;
HINSTANCE hInstance, hNewInstance;
WNDCLASS cw;
char currentDate[11], initials[4];
D3DXMATRIX mview, mprojection,mworld;
float rotationSpeed =fpuDiv( 1.0f, 60.0f);
float forwardSpeed = 40.0f;
IDirect3DDevice9* Device = 0;
int recordPlace = -1;

Terrain* TheTerrain = 0;
input TheInput;

int x = GetSystemMetrics(SM_CXSCREEN);
int y = GetSystemMetrics(SM_CYSCREEN);
const int Width  = x;
const int Height = y;

bool gameover = false;

bool boolApples[10] = {true,true,true,true,true,true,true,true,true,true};
bool allfound = false, messageDone = true;
int numberFound = 10;
int numbertrees = 499, numberApples = 10;
D3DXVECTOR3 TreePositions[500], ApplePositions[10];

XFile Tree, Apple;

float aspectRatio = fpuDiv( (float)Width,(float)Height);


/////mirror tex
IDirect3DTexture9* MirrorTex = 0;

//camera
Camera TheCamera(Camera::LANDOBJECT);

LPDIRECT3DTEXTURE9 texMap;
LPDIRECT3DTEXTURE9 buttonstex;


// Font mesh
ID3DXFont *m_font;

ID3DXSprite* spriteMap;
ID3DXSprite* spritePlayer;
ID3DXSprite* spriteApple[10];
ID3DXSprite* spriteButtons;


// Double word value for creating a timer
DWORD dwFinalTick, dwInitialTick;

// Variables for holding the actual second count because using GetTickCount returns a millisecond
int seconds = 0, countDown = 0;
double dVelSeconds = 0, dTempSeconds = 0;
char buffers[50];
char buffers2[150];

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z, 
		   float nx, float ny, float nz,
		   float u, float v)
	{
		_x  = x;  _y  = y;  _z  = z;
		_nx = nx; _ny = ny; _nz = nz;
		_u  = u;  _v  = v;
	}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;

	static const DWORD FVF;
};
const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

//
// Framework Functions
//
// Function to display time
void DisplayTime()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect2;
    rect2.left=fpuMul( Width,fpuDiv( 90,100));
    rect2.right=Width;
    rect2.top=0;
    rect2.bottom=fpuAdd(rect2.top,20);

	// Displaying the text
	sprintf(buffers, "Time: %i seconds", seconds);

	m_font->DrawText(NULL, buffers, 50, &rect2, 0, fontColor );
}
void Collides()
{
	for (int i = 0; i < 10; i++)
	{
		if(boolApples[i])
		{
			if (TheCamera.GetPosition().x <= ApplePositions[i].x + 15) 
			{
				if(TheCamera.GetPosition().z <= ApplePositions[i].z + 15)
				{
					if (TheCamera.GetPosition().x >= ApplePositions[i].x - 15) 
					{
						if (TheCamera.GetPosition().z >= ApplePositions[i].z - 15)
						{
								boolApples[i] = false;
								numberFound--;
								ApplePositions[i].x = 500;
								ApplePositions[i].z = 500;
						}
					}
				}
			}
		}
	}
	
	for(int i = 0; i < 10; i++)
	{
		if(boolApples[i])
		{
			gameover = false;
			return;
		}
	}
	gameover = true;

}
void FastestTimeTests()
{
		bool newRecord = false;
	if(seconds < scoreDataReturn[0].highScore) 
	{
		recordPlace = 0;
		for (int i = 3; i > -1;i--)
		{
			scoreDataReturn[i+1] = scoreDataReturn[i];
		}
		newRecord=true;
	}
	else if(seconds < scoreDataReturn[1].highScore)
	{
		recordPlace = 1;
		for (int i = 3; i > 0;i--)
		{
			scoreDataReturn[i+1] = scoreDataReturn[i];
		}
		newRecord=true;
	}
	else if(seconds < scoreDataReturn[2].highScore)
	{
		recordPlace = 2;
		for (int i = 3; i > 1;i--)
		{
			scoreDataReturn[i+1] = scoreDataReturn[i];
		}
		newRecord=true;
	}
	else if(seconds < scoreDataReturn[3].highScore)
	{
		recordPlace = 3;
		for (int i = 3; i > 2;i--)
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
		char TempBuff[80] = "Please enter your initials in the format FML. (First Middle Last)";

		hMHighScore = CreateWindowEx(NULL, "WinClass2", "New Track Record!", WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE, Width/2 - 230,Height/2 - 75, 460, 150,	NULL, NULL, hNewInstance,	NULL);

		CreateWindowEx(NULL, "button", "Enter", WS_CHILD | WS_VISIBLE | BS_CENTER, 25, 75, 400, 20, hMHighScore, (HMENU)BUT_HighScore, hNewInstance, NULL);

		hHighScore = CreateWindowEx(NULL, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_UPPERCASE, 25, 50, 400, 20, hMHighScore, (HMENU)BOX_HighScore, hNewInstance, NULL);

		HDC hdc = GetDC(hMHighScore);

		::TextOutA(hdc, 25, 20, TempBuff, (int)strlen(TempBuff));
	}
}

void DrawMinimap()
{
	D3DCOLOR MapColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DCOLOR TrashColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	D3DCOLOR PlayerColor = D3DCOLOR_ARGB(255, 0, 0, 255);
	
	RECT mapRect;
	mapRect.left=0;
	mapRect.right=128;
	mapRect.top=0;
	mapRect.bottom=128;

	D3DXVECTOR3 mapPos(25, 25, 0);

	spriteMap->Begin(NULL);
	spriteMap->Draw(texMap, NULL, NULL, &mapPos, MapColor);
	spriteMap->End();

	mapRect.left=0;
	mapRect.right=8;
	mapRect.top=0;
	mapRect.bottom=8;

	D3DXVECTOR3 playerPos(fpuAdd(fpuDiv( TheCamera.GetPosition().x, 32), 89),fpuAdd(fpuDiv( -TheCamera.GetPosition().z, 32), 89), 0 );
	D3DXVECTOR3 pcenter(4, 4, 0);

	spritePlayer->Begin(NULL);
	spritePlayer->Draw(texMap, &mapRect, &pcenter, &playerPos, PlayerColor);
	spritePlayer->End();

	mapRect.left=0;
	mapRect.right=4;
	mapRect.top=0;
	mapRect.bottom=4;

	D3DXVECTOR3 applePos;
	D3DXVECTOR3 acenter(2, 2, 0);
	for(int i = 0; i < 10; i++)
	{
		if(boolApples[i])
		{
			applePos.x = fpuAdd(fpuDiv(ApplePositions[i].x, 32), 89);
			applePos.y = fpuAdd(fpuDiv(-ApplePositions[i].z, 32), 89);
			applePos.z = 0;
			spriteApple[i]->Begin(NULL);
			spriteApple[i]->Draw(texMap, &mapRect, &acenter, &applePos, TrashColor);
			spriteApple[i]->End();
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
	srand(GetTickCount());
	D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);

	TheTerrain = new Terrain(Device, "HM - Copy.raw", 1024,1024,5,1.0f);
	TheTerrain->genTexture(&lightDirection);
	TheTerrain->loadTexture("HMTex.jpg");

	Tree.init(Device, "trees/palm_tree_3.x");
	Apple.init(Device, "Apple.x");
	numbertrees = rand() % 300 - 1;
	float height;

	D3DXVECTOR3 f;
	f = TheCamera.GetPosition();
	f.y = TheTerrain->getHeight(f.x, f.z) + 20;
	TheCamera.setPosition(&f);

	
	D3DXCreateFont(Device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );
	//
	// Lights.
	//

	D3DXCreateSprite(Device, &spriteMap);
	D3DXCreateSprite(Device, &spriteButtons);
	D3DXCreateSprite(Device, &spritePlayer);
	for(int i = 0; i < 10; i = fpuAdd(i,1))
	{
		D3DXCreateSprite(Device, &spriteApple[i]);
	}
	
	D3DXCreateTextureFromFile(Device, "HMTex2.jpg", &texMap);
	srand(GetTickCount());

	D3DXVECTOR3 lightDir(0.707f, -0.707f, 0.707f);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = d3d::InitDirectionalLight(&lightDir, &color);

	Device->SetLight(0, &light);
	Device->LightEnable(0, true);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	for(int i = 0; i < numbertrees; i = fpuAdd(i,1))
	{
		TreePositions[i].x = rand() % 1400 - 900;
		TreePositions[i].z = rand() % 1275 - 300;
		height = TheTerrain->getHeight(TreePositions[i].x, TreePositions[i].z);
		TreePositions[i].y = height;
	}
	for(int i = 0; i < numberApples; i = fpuAdd(i,1))
	{
		if(boolApples[i])
		{
		ApplePositions[i].x = rand() % 1400 - 900;
		ApplePositions[i].z = rand() % 1275 - 300;
		height = TheTerrain->getHeight(ApplePositions[i].x, ApplePositions[i].z);
		ApplePositions[i].y = height + 10;
		}
	}

	//build skybox
	BuildSkybox(Device);

	//
	// Set Camera.
	//

	D3DXVECTOR3    pos(-0.0f, -197.0f, -0.0f);
	D3DXVECTOR3 target(0.0, 0.0f, 0.0f);
	D3DXVECTOR3     up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &pos, &target, &up);

	Device->SetTransform(D3DTS_VIEW, &V);

	D3DXVECTOR3    pos2(-0.0f, -10.0f, 0.0f);
	D3DXVECTOR3 target2(0.0, 0.0f, 0.0f);
	D3DXVECTOR3     up2(0.0f, 1.0f, 0.0f);

//	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&mview, &pos2, &target2, &up2);

	//Device->SetTransform(D3DTS_VIEW, &mview);

	//
	// Set projection matrix.
	//
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			fpuDiv( D3DX_PI, 4.0f), // 45 - degree
			fpuDiv( (float)Width, (float)Height),
			1.0f,
			20001.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	D3DXMatrixPerspectiveFovLH(&mprojection, fpuDiv( D3DX_PI, 4.0f), fpuDiv( (float)Width, (float)Height), 1.0f, 20001.0f);

	// ambient light
	Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255,255,255));

	//Device->SetTransform(D3DTS_PROJECTION, &mprojection);

	return true;
}

void Cleanup()
{
	//cleanup audio
	TheInput.CleanUpInput();
	AudioCleanup();		
	d3d::Delete<Terrain*>(TheTerrain);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		//update audio
		AudioUpdate();

		TheInput.MouseUpdate();
		TheInput.KeyUpdate();
		TheInput.JoyUpdate();

		//keyboard
		D3DXVECTOR3 lastpos;
		TheCamera.getPosition(&lastpos);
		if(TheInput.KeyTest(DIK_W))
		{
			TheCamera.walk(fpuMul( 40.0f, timeDelta));
		}
		if(TheInput.KeyTest(DIK_S))
		{
			TheCamera.walk(fpuMul( -40.0f, timeDelta));
		}
		if( TheInput.KeyTest(DIK_A))
		{
			TheCamera.yaw(fpuMul( -4.0f, timeDelta));
		}
		if(TheInput.KeyTest(DIK_D))
		{
			TheCamera.yaw(fpuMul( 4.0f, timeDelta));
		}
		if(TheInput.KeyTest(DIK_I))
		{
			TheCamera.pitch(fpuMul( -4.0f,timeDelta));
		}
		if(TheInput.KeyTest(DIK_K))
		{
			TheCamera.pitch(fpuMul( 4.0f, timeDelta));
		}
		if(TheInput.JoylXTest())
		{
			TheCamera.yaw(fpuMul( fpuMul( .04f, timeDelta), TheInput.JoylXTest()));
		}
		if(fpuSub( TheInput.JoylZTest(),32768))
		{
			TheCamera.walk(fpuMul( fpuMul( -.008f, timeDelta), fpuSub(TheInput.JoylZTest(),32768)));
		}
		if(TheInput.JoylYTest())
		{
			TheCamera.pitch(fpuMul( fpuMul( -.04f, timeDelta), TheInput.JoylYTest()));
		}
		D3DXVECTOR3 f = TheCamera.GetPosition();
		float height = fpuAdd(TheTerrain->getHeight(f.x, f.z),20);

		
		if(f.x > 2500)
			f.x = 2500;
		if(f.x < -2500)
			f.x = -2500;
		
		if(f.z > 2500)
			f.z = 2500;
		if(f.z < -2500)
			f.z = -2500;

		//if(f.y > 390)
		//	f.y = 390;
		//if(f.y < 10)
		//	f.y = 10;
		
		f.y = height;

		if(f.y > lastpos.y + 20 || f.y < lastpos.y-20)
			f = lastpos;

		TheCamera.setPosition(&f);

		//camera stuff
		D3DXMATRIX V, o;
		TheCamera.getViewMatrix(&V);
		Device->SetTransform(D3DTS_VIEW, &V);

		//UpdateCameraThirdPerson();
		//
		// Draw the scene:
		//
		Device->Clear(0, 0, 
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			0xff000000, 1.0f, 0L);

		Device->BeginScene();
				
		D3DXMATRIX I;
		D3DXMatrixIdentity(&I);
		if(TheTerrain)
			TheTerrain->draw(&I, false);

		//Device->SetTexture(0, Armor)
D3DXMATRIX i, tripler, grow;

		

		DisplayTime();

		for(int i = 0; i < numbertrees; i = fpuAdd(i,1))
		{
			D3DXMatrixTranslation(&tripler, TreePositions[i].x ,TreePositions[i].y ,fpuSub(TreePositions[i].z,10));
			D3DXMatrixScaling(&grow,5,5,5);
			D3DXMatrixMultiply(&tripler, &grow, &tripler);
			Device->SetTransform(D3DTS_WORLD, &tripler);
			Tree.Draw(NULL);
		}
		
		for(int i = 0; i < numberApples; i = fpuAdd(i,1))
		{
			D3DXMatrixTranslation(&tripler, ApplePositions[i].x ,ApplePositions[i].y ,fpuSub(ApplePositions[i].z,10));
			D3DXMatrixScaling(&grow,5,5,5);
			D3DXMatrixMultiply(&tripler, &grow, &tripler);
			Device->SetTransform(D3DTS_WORLD, &tripler);
			Apple.Draw(NULL);
		}
		
		Collides();
		renderSkybox(Device, TheCamera);
		DrawMinimap();

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
		if(messageDone)
		if(gameover)
		{
			FastestTimeTests();
			messageDone = false;
			gameover = false;
			seconds = 0;			
		}
	}

	if(fpuSub(GetTickCount(),dwFinalTick) > 1000)
	{
		seconds = fpuAdd(seconds,1);
		dwInitialTick = dwFinalTick;
		dwFinalTick = GetTickCount();

		countDown = fpuAdd(countDown, 1);
	}
	return true;
}


//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		{
			::PostQuitMessage(0);
			break;
		}
		
	case WM_KEYDOWN:
		{
			if( wParam == VK_ESCAPE )
				::DestroyWindow(hwnd);
		}

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
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine,int showCmd)
{
	//saveXFile("CLK", 50, "03/19/13", 1);
	//saveXFile("ABC", 60, "03/19/13", 2);
	//saveXFile("DEF", 80, "03/19/13", 3);
	//saveXFile("GHI", 110, "03/19/13", 4);
	//saveXFile("JKL", 150, "03/19/13", 5);
	LoadXFile();
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
	if(FAILED(AudioSetup()))
	{
		::MessageBox(0, "AudioSetup() - FAILED", 0, 0);
		return 0;
	}
	else
		AudioPlay("Medieval");
			
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

	::MessageBoxA(g_hwnd, "Welcome to A Knight's Code", "Welcome", 0);
	::MessageBoxA(g_hwnd, "As a Squire you must collect food for your knight", "Instructions", 0);

	if( !RegisterClass(&cw)) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}


	if(!TheInput.SetupInput(hinstance, g_hwnd))
	{
		::MessageBox(0, "TheInput.SetupInput(hinstance, mainHWND) - FAILED", 0, 0);
		return 0;
	}
		/*::MessageBoxA(0, "The Objective of the game is to collect the trash\n(everything but trees is trash)\n\nWASD to move\nIK to look up and down", "Welcome", MB_OK);*/
	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}