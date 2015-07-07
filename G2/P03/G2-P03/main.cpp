#include "base.h"
/*****************************************************************************
//ADJUST ALL SPEED HERE
******************************************************************************/
float DTime = 0.0090f;

//
// Globals
//

bool bkey = false;
bool bmouse = false;
bool bjoy = false;

double speed = 0;

D3DMATERIAL9 mtrl0, mtrl1, mtrl2, mtrl3, mtrl4, mtrl5, mtrl6, mtrl7, mtrl8, mtrl9;
D3DMATERIAL9 mtrlWhite;

HINSTANCE main_instance = NULL;
HWND main_hwnd = 0;

IDirect3DDevice9* Device = 0;

LPDIRECTINPUT8 lpDI = NULL;

LPDIRECTINPUTDEVICE8 lpDIKey = NULL;
UCHAR keyboard_state[256];

LPDIRECTINPUTDEVICE8 lpDIMouse = NULL;
DIMOUSESTATE mouse_state;

D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;

bool mouse = false;
bool keyboard = false;
bool joystick = false;

int numberofasteroids;
ID3DXMesh** pAsteroids;
D3DXVECTOR3* vAsteroids;
D3DMATERIAL9* mtrlAsteroids;
D3DXVECTOR3* sAsteroids;
double* size;
bool* bAsteroids;

// Direct Input 8 – Joystick - GOES UP TOP WITH ALL YOUR OTHER
//GLOBALS
LPDIRECTINPUTDEVICE8 lpDIJS = NULL;
GUID joystickGUID; // guid for main joystick
char joyname[80]; // name of joystick
DIJOYSTATE joy_state; // contains state of joystick


const int Width  = 900;
const int Height = 600;

D3DXMATRIX World;

DWORD starttime = 0;

Camera TheCamera(Camera::AIRCRAFT);

ID3DXMesh* StartPlanet;
ID3DXMesh* EndPlanet;

ID3DXMesh** Spaceship;
D3DXVECTOR3* vSpaceship;

D3DXVECTOR3 vEndPlanet;

D3DXVECTOR3 p;
D3DXVECTOR3 t;
D3DXCOLOR c = d3d::WHITE;

int numberFound = 0;
double seconds = 0;

char buffers[50];
char buffers2[50];
char buffers3[100];

ID3DXFont *m_font;

DWORD dwLastTick = GetTickCount();

BOOL CALLBACK DI_Enum_Joysticks(LPCDIDEVICEINSTANCE lpddi, LPVOID guid_ptr)
{
	// this function enumerates the joysticks, but
	// stops at the first one and returns the
	// instance guid of it, so we can create it
	*(GUID*)guid_ptr = lpddi->guidInstance;

	// copy name into global
	strcpy(joyname, (char *)lpddi->tszProductName);

	// stop enumeration after one iteration
	return(DIENUM_STOP);

} // end DI_Enum_Joysticks


void DisplayTime(int seconds)
{
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255); 

	RECT rect2;
	rect2.left=2;
	rect2.right=780;
	rect2.top=40;
	rect2.bottom=rect2.top+20;

	sprintf(buffers2, "Time: %d seconds", seconds);

	m_font->DrawText(NULL, buffers2, 50, &rect2, 0, fontColor );
}

void Randomizer()
{
	numberofasteroids = rand()%100;
	delete [] pAsteroids;
	delete [] vAsteroids;
	delete [] mtrlAsteroids;
	delete [] sAsteroids;
	delete [] bAsteroids;
	delete [] size;

	pAsteroids = new ID3DXMesh*[numberofasteroids];
	vAsteroids = new D3DXVECTOR3[numberofasteroids];
	mtrlAsteroids = new D3DMATERIAL9[numberofasteroids];
	sAsteroids = new D3DXVECTOR3[numberofasteroids];
	size = new double[numberofasteroids];
	bAsteroids = new bool[numberofasteroids];

	for(int i = 0; i < numberofasteroids; i++)
	{
		vAsteroids[i].x = (rand() % 2000 - 1000);
		vAsteroids[i].y = (rand() % 2000 - 1000);
		vAsteroids[i].z = (rand() % 10000);
		sAsteroids[i].x = (rand() % 200 - 100) / 100.0;
		sAsteroids[i].y = (rand() % 200 - 100) / 100.0;
		sAsteroids[i].z = (rand() % 200 - 100) / 100.0;
		D3DXCOLOR c1, c2, c3, c4;
		c1 = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
		c2 = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
		c3 = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
		c4 = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
		float p = rand() % 1000 / 1000.0;
		size[i] = rand() % 100 + 1;
		D3DXCreateSphere(Device, size[i], 180, 180, &pAsteroids[i], 0);
		mtrlAsteroids[i] = d3d::InitMtrl( c1, c2, c3, c4, p );
		bAsteroids[i] = true;
	}
}

void Collides(D3DXVECTOR3 camera)
{
	if (camera.x <= vEndPlanet.x + 300) 
	{
		if (camera.y <= vEndPlanet.y + 300) 
		{
			if(camera.z <= vEndPlanet.z + 300)
			{
				if (camera.x >= vEndPlanet.x - 300) 
				{
					if (camera.y >= vEndPlanet.y - 300) 
					{
						if (camera.z >= vEndPlanet.z - 300)
						{
							Randomizer();
							sprintf(buffers3, "Seconds taken to reach the end: %f\n\nWould you like to play again?", seconds);
							int answer = MessageBox(0, buffers3, "Congratulations", MB_YESNO);
							if(answer == IDNO)
								::PostQuitMessage(0);
							seconds = 0;
							D3DXVECTOR3 camStart(0.0f, 0.0f, 0.0f);
							TheCamera.setPosition(&camStart);
							speed = 0;

						}
					}
				}
			}
		}
	}
	for(int i = 0; i < numberofasteroids; i++)
	{
		if(bAsteroids[i])
		{
			if (camera.x <= vAsteroids[i].x + size[i]) 
			{
				if (camera.y <= vAsteroids[i].y + size[i]) 
				{
					if(camera.z <= vAsteroids[i].z + size[i])
					{
						if (camera.x >= vAsteroids[i].x - size[i]) 
						{
							if (camera.y >= vAsteroids[i].y - size[i]) 
							{
								if (camera.z >= vAsteroids[i].z - size[i])
								{
									seconds += 30;
									bAsteroids[i] = false;
								}
							}
						}
					}
				}
			}
		}
	}

}

//
// Framework functions
//
bool Setup()
{
	if(FAILED(DirectInput8Create(main_instance, DIRECTINPUT_VERSION, IID_IDirectInput8,	(void**)&lpDI, NULL)))
		{
			return(0);
		}
			
	//Check for DI Device
	if(bkey)
	{


		// Check for Keyboard

		if(FAILED(lpDI->CreateDevice(GUID_SysKeyboard, &lpDIKey, NULL)))
		{
			return(0);
		}

		if(FAILED(lpDIKey->SetCooperativeLevel(main_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		{
			return(0);
		}

		if(FAILED(lpDIKey->SetDataFormat(&c_dfDIKeyboard)))
		{
			return(0);
		}

		if(FAILED(lpDIKey->Acquire()))
		{
			return(0);
		}
	}
	if(bmouse)
	{
		// Check for Mouse

		if(FAILED(lpDI->CreateDevice(GUID_SysMouse, &lpDIMouse, NULL)))
		{
			return(0);
		}

		if(FAILED(lpDIMouse->SetCooperativeLevel(main_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		{
			return(0);
		}

		if(FAILED(lpDIMouse->SetDataFormat(&c_dfDIMouse)))
		{
			return(0);
		}

		if(FAILED(lpDIMouse->Acquire()))
		{
			return(0);
		}
	}
	if(bjoy)
	{
		//Direct Input 8 - J O Y S T I C K goes in Setup function
		// first find the GUID of your particular joystick
		lpDI->EnumDevices(DI8DEVCLASS_GAMECTRL, DI_Enum_Joysticks, &joystickGUID, DIEDFL_ATTACHEDONLY); 
		if (FAILED(lpDI->CreateDevice(joystickGUID, &lpDIJS, NULL)))
		{
			return(0);
		}
		if (FAILED(lpDIJS->SetCooperativeLevel(main_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		{
			return(0);
		}
		if (FAILED(lpDIJS->SetDataFormat(&c_dfDIJoystick)))
		{
			return(0);
		}
		// set the range of the joystick
		DIPROPRANGE joy_axis_range;

		// first x axis
		joy_axis_range.lMin = -100;
		joy_axis_range.lMax = 100;
		joy_axis_range.diph.dwSize = sizeof(DIPROPRANGE); 
		joy_axis_range.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		joy_axis_range.diph.dwObj = DIJOFS_X;
		joy_axis_range.diph.dwHow = DIPH_BYOFFSET;

		lpDIJS->SetProperty(DIPROP_RANGE,&joy_axis_range.diph);

		// now y-axis
		joy_axis_range.lMin = -100;
		joy_axis_range.lMax = 100;

		joy_axis_range.diph.dwSize = sizeof(DIPROPRANGE); 
		joy_axis_range.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		joy_axis_range.diph.dwObj = DIJOFS_Y;
		joy_axis_range.diph.dwHow = DIPH_BYOFFSET;

		lpDIJS->SetProperty(DIPROP_RANGE,&joy_axis_range.diph);

		// and now the dead band

		DIPROPDWORD dead_band; // here's our property word

		dead_band.diph.dwSize = sizeof(dead_band);
		dead_band.diph.dwHeaderSize = sizeof(dead_band.diph);
		dead_band.diph.dwObj = DIJOFS_X;
		dead_band.diph.dwHow = DIPH_BYOFFSET;

		// 10% will be used on both sides of the range +/-
		dead_band.dwData = 1000;

		// finally set the property
		lpDIJS->SetProperty(DIPROP_DEADZONE,&dead_band.diph);

		dead_band.diph.dwSize = sizeof(dead_band);
		dead_band.diph.dwHeaderSize = sizeof(dead_band.diph);
		dead_band.diph.dwObj = DIJOFS_Y;
		dead_band.diph.dwHow = DIPH_BYOFFSET;

		// 10% will be used on both sides of the range +/-
		dead_band.dwData = 1000;

		// finally set the property
		lpDIJS->SetProperty(DIPROP_DEADZONE,&dead_band.diph);


		//acquire the joystick
		if (FAILED(lpDIJS->Acquire()))
		{
			return(0);
		}
	}

	D3DXCreateFont(Device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );

	srand(time(0));

	Randomizer();

	mtrl0 = d3d::BLACK_MTRL;
	mtrl1 = d3d::BLACK_MTRL;
	mtrl2 = d3d::RED_MTRL;
	mtrl3 = d3d::GREEN_MTRL;
	mtrl4 = d3d::BLUE_MTRL;
	mtrl5 = d3d::BUGOLD_MTRL;
	mtrl6 = d3d::BUGREEN_MTRL;
	mtrl7 = d3d::MAGENTA_MTRL;
	mtrl8 = d3d::YELLOW_MTRL;
	mtrl9 = d3d::GRAY_MTRL;
	mtrlWhite = d3d::WHITE_MTRL;

	D3DXCreateSphere(Device, 300, 180, 180, &EndPlanet, 0);
	D3DXCreateSphere(Device, 100, 180, 180, &StartPlanet, 0);
	//Translation
	D3DXMatrixTranslation(&World, 0.0f, 2.0f, 0.0f);

	numberFound = 0;

	D3DXVECTOR3 camStart(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 dir(0.0f, -1.0f, 0.0f);
	D3DXVECTOR3 pos(0.0f, 123.0f, 0.0f);
	D3DXCOLOR cBlue = d3d::LIGHTBLUE;
	D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &cBlue, &pos);

	TheCamera.setPosition(&camStart);
	TheCamera.getPosition(&p);
	TheCamera.getLook(&t);

	Spaceship = new ID3DXMesh*[8];
	vSpaceship = new D3DXVECTOR3[8];

	D3DXCreateBox(Device, 5, 2.5, .1, &Spaceship[0], 0);		//front
	D3DXCreateBox(Device, 5, 5, .1, &Spaceship[1], 0);		//back
	D3DXCreateBox(Device, 5, .1, 5, &Spaceship[2], 0);		//up
	D3DXCreateBox(Device, 5, .1, 5, &Spaceship[3], 0);		//down
	D3DXCreateBox(Device, .1, 5, 5, &Spaceship[4], 0);		//left
	D3DXCreateBox(Device, .1, 5, 5, &Spaceship[5], 0);		//right
	D3DXCreateSphere(Device, .3,180, 180, &Spaceship[6], 0);	//green
	D3DXCreateSphere(Device, .3,180, 180, &Spaceship[7], 0); //red

	vSpaceship[0].x = p.x;
	vSpaceship[0].y = p.y;
	vSpaceship[0].z = p.z + 2.5;
	vSpaceship[1].x = p.x;
	vSpaceship[1].y = p.y;
	vSpaceship[1].z = p.z - 2.5;
	vSpaceship[2].x = p.x;
	vSpaceship[2].y = p.y + 2.5;
	vSpaceship[2].z = p.z;
	vSpaceship[3].x = p.x;
	vSpaceship[3].y = p.y - 2.5;
	vSpaceship[3].z = p.z;
	vSpaceship[4].x = p.x + 2.5;
	vSpaceship[4].y = p.y;
	vSpaceship[4].z = p.z;
	vSpaceship[5].x = p.x + 2.5;
	vSpaceship[5].y = p.y;
	vSpaceship[5].z = p.z;

	vSpaceship[6].x = p.x + 1;
	vSpaceship[6].y = p.y - .6;
	vSpaceship[6].z = p.z + 2.5;

	vSpaceship[7].x = p.x - 1;
	vSpaceship[7].y = p.y - .6;
	vSpaceship[7].z = p.z + 2.5;

	
	

	//
	// Set camera.
	//


	//Device->SetTransform(D3DTS_VIEW, &V);
	//
	// Set projection matrix.
	//
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.25f, // 45 - degree
		(float)Width / (float)Height,
		0.01f,	
		1000000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	Device->SetRenderState(D3DRS_LIGHTING, true);

	// ambient light
	Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255,255,255));

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true); 

	vEndPlanet.x = 0;
	vEndPlanet.y = 0;
	vEndPlanet.z = 10000;

	//Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return true;
}

void Cleanup()
{
	//d3d::Release<ID3DXMesh*>(obj0Mesh);
	//d3d::Release<ID3DXMesh*>(oceanMesh);

	if(lpDIMouse)
		lpDIMouse->Unacquire();
	if(lpDIMouse)
		lpDIMouse->Release();

	if(lpDIKey)
		lpDIKey->Unacquire();
	if(lpDIKey)
		lpDIKey->Release();

	if (lpDIJS)
		lpDIJS->Unacquire();

	if (lpDIJS)
		lpDIJS->Release();

}

bool Display()
{


	if( Device )
	{
		HRESULT hresult;
		
		if(bkey)
		{
			hresult = lpDIKey->GetDeviceState(256, (LPVOID)keyboard_state);
			if(hresult == DIERR_INPUTLOST)
			{
				if(FAILED(lpDIKey->Acquire()))
				{
					return 0;
				}
			}

			if(keyboard_state[DIK_SPACE]&0x80)
			{
				speed = 0;
			}
			else
			{
				if(keyboard_state[DIK_RIGHT]&0x80)
				{
					speed += numberofasteroids;
					TheCamera.strafe(speed * DTime);
				}
				if(keyboard_state[DIK_LEFT]&0x80)
				{
					speed += numberofasteroids;
					TheCamera.strafe(speed * DTime * -1);
				}
				if(keyboard_state[DIK_UP]&0x80)
				{
					speed += numberofasteroids;
					TheCamera.walk(speed * DTime);
				}
				if(keyboard_state[DIK_DOWN]&0x80)
				{
					speed += numberofasteroids;
					TheCamera.walk(speed* DTime * -1);	
				}
				if(keyboard_state[DIK_PGUP]&0x80)
				{
					speed += numberofasteroids;
					TheCamera.fly(speed * DTime);	
				}
				if(keyboard_state[DIK_PGDN]&0x80)
				{
					speed += numberofasteroids;
					TheCamera.fly(speed * DTime * -1);	
				}
			}
			if(keyboard_state[DIK_W]&0x80)
			{
				TheCamera.pitch(-0.10 * DTime);
			}
			if(keyboard_state[DIK_A]&0x80)
			{
				TheCamera.yaw(-0.10 * DTime);
			}
			if(keyboard_state[DIK_S]&0x80)
			{
				TheCamera.pitch(0.10 * DTime);
			}
			if(keyboard_state[DIK_D]&0x80)
			{
				TheCamera.yaw(0.10 * DTime);
			}
			if(keyboard_state[DIK_Q]&0x80)
			{
				TheCamera.roll(-0.10 * DTime);
			}
			if(keyboard_state[DIK_E]&0x80)
			{
				TheCamera.roll(0.10 * DTime);
			}
		}

		if(speed >= numberofasteroids * 10)
			speed = numberofasteroids * 10;

		if(bmouse)
		{

			HRESULT hresult2;

			hresult2 = lpDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID) &mouse_state);

			if(hresult2 == DIERR_INPUTLOST)
			{
				if(FAILED(lpDIMouse->Acquire()))
				{
					return 0;
				}
			}

			TheCamera.yaw(mouse_state.lX*.001f);
			TheCamera.pitch(mouse_state.lY*.001f);
			TheCamera.roll(mouse_state.lZ*.001f);

			if(mouse_state.rgbButtons[0]&0x80)
			{
				speed += numberofasteroids;
				TheCamera.walk(speed * DTime);
			}
			if(mouse_state.rgbButtons[1] & 0x80)
			{
				speed += numberofasteroids;
				TheCamera.walk(speed * DTime * -1);
			}
			if(mouse_state.rgbButtons[2]&0x80)
			{
				speed += numberofasteroids;
				TheCamera.strafe(speed * DTime);
			}
			if(mouse_state.rgbButtons[3] & 0x80)
			{
				speed += numberofasteroids;
				TheCamera.strafe(speed * DTime * -1);
			}
		}

		if(bjoy)
		{
			// J O Y S T I C K 

			lpDIJS->Poll(); // this is needed for joysticks only
			lpDIJS->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID)&joy_state);


			TheCamera.pitch(joy_state.lY * .0001f); 
			TheCamera.yaw(joy_state.lX * .0001f);

			if(joy_state.rgbButtons[0]&0x80)
			{
				speed += numberofasteroids;
				TheCamera.walk(speed * DTime);
			}
			if(joy_state.rgbButtons[1]&0x80)
			{
				speed += numberofasteroids;
				TheCamera.walk(-1 * speed * DTime);
			}
			if(joy_state.rgbButtons[5]&0x80)
			{
				speed += numberofasteroids;
				TheCamera.strafe(speed * DTime);
			}
			if(joy_state.rgbButtons[4]&0x80)
			{
				speed += numberofasteroids;
				TheCamera.strafe(-1 * speed * DTime);
			}

		}

		//
		// Render
		//

		D3DXMATRIX planetendmat, planetstartmat;
		D3DXMATRIX *mAsteroids;
		D3DXMATRIX *mSpaceship;
		mSpaceship = new D3DXMATRIX[9];
		mAsteroids = new D3DXMATRIX[numberofasteroids];
		for(int i = 0; i < numberofasteroids; i++)
		{
			vAsteroids[i] += sAsteroids[i];
			if ( vAsteroids[i].x >= 1000 || vAsteroids[i].x <= -1000)
			{
				sAsteroids[i].x *= -1;
			}
			if ( vAsteroids[i].y >= 1000 || vAsteroids[i].y <= -1000)
			{
				sAsteroids[i].y *= -1;
			}
			if ( vAsteroids[i].z >= 10000 || vAsteroids[i].z <= 0)
			{
				sAsteroids[i].z *= -1;
			}
			D3DXMatrixTranslation(&mAsteroids[i], vAsteroids[i].x, vAsteroids[i].y, vAsteroids[i].z);
		}

		//TheCamera.getPosition(&p);
		vSpaceship[0].x = p.x;
		vSpaceship[0].y = p.y - 1.5;
		vSpaceship[0].z = p.z + 2.5;
		vSpaceship[1].x = p.x;
		vSpaceship[1].y = p.y;
		vSpaceship[1].z = p.z - 2.5;
		vSpaceship[2].x = p.x;
		vSpaceship[2].y = p.y + 2.5;
		vSpaceship[2].z = p.z;
		vSpaceship[3].x = p.x;
		vSpaceship[3].y = p.y - 2.5;
		vSpaceship[3].z = p.z;
		vSpaceship[4].x = p.x + 2.5;
		vSpaceship[4].y = p.y;
		vSpaceship[4].z = p.z;
		vSpaceship[5].x = p.x - 2.5;
		vSpaceship[5].y = p.y;
		vSpaceship[5].z = p.z;
			vSpaceship[6].x = p.x + 1;
	vSpaceship[6].y = p.y - .6;
	vSpaceship[6].z = p.z + 2.5;

	vSpaceship[7].x = p.x - 1;
	vSpaceship[7].y = p.y - .6;
	vSpaceship[7].z = p.z + 2.5;

		for(int i = 0; i < 8; i++)
		{
			D3DXMatrixTranslation(&mSpaceship[i], vSpaceship[i].x, vSpaceship[i].y, vSpaceship[i].z);
		}


		D3DXMatrixTranslation(&planetendmat,vEndPlanet.x,vEndPlanet.y,vEndPlanet.z);
		D3DXMatrixTranslation(&planetstartmat,0, 0, -101);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000, 1.0f, 0);
		Device->BeginScene();
		Device->SetMaterial(&mtrl4);
		Device->SetTransform(D3DTS_WORLD, &planetendmat);
		EndPlanet->DrawSubset(0);
		Device->Present(0,0,0,0);
		Device->SetMaterial(&mtrl3);
		Device->SetTransform(D3DTS_WORLD, &planetstartmat);
		StartPlanet->DrawSubset(0);
		Device->Present(0,0,0,0);

		for(int i = 0; i < numberofasteroids; i++)
		{
			Device->SetMaterial(&mtrlAsteroids[i]);
			Device->SetTransform(D3DTS_WORLD, &mAsteroids[i]);
			pAsteroids[i]->DrawSubset(0);
			Device->Present(0, 0, 0, 0);
		}
		Device->SetMaterial(&mtrl9);
		for(int i = 0; i < 6; i++)
		{
			Device->SetTransform(D3DTS_WORLD, &mSpaceship[i]);
			Spaceship[i]->DrawSubset(0);
			Device->Present(0, 0, 0, 0);
		}
		Device->SetMaterial(&mtrl3);
		Device->SetTransform(D3DTS_WORLD, &mSpaceship[6]);
		Spaceship[6]->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
				Device->SetMaterial(&mtrl2);
		Device->SetTransform(D3DTS_WORLD, &mSpaceship[7]);
		Spaceship[7]->DrawSubset(0);
		Device->Present(0, 0, 0, 0);


		D3DXMATRIX V, T;
		TheCamera.getViewMatrix(&V);
		TheCamera.getPosition(&p);

		Device->SetTransform(D3DTS_VIEW, &V);





		Collides(p);

		DisplayTime(seconds);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}

	seconds += (GetTickCount() - dwLastTick) / 1000.0;
	dwLastTick = GetTickCount();


	while((GetTickCount() - starttime) < (1000 / 30))
	{
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
	main_instance = hinstance;

	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	::MessageBox(0, "Reach the Blue planet in the shorest time possible", "Instructions", 0);
	int answer = MessageBox(0, "Abort = Keyboard\nRetry = Mouse\nIgnore = Joystick (may have issues - theoretically should work, but nothing happens when trying to test)", "Choose Input", MB_ABORTRETRYIGNORE);	
	if (answer == IDABORT)
	{
		bkey = true;
		::MessageBox(0, " QWEASD for pitch/roll/yaw \n Up/Down/Left/Right/Pgup/Pgdn for Movement \n space for break", "Instructions", 0);
	}
	if (answer == IDRETRY)
	{
		::MessageBox(0, "Left click to go forward\nRight click to go backwards.\nMiddle click and mouse button 4 (page back usually) for strafing", "Instructions", 0);
		bmouse = true;
	}
	if (answer == IDIGNORE)
	{
		::MessageBox(0, "YMMV but it should be:\nLeft Joystick is pitch/yaw, A and B to go forward and backward respectively\nLeft and Right Bumber to strafe their respective directions", "Instructions", 0);
		bjoy = true;
	}

	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}

