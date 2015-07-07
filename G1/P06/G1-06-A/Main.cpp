#include "base.h"

IDirect3DDevice9* Device = 0;

const int win_x = 800;
const int win_y = 600;


IDirect3DVertexBuffer9* CubeVB = 0;
IDirect3DIndexBuffer9* CubeIB = 0;
IDirect3DVertexBuffer9* CubeVB2 = 0;
IDirect3DIndexBuffer9* CubeIB2 = 0;

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
	Device->CreateVertexBuffer(8 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &CubeVB, 0);

	Device->CreateIndexBuffer(36 * sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&CubeIB,0);

	Device->CreateVertexBuffer(8 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &CubeVB2, 0);

	Device->CreateIndexBuffer(36 * sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&CubeIB2,0);

	Vertex* vertices;
	CubeVB->Lock(0,0,(void**)&vertices, 0);

	vertices[0] = Vertex(-1.0f, -1.0f, -1.0f);
	vertices[1] = Vertex(-1.0f, 1.0f, -1.0f);
	vertices[2] = Vertex( 1.0f, 1.0f, -1.0f);
	vertices[3] = Vertex( 1.0f, -1.0f, -1.0f);
	vertices[4] = Vertex(-1.0f, -1.0f, 1.0f);
	vertices[5] = Vertex(-1.0f, 1.0f, 1.0f);
	vertices[6] = Vertex( 1.0f, 1.0f, 1.0f);
	vertices[7] = Vertex( 1.0f, -1.0f, 1.0f);

	CubeVB->Unlock();

	Vertex* vertices2;
	CubeVB2->Lock(0,0,(void**)&vertices2, 0);

	vertices2[0] = Vertex( 1.0f, -0.5f, -0.5f);
	vertices2[1] = Vertex( 1.0f, 0.5f, -0.5f);
	vertices2[2] = Vertex( 2.0f, 0.5f, -0.5f);
	vertices2[3] = Vertex( 2.0f, -0.5f, -0.5f);
	vertices2[4] = Vertex( 1.0f, -0.5f, 0.5f);
	vertices2[5] = Vertex( 1.0f, 0.5f, 0.5f);
	vertices2[6] = Vertex( 2.0f, 0.5f, 0.5f);
	vertices2[7] = Vertex( 2.0f, -0.5f, 0.5f);

	CubeVB2->Unlock();

	WORD* indices = 0;
	CubeIB->Lock(0,0,(void**)&indices, 0);

	// front side
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	// back side
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;
	// left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;
	// right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;
	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	CubeIB->Unlock();

		WORD* indices2 = 0;
	CubeIB2->Lock(0,0,(void**)&indices2, 0);

	// front side
	indices2[0] = 0; indices2[1] = 1; indices2[2] = 2;
	indices2[3] = 0; indices2[4] = 2; indices2[5] = 3;
	// back side
	indices2[6] = 4; indices2[7] = 6; indices2[8] = 5;
	indices2[9] = 4; indices2[10] = 7; indices2[11] = 6;
	// left side
	indices2[12] = 4; indices2[13] = 5; indices2[14] = 1;
	indices2[15] = 4; indices2[16] = 1; indices2[17] = 0;
	// right side
	indices2[18] = 3; indices2[19] = 2; indices2[20] = 6;
	indices2[21] = 3; indices2[22] = 6; indices2[23] = 7;
	// top
	indices2[24] = 1; indices2[25] = 5; indices2[26] = 6;
	indices2[27] = 1; indices2[28] = 6; indices2[29] = 2;

	// bottom
	indices2[30] = 4; indices2[31] = 0; indices2[32] = 3;
	indices2[33] = 4; indices2[34] = 3; indices2[35] = 7;

	CubeIB2->Unlock();

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

	d3d::Release<IDirect3DVertexBuffer9*>(CubeVB);
	d3d::Release<IDirect3DIndexBuffer9*>(CubeIB);
		d3d::Release<IDirect3DVertexBuffer9*>(CubeVB2);
	d3d::Release<IDirect3DIndexBuffer9*>(CubeIB2);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		//
		// spin the cube:
		//
		D3DXMATRIX Rx, Ry, Rz;
		// rotate 45 degrees on x-axis
		D3DXMatrixRotationX(&Rx, 3.14f / 4.0f);

		D3DXMatrixRotationY(&Ry, 3.14f / 4.0f);
		D3DXMatrixRotationZ(&Rz, 3.14f / 4.0f);

		D3DXMATRIX p =Ry * Rx  * Rz;
		Device->SetTransform(D3DTS_WORLD, &p);
		//
		// draw the scene:
		//
		Device->Clear(0, 0,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			0xffffffff, 1.0f, 0);
		Device->BeginScene();
		Device->SetStreamSource(0, CubeVB, 0, sizeof(Vertex));
		Device->SetIndices(CubeIB);
		Device->SetFVF(Vertex::FVF);
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0, 0, 8, 0, 12);

				Device->SetStreamSource(0, CubeVB2, 0, sizeof(Vertex));
		Device->SetIndices(CubeIB2);
		Device->SetFVF(Vertex::FVF);
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0, 0, 8, 0, 12);
		Device->EndScene();
		Device->Present(0, 0, 0, 0);
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