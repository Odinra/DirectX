#include "d3dUtility.h"
#include <vector>
/*****************************************************************************
//ADJUST ALL SPEED HERE
******************************************************************************/
float DTime = 0.00090f;

//XFiles
XFile Tiger;//1
XFile Castle;//2
XFile Grenade;//3
XFile Manor;//4
XFile Monster;//5
XFile RavengerSiren;//6
XFile Sectoid;//7
XFile Slenderman;//8
XFile Soccer;//9
XFile Turret;//10
XFile Ultraman;//11
XFile Zombie;//12
D3DXVECTOR3 TigerPos(50,5,250);
D3DXVECTOR3 CastlePos(0,0,200);//2
D3DXVECTOR3 GrenadePos(30,0,275);//3
D3DXVECTOR3 ManorPos(0,0,500);//4
D3DXVECTOR3 MonsterPos(10,0,175);//5
D3DXVECTOR3 RavengerSirenPos(0,0,165);//6
D3DXVECTOR3 SectoidPos(-10,0,210);//7
D3DXVECTOR3 SlendermanPos(-20,0,130);//8
D3DXVECTOR3 SoccerPos(-30,0,275);//9
D3DXVECTOR3 TurretPos(-40,0,230);//10
D3DXVECTOR3 UltramanPos(-50,10,230);//11
D3DXVECTOR3 ZombiePos(-60,0,160);//12
double sizeModifier = 100;
bool shrunk = false;

D3DXMATRIX MatrixProj;

//
// Globals
//
HWND mainHWND;
bool pause;
Audio sound;
PCSTR Song = "Song";
PCSTR Bang = "Bang";
PCSTR Voice = "Voice";
IDirect3DDevice9* Device = 0;
const int Width  = 640;
const int Height = 480;
D3DMATERIAL9 Mtrls[10];
D3DXVECTOR3 camStart(0.0f, 8.5f, -10.0f);
Cube* Box;
IDirect3DTexture9* TexGround = 0;
IDirect3DTexture9* TexSky = 0;
IDirect3DTexture9* TexWood = 0;
IDirect3DTexture9* TexDirections = 0;
IDirect3DTexture9* Stone =0;
IDirect3DTexture9* DoNot = 0;
Camera TheCamera(Camera::AIRCRAFT);
IDirect3DVertexBuffer9* VBufferGround = 0;
D3DXVECTOR3 p;
D3DXVECTOR3 t;
DWORD timeelapsed, currtime, lasttime;
//creates instance of light
D3DXVECTOR3 dir(1.0f, 0.0f, 0.0f);
D3DXCOLOR c = d3d::WHITE;
D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);
bool Setup()
{
	Tiger.init(Device, "Tiger.X");//1
	Castle.init(Device, "Castle.X");//2
	Grenade.init(Device, "Grenade.X");//3
	Manor.init(Device, "Manor.X");//4
	Monster.init(Device, "Monster.X");//5
	RavengerSiren.init(Device, "RavengerSiren.X");//6
	Sectoid.init(Device, "Sectoid.X");//7
	Slenderman.init(Device, "Slenderman.X");//8
	Soccer.init(Device, "Soccer.X");//9
	Turret.init(Device, "Turret.X");//10
	Ultraman.init(Device, "Ultraman.X");//11
	Zombie.init(Device, "Zombie.X");//12

	//Set texture filters.
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//
	// Create the BackDrop quad.
	//
	//
	//Ground
	//
	Device->CreateVertexBuffer(42 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBufferGround, 0);

	Vertex* VGround;
	VBufferGround->Lock(0, 0, (void**)&VGround, 0);

	VGround[0] = Vertex(-0500.0f, 0.0f,-0500.0f, 0.0f, 1.0f, 0.0f,   0.0f, 100.0f);
	VGround[1] = Vertex(-0500.0f, 0.0f,0500.0f, 0.0f, 1.0f, 0.0f,   0.0f,   0.0f);
	VGround[2] = Vertex( 0500.0f, 0.0f,0500.0f, 0.0f, 1.0f, 0.0f, 100.0f,   0.0f);
	VGround[3] = Vertex(-0500.0f, 0.0f,-0500.0f, 0.0f, 1.0f, 0.0f,   0.0f, 100.0f);
	VGround[4] = Vertex(0500.0f, 0.0f,0500.0f, 0.0f, 1.0f, 0.0f, 100.0f,   0.0f);
	VGround[5] = Vertex(0500.0f, 0.0f,-0500.0f, 0.0f, 1.0f, 0.0f, 100.0f, 100.0f);
	//
	//Sky
	//
	VGround[6] = Vertex(0500.0f, 1000.0f,0500.0f, 0.0f, -1.0f, 0.0f,   0.0f, 1.0f);
	VGround[7] = Vertex(-0500.0f, 1000.0f, 0500.0f, 0.0f, -1.0f, 0.0f,   0.0f,   0.0f);
	VGround[8] = Vertex( -0500.0f, 1000.0f, -0500.0f, 0.0f, -1.0f, 0.0f, 1.0f,   0.0f);
	VGround[9] = Vertex(0500.0f, 1000.0f,500.0f, 0.0f, -1.0f, 0.0f,   0.0f, 1.0f);
	VGround[10] = Vertex( -0500.0f, 1000.0f,-0500.0f, 0.0f, -1.0f, 0.0f, 1.0f,   0.0f);
	VGround[11] = Vertex( 0500.0f, 1000.0f,-0500.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	//
	//North
	//
	VGround[12] = Vertex(-0500.0f, -000.0f, 0500.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[13] = Vertex(-0500.0f,  1000.0f, 0500.0f, 0.0f, 0.0f, -1.0f,   0.0f,   0.0f);
	VGround[14] = Vertex( 0500.0f,  1000.0f, 0500.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[15] = Vertex(-0500.0f, -000.0f, 0500.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[16] = Vertex( 0500.0f,  1000.0f, 0500.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[17] = Vertex( 0500.0f, -000.0f, 0500.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);	
	//
	//South
	//
	VGround[18] = Vertex( 0500.0f, -0000.0f, -0500.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f);
	VGround[19] = Vertex( 0500.0f,  1000.0f, -0500.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f);
	VGround[20] = Vertex(-0500.0f,  1000.0f, -0500.0f, 0.0f, 0.0f, 1.0f, 1.0f,   0.0f);
	VGround[21] = Vertex( 0500.0f, -0000.0f, -0500.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f);
	VGround[22] = Vertex(-0500.0f,  1000.0f, -0500.0f, 0.0f, 0.0f, 1.0f, 1.0f,   0.0f);
	VGround[23] = Vertex(-0500.0f, -0000.0f, -0500.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	//
	//East
	//
	VGround[24] = Vertex( 0500.0f, -0000.0f,  0500.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[25] = Vertex( 0500.0f,  1000.0f,  0500.0f, -1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VGround[26] = Vertex( 0500.0f,  1000.0f, -0500.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[27] = Vertex( 0500.0f, -0000.0f,  0500.0f, -1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[28] = Vertex( 0500.0f,  1000.0f, -0500.0f, -1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[29] = Vertex( 0500.0f, -0000.0f, -0500.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	//
	////West
	//
	VGround[30] = Vertex(-0500.0f, -0000.0f, -0500.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[31] = Vertex(-0500.0f,  1000.0f, -0500.0f, 1.0f, 0.0f, 0.0f,   0.0f,   0.0f);
	VGround[32] = Vertex(-0500.0f,  1000.0f,  0500.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[33] = Vertex(-0500.0f, -0000.0f, -0500.0f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f);
	VGround[34] = Vertex(-0500.0f,  1000.0f,  0500.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f);
	VGround[35] = Vertex(-0500.0f, -0000.0f,  0500.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	
	//
	//Message
	//
	VGround[36] = Vertex(-10.0f, 12.5f, 20.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[37] = Vertex(-10.0f,  20.5f, 20.0f, 0.0f, 0.0f, -1.0f,   0.0f,   0.0f);
	VGround[38] = Vertex( 10.0f,  20.5f, 20.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[39] = Vertex(-10.0f, 12.5f, 20.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[40] = Vertex( 10.0f,  20.5f, 20.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[41] = Vertex( 10.0f, 12.5f, 20.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);	

	VBufferGround->Unlock();
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
	D3DXCreateTextureFromFile(Device, "Stone.jpg", &Stone);
	D3DXCreateTextureFromFile(Device, "DoNot.png", &DoNot);
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
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

}
void Cleanup()
{
		d3d::Release<IDirect3DVertexBuffer9*>(VBufferGround);
}
bool message = true;
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
			TheCamera.pitch(-.250 * DTime);
		if(::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			TheCamera.pitch(.250 * DTime);
		if(::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			TheCamera.yaw(-.250 * DTime);
		if(::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			TheCamera.yaw(.250 * DTime);
		if(::GetAsyncKeyState(VK_HOME) & 0x8000f)
			TheCamera.roll(.250 * DTime);
		if(::GetAsyncKeyState(VK_END) & 0x8000f)
			TheCamera.roll(-.250 * DTime);
		if(TheCamera._up.y < 0)
			TheCamera._up.y *= -1;

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
		Device->BeginScene();
		DrawWalls();
		D3DXMATRIX i, tripler, grow;
		D3DXMatrixIdentity(&i);
		Device->SetTransform(D3DTS_WORLD, &i);
		
		//1
		D3DXMatrixTranslation(&tripler, TigerPos.x, TigerPos.y, TigerPos.z);
		D3DXMatrixScaling(&grow, 5/sizeModifier, 5/sizeModifier, 5/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Tiger.Draw(Stone);
		//2	
		D3DXMatrixTranslation(&tripler, CastlePos.x, CastlePos.y, CastlePos.z);
		D3DXMatrixScaling(&grow, 2.5/sizeModifier, 1/sizeModifier, 2.5/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Castle.Draw(Stone);
		//3		
		D3DXMatrixTranslation(&tripler, GrenadePos.x, GrenadePos.y, GrenadePos.z);
		D3DXMatrixScaling(&grow, .1/sizeModifier, .1/sizeModifier, .1/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Grenade.Draw(Stone);
		//4
		D3DXMatrixTranslation(&tripler, ManorPos.x, ManorPos.y, ManorPos.z);
		D3DXMatrixScaling(&grow, 5000/sizeModifier, 5000/sizeModifier, 50);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Manor.Draw(Stone);
		//5		
		D3DXMatrixTranslation(&tripler, MonsterPos.x, MonsterPos.y, MonsterPos.z);
		D3DXMatrixScaling(&grow, 1/sizeModifier, 1/sizeModifier, 1/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Monster.Draw(Stone);
		//6		
		D3DXMatrixTranslation(&tripler, RavengerSirenPos.x, RavengerSirenPos.y, RavengerSirenPos.z);
		D3DXMatrixScaling(&grow, .1/sizeModifier, .1/sizeModifier, .1/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		RavengerSiren.Draw(Stone);
		//7		
		D3DXMatrixTranslation(&tripler, SectoidPos.x, SectoidPos.y, SectoidPos.z);
		D3DXMatrixScaling(&grow, 3/sizeModifier, 3/sizeModifier, 3/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Sectoid.Draw(Stone);
		//8		
		D3DXMatrixTranslation(&tripler, SlendermanPos.x, SlendermanPos.y, SlendermanPos.z);
		D3DXMatrixScaling(&grow, .05/sizeModifier, .05/sizeModifier, .05/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Slenderman.Draw(Stone);
		//9		
		D3DXMatrixTranslation(&tripler, SoccerPos.x, SoccerPos.y, SoccerPos.z);
		D3DXMatrixScaling(&grow, .05/sizeModifier, .05/sizeModifier, .05/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Soccer.Draw(Stone);
		//10		
		D3DXMatrixTranslation(&tripler, TurretPos.x, TurretPos.y, TurretPos.z);
		D3DXMatrixScaling(&grow, .1/sizeModifier, .1/sizeModifier, .1/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Turret.Draw(Stone);
		//11		
		D3DXMatrixTranslation(&tripler, UltramanPos.x, UltramanPos.y, UltramanPos.z);
		D3DXMatrixScaling(&grow, .01/sizeModifier, .01/sizeModifier, .01/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Ultraman.Draw(Stone);
		//12		
		D3DXMatrixTranslation(&tripler, ZombiePos.x, ZombiePos.y, ZombiePos.z);
		D3DXMatrixScaling(&grow, .1/sizeModifier, .1/sizeModifier, .1/sizeModifier);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		Zombie.Draw(Stone);

		if(!shrunk && p.z > 10)
		{
			shrunk = true;
			sound.AudioPlay(Voice);
			::MessageBoxA(0, "OH NO! you appear to be Shrinking\nStart Running to try and reach the manor", "Oh No!", MB_OK);
			DTime *= 5;
		}
		else if(shrunk)
		{
			
			if(sizeModifier >1)
			{
				sizeModifier-=.005;
			}
			else if(message)
			{
				message = false;
				::MessageBoxA(0, "It's too late, however you seem to be at the entrance to a castle and there appears to be some createures on the inside.\nMaybe you should try to approach one of them, Be Careful Though: they could be Evil", "Too Late", MB_OK);
			}
		}
		static bool approach = false;
		if(!approach)
			if(p.z > 125)
			{
				::MessageBoxA(0, "The creatures seem to be frozen and have had all their color drained...\nThey look like they were once the things that only exis in nightmares\nWhat kind of Powerfull Monster could have done this?\nMaybe you shouldn't have ignored those warnings.", "", MB_OK);
				approach = true;
			}
			static bool bang = false;
		if(p.z > 0)
		{
			if(!bang)
			{
				bang = true;
				sound.AudioPlay(Bang);
			}
			Device->SetStreamSource(0, VBufferGround, 0, sizeof(Vertex));
			Device->SetFVF(FVF_VERTEX);
			Device->SetTexture(0, DoNot);
			Device->SetTransform(D3DTS_WORLD, &i);
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 36, 2);
			Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		}

		
		D3DXMATRIX V, T;
		TheCamera.getViewMatrix(&V);
		Device->SetTransform(D3DTS_VIEW, &V);
		TheCamera.getPosition(&p);
		if (p.y != 8.5)
			p.y = 8.5;
		TheCamera.setPosition(&p);
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
            MessageBox( 0, "Failed to init XACT./n(sometimes Xact like to act up the first time ran on new computers try going to the Sound.xap file in the project folder and pressing F7 then enter)", "XACT Tutorial", MB_OK );
       sound.CleanupXACT();
        return 0;
    }		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}
	sound.AudioPlay(Song);
	::MessageBoxA(0, "You wake up in a field, and as you look around all you see is a scary mansion off in the distance\nYou decide to make your way towards the mansion in hopes of finding help", "Welcome", MB_OK);
	::MessageBoxA(0, "Use WSAD to move the camera around\nUse the Arrow Keys to look around", "Welcome", MB_OK);
	d3d::EnterMsgLoop( Display );
	Cleanup();
	Device->Release();
	return 0;
}