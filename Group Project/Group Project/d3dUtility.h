#ifndef __d3dUtilityH__
#define __d3dUtilityH__

#include <d3dx9.h>
#include <string>
#include "CSocket.h"
#include "camera.h"
#include <cstdlib>
#include <ctime>
#include "DINPUT.H"
#include <xact3.h>
#include "audio.h"
#include "vertex.h"
#include "cube.h"
#include "xFile.h"
#include <time.h>
#include "fpuMath.h"
#include "Input.H"
#include "Terrain.h"
#include "Skybox.h"
#include <list>
#include <assert.h>
#include "LoadXFile.h"
#include "SaveXFile.h"
#include <stdio.h>


#define BUT_HighScore	1005
#define BOX_HighScore	2004

extern high_score_return scoreDataReturn[6];

// Direct3D namespace to hold functions and processes considered necessary for Direct3D window creation and functionality.
namespace d3d
{
	// Function for intializing Direct3D with parameters that include a handle to the instance, the dimensions of the window, a boolean for determining if
	// the window will be fullscreened or windowed, a Direct3D device type that determines if the device is a Hardware Abstract Layer device or a Reference
	// rasterizer device, and a double pointer to the Direct3D device.
	bool InitD3D(
		HINSTANCE hInstance,       // [in] Application instance.
		int width, int height,     // [in] Backbuffer dimensions.
		bool windowed,             // [in] Windowed (true)or full screen (false).
		D3DDEVTYPE deviceType,     // [in] HAL or REF
		IDirect3DDevice9** device);// [out]The created device.

	// A function that allows the program to enter into the main loop which keeps the window open until the user ends the loop or an error occurs
	// The parameter that is included is timeDelta which keeps an elasped time.
	int EnterMsgLoop( 
		bool (*ptr_display)(float timeDelta));

	// A handle result callback function named WndProc, short for Window Process, which includes parameters for the handle to the window, a window message,
	// a word parameter(which means it is a 16-bit value), and a long parameter(32-bit value). This function is where Window Messages will be handled and
	// appropriately filtered to the proper case (If using a switch statement).
	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam, // Useful for sending handles and integers
		LPARAM lParam); // If sending pointers
	
	// A function for releasing any class templates that are currently being used.

	// Use of the class template is so that the program can easily release any resources being used without having to create seperate functions for
	// each Direct3D variable being used.
	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}

	
		
	// A function for deleting any class templates that have just been released and are no longer needed

	// This function is generally used upon exiting the program when resources have been released and are no longer needed and need to be deleted.

	// The use of a template class is similar to the release function in that it allows the program to delete any Direct3D resource without needing a
	// seperate function for each resource.
	template<class T> void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}

	//
	//COLORS
	//
	
	// Direct3D color prototyping for ease of use later on in the program. This bank is created so that color resources are stored and available for use
	// and so that the main functions are not cluttered up with resource creation.
	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(200, 200, 200) ); // White color
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) ); // Black color
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) ); // Red color
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) ); // Green color
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  7,   0, 255) ); // Blue color
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) ); // Yellow color
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) ); // Cyan color
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) ); // Magenta color
	const D3DXCOLOR		ORANGE( D3DCOLOR_XRGB(255, 106,   0) ); // Orange color

	const D3DXCOLOR BEACH_SAND( D3DCOLOR_XRGB(255, 249, 157) );
	const D3DXCOLOR DESERT_SAND( D3DCOLOR_XRGB(250, 205, 135) );

	const D3DXCOLOR LIGHTGREEN( D3DCOLOR_XRGB( 60, 184, 120) );
	const D3DXCOLOR  PUREGREEN( D3DCOLOR_XRGB(  0, 166,  81) );
	const D3DXCOLOR  DARKGREEN( D3DCOLOR_XRGB(  0, 114,  54) );

	const D3DXCOLOR LIGHT_YELLOW_GREEN( D3DCOLOR_XRGB(124, 197, 118) );
	const D3DXCOLOR  PURE_YELLOW_GREEN( D3DCOLOR_XRGB( 57, 181,  74) );
	const D3DXCOLOR  DARK_YELLOW_GREEN( D3DCOLOR_XRGB( 25, 123,  48) );

	const D3DXCOLOR LIGHTBROWN(D3DCOLOR_XRGB(198, 156, 109));
	const D3DXCOLOR DARKBROWN( D3DCOLOR_XRGB(115, 100,  87));

	////
	//// Materials
	////

	// Function for initializing a Direct3D material based on the color parameters that are passed to it.
	// 
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, // Ambient color
		D3DXCOLOR d, // Diffuse color
		D3DXCOLOR s, // Specular color
		D3DXCOLOR e, // Emissive color
		float p); // Floating point value for power of light values on the object to affect the change of color

	
	// Direct3D Material Prototype Bank
	// This bank is created so that we can avoid having to clutter up the main functions with resource creation for the materials and also for ease of use.
	const D3DMATERIAL9 WHITE_MTRL	= InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f); // White material
	const D3DMATERIAL9 RED_MTRL		= InitMtrl(RED, RED, RED, BLACK, 2.0f); // Red material
	const D3DMATERIAL9 GREEN_MTRL	= InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f); // Green material
	const D3DMATERIAL9 BLUE_MTRL	= InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f); // Blue material
	const D3DMATERIAL9 CYAN_MTRL	= InitMtrl(CYAN, CYAN, CYAN, BLACK, 2.0f); // Cyan material
	const D3DMATERIAL9 YELLOW_MTRL	= InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f); // Yellow material
	const D3DMATERIAL9 ORANGE_MTRL	= InitMtrl(ORANGE,ORANGE,ORANGE, BLACK, 2.0f); // Orange material
	const D3DMATERIAL9 BLACK_MTRL	= InitMtrl(BLACK,BLACK,BLACK, BLACK, 2.0f); // Black material


	//
	// Lights
	//

	// Function prototypes for creating the three different lights that are available for use in Direct3D

	// Directional light is a light source that has only direction and a color and no position. This type of light is parallel and is used to mimic light
	// objects that can be at a long distance away, like the sun. Directional lights are not affected by attentuation or range, so they do not decay over large
	// distances

	// This function intializes Direct3D light variable as a directional light that takes a D3D 3d vector for the direction of the light, and a D3D color
	// variable
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);

	// A point light is a light source that that has position and color but no particular direction as they emit an equal amount of light in all directions.
	// A good example of a point light would be an open lightbulb that radiates light equally in all directions, or almost in all directions by real life
	// standards. Point lights do decay over distance as they are effected by attentuation and range, so at long distances point lights will become dimmer.

	// Initializes a D3D light variable as a point light that takes a D3D 3d vector for the position, and a D3D color variable
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);

	// A spotlight is a light source that includes position, direction, and color as they emanate from a specific position and illuminate any objects that
	// they are currently pointed at. Spotlights are effected by attentuation and range, so spotlights stronger at the middle and gradually decrease in
	// illumination as it reaches the edges until there is no more light on any particular object. The magnitude of a spotlight is usually classified by
	// the theta angle of the light, which is the where the strongest portion of light will be, and the phi, which is the whole angle of light and by
	// calculating the phi minus the theta, the outer circle of spotlight can be known and determined as the weaker portion of the light.

	// Initializes a D3D light variable as a spotlight which takes parameters for a D3D 3d vector the position, a D3D 3d vector the direction, and D3D color
	// variable
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);

	// Drawing

	// Function references "sand.bmp" and "water,bmp" internally.  This file must
	// be in the working directory.
	bool DrawBasicScene(
		IDirect3DDevice9* device,// Pass in 0 for cleanup.
		float scale);            // uniform scale 

	//
	// Bounding Objects
	//

	struct BoundingBox
	{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);

		D3DXVECTOR3 _min;
		D3DXVECTOR3 _max;
	};

	struct BoundingSphere
	{
		BoundingSphere();

		D3DXVECTOR3 _center;
		float       _radius;
	};

	//
	// Constants
	//

	const float INFINITY = FLT_MAX;
	const float EPSILON  = 0.001f;

	//
	// Drawing
	//

	// Function references "desert.bmp" internally.  This file must
	// be in the working directory.

	// Vertex Structures

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

	
	//
	// Randomness
	//

	// Desc: Return random float in [lowBound, highBound] interval.
	float GetRandomFloat(float lowBound, float highBound);
	

	// Desc: Returns a random vector in the bounds specified by min and max.
	void GetRandomVector(
		D3DXVECTOR3* out,
		D3DXVECTOR3* min,
		D3DXVECTOR3* max);

	//
	// Conversion
	//
	DWORD FtoDw(float f);

	//
	// Interpolation
	//

	float Lerp(float a, float b, float t);

}

#endif // __d3dUtilityH__
// END OF HEADER