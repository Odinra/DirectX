//////////////////////////////////////////////////////////////////////////////////////////
////////
//
// File: camera.h
//
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0
//
// Desc: Defines a camera's position and orientation.
//
//////////////////////////////////////////////////////////////////////////////////////////
////////

// START OF HEADER
#ifndef __cameraH__
#define __cameraH__
#include <d3dx9.h>

// Definition of camera class
class Camera
{
	// public functions and variables
public:
	enum CameraType { LANDOBJECT, AIRCRAFT }; // Enumerated data type to define what kind of camera is being used
	Camera(); // Camera class constructor
	Camera(CameraType cameraType); // Overloaded camera class constructor that include parameter for enumerated data type that defines camera type
	~Camera(); // Camera class destructor
	void strafe(float units); // left/right
	void fly(float units); // up/down
	void walk(float units); // forward/backward
	void pitch(float angle); // rotate on right vector
	void yaw(float angle); // rotate on up vector
	void racingYaw(float angle, float units);
	void roll(float angle); // rotate on look vector
	void getViewMatrix(D3DXMATRIX* V); // Function that will return a Direct3D matrix of the camera's current viewing matrix
	void setCameraType(CameraType cameraType); // Function for setting the camera type (In case that you need to change camera type after it is set in constructor)
	void getPosition(D3DXVECTOR3* pos); // A function that will return a Direct3D 3d vector of the camera's current position
	void setPosition(D3DXVECTOR3* pos); // A function that allows the user to enter a D3DX 3d vector to set the camera's position
	void getRight(D3DXVECTOR3* right); // A function that allows the user to enter a D3DX 3d vector to change the camera's right vector
	void getUp(D3DXVECTOR3* up); // A function that allows the user to enter a D3DX 3d vector to change the camera's up vector
	void getLook(D3DXVECTOR3* look); // A function that allows the user to enter a D3DX 3d vector to change the camera's look vector
	D3DXVECTOR3 _up; // A D3DX 3d vector that holds the up vector

	
/*private:*/ // private functions and variables
	CameraType _cameraType; // Enumerated data type that holds the current camera type
	D3DXVECTOR3 _right; // A D3DX 3d vector that holds the right vector
	D3DXVECTOR3 _look; // A D3DX 3d vector that holds the look vector
	D3DXVECTOR3 _pos; // A D3DX 3d vector that holds the position vector
};

class Opponent
{
public:
	Opponent(); 
	~Opponent();
	void walk(float units);
	void racingYaw(float angle, float units);
		void getPosition(D3DXVECTOR3* pos); // A function that will return a Direct3D 3d vector of the camera's current position
	void setPosition(D3DXVECTOR3* pos); // A function that allows the user to enter a D3DX 3d vector to set the camera's position
	void getLook(D3DXVECTOR3* look); // A function that allows the user to enter a D3DX 3d vector to change the camera's look vector

	D3DXVECTOR3 _up; // A D3DX 3d vector that holds the up vector

	D3DXVECTOR3 _right; // A D3DX 3d vector that holds the right vector
	D3DXVECTOR3 _look; // A D3DX 3d vector that holds the look vector
	D3DXVECTOR3 _pos; // A D3DX 3d vector that holds the position vector
};
#endif // __cameraH__

// END OF HEADER