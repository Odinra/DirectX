#include "base.h"
#include "main.h"
#include "audio.h"
#include "skybox.h"
#include "xFile.h"
#include <stdlib.h>     /* srand, rand */

//
// Globals
//

float avatarYaw;
D3DXVECTOR3 AvatarPosition(0,0,0), CameraReference(0,0,10), avatarDirection(0,0,0), thirdPersonReference(0, 10, -10);
D3DXMATRIX mview, mprojection,mworld;
float rotationSpeed = 1.0f / 60.0f;
float forwardSpeed = 40.0f;
IDirect3DDevice9* Device = 0;

Terrain* TheTerrain = 0;

const int Width  = 1000;
const int Height = 800;

float aspectRatio = (float)Width/(float)Height;

XFile Barrels, Dalek, tank, Table, Ton, Tree;

/////mirror tex
IDirect3DTexture9* MirrorTex = 0;

//camera
Camera TheCamera(Camera::AIRCRAFT);

LPDIRECT3DTEXTURE9 texMap;

int numbertrees = 99;
D3DXVECTOR3 TrashPositions[10], TreePositions[100];
bool BoolTrash[10];
bool allfound = false, messageDone = true;
int numberFound = 10;

// Font mesh
ID3DXFont *m_font;

ID3DXSprite* spriteMap;
ID3DXSprite* spritePlayer;
ID3DXSprite* spriteTrash[10];


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
void UpdateCameraThirdPerson()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, -avatarYaw);
	D3DXVECTOR3 transformedReference;
	D3DXVECTOR4 vec4;
	D3DXVec3Transform(&vec4, &thirdPersonReference, &rotationMatrix);
	transformedReference.x = vec4.x;
	transformedReference.y = vec4.y;
	transformedReference.z = vec4.z;

	D3DXVECTOR3 cameraPosition(transformedReference.z + AvatarPosition.x, transformedReference.y + transformedReference.y, transformedReference.x + transformedReference.z);

	D3DXVECTOR3 up(0,1,0);
	D3DXMatrixLookAtLH(&mview, &cameraPosition, &AvatarPosition, &up);


	//Device->SetTransform(D3DTS_VIEW, &mview);

	D3DXMatrixPerspectiveFovLH(&mprojection, D3DX_PI / 4, aspectRatio, 0.1f, 5001.0f);

	D3DXMATRIX myaw, mpos;
	D3DXMatrixRotationY(&mpos, avatarYaw);
	D3DXMatrixTranslation(&mpos, AvatarPosition.x, AvatarPosition.y, AvatarPosition.z);
	D3DXMatrixMultiply(&mworld, &myaw, &mpos);

	//Device->SetTransform(D3DTS_WORLD, &mworld);
}
// Function to display time
void DisplayTime()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect2;
    rect2.left=800;
    rect2.right=1100;
    rect2.top=0;
    rect2.bottom=rect2.top+20;

	// Displaying the text
	sprintf(buffers, "Time: %i seconds", seconds);

	m_font->DrawText(NULL, buffers, 50, &rect2, 0, fontColor );
}

void DisplayRemaining()
{
	// set color of font
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	// setting the position of font
	RECT rect1;
    rect1.left=800;
    rect1.right=1100;
    rect1.top=40;
    rect1.bottom=rect1.top+20;

	// Displaying the text
	sprintf(buffers2, "Trash Uncollected: %i", numberFound);

	m_font->DrawText(NULL, buffers2, 150, &rect1, 0, fontColor );

	
}

void DrawMinimap()
{
	D3DCOLOR MapColor = D3DCOLOR_ARGB(255, 0, 0, 0);
	D3DCOLOR TrashColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	D3DCOLOR PlayerColor = D3DCOLOR_ARGB(255, 0, 0, 255);
	
	RECT mapRect;
	mapRect.left=0;
	mapRect.right=100;
	mapRect.top=0;
	mapRect.bottom=100;

	D3DXVECTOR3 mapPos(25, 25, 0);

	spriteMap->Begin(NULL);
	spriteMap->Draw(texMap, &mapRect, NULL, &mapPos, MapColor);
	spriteMap->End();

	mapRect.left=0;
	mapRect.right=10;
	mapRect.top=0;
	mapRect.bottom=10;

	D3DXVECTOR3 playerPos(TheCamera.GetPosition().x / 4 + 75,TheCamera.GetPosition().z / 4 + 75, 0 );
	D3DXVECTOR3 pcenter(5, 5, 0);

	spritePlayer->Begin(NULL);
	spritePlayer->Draw(texMap, &mapRect, &pcenter, &playerPos, PlayerColor);
	spritePlayer->End();

	mapRect.left=0;
	mapRect.right=5;
	mapRect.top=0;
	mapRect.bottom=5;

	D3DXVECTOR3 trashPos;
	D3DXVECTOR3 tcenter(2.5, 2.5, 0);
	for(int i = 0; i < 10; i++)
	{
		if(BoolTrash[i])
		{
			trashPos.x = TrashPositions[i].x / 4 + 75;
			trashPos.y = TrashPositions[i].z / 4 + 75;
			trashPos.z = 0;
			spriteTrash[i]->Begin(NULL);
			spriteTrash[i]->Draw(texMap, &mapRect, &tcenter, &trashPos, TrashColor);
			spriteTrash[i]->End();
		}
	}

}
void Collides()
{
	for (int i = 0; i < 10; i++)
	{
		if(BoolTrash[i])
		{
			if (TheCamera.GetPosition().x <= TrashPositions[i].x + 15) 
			{
				if(TheCamera.GetPosition().z <= TrashPositions[i].z + 15)
				{
					if (TheCamera.GetPosition().x >= TrashPositions[i].x - 15) 
					{
						if (TheCamera.GetPosition().z >= TrashPositions[i].z - 15)
						{
							BoolTrash[i] = false;
							numberFound--;
							TrashPositions[i].x = 500;
							TrashPositions[i].z = 500;
						}
					}
				}
			}
		}
	}
	
	for(int i = 0; i < 10; i++)
	{
		if(BoolTrash[i])
		{
			allfound = false;
			return;
		}
	}
	allfound = true;

}
bool Setup()
{
		D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);

	TheTerrain = new Terrain(Device, "Faces.raw", 734,1024,20,1.0f);
	TheTerrain->genTexture(&lightDirection);
	TheTerrain->loadTexture("Faces.jpg");

	
		D3DXCreateFont(Device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );
	//
	// Lights.
	//
	Barrels.init(Device, "barells/barrels.x");
	Dalek.init(Device, "dalek/dalek.x");
	tank.init(Device, "Oiltank/tank.x");
	Table.init(Device, "table/table.x");
	Ton.init(Device, "ton/ton3.x");
	Tree.init(Device, "trees/palm_tree_3.x");

	numbertrees = rand() % 100 - 1;

	for(int i = 0;  i < 10; i++)
		BoolTrash[i] = true;

	D3DXCreateSprite(Device, &spriteMap);
	D3DXCreateSprite(Device, &spritePlayer);
	for(int i = 0; i < 10; i++)
	{
		D3DXCreateSprite(Device, &spriteTrash[i]);
	}
	
	D3DXCreateTextureFromFile(Device, "Map.png", &texMap);
	srand(GetTickCount());

	TrashPositions[0].x = rand() % 360 - 180;
	TrashPositions[0].z = rand() % 360 - 180;
	float height = TheTerrain->getHeight(TrashPositions[0].x, TrashPositions[0].z);
	TrashPositions[0].y = height;

	TrashPositions[1].x = rand() % 360 - 180;
	TrashPositions[1].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[1].x, TrashPositions[1].z);
	TrashPositions[1].y = height;

	TrashPositions[2].x = rand() % 360 - 180;
	TrashPositions[2].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[2].x, TrashPositions[2].z);
	TrashPositions[2].y = height;

	TrashPositions[3].x = rand() % 360 - 180;
	TrashPositions[3].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[3].x, TrashPositions[3].z);
	TrashPositions[3].y = height;

	TrashPositions[4].x = rand() % 360 - 180;
	TrashPositions[4].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[4].x, TrashPositions[4].z);
	TrashPositions[4].y = height;

	TrashPositions[5].x = rand() % 360 - 180;
	TrashPositions[5].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[5].x, TrashPositions[5].z);
	TrashPositions[5].y = height;

	TrashPositions[6].x = rand() % 360 - 180;
	TrashPositions[6].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[6].x, TrashPositions[6].z);
	TrashPositions[6].y = height;

	TrashPositions[7].x = rand() % 360 - 180;
	TrashPositions[7].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[7].x, TrashPositions[7].z);
	TrashPositions[7].y = height;

	TrashPositions[8].x = rand() % 360 - 180;
	TrashPositions[8].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[8].x, TrashPositions[8].z);
	TrashPositions[8].y = height;

	TrashPositions[9].x = rand() % 360 - 180;
	TrashPositions[9].z = rand() % 360 - 180;
	height = TheTerrain->getHeight(TrashPositions[9].x, TrashPositions[9].z);
	TrashPositions[9].y = height;

	for(int i = 0; i < numbertrees; i++)
	{
		TreePositions[i].x = rand() % 360 - 180;
		TreePositions[i].z = rand() % 360 - 180;
		height = TheTerrain->getHeight(TreePositions[i].x, TreePositions[i].z);
		TreePositions[i].y = height;
	}

	D3DXVECTOR3 lightDir(0.707f, -0.707f, 0.707f);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = d3d::InitDirectionalLight(&lightDir, &color);

	Device->SetLight(0, &light);
	Device->LightEnable(0, true);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

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
			D3DX_PI / 4.0f, // 45 - degree
			(float)Width / (float)Height,
			1.0f,
			20001.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	D3DXMatrixPerspectiveFovLH(&mprojection, D3DX_PI / 4.0f, (float)Width / (float)Height, 1.0f, 20001.0f);

	//Device->SetTransform(D3DTS_PROJECTION, &mprojection);

	return true;
}

void Cleanup()
{
	//cleanup audio
	AudioCleanup();		
	d3d::Delete<Terrain*>(TheTerrain);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		//update audio
		AudioUpdate();

		//keyboard
		if( ::GetAsyncKeyState('W') & 0x8000f)
		{
			TheCamera.walk(40.0f * timeDelta);
			//D3DXMATRIX forwardMovement;
			//D3DXMatrixRotationY(&forwardMovement, avatarYaw);
			//D3DXVECTOR3 v(0,0,forwardSpeed);
			//D3DXVECTOR4 vec4;
			//D3DXVec3Transform(&vec4, &v, &forwardMovement);
			//avatarDirection.x = v.x = vec4.x;
			//avatarDirection.y = v.y = vec4.y;
			//avatarDirection.z = v.z = vec4.z;
			//AvatarPosition.z += v.z;
			//AvatarPosition.x += v.x;
		}
		if( ::GetAsyncKeyState('S') & 0x8000f)
		{
			TheCamera.walk(-40.0f * timeDelta);
			//D3DXMATRIX forwardMovement;
			//D3DXMatrixRotationY(&forwardMovement, avatarYaw);
			//D3DXVECTOR3 v(0,0,-forwardSpeed);
			//D3DXVECTOR4 vec4;
			//D3DXVec3Transform(&vec4, &v, &forwardMovement);
			//avatarDirection.x = v.x = vec4.x;
			//avatarDirection.y = v.y = vec4.y;
			//avatarDirection.z = v.z = vec4.z;
			//AvatarPosition.z += v.z;
			//AvatarPosition.x += v.x;
		}
		if( ::GetAsyncKeyState('A') & 0x8000f)
		{
			TheCamera.yaw(-4.0f * timeDelta);
			//avatarYaw -= rotationSpeed;
		}
		if( ::GetAsyncKeyState('D') & 0x8000f)
		{
			TheCamera.yaw(4.0f * timeDelta);
			//avatarYaw -= rotationSpeed;
		}
		if( ::GetAsyncKeyState('I') & 0x8000f)
		{
			TheCamera.pitch(-4.0f * timeDelta);
		}
		if( ::GetAsyncKeyState('K') & 0x8000f)
		{
			TheCamera.pitch(4.0f * timeDelta);
		}

		D3DXVECTOR3 f = TheCamera.GetPosition();
		if(f.x > 190)
			f.x = 190;
		if(f.x < -190)
			f.x = -190;
		
		if(f.z > 190)
			f.z = 190;
		if(f.z < -190)
			f.z = -190;

		//if(f.y > 390)
		//	f.y = 390;
		//if(f.y < 10)
		//	f.y = 10;
		float height = TheTerrain->getHeight(f.x, f.z);
		f.y = height + 5.0f;


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

		Collides();

		DisplayTime();
		DisplayRemaining();

		//
		//Barrels1
		//
		if(BoolTrash[0])
		{
		
		D3DXMatrixTranslation(&tripler, TrashPositions[0].x + 0,TrashPositions[0].y, TrashPositions[0].z-10);
		D3DXMatrixScaling(&grow, .05,.05,.05);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Barrels.Draw(NULL);
		}

		//
		//Barrels2
		//
		if(BoolTrash[1])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[1].x +0,TrashPositions[1].y,TrashPositions[1].z-10);
		D3DXMatrixScaling(&grow, .05,.05,.05);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Barrels.Draw(NULL);
		}
		//
		//Dalek1
		//
		if(BoolTrash[2])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[2].x +0,TrashPositions[2].y+8,TrashPositions[2].z-10);
		D3DXMatrixScaling(&grow, .05,.05,.05);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Dalek.Draw(NULL);
		}
		//
		//Dalek2
		//
		if(BoolTrash[3])
		{
		D3DXMatrixTranslation(&tripler,TrashPositions[3].x +0,TrashPositions[3].y+8,TrashPositions[3].z-10);
		D3DXMatrixScaling(&grow, .05,.05,.05);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Dalek.Draw(NULL);
		}
		//
		//Tank1
		//		
		if(BoolTrash[4])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[4].x +40,TrashPositions[4].y+14,TrashPositions[4].z+0);
		D3DXMatrixScaling(&grow, .1,.1,.1);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		tank.Draw(NULL);
		}
		//
		//Tank2
		//
		if(BoolTrash[5])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[5].x +40,TrashPositions[5].y+14,TrashPositions[5].z+0);
		D3DXMatrixScaling(&grow, .1,.1,.1);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		tank.Draw(NULL);
		}

		//
		//Table1
		//		
		if(BoolTrash[6])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[6].x +0,TrashPositions[6].y,TrashPositions[6].z-10);
		D3DXMatrixScaling(&grow, 10,10,10);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Table.Draw(NULL);
		}
		//
		//Table2
		//
		if(BoolTrash[7])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[7].x +0,TrashPositions[7].y,TrashPositions[7].z-10);
		D3DXMatrixScaling(&grow,10,10,10);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Table.Draw(NULL);
		}
		//
		//Ton1
		//
		if(BoolTrash[8])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[8].x +0,TrashPositions[8].y,TrashPositions[8].z-10);
		D3DXMatrixScaling(&grow,10,10,10);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Ton.Draw(NULL);
		}
		//
		//Ton2
		//
		if(BoolTrash[9])
		{
		D3DXMatrixTranslation(&tripler, TrashPositions[9].x +0,TrashPositions[8].y,TrashPositions[9].z-10);
		D3DXMatrixScaling(&grow,10,10,10);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Ton.Draw(NULL);
		}

		for(int i = 0; i < numbertrees; i++)
		{
			D3DXMatrixTranslation(&tripler, TreePositions[i].x +0,TreePositions[i].y,TreePositions[i].z-10);
			D3DXMatrixScaling(&grow,5,5,5);
			D3DXMatrixMultiply(&tripler, &grow, &tripler);
			Device->SetTransform(D3DTS_WORLD, &tripler);
			Tree.Draw(NULL);
		}

		if(messageDone)
		{
		if(allfound)
		{
			sprintf(buffers, "Seconds taken to find all objects: %i", seconds);
			::MessageBoxA(0, buffers, "Congratulations", 0);
			//::PostQuitMessage(0);
			messageDone = false;
		}
		}

		renderSkybox(Device, TheCamera);
		DrawMinimap();

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}

	if(GetTickCount() - dwFinalTick > 1000)
	{
		seconds = seconds + 1;
		dwInitialTick = dwFinalTick;
		dwFinalTick = GetTickCount();

		countDown = countDown+ 1;
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
		{
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
		::MessageBoxA(0, "The Objective of the game is to collect the trash\n(everything but trees is trash)\n\nWASD to move\nIK to look up and down", "Welcome", MB_OK);
	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}