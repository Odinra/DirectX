#include "base.h"
//Global
#include <iostream>
#include <Windows.h>

IDirect3DDevice9* Device = 0;

const int Width = 800;
const int Height = 600;

bool byRot = true, bxRot = true, bzRot = true;

int red = 90, green = 120, blue = 85;
D3DXCOLOR CK(D3DCOLOR_XRGB(red, green, blue));


ID3DXMesh* Text = 0;

DWORD starttime = 0;

RECT rect;

bool Setup()
{
	HDC hdc = CreateCompatibleDC(0);
	HFONT hFont;
	HFONT hFontOld;

	LOGFONT lf;

	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 20;

	lf.lfWidth = 12;

	lf.lfWeight = 500;

	lf.lfCharSet = DEFAULT_CHARSET;

	strcpy_s(lf.lfFaceName, "Comic Sans MS");

	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);

	D3DXCreateText(Device, hdc, "Christopher King", 0.0001f, 0.4f, &Text, 0,0);

	

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
		// position and aim the camera
	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);

	Device->SetTransform(D3DTS_VIEW, &V);

	// set projection matrix
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH( &proj, D3DX_PI * 0.5f, (float)Width / (float)Height, 1.0f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	// set the render states
	Device->SetRenderState(D3DRS_FILLMODE, 5);

	return true;
}

void Cleanup()
{
	d3d::Release<ID3DXMesh*>(Text);


}

bool Display()
{
	if(Device)
	{
		CK = D3DCOLOR_XRGB(red, green, blue);
		D3DXMATRIX yRot, xRot, zRot, T;
		static float y = 0.0f, x = 0.0f, z = 0.0f;
		
		D3DXMatrixTranslation(&T, -1.6f, 0.0f, 0.0f);
		
		if (byRot)
		{
			y += .0001;

			if ( y >= 6.28)
				y = 0.0f;

			D3DXMatrixRotationY(&yRot, y);

			T  *= yRot;
		}

		if (bxRot)
		{
			x += .0001;

			if ( x >= 6.28)
				x = 0.0f;

			D3DXMatrixRotationX(&xRot, x);

			T  *= xRot;
		}

		if (bzRot)
		{
			z += .0001;

			if ( z >= 6.28)
				z = 0.0f;

			D3DXMatrixRotationZ(&zRot, z);

			T  *= zRot;
		}




		Device ->SetTransform(D3DTS_WORLD, &T);

		Device->Clear(0,0,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();
		Device->SetMaterial(&d3d::InitMtrl(CK, CK, CK, CK, 5.0f));
		Text->DrawSubset(0);
		Device->EndScene();
		Device->Present(0,0,0,0);
	}
	
	return true;
}

//WndProc
LRESULT CALLBACK d3d::WndProc(HWND hwnd,
	UINT msg, WPARAM wparam, LPARAM lparam)
{

	switch(msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
			::DestroyWindow(hwnd);
		switch(wparam)
		{
		case 'X':
			if(bxRot) bxRot = false;
			else bxRot = true;
			break;
		case 'Y':
			if(byRot) byRot = false;
			else byRot = true;
			break;
		case 'Z':
			if(bzRot) bzRot = false;
			else bzRot = true;
			break;
		case 'R':
			red++;
			if (red >= 255)
				red = 0;
			break;
		case 'G':
			green++;
			if (green >= 255)
				green = 0;
			break;
		case 'B':
			blue++;
			if (blue >= 255)
				blue = 0;
			break;
		case 'T':
			red--;
			if (red <= 0)
				red = 255;
			break;
		case 'H':
			green--;
			if (green <= 0)
				green = 255;
			break;
		case 'N':
			blue--;
			if (blue <= 0)
				blue = 255;
			break;
		default: break;
		}
		break;
	}
	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}
//WinMain

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevInstance, PSTR cmdLine, int showCmd)
{
	if (!d3d::InitD3D(hinstance, Width, Height, true, 
		D3DDEVTYPE_HAL, &Device))
	{
		::MessageBoxA(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if(!Setup())
	{
		::MessageBoxA(0, "SetupD3D() - FAILED", 0, 0);
		return 0;
	}

	    MessageBox(NULL,"Z X and Y to turn on/off the rotation for that angle\nR G and B to increase the color intensities\nT H and N to decrease the color intensities", "Font Practicing stuffs", MB_ICONEXCLAMATION | MB_OK);
	
	d3d::EnterMsgLoop(Display);
	Cleanup();
	Device->Release();
	return 0;
}