#include "base.h"

IDirect3DDevice9* Device = 0;

const int win_x = 800;
const int win_y = 600;



IDirect3DVertexBuffer9* SphereVB = 0;
IDirect3DIndexBuffer9* SphereIB = 0;

IDirect3DVertexBuffer9* CylinderVB = 0;
IDirect3DIndexBuffer9* CylinderIB = 0;

IDirect3DVertexBuffer9* TorusVB = 0;
IDirect3DIndexBuffer9* TorusIB = 0;

IDirect3DVertexBuffer9* CubeVB = 0;
IDirect3DIndexBuffer9* CubeIB = 0;

DWORD starttime = 0;

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z)
	{_x = x; _y = y; _z = z;}

	float _x, _y, _z;
	
	static const DWORD FVF;
};
const DWORD Vertex::FVF = D3DFVF_XYZ;

bool Setup()
{
	Device->CreateVertexBuffer(3 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &SphereVB, 0);
	Device->CreateVertexBuffer(3 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &CylinderVB, 0);
	Device->CreateVertexBuffer(3 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &TorusVB, 0);
	Device->CreateVertexBuffer(3 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &CubeVB, 0);

	Device->CreateIndexBuffer(36 * sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&SphereIB,0);
	Device->CreateIndexBuffer(36 * sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&CylinderIB,0);
	Device->CreateIndexBuffer(36 * sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&TorusIB,0);
	Device->CreateIndexBuffer(36 * sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&CubeIB,0);


	// position and aim the camera
	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);

	Device->SetTransform(D3DTS_VIEW, &V);

	// set projection matrix
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH( &proj, D3DX_PI * 0.5f, (float)win_x / (float)win_y, 1.0f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	// set the render states
	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return true;
}

void Cleanup()
{
d3d::Release<IDirect3DVertexBuffer9*>(SphereVB);
d3d::Release<IDirect3DIndexBuffer9*>(SphereIB);
d3d::Release<IDirect3DVertexBuffer9*>(CylinderVB);
d3d::Release<IDirect3DIndexBuffer9*>(CylinderIB);
d3d::Release<IDirect3DVertexBuffer9*>(TorusVB);
d3d::Release<IDirect3DIndexBuffer9*>(TorusIB);
d3d::Release<IDirect3DVertexBuffer9*>(CubeVB);
d3d::Release<IDirect3DIndexBuffer9*>(CubeIB);
}

bool Display(float timeDelta)
{
	if(Device)
	{
		D3DXMATRIX CubeRx, CubeRy, CubeTr, CylinderTr, SphereTr, TorusTr;

		ID3DXMesh* Sphere = 0;
		ID3DXMesh* Cylinder = 0;
		ID3DXMesh* Torus = 0;
		ID3DXMesh* Cube = 0;

		D3DXCreateBox(Device, 1, 1, 1, &Cube, NULL);

		D3DXCreateCylinder(Device, 1, 1, 2, 45, 45, &Cylinder,NULL);
		D3DXCreateSphere(Device, 1, 45,45,&Sphere, NULL);
		D3DXCreateTorus(Device, .5, 1, 45,45,&Torus, NULL);

		D3DXMatrixRotationZ(&CubeRx, 3.14f / 4.0f);
		
		D3DXMatrixTranslation(&CubeTr, -1,-1,-1);
		
		static float cubey = 0.0f;
		D3DXMatrixRotationZ(&CubeRy, cubey);
		cubey += timeDelta;

		if(cubey >= 6.28f)
			cubey = 0.0f;

		D3DXMATRIX Cubep = CubeRx * CubeRy * CubeTr;
		Device->Clear(0,0,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
		Device->SetTransform(D3DTS_WORLD, &Cubep);

		Device->Clear(0,0,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

		Device->BeginScene();
		Cube->DrawSubset(0);
		//Device->EndScene();
		Device->Present(0,0,0,0);
		Cube->Release();
		Cube = 0;

		D3DXMatrixTranslation(&CylinderTr, 1.5,1.5,1.5);


		D3DXMATRIX Cylinderp =	(CubeRy * .5) *  CylinderTr;	
		Device->SetTransform(D3DTS_WORLD, &Cylinderp);



		//Device->BeginScene();
		Cylinder->DrawSubset(0);

		Device->Present(0,0,0,0);
		Cylinder->Release();
		Cylinder = 0;
		
		D3DXMatrixTranslation(&SphereTr, -1.5, 1.5, 1.5);


		D3DXMATRIX Spherep =	(CubeRy * 2) *  SphereTr;	
		Device->SetTransform(D3DTS_WORLD, &Spherep);

		Sphere->DrawSubset(0);
		Device->Present(0,0,0,0);
		Sphere->Release();
		Sphere = 0;

		D3DXMatrixTranslation(&TorusTr, 1.5,-1.5, -1.5);

		D3DXMATRIX Torusp =	(CubeRy * 1.5) *  TorusTr;	
		Device->SetTransform(D3DTS_WORLD, &Torusp);

		Torus->DrawSubset(0);
		Device->EndScene();
		Device->Present(0,0,0,0);
		Torus->Release();
		Torus = 0;

		/*Device->SetStreamSource(0,CubeVB, 0, sizeof(Vertex));
		Device->SetIndices(CubeIB);
		Device->SetFVF(Vertex::FVF);*/

		//Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,8,0,12);

	}
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);
		break;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, PSTR cmdLine, int showCmd)
{

	if(!d3d::InitD3D(hinstance, win_x, win_y, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
	}

	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
	}

	d3d::EnterMsgLoop(Display);
	Cleanup();
	Device->Release();
	return 0;
}