#ifndef XFILE_H
#define XFILE_H
#include "d3dx9.h"
#include "d3dUtility.h"

#include <vector>

class XFile
{
private:
	IDirect3DDevice9* m_pdevice;
	ID3DXBuffer* adjBuffer;
	std::vector<D3DMATERIAL9>m_Materials;
	std::vector<IDirect3DTexture9*>m_Textures;

public:
	XFile();
	~XFile();
	void init(IDirect3DDevice9* device, LPCSTR pFilename);
	void Draw(IDirect3DTexture9 *TEX);
	ID3DXMesh* m_pMesh;
};
#endif