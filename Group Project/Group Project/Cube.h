// Cube header file for creating a basic 3d cube in DirectX via use of indices and vertices and also has the ability to allow users
// to add a texture to the cube.

// START OF HEADER
#ifndef __cubeH__
#define __cubeH__

#include <d3dx9.h>
#include <string>

// Cube class definition
class Cube
{
// Public functions and variables
public:
	// Cube class constructor that contains a parameter for the pointer to the Direct3D device
	Cube(IDirect3DDevice9* device);
	// Cube class destructor
	~Cube();

	// Draw function that includes function parameters for a pointer to the D3DX matrix for the world, a pointer to the D3D material being 
	// used, and a pointer to the D3D texture.
	bool draw(D3DXMATRIX* world, D3DMATERIAL9* mtrl, IDirect3DTexture9* tex);

// Private functions and variables
private:
	// Pointer to the D3D device
	IDirect3DDevice9*       _device;
	// Pointer to the D3D vertex buffer
	IDirect3DVertexBuffer9* _vb;
	// Pointer to the D3D index buffer
	IDirect3DIndexBuffer9*  _ib;
};
#endif //__cubeH__
// END OF HEADER