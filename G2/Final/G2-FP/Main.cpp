#include "d3dUtility.h"
#include <vector>
/*****************************************************************************
//ADJUST ALL SPEED HERE
******************************************************************************/
float DTime = 0.180f;

XFile Knight;

extern EvilCastle* Ecastle;
extern GoodCastle* Gcastle;
extern EvilKnight* EKnight[20];
extern EvilMage* EMage[20];
extern EvilPeon* EPeon[20];
extern GoodKnight* GKnight[20];
extern GoodMage* GMage[20];
extern GoodPeon* GPeon[20];
COMPUTERAI cAI;

D3DXVECTOR3 KnightPos(0,0,0);

D3DXMATRIX MatrixProj;
unsigned currtime, lasttime;
int GP = 70;

//
// Globals
//
HWND mainHWND;
bool pause;
Audio sound;
PCSTR Song = "Song";
IDirect3DDevice9* Device = 0;

XFile KNIGHT;

int x = GetSystemMetrics(SM_CXSCREEN);
int y = GetSystemMetrics(SM_CYSCREEN);
const int Width  = x;
const int Height = y;

D3DMATERIAL9 Mtrls[10];

D3DXVECTOR3 camStart(0.0f, 8.5f, -400.0f);

Cube* Box;

IDirect3DTexture9* TexBackGround = 0,* Armor = 0;

Camera TheCamera(Camera::LANDOBJECT);

IDirect3DVertexBuffer9* VBuffer = 0;

D3DXVECTOR3 p;
D3DXVECTOR3 t;
DWORD timeelapsed;/*, currtime, lasttime;*/
//creates instance of light
D3DXVECTOR3 dir(1.0f, 0.0f, 0.0f);
D3DXCOLOR c = d3d::WHITE;
D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);

unsigned peonCurrent, peonLast, mageCurrent, mageLast, knightCurrent, KnightLast;

ID3DXFont *m_font;

// Creating an instance for the input device
HINSTANCE input_instance = NULL;
// Main window handle
HWND main_hwnd = 0;

// Direct Input 8
// Setting up the device for Direct Input, the keyboard, and the mouse
LPDIRECTINPUT8 lpDI = NULL;
LPDIRECTINPUTDEVICE8 lpDIKey = NULL;

// Keyboard state
UCHAR keyboard_state[256];

LPDIRECTINPUTDEVICE8 lpDIMouse = NULL;
// Direct Input state for the mouse
DIMOUSESTATE mouse_state;

// Setting Direct3D Device type
D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;

// Direct Input 8 – Joystick - GOES UP TOP WITH ALL YOUR OTHER
//GLOBALS
LPDIRECTINPUTDEVICE8 lpDIJS = NULL;
GUID joystickGUID; // guid for main joystick
char joyname[80]; // name of joystick
DIJOYSTATE joy_state; // contains state of joystick

bool keyboard= true, mouse = true, joystick;

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

void DisplayMoney()
{

    // Create a colour for the text - in this case white
    D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 128, 25);   

    // Create a rectangle to indicate where on the screen it should be drawn
    RECT rect;
    rect.left=2;
    rect.right=85;
    rect.top=10;
    rect.bottom=rect.top+20;
    char buffers[10];
	sprintf(buffers, "GP: %d", GP);
	
    // Draw some text
    m_font->DrawText(NULL, buffers, 50, &rect, 0, fontColor );
}

bool Setup()
{
	KNIGHT.init(Device, "KX2.X");
	currtime = lasttime = time(0);
	D3DXCreateFont(Device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );

	//Check for DI Device

	if(FAILED(DirectInput8Create(input_instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&lpDI, NULL)))
	{
		return(0);
	}

	// Check for Keyboard
	if(keyboard)
	{
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
	if(mouse)
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
	if(joystick)
	{
	// Joystick

	
	// Direct Input 8 - J O Y S T I C K goes in Setup function
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


	// acquire the joystick
	if (FAILED(lpDIJS->Acquire()))
	{
		return(0);
	}
	}
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
	Device->CreateVertexBuffer(42 * sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF_VERTEX, D3DPOOL_MANAGED, &VBuffer, 0);

	Vertex* VGround;
	VBuffer->Lock(0, 0, (void**)&VGround, 0);

	peonCurrent = peonLast = mageCurrent = mageLast = knightCurrent = KnightLast = time(0);

	//
	//North
	//
	VGround[0] = Vertex(-1500.0f, -500.0f, 05.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[1] = Vertex(-1500.0f,  500.0f, 05.0f, 0.0f, 0.0f, -1.0f,   0.0f,   0.0f);
	VGround[2] = Vertex( 1500.0f,  500.0f, 05.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[3] = Vertex(-1500.0f, -500.0f, 05.0f, 0.0f, 0.0f, -1.0f,   0.0f, 1.0f);
	VGround[4] = Vertex( 1500.0f,  500.0f, 05.0f, 0.0f, 0.0f, -1.0f, 1.0f,   0.0f);
	VGround[5] = Vertex( 1500.0f, -500.0f, 05.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	
	//sheets
	VGround[6]  = Vertex(-1, 0, 0, 0, 0, -1, 0, 1);
	VGround[7]  = Vertex(-1, 2, 0, 0, 0, -1, 0, 0);
	VGround[8]  = Vertex( 1, 2, 0, 0, 0, -1, 1, 0);
	VGround[9]  = Vertex(-1, 0, 0, 0, 0, -1, 0, 1);
	VGround[10] = Vertex( 1, 2, 0, 0, 0, -1, 1, 0);
	VGround[11] = Vertex( 1, 0, 0, 0, 0, -1, 1, 1);

	VBuffer->Unlock();	
	
	Ecastle = new EvilCastle(Device);
	Gcastle = new GoodCastle(Device);
	for (int i = 0; i < 20; i++)
	{
		EMage[i] = new EvilMage(Device);
		GMage[i] = new GoodMage(Device);
		EKnight[i] = new EvilKnight(Device);
		GKnight[i] = new GoodKnight(Device);
		EPeon[i] = new EvilPeon(Device);
		GPeon[i] = new GoodPeon(Device);
	}

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
	D3DXCreateTextureFromFile(Device, "BackGround.png", &TexBackGround);
	D3DXCreateTextureFromFile(Device, "Armor.jpg", &Armor);
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
		// Cleaning up direct input devices
	if(lpDIMouse)
		lpDIMouse->Unacquire();
	if(lpDIMouse)
		lpDIMouse->Release();

	if(lpDIKey)
		lpDIKey->Unacquire();
	if(lpDIKey)
		lpDIKey->Release();

	//if (lpDIJS)
	//	lpDIJS->Unacquire();
	//if (lpDIJS)
	//	lpDIJS->Release();

	if(lpDI)
		lpDI->Release();	
}
bool bbreak = false;
bool Display(float timeDelta)
{
	if( Device )
	{
		peonCurrent = knightCurrent = mageCurrent = time(0);
		currtime = time(0);
		if (keyboard == true)
		{
			// creating result to hold keyboard state result

			HRESULT hresult;
			hresult = lpDIKey->GetDeviceState(256, (LPVOID)keyboard_state);
			if(hresult == DIERR_INPUTLOST)
			{
				if(FAILED(lpDIKey->Acquire()))
				{
					return 0;
				}
			}

			// Update the camera based on keyboard state
			if(keyboard_state[DIK_P]&0x80)
				pause = true;
			if(keyboard_state[DIK_LEFTARROW]&0x80)
				TheCamera.strafe(-1.0 * DTime);
			if(keyboard_state[DIK_RIGHTARROW]&0x80)
				TheCamera.strafe(1.0 * DTime);

			if(keyboard_state[DIK_1]&0x80)
				if(GP >= GPeon[0]->cost && peonCurrent - peonLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GPeon[i]->inPlay)
						{
							GP -= GPeon[0]->cost;
							bbreak = true;
							peonLast = peonCurrent;
							GPeon[i]->PutInPlay();
						}
						i++;
					}while( i < 20 && !bbreak);
				}
			if(keyboard_state[DIK_2]&0x80)
				if(GP >= GKnight[0]->cost && knightCurrent- KnightLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GKnight[i]->inPlay)
						{
							GP -= GKnight[0]->cost;
							bbreak = true;
							KnightLast = knightCurrent;
							GKnight[i]->PutInPlay();
						}
						i++;
					}while( i < 20 && !bbreak);
				}
			if(keyboard_state[DIK_3]&0x80)
				if(GP >= GMage[0]->cost && mageCurrent- mageLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GMage[i]->inPlay)
						{
								GP -= GMage[0]->cost;
								bbreak = true;
								mageLast = mageCurrent;
								GMage[i]->PutInPlay();
							}
							i++;
						}while( i < 20 && !bbreak);
					}
		}

		if (mouse == true)
		{

			// Creating result to hold mouse state result

			HRESULT hresult2;

			hresult2 = lpDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID) &mouse_state);

			if(hresult2 == DIERR_INPUTLOST)
			{
				if(FAILED(lpDIMouse->Acquire()))
				{
					return 0;
				}
			}

			// Update the camera based on mouse state

			if(mouse_state.rgbButtons[0]&0x80)
				if(GP >= GPeon[0]->cost && peonCurrent - peonLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GPeon[i]->inPlay)
						{
							GP -= GPeon[0]->cost;
							bbreak = true;
							peonLast = peonCurrent;
							GPeon[i]->PutInPlay(); 
						}
						i++;
					}while( i < 20 && !bbreak);
				}

			if(mouse_state.rgbButtons[1]&0x80)
				if(GP >= GKnight[0]->cost && knightCurrent- KnightLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GKnight[i]->inPlay)
						{
							GP -= GKnight[0]->cost;
							bbreak = true;
							KnightLast = knightCurrent;
							GKnight[i]->PutInPlay();
						}
						i++;
					}while( i < 20 && !bbreak);
				}

			if(mouse_state.rgbButtons[2]&0x80)
				if(GP >= GMage[0]->cost && mageCurrent- mageLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GMage[i]->inPlay)
						{
								GP -= GMage[0]->cost;
								bbreak = true;
								mageLast = mageCurrent;
								GMage[i]->PutInPlay();
							}
							i++;
						}while( i < 20 && !bbreak);
					}

			if(mouse_state.lX)
			{
				TheCamera.strafe(mouse_state.lX * DTime);
			}
		}
		if(joystick == true)
		{
			lpDIJS->Poll(); // this is needed for joysticks only
			lpDIJS->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID)&joy_state);

			// Update the camera based on joystick state

			if(joy_state.lX)
			{
				TheCamera.strafe(joy_state.lX * DTime *.1);
			}

			if(joy_state.rgbButtons[0]&0x80)
				if(GP >= GPeon[0]->cost && peonCurrent - peonLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GPeon[i]->inPlay)
						{
							GP -= GPeon[0]->cost;
							bbreak = true;
							peonLast = peonCurrent;
							GPeon[i]->PutInPlay();
						}
						i++;
					}while( i < 20 && !bbreak);
				}
			if(joy_state.rgbButtons[1]&0x80)
				if(GP >= GKnight[0]->cost && knightCurrent- KnightLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GKnight[i]->inPlay)
						{
							GP -= GKnight[0]->cost;
							bbreak = true;
							KnightLast = knightCurrent;
							GKnight[i]->PutInPlay();
						}
						i++;
					}while( i < 20 && !bbreak);
				}
			if(joy_state.rgbButtons[2]&0x80)
				if(GP >= GKnight[0]->cost && knightCurrent- KnightLast >= 1)
				{
					bbreak = false;
					int i = 0;
					do
					{
						if(!GKnight[i]->inPlay)
						{
							GP -= GKnight[0]->cost;
							bbreak = true;
							KnightLast = knightCurrent;
							GKnight[i]->PutInPlay();
						}
						i++;
					}while( i < 20 && !bbreak);
				}
		}
		Device->SetRenderState(D3DRS_LIGHTING, false);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
		Device->BeginScene();
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		D3DXMATRIX i, tripler, grow;
		D3DXMatrixIdentity(&i);
		Device->SetTransform(D3DTS_WORLD, &i);
		D3DXMatrixIdentity(&i);
		Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
		Device->SetFVF(FVF_VERTEX);
		Device->SetTexture(0, TexBackGround);
		Device->SetTransform(D3DTS_WORLD, &i);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//1
		Device->SetTexture(0, Armor);
		D3DXMatrixTranslation(&tripler, 0,0,-10);
		D3DXMatrixScaling(&grow, .5,.5,.5);
		D3DXMatrixMultiply(&tripler, &grow, &tripler);
		Device->SetTransform(D3DTS_WORLD, &tripler);
		KNIGHT.Draw();
		
		Ecastle->Update();
		Gcastle->Update();
		cAI.upDate();
		for(int i = 0; i < 20; i++)
		{
			GKnight[i]->Update();
			GPeon[i]->Update();
			GMage[i]->Update();
			EMage[i]->Update();
			EKnight[i]->Update();
			EPeon[i]->Update();
		}
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3DXMATRIX V, T;
		TheCamera.getViewMatrix(&V);
		Device->SetTransform(D3DTS_VIEW, &V);
		TheCamera.getPosition(&p);
		if (p.y != 8.5)
			p.y = 8.5;
		if(p.x < -925)
			p.x = -925;
		if(p.x > 925)
			p.x = 925;
		TheCamera.setPosition(&p);
		TheCamera.getLook(&t);
		if(currtime - lasttime > 1)
		{

			GP++;
			cAI.gold++;
			lasttime = currtime;
			if(currtime % 20 == 0)
			{
				GP += 25;
				cAI.gold += 50;
			}
			if(currtime % 100 == 0)
			{
				GP += 100;
				cAI.gold += 100;
			}
		}
		DisplayMoney();
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
	//::MessageBoxA(0, "There are Several textures that need to be loaded, this could take some time", "Loading", MB_OK);
	input_instance = hinstance;
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
		int answer = MessageBox(0, "Abort = Keyboard\nRetry = Mouse\nIgnore = Joystick (may have issues - theoretically should work, but nothing happens when trying to test)", "Choose Input", MB_ABORTRETRYIGNORE);	
	if (answer == IDABORT)
	{
		keyboard = true;
		::MessageBox(0, "Left Right move move the camera\n1 for peon\n2 for knight\n3 for mage", "Instructions", 0);
	}
	if (answer == IDRETRY)
	{
		::MessageBox(0, "Left click for Peon\nRight click for Knight.\nMiddle click for Mage", "Instructions", 0);
		mouse = true;
	}
	if (answer == IDIGNORE)
	{
		::MessageBox(0, "YMMV but it should be:\nLeft Joystick is move left/right, A for peons and B for knights and x for Mages", "Instructions", 0);
		joystick = true;
	}
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}
	sound.AudioPlay(Song);
	::MessageBoxA(0, "The Objective of the game is to attack and destroy the Evil Castle, while not letting your castle be destroyed\nPress 1 to Spawn a Peon 5GP(weak but faster)\nPress 2 to spawn a Knight 25GP(medium speed and Medium attacks)\nPress 3 to spawn a Mage 100GP(slow speed but massive damage)\nUse the left and right arrow keys", "Welcome", MB_OK);
	d3d::EnterMsgLoop( Display );
	Cleanup();
	Device->Release();
	return 0;
}