#ifndef INPUT_H_
#define INPUT_H_

#include "DINPUT.H"
#include "d3dUtility.h"

struct input
{
private:
	// Direct Input 8
	// Setting up the device for Direct Input, the keyboard, and the mouse
	LPDIRECTINPUT8 lpDI;
	LPDIRECTINPUTDEVICE8 lpDIKey;

	// Keyboard state
	UCHAR keyboard_state[256];

	LPDIRECTINPUTDEVICE8 lpDIMouse;
	// Direct Input state for the mouse
	DIMOUSESTATE mouse_state;

	// Setting Direct3D Device type
	D3DDEVTYPE deviceType;

	// Direct Input 8 – Joystick - GOES UP TOP WITH ALL YOUR OTHER
	//GLOBALS
	LPDIRECTINPUTDEVICE8 lpDIJS;
	GUID joystickGUID; // guid for main joystick
	char joyname[80]; // name of joystick
	DIJOYSTATE joy_state; // contains state of joystick

	bool joyConnected;
public:

	bool SetupInput(HINSTANCE input_instance, HWND main_hwnd);

	void CleanUpInput();

	bool KeyTest(int);

	bool MouseKeyTest(int);
	long MouseXTest();
	long MouseYTest();
	long MouseZTest();

	bool JoyKeyTest(int);				/* 128 buttons                  */
	long JoylXTest();					/* x-axis position              */
	long JoylYTest();                   /* y-axis position              */
	long JoylZTest();                   /* z-axis position              */
	long JoyrXTest();                   /* x-axis rotation              */
	long JoyrYTest();                   /* y-axis rotation              */
	long JoyrZTest();                   /* z-axis rotation              */
	long JoyrglSliderTest(int);         /* extra axes positions         */
	DWORD JoyrgdwPOVTest(int);          /* POV directions               */
	//long JoylVXTest();                  /* x-axis velocity              */
	//long JoylVYTest();                  /* y-axis velocity              */
	//long JoylVZTest();                  /* z-axis velocity              */
	//long JoylVRxTest();                 /* x-axis angular velocity      */
	//long JoylVRyTest();                 /* y-axis angular velocity      */
	//long JoylVRzTest();                 /* z-axis angular velocity      */
	//long JoyrglVSliderTest(int);        /* extra axes velocities        */
	//long JoylAXTest();                  /* x-axis acceleration          */
	//long JoylAYTest();                  /* y-axis acceleration          */
	//long JoylAZTest();                  /* z-axis acceleration          */
	//long JoylARxTest();                 /* x-axis angular acceleration  */
	//long JoylARyTest();                 /* y-axis angular acceleration  */
	//long JoylARzTest();                 /* z-axis angular acceleration  */
	//long JoyrglASliderTest(int);        /* extra axes accelerations     */
	//long JoylFXTest();                  /* x-axis force                 */
	//long JoylFYTest();                  /* y-axis force                 */
	//long JoylFZTest();                  /* z-axis force                 */
	//long JoylFRxTest();                 /* x-axis torque                */
	//long JoylFRyTest();                 /* y-axis torque                */
	//long JoylFRzTest();                 /* z-axis torque                */
	//long JoyrglFSliderTest(int);		/* extra axes forces            */

	bool KeyUpdate();
	bool MouseUpdate();
	void JoyUpdate();

};
//BOOL CALLBACK DI_Enum_Joysticks(LPCDIDEVICEINSTANCE lpddi, LPVOID guid_ptr);

#endif