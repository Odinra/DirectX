#include "xFile.h"

XFile::XFile()
{}
XFile::~XFile()
{
	if(m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = 0;
	}
}
void XFile::init(IDirect3DDevice9* device, LPCSTR pFilename)
{
	m_pdevice = device;
	ID3DXBuffer*mtrlBuffer = 0;
	DWORD numMtrls = 0;

	if(FAILED(D3DXLoadMeshFromX(pFilename, D3DXMESH_MANAGED, device, &adjBuffer, &mtrlBuffer, 0, &numMtrls, &m_pMesh)))
	{
		MessageBox(0, "MESH failure", "failure", 0);
	}

	if( mtrlBuffer != 0 && numMtrls != 0 )

	{

		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();


		for(int i = 0; i < numMtrls; i++)

		{

			// the MatD3D property doesn't have an ambient value set

			// when its loaded, so set it now:

			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// save the ith material

			m_Materials.push_back( mtrls[i].MatD3D );

			// check if the ith material has an associative texture

			if( mtrls[i].pTextureFilename != 0 )

			{

				// yes, load the texture for the ith subset

				IDirect3DTexture9* tex = 0;

				D3DXCreateTextureFromFile(

					device,

					mtrls[i].pTextureFilename,

					&tex);

				// save the loaded texture

				m_Textures.push_back( tex );

			}

			else

			{

				// no texture for the ith subset

				m_Textures.push_back( 0 );

			}

		}

	}

	d3d::Release<ID3DXBuffer*>(mtrlBuffer); // done w/ buffer

	if(FAILED(m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT| D3DXMESHOPT_VERTEXCACHE, (DWORD*)adjBuffer->GetBufferPointer(), 0, 0, 0)))
	{
		::MessageBox(0, "Opt Failed", 0, 0);
	}

	d3d::Release<ID3DXBuffer*>(adjBuffer);
}

void XFile::Draw(IDirect3DTexture9 *TEX)
{
	for(int i = 0; i < m_Materials.size(); i++)
	{
		m_pdevice->SetMaterial(&m_Materials[i]);
		if(m_Textures.size() >= 1)
			m_pdevice->SetTexture(0,m_Textures[i]);
		else
			m_pdevice->SetTexture(0,TEX);
		m_pMesh->DrawSubset(i);
	}
}
