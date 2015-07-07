#include "Input.H"

BOOL CALLBACK DI_Enum_Joysticks(LPCDIDEVICEINSTANCE lpddi, LPVOID guid_ptr)
{
	// this function enumerates the joysticks, but
	// stops at the first one and returns the
	// instance guid of it, so we can create it
	*(GUID*)guid_ptr = lpddi->guidInstance;
	char joyname[80]; // name of joystick
	// copy name into global
	strcpy(joyname, (char *)lpddi->tszProductName);

	// stop enumeration after one iteration
	return(DIENUM_STOP);

} // end DI_Enum_Joysticks

bool input::SetupInput(HINSTANCE input_instance, HWND main_hwnd)
{
	joyConnected = true;
	lpDI = NULL;
	lpDIKey = NULL;
	lpDIMouse = NULL;
	deviceType = D3DDEVTYPE_HAL;
	lpDIJS = NULL;
	//Check for DI Device

	if(FAILED(DirectInput8Create(input_instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&lpDI, NULL)))
	{
		return false;
	}

	if(FAILED(lpDI->CreateDevice(GUID_SysKeyboard, &lpDIKey, NULL)))
	{
		return false;
	}

	if(FAILED(lpDIKey->SetCooperativeLevel(main_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return false;
	}

	if(FAILED(lpDIKey->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}

	if(FAILED(lpDIKey->Acquire()))
	{
		return false;
	}

	// Check for Mouse

	if(FAILED(lpDI->CreateDevice(GUID_SysMouse, &lpDIMouse, NULL)))
	{
		return false;
	}

	if(FAILED(lpDIMouse->SetCooperativeLevel(main_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return false;
	}

	if(FAILED(lpDIMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return false;
	}

	if(FAILED(lpDIMouse->Acquire()))
	{
		return false;
	}

	// Joystick


	// Direct Input 8 - J O Y S T I C K goes in Setup function
	// first find the GUID of your particular joystick
	lpDI->EnumDevices(DI8DEVCLASS_GAMECTRL, DI_Enum_Joysticks, &joystickGUID, DIEDFL_ATTACHEDONLY);
	if (FAILED(lpDI->CreateDevice(joystickGUID, &lpDIJS, NULL)))
	{
		joyConnected = false;
	}
	if(joyConnected)
	{
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

	return true;
}

void input::CleanUpInput()
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
	if(joyConnected)
	{
		if (lpDIJS)
			lpDIJS->Unacquire();
		if (lpDIJS)
			lpDIJS->Release();
	}
	if(lpDI)
		lpDI->Release();
}

bool input::KeyUpdate()
{
	HRESULT hresult;
	hresult = lpDIKey->GetDeviceState(256, (LPVOID)keyboard_state);
	if(hresult == DIERR_INPUTLOST)
	{
		if(FAILED(lpDIKey->Acquire()))
		{
			return false;
		}
	}

	return true;
}
bool input::MouseUpdate()
{
	// Creating result to hold mouse state result

	HRESULT hresult2;

	hresult2 = lpDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID) &mouse_state);

	if(hresult2 == DIERR_INPUTLOST)
	{
		if(FAILED(lpDIMouse->Acquire()))
		{
			return false;
		}
	}

	return true;
}

void input::JoyUpdate()
{
	if(joyConnected)
	{
	lpDIJS->Poll(); // this is needed for joysticks only
	lpDIJS->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID)&joy_state);
	}
}

bool input::KeyTest(int KEY)
{
	if(keyboard_state[KEY]&0x080)
		return true;
	else
		return false;
}

bool input::MouseKeyTest(int KEY)
{
	if(mouse_state.rgbButtons[KEY]&0x80)
		return true;
	else
		return false;
}

long input::MouseXTest(){return mouse_state.lX;}
long input::MouseYTest(){return mouse_state.lY;}
long input::MouseZTest(){return mouse_state.lZ;}

bool input::JoyKeyTest(int KEY)
{
	if(joyConnected)
	{
	if(joy_state.rgbButtons[KEY]&0x80)
		return true;
	else
		return false;
	}
	return false;
}

long input::JoylXTest(){if(joyConnected)return joy_state.lX;return 0;}
long input::JoylYTest(){if(joyConnected)return joy_state.lY;return 0;}
long input::JoylZTest(){if(joyConnected)return joy_state.lZ;return 32767;}
long input::JoyrXTest(){if(joyConnected)return joy_state.lRx;return 0;}
long input::JoyrYTest(){if(joyConnected)return joy_state.lRy;return 0;}
long input::JoyrZTest(){if(joyConnected)return joy_state.lRz;return 0;}
long input::JoyrglSliderTest(int KEY){if(joyConnected)return joy_state.rglSlider[KEY];return 0;}
DWORD input::JoyrgdwPOVTest(int key){if(joyConnected)return joy_state.rgdwPOV[key];return 0;}