
#include "d3dUtility.h"
#include <vector>
/*****************************************************************************
//ADJUST ALL SPEED HERE
******************************************************************************/
float DTime = 0.0090f;

//
// Globals
//

HWND mainHWND;

double leftHeight = -10, rightHeight = -10, middleHieght = -10;
double leftSpeed = .0010, rightSpeed = .0025;
 
bool pause;

bool bGame = false;

Audio sound;
PCSTR Song = "Song";

IDirect3DDevice9* Device = 0; 

const int Width  = 640;
const int Height = 480;
ID3DXMesh* GunObjects[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
D3DXMATRIX GunWorlds[15];

D3DMATERIAL9 Mtrls[10];

D3DXVECTOR3 camStart(0.0f, 8.5f, -0.0f);

Cube* Box;

IDirect3DTexture9* TexGround = 0;
IDirect3DTexture9* TexSky = 0;
IDirect3DTexture9* TexWood = 0;
IDirect3DTexture9* TexPrizes = 0;
IDirect3DTexture9* TexBack= 0;
IDirect3DTexture9* TexDirections = 0;
IDirect3DTexture9* TexCrate = 0;
IDirect3DTexture9* TexTarget = 0;
IDirect3DTexture9* TexBanner = 0;

Camera TheCamera(Camera::AIRCRAFT);

IDirect3DVertexBuffer9* VBufferGround = 0;
//IDirect3DVertexBuffer9* VBufferNorth = 0;
//IDirect3DVertexBuffer9* VBufferEast = 0;
//IDirect3DVertexBuffer9* VBufferSouth = 0;
//IDirect3DVertexBuffer9* VBufferWest = 0;
//IDirect3DVertexBuffer9* VBufferSky = 0;

D3DXVECTOR3 p;
D3DXVECTOR3 t;

bool gameover = false;

DWORD timeelapsed, currtime, lasttime;

struct Bullets
{

	ID3DXMesh* mesh;
	D3DXVECTOR3* Position, *Direction;
	Bullets(D3DXVECTOR3* p, D3DXVECTOR3* d, ID3DXMesh* m)
	{
		Position = p;
		Direction = d;
		mesh = m;
	}
	Bullets(){}
	void move()
	{
		Position->operator+=(*Direction);
	}
};

std::vector<Bullets*> bullets;

//IDirect3DIndexBuffer9* IBufferBackGround = 0;


IDirect3DVertexBuffer9* VBuffer = 0;
//IDirect3DIndexBuffer9* IBuffer = 0;

//Cube* Box;
//
// Framework Functions
//

template <typename T>
void remove(std::vector<T>& vec, size_t pos)
{
    std::vector<T>::iterator it = vec.begin();
    std::advance(it, pos);
    vec.erase(it);
}

void firebullets()
{
	currtime = GetTickCount();
	if(currtime - lasttime >= 500)
	{
		ID3DXMesh* mesh;
		D3DXVECTOR3* Position, *Direction;

		Position = new D3DXVECTOR3(0,0,0);
		Direction = new D3DXVECTOR3(0,0,0);

		TheCamera.getPosition(Position);
		TheCamera.getLook(Direction);

		D3DXCreateSphere(Device, 1, 180, 180, &mesh, 0);
		
		Bullets *b = new Bullets(Position, Direction, mesh);
		


		D3DXVec3Normalize(b->Direction, b->Direction);
		b->Direction->x /= 10;
		b->Direction->y /= 10;
		b->Direction->z /= 10;

		bullets.push_back(b);

		lasttime = currtime;
	}
}

void playgame()
{

	TheCamera.setPosition(&camStart);
	if(::GetAsyncKeyState(VK_SPACE) & 0x8000f)
		firebullets();

	//std::vector<Bullets>::iterator itor;

	for(int i = 0; i != bullets.size(); i++)
	{

		D3DXVECTOR3 bbox[] = { D3DXVECTOR3(-1.5f, 7.0f, 20.0f), D3DXVECTOR3(1.5f, 5.0f, 20.0f), D3DXVECTOR3(-1.5f, 5.0f, 20.0f), D3DXVECTOR3(-1.5f, 7.0f, 20.0f), D3DXVECTOR3(1.5f, 7.0f, 20.0f), D3DXVECTOR3(1.5f, 5.0f, 20.0f)};
		D3DXVECTOR3 bmax(1.5, 7.0, 21), bmin(-1.5, 5.0, 20) ;

		//D3DXComputeBoundingBox(bbox, 6, sizeof(D3DXVECTOR3), &bmin, &bma

		if(bullets[i]->Position->x < bmax.x)
		{
			if(bullets[i]->Position->x > bmin.x)
			{
				if(bullets[i]->Position->y < bmax.y)
				{
					if(bullets[i]->Position->y > bmin.y)
					{
						if(bullets[i]->Position->z < bmax.z)
						{
							if(bullets[i]->Position->z > bmin.z)
							{
   								middleHieght+= .5;
								remove(bullets, i);
								if( i >= bullets.size())
									return;
							}
						}
					}
				}
			}
		}
		else if(bullets[i]->Position->x >= 30 ||bullets[i]->Position->x <= -30)
			remove(bullets, i);
		else if(bullets[i]->Position->y >= 20 ||bullets[i]->Position->x <= -20)
			remove(bullets, i);
		else if(bullets[i]->Position->x >= 30 ||bullets[i]->Position->x <= -30)
			remove(bullets, i);
	}

	if(gameover)
		bGame = false;
}
bool Setup()
{
	//
	// Create the BackDrop quad.
	//
	//Ground
	Device->CreateVertexBuffer(36 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBufferGround, 0);

	Vertex* VGround;
	VBufferGround->Lock(0, 0, (void**)&VGround, 0);

	VGround[0] = Vertex(-100.0f, 0.0f,-100.0f, 0.0f, 1.0f, 0.0f,   0.0f, 100.0f);
	VGround[1] = Vertex(-100.0f, 0.0f,100.0f, 0.0f, 1.0f, 0.0f,   0.0f,   0.0f);
	VGround[2] = Vertex( 100.0f, 0.0f,100.0f, 0.0f, 1.0f, 0.0f, 100.0f,   0.0f);
	VGround[3] = Vertex(-100.0f, 0.0f,-100.0f, 0.0f, 1.0f, 0.0f,   0.0f, 100.0f);
	VGround[4] = Vertex(100.0f, 0.0f,100.0f, 0.0f, 1.0f, 0.0f, 100.0f,   0.0f);
	VGround[5] = Vertex(100.0f, 0.0f,-100.0f, 0.0f, 1.0f, 0.0f, 100.0f, 100.0f);


	//VBufferGround->Unlock();

	////Sky
	//Device->CreateVertexBuffer(6 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBufferSky, 0);

	//Vertex* VSky;
	//VBufferSky->Lock(0, 0, (void**)&VSky, 0);

	VGround[6] = Vertex(100.0f, 200.0f,100.0f, 0.0f, -1.0f, 0.0f,   0.0f, 1.0f);
	VGround[7] = Vertex(-100.0f, 200.0f, 100.0f, 0.0f, -1.0f, 0.0f,   0.0f,   0.0f);
	VGround[8] = Vertex( -100.0f, 200.0f, -100.0f, 0.0f, -1.0f, 0.0f, 1.0f,   0.0f);
	VGround[9] = Vertex(100.0f, 200.0f,100.0f, 0.0f, -1.0f, 0.0f,   0.0f, 1.0f);
	VGround[10] = Vertex( -100.0f, 200.0f,-100.0f, 0.0f, -1.0f, 0.0f, 1.0f,   0.0f);
	VGround[11] = Vertex( 100.0f, 200.0f,-100.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);


	//VBufferSky->Unlock();
	//
	////North
	//Device->CreateVertexBuffer(6 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBufferNorth, 0);

	//Vertex* VNorth;
	//VBufferNorth->Lock(0, 0, (void**)&VNorth, 0);

	VGround[12] = Vertex(-100.0f, -000.0f, 100.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[13] = Vertex(-100.0f,  200.0f, 100.0f, 0.0f, 0.0f, -1.0f,   0.0f,   0.0f);
	VGround[14] = Vertex( 100.0f,  200.0f, 100.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[15] = Vertex(-100.0f, -000.0f, 100.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[16] = Vertex( 100.0f,  200.0f, 100.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[17] = Vertex( 100.0f, -000.0f, 100.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);


	//VBufferNorth->Unlock();

	////South
	//Device->CreateVertexBuffer(6 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBufferSouth, 0);

	//Vertex* VSouth;
	//VBufferSouth->Lock(0, 0, (void**)&VSouth, 0);

	VGround[18] = Vertex( 100.0f, -000.0f, -100.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f);
	VGround[19] = Vertex( 100.0f,  200.0f, -100.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f);
	VGround[20] = Vertex(-100.0f,  200.0f, -100.0f, 0.0f, 0.0f, 1.0f, 1.0f,   0.0f);
	VGround[21] = Vertex( 100.0f, -000.0f, -100.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f);
	VGround[22] = Vertex(-100.0f,  200.0f, -100.0f, 0.0f, 0.0f, 1.0f, 1.0f,   0.0f);
	VGround[23] = Vertex(-100.0f, -000.0f, -100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


	//VBufferSouth->Unlock();

	////East
	//Device->CreateVertexBuffer(6 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBufferEast, 0);

	//Vertex* VEast;
	//VBufferEast->Lock(0, 0, (void**)&VEast, 0);

	VGround[24] = Vertex( 100.0f, -000.0f,  100.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[25] = Vertex( 100.0f,  200.0f,  100.0f, -1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VGround[26] = Vertex( 100.0f,  200.0f, -100.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[27] = Vertex( 100.0f, -000.0f,  100.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[28] = Vertex( 100.0f,  200.0f, -100.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[29] = Vertex( 100.0f, -000.0f, -100.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);


	//VBufferEast->Unlock();
	//
	////West
	//Device->CreateVertexBuffer(6 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBufferWest, 0);

	//Vertex* VWest;
	//VBufferWest->Lock(0, 0, (void**)&VWest, 0);

	VGround[30] = Vertex(-100.0f, -000.0f, -100.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[31] = Vertex(-100.0f,  200.0f, -100.0f, 1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VGround[32] = Vertex(-100.0f,  200.0f,  100.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[33] = Vertex(-100.0f, -000.0f, -100.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[34] = Vertex(-100.0f,  200.0f,  100.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[35] = Vertex(-100.0f, -000.0f,  100.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);


	VBufferGround->Unlock();
	// quad built from two triangles, note texture coordinates:
	
		Device->CreateVertexBuffer(100 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBuffer, 0);

	Vertex* VBuilding;
	VBuffer->Lock(0, 0, (void**)&VBuilding, 0);

	VBuilding[0] = Vertex(-30.0f, 0.10f,-0.0f, 0.0f, 1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[1] = Vertex(-30.0f, 0.10f,30.0f, 0.0f, 1.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[2] = Vertex( 30.0f, 0.10f,30.0f, 0.0f, 1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[3] = Vertex(-30.0f, 0.10f,-0.0f, 0.0f, 1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[4] = Vertex(30.0f, 0.10f,30.0f, 0.0f, 1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[5] = Vertex(30.0f, 0.10f,-0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 20.0f);

	VBuilding[6] = Vertex(-30.0f, 15.0f,30.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[7] = Vertex(30.0f, 15.0f, 30.0f, 0.0f, -1.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[8] = Vertex( 30.0f, 15.0f, -0.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[9] = Vertex(-30.0f, 15.0f,30.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[10] = Vertex( 30.0f, 15.0f,-0.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[11] = Vertex( -30.0f, 15.0f,-0.0f, 0.0f, -1.0f, 0.0f, 2.0f, 20.0f);

	VBuilding[12] =Vertex(-30.0f, -000.10f, 30.0f, 0.0f, 0.0f, -1.0f,   0.0f, 20.0f);
	VBuilding[13] = Vertex(-30.0f,  15.0f, 30.0f, 0.0f, 0.0f, -1.0f,   0.0f,   0.0f);
	VBuilding[14] = Vertex( 30.0f,  15.0f, 30.0f, 0.0f, 0.0f, -1.0f, 2.0f,   0.0f);
	VBuilding[15] = Vertex(-30.0f, -000.10f, 30.0f, 0.0f, 0.0f, -1.0f,   0.0f, 20.0f);
	VBuilding[16] = Vertex( 30.0f,  15.0f, 30.0f, 0.0f, 0.0f, -1.0f, 2.0f,   0.0f);
	VBuilding[17] = Vertex( 30.0f, -000.10f, 30.0f, 0.0f, 0.0f, -1.0f, 2.0f, 20.0f);
	
	VBuilding[18] = Vertex( -30.0f, -000.10f, -0.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VBuilding[19] = Vertex( -30.0f,  5.0f, -0.0f, 0.0f, 0.0f, -1.0f,   0.0f,  0.0f);
	VBuilding[20] = Vertex(30.0f,  5.0f, -0.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VBuilding[21] = Vertex(-30.0f, -000.10f, -0.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VBuilding[22] = Vertex(30.0f,  5.0f, -0.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VBuilding[23] = Vertex(30.0f, -000.10f, -0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	
	VBuilding[24] =Vertex(30.0f, -000.10f, 30.0f, 0.0f, 0.0f, -1.0f,   0.0f, 20.0f);
	VBuilding[25] = Vertex(30.0f,  15.0f, 30.0f, 0.0f, 0.0f, -1.0f,   0.0f,   0.0f);
	VBuilding[26] = Vertex( -30.0f,  15.0f, 30.0f, 0.0f, 0.0f, -1.0f, 2.0f,   0.0f);
	VBuilding[27] = Vertex(30.0f, -000.10f, 30.0f, 0.0f, 0.0f, -1.0f,   0.0f, 20.0f);
	VBuilding[28] = Vertex( -30.0f,  15.0f, 30.0f, 0.0f, 0.0f, -1.0f, 2.0f,   0.0f);
	VBuilding[29] = Vertex( -30.0f, -000.10f, 30.0f, 0.0f, 0.0f, -1.0f, 2.0f, 20.0f);

	VBuilding[30] = Vertex( 30.0f, -000.10f, -0.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VBuilding[31] = Vertex( 30.0f,  5.0f, -0.0f, 0.0f, 0.0f, -1.0f,   0.0f,  0.0f);
	VBuilding[32] = Vertex(-30.0f,  5.0f, -0.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VBuilding[33] = Vertex(30.0f, -000.10f, -0.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VBuilding[34] = Vertex(-30.0f,  5.0f, -0.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VBuilding[35] = Vertex(-30.0f, -000.10f, -0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	VBuilding[36] = Vertex(30.0f, 15.0f,30.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[37] = Vertex(-30.0f, 15.0f, 30.0f, 0.0f, -1.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[38] = Vertex( -30.0f, 15.0f, -0.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[39] = Vertex(30.0f, 15.0f,30.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[40] = Vertex( -30.0f, 15.0f,-0.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[41] = Vertex( 30.0f, 15.0f,-0.0f, 0.0f, -1.0f, 0.0f, 2.0f, 20.0f);

	VBuilding[42] = Vertex(-30.0f, -000.10f, 30.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[43] = Vertex(-30.0f,  15.0f, 030.0f, 1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[44] = Vertex(-30.0f,  15.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[45] = Vertex(-30.0f, -000.10f, 030.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[46] = Vertex(-30.0f,  15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[47] = Vertex(-30.0f, -000.10f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	VBuilding[48] = Vertex( 30.0f, -000.10f,  0.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[49] = Vertex( 30.0f,  15.0f,  0.0f, -1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[50] = Vertex( 30.0f,  15.0f, 030.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[51] = Vertex( 30.0f, -000.10f,  0.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[52] = Vertex( 30.0f,  15.0f, 30.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[53] = Vertex( 30.0f, -000.10f, 030.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	VBuilding[54] = Vertex(30.0f, 5.0f,10.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[55] = Vertex(-30.0f, 5.0f, 10.0f, 0.0f, -1.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[56] = Vertex( -30.0f, 5.0f, -5.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[57] = Vertex(30.0f, 5.0f,10.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[58] = Vertex( -30.0f, 5.0f,-05.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[59] = Vertex( 30.0f, 5.0f,-05.0f, 0.0f, -1.0f, 0.0f, 2.0f, 20.0f);

	VBuilding[60] = Vertex(-30.0f, 5.0f,10.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[61] = Vertex(30.0f, 5.0f, 10.0f, 0.0f, -1.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[62] = Vertex(30.0f, 5.0f, -5.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[63] = Vertex(-30.0f, 5.0f,10.0f, 0.0f, -1.0f, 0.0f,   0.0f, 20.0f);
	VBuilding[64] = Vertex( 30.0f, 5.0f,-05.0f, 0.0f, -1.0f, 0.0f, 2.0f,   0.0f);
	VBuilding[65] = Vertex( -30.0f, 5.0f,-05.0f, 0.0f, -1.0f, 0.0f, 2.0f, 20.0f);

	VBuilding[66] = Vertex(-30.0f, -000.10f, 00.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[67] = Vertex(-30.0f,  15.0f, 00.0f, 1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[68] = Vertex(-30.0f,  15.0f,  30.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[69] = Vertex(-30.0f, -000.10f, 00.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[70] = Vertex(-30.0f,  15.0f,  30.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[71] = Vertex(-30.0f, -000.10f,  30.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	VBuilding[72] = Vertex( 30.0f, -000.10f,  30.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[73] = Vertex( 30.0f,  15.0f,  30.0f, -1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VBuilding[74] = Vertex( 30.0f,  15.0f, 00.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[75] = Vertex( 30.0f, -000.10f,  30.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VBuilding[76] = Vertex( 30.0f,  15.0f, 00.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VBuilding[77] = Vertex( 30.0f, -000.10f, 00.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	VBuilding[78] =Vertex(-30.0f, 005.10f, 29.90f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VBuilding[79] = Vertex(-30.0f,  15.0f, 29.90f, 0.0f, 0.0f, -1.0f,   0.0f,   0.0f);
	VBuilding[80] = Vertex( 30.0f,  15.0f, 29.90f, 0.0f, 0.0f, -1.0f, 2.0f,   0.0f);
	VBuilding[81] = Vertex(-30.0f, 005.10f, 29.90f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VBuilding[82] = Vertex( 30.0f,  15.0f, 29.90f, 0.0f, 0.0f, -1.0f, 2.0f,   0.0f);
	VBuilding[83] = Vertex( 30.0f, 005.10f, 29.90f, 0.0f, 0.0f, -1.0f, 2.0f, 1.0f);

	//Target verticies
	VBuilding[84] = Vertex(-1.5f, 7.0f, 20.0f, 0, 0, 1, 0.0f, 0.0f);
	VBuilding[85] = Vertex( 1.5f, 5.0f, 20.0f, 0, 0, 1, 1.0f, 1.0f);
	VBuilding[86] = Vertex(-1.5f, 5.0f, 20.0f, 0, 0, 1, 0.0f, 1.0f);
	VBuilding[87] = Vertex(-1.5f, 7.0f, 20.0f, 0, 0, 1, 0.0f, 0.0f);
	VBuilding[88] = Vertex( 1.5f, 7.0f, 20.0f, 0, 0, 1, 1.0f, 0.0f);
	VBuilding[89] = Vertex( 1.5f, 5.0f, 20.0f, 0, 0, 1, 1.0f, 1.0f);

	//Banner verticies
	VBuilding[90] = Vertex(-1.0f, 15.0f, 21.0f, 0, 0, 1, 0.0f, 0.0f);
	VBuilding[91] = Vertex( 1.0f,  5.0f, 21.0f, 0, 0, 1, 1.0f, 1.0f);
	VBuilding[92] = Vertex(-1.0f,  5.0f, 21.0f, 0, 0, 1, 0.0f, 1.0f);
	VBuilding[93] = Vertex(-1.0f, 15.0f, 21.0f, 0, 0, 1, 0.0f, 0.0f);
	VBuilding[94] = Vertex( 1.0f, 15.0f, 21.0f, 0, 0, 1, 1.0f, 0.0f);
	VBuilding[95] = Vertex( 1.0f,  5.0f, 21.0f, 0, 0, 1, 1.0f, 1.0f);
	VBuffer->Unlock();


	//
	// Create the cube.
	//
	Box = new Cube(Device);

	D3DXCreateBox(Device,.5,.5,3,&GunObjects[0],0);
	D3DXCreateBox(Device,.5,1,.5,&GunObjects[1],0);
	D3DXCreateBox(Device,.5,.6,.5,&GunObjects[2],0);
	D3DXCreateCylinder(Device, .1,.1,.7,4,4,&GunObjects[3],0);
	//waterhose
	D3DXCreateBox(Device,.1,2,.1,&GunObjects[4],0);
	//gun move
	D3DXMatrixTranslation(&GunWorlds[0], 0.0f, 6.5f, 0.0f);
	//D3DXMatrixRotationY(&GunWorlds[1],(90* (3.14159265/180) )); 
	D3DXMatrixTranslation(&GunWorlds[1], 0.0f, 6.0f, -1.25f);
	D3DXMatrixTranslation(&GunWorlds[2], 0.0f, 6.0f, 0.0f);
	D3DXMatrixTranslation(&GunWorlds[3], 0.0f, 6.5f, 1.8f);
	D3DXMatrixTranslation(&GunWorlds[4], 0.0f, 5.5f, -1.25f);
	///////////////////////////////////////////////////////////////
	//2
	//Gun
	D3DXCreateBox(Device,.5,.5,3,&GunObjects[5],0);
	D3DXCreateBox(Device,.5,1,.5,&GunObjects[6],0);
	D3DXCreateBox(Device,.5,.6,.5,&GunObjects[7],0);
	D3DXCreateCylinder(Device, .1,.1,.7,4,4,&GunObjects[8],0);
	//waterhose
	D3DXCreateBox(Device,.1,2,.1,&GunObjects[9],0);
	//gun move
	D3DXMatrixTranslation(&GunWorlds[5], -15.0f, 6.5f, 0.0f);
	D3DXMatrixTranslation(&GunWorlds[6], -15.0f, 6.0f, -1.25f);
	D3DXMatrixTranslation(&GunWorlds[7], -15.0f, 6.0f, 0.0f);
	D3DXMatrixTranslation(&GunWorlds[8], -15.0f, 6.5f, 1.8f);
	D3DXMatrixTranslation(&GunWorlds[9], -15.0f, 5.5f, -1.25f);
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	//3
	//Gun
	D3DXCreateBox(Device,.5,.5,3,&GunObjects[10],0);
	D3DXCreateBox(Device,.5,1,.5,&GunObjects[11],0);
	D3DXCreateBox(Device,.5,.6,.5,&GunObjects[12],0);
	D3DXCreateCylinder(Device, .1,.1,.7,4,4,&GunObjects[13],0);
	//waterhose
	D3DXCreateBox(Device,.1,2,.1,&GunObjects[14],0);
	//gun move
	D3DXMatrixTranslation(&GunWorlds[10], 15.0f, 6.5f, 0.0f);
	D3DXMatrixTranslation(&GunWorlds[11], 15.0f, 6.0f, -1.25f);
	D3DXMatrixTranslation(&GunWorlds[12], 15.0f, 6.0f, 0.0f);
	D3DXMatrixTranslation(&GunWorlds[13], 15.0f, 6.5f, 1.8f);
	D3DXMatrixTranslation(&GunWorlds[14], 15.0f, 5.5f, -1.25f);

		//Materials
	Mtrls[0] = d3d::RED_MTRL;
	Mtrls[1] = d3d::BLUE_MTRL;
	Mtrls[2] = d3d::GREEN_MTRL;
	Mtrls[3] = d3d::YELLOW_MTRL;
	Mtrls[4] = d3d::WHITE_MTRL;
	Mtrls[5] = d3d::CYAN_MTRL;
	Mtrls[6] = d3d::ORANGE_MTRL;
	Mtrls[7] = d3d::BLACK_MTRL;

	

	//
	// Load the textures and set filters.
	//
	D3DXCreateTextureFromFile(Device, "Clouds.jpg", &TexSky);
	D3DXCreateTextureFromFile(Device, "Sky.jpg", &TexDirections);
	D3DXCreateTextureFromFile(Device, "Grass.jpg", &TexGround);
	D3DXCreateTextureFromFile(Device, "Wood.jpg", &TexWood);
	D3DXCreateTextureFromFile(Device, "Back.png", &TexBack);
	D3DXCreateTextureFromFile(Device, "PrizeWall.jpg", &TexPrizes);
	D3DXCreateTextureFromFile(Device, "crate.jpg", &TexCrate);
	D3DXCreateTextureFromFile(Device, "Target.png", &TexTarget);
	D3DXCreateTextureFromFile(Device, "Banner.png", &TexBanner);

	//
	// set alpha blending stuff
	//

	// use alpha channel in texture for alpha
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);


	// set blending factors so that alpha component determines transparency
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	// 
	// disable lighting
	//

	Device->SetRenderState(D3DRS_LIGHTING, false);
	//
	// set camera
	//
	
	
	D3DXVECTOR3 dir(0.0f, -1.0f, 0.0f);
	D3DXVECTOR3 pos(0.0f, 123.0f, 0.0f);

	TheCamera.setPosition(&camStart);
	TheCamera.getPosition(&p);
	TheCamera.getLook(&t);

	//flashLight = d3d::InitSpotLight(&p, &t, &c);

	//D3DXVECTOR3 pos(0.0f,10.f, -10.5f);
	//D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	//D3DXMATRIX V;
	//D3DXMatrixLookAtLH(
	//	&V,
	//	&pos,
	//	&target,
	//	&up);

	//Device->SetTransform(D3DTS_VIEW, &V);

	//
	// Set projection matrix
	//
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.5f, // 90 - degree
			(float)Width / (float)Height,
			1.0f,
			1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

void DrawWalls()
{
			D3DXMATRIX i;
		D3DXMatrixIdentity(&i);
		Device->SetStreamSource(0, VBufferGround, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexGround);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		Device->SetStreamSource(0, VBufferGround, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexDirections);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 12, 2);

				Device->SetStreamSource(0, VBufferGround, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexDirections);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

						Device->SetStreamSource(0, VBufferGround, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexDirections);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 24, 2);

		Device->SetStreamSource(0, VBufferGround, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexDirections);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 30, 2);

		Device->SetStreamSource(0, VBufferGround, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexSky);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 6, 2);

		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexWood);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 22);

		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexPrizes);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 66, 4);

		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexBack);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 78, 2);
		
		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexTarget);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 84, 2);

		D3DXMATRIX tripler;
		D3DXMatrixTranslation(&tripler, 15, 0, 0);
		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexTarget);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 84, 2);

		D3DXMatrixTranslation(&tripler, -15, 0, 0);
		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexTarget);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 84, 2);




}
void Cleanup()
{
		for(int i = 0; i < 6; i++)
			d3d::Release<ID3DXMesh*>(GunObjects[i]);

		d3d::Release<IDirect3DVertexBuffer9*>(VBuffer);
		d3d::Release<IDirect3DVertexBuffer9*>(VBufferGround);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		if(::GetAsyncKeyState('P') & 0x8000f)
			pause = true;

				if(::GetAsyncKeyState('W') & 0x8000f)
			TheCamera.walk(1.0 * DTime);
		if(::GetAsyncKeyState('S') & 0x8000f)
			TheCamera.walk(-1.0 * DTime);
		if(::GetAsyncKeyState('A') & 0x8000f)
			TheCamera.strafe(-1.0 * DTime);
		if(::GetAsyncKeyState('D') & 0x8000f)
			TheCamera.strafe(1.0 * DTime);
		if(::GetAsyncKeyState('F') & 0x8000f)
			TheCamera.fly(-1.0 * DTime);
		if(::GetAsyncKeyState('R') & 0x8000f)
			TheCamera.fly(1.0 * DTime);

		if(::GetAsyncKeyState(VK_UP) & 0x8000f)
			TheCamera.pitch(-1.0 * DTime);
		if(::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			TheCamera.pitch(
			1.0 * DTime);
		if(::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			TheCamera.yaw(-1.0 * DTime);
		if(::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			TheCamera.yaw(1.0 * DTime);
		if(::GetAsyncKeyState(VK_HOME) & 0x8000f)
			TheCamera.roll(1.0 * DTime);
		if(::GetAsyncKeyState(VK_END) & 0x8000f)
			TheCamera.roll(-1.0 * DTime);

		if(!bGame)
			if(::GetAsyncKeyState(VK_RETURN) & 0x8000f)
			{
				::MessageBoxA(0, "Use the arrow keys to look around\nPress Spacebar to fire\n Aim for the middle target", "Game Controls", MB_OK);
				::MessageBoxA(0, "It is a known bug that the Bullets aren't showing up, but they are there", "KNOWN BUG", MB_OK);
				bGame = true;
			}
		if(middleHieght == 0)
		{
			bGame = false;
			::MessageBoxA(0, "YAY YOU WON!", "Congratulaions", MB_OK);
			middleHieght = -10;
		}

		//
		// Render
		//

		if (bGame)
			playgame();

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
		Device->BeginScene();
		
		DrawWalls();
		D3DXMATRIX i, tripler;
		D3DXMatrixIdentity(&i);
		Device->SetTransform(D3DTS_WORLD, &i);
		if(Box)
			Box->draw(&i, 0, TexCrate);
		
		D3DXMatrixTranslation(&tripler, 15, 0, 0);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		if(Box)
			Box->draw(&tripler, 0, TexCrate);
				
		D3DXMatrixTranslation(&tripler, -15, 0, 0);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		if(Box)
			Box->draw(&tripler, 0, TexCrate);



		D3DXMatrixTranslation(&tripler, 0, middleHieght, 0);
		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexBanner);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 90, 2);
		
		leftHeight += leftSpeed;

		if (leftHeight >= -0.001 || leftHeight <= -9.999)
			leftSpeed *= -1;
		D3DXMatrixTranslation(&tripler, -15, leftHeight, 0);
		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexBanner);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 90, 2);

		rightHeight += rightSpeed;

		if (rightHeight >= -0.001 || rightHeight <= -9.99975)
			rightSpeed *= -1;

		D3DXMatrixTranslation(&tripler, 15, rightHeight, 0);
		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexBanner);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 90, 2);

		Device->SetTexture(0, TexGround);

		Device->SetRenderState(D3DRS_LIGHTING, true);
		
		

		
		//Set Up Directional light
	D3DXVECTOR3 dir(0.0f, -10.0f, 0.0f);
	D3DXCOLOR c = d3d::WHITE;
		D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);



	//Set and enable light
	Device->SetLight(0, &dirLight);
	Device->LightEnable(0, true);

	//Set light render states
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);
		Device->SetMaterial(&Mtrls[0]);
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->move();
			bullets[i]->mesh->DrawSubset(0);
		}
			
		///////////////////////////////////////////////////////////////////////////////
		//1
		//gun
		//Gun1
		Device->SetMaterial(&Mtrls[4]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[0]);
		GunObjects[0]->DrawSubset(0);
		
		//Gun2
		
		Device->SetMaterial(&Mtrls[2]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[1]);
		GunObjects[1]->DrawSubset(0);
		

		//Gun3
		//Device->SetRenderState(D3DRS_LIGHTING, true);
		Device->SetMaterial(&Mtrls[1]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[2]);
		GunObjects[2]->DrawSubset(0);
		//Device->SetRenderState(D3DRS_LIGHTING, false);
		//Gun4
		Device->SetMaterial(&Mtrls[5]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[3]);
		GunObjects[3]->DrawSubset(0);
		//waterhose
		Device->SetMaterial(&Mtrls[6]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[4]);
		GunObjects[4]->DrawSubset(0);
		/////////////////////////////////////////
		//2
		//gun
		//Gun1
		Device->SetMaterial(&Mtrls[4]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[5]);
		GunObjects[5]->DrawSubset(0);
		
		//Gun2
		Device->SetMaterial(&Mtrls[2]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[6]);
		GunObjects[6]->DrawSubset(0);

		//Gun3
		Device->SetMaterial(&Mtrls[1]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[7]);
		GunObjects[7]->DrawSubset(0);

		//Gun4
		Device->SetMaterial(&Mtrls[5]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[8]);
		GunObjects[8]->DrawSubset(0);
		//waterhose
		Device->SetMaterial(&Mtrls[6]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[9]);
		GunObjects[9]->DrawSubset(0);
		/////////////////////////////////////////
		/////////////////////////////////////////
		//3
		//gun
		//Gun1
		Device->SetMaterial(&Mtrls[4]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[10]);
		GunObjects[10]->DrawSubset(0);
		
		//Gun2
		Device->SetMaterial(&Mtrls[2]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[11]);
		GunObjects[11]->DrawSubset(0);

		//Gun3
		Device->SetMaterial(&Mtrls[1]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[12]);
		GunObjects[12]->DrawSubset(0);

		//Gun4
		Device->SetMaterial(&Mtrls[5]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[13]);
		GunObjects[13]->DrawSubset(0);
		//waterhose
		Device->SetMaterial(&Mtrls[6]);
		Device->SetTransform(D3DTS_WORLD, &GunWorlds[14]);
		GunObjects[14]->DrawSubset(0);
		///////////////////////////////

		Device->SetRenderState(D3DRS_LIGHTING, false);

				D3DXMATRIX V, T;
		TheCamera.getViewMatrix(&V);

		Device->SetTransform(D3DTS_VIEW, &V);

		TheCamera.getPosition(&p);
		TheCamera.getLook(&t);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);

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
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

		HRESULT hr;
    if( FAILED( hr = sound.PrepareXACT() ) )
    {
        if( hr == HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ) )
            MessageBox( 0, "Failed to init XACT because media not found.", "XACT Tutorial", MB_OK );
        else
            MessageBox( 0, "Failed to init XACT.", "XACT Tutorial", MB_OK );
       sound.CleanupXACT();
        return 0;
    }
		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	sound.AudioPlay(Song);

	::MessageBoxA(0, "Use WSAD and RF to move the camera around\nUse the Arrow Keys to look around\nWhen ready to start playing press ENTER", "Welcome", MB_OK);

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}