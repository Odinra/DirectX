#include "base.h"

bool d3d::InitD3D(HINSTANCE hInstance, int width, int height, bool windowed, D3DDEVTYPE deviceType,
	IDirect3DDevice9** device)
{

	WNDCLASS winclass;
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = (WNDPROC)d3d::WndProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hInstance;
	winclass.hIcon = LoadIcon(0, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(0, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject
		(WHITE_BRUSH);
	winclass.lpszMenuName =  0;
	winclass.lpszClassName = "Direct3D";

	if(!RegisterClass(&winclass))
	{
		::MessageBoxA(0, "RegisterClass() - Failed", 0, 0);
		return false;
	}

	HWND hwnd;

	hwnd = ::CreateWindow("Direct3D", "This is a 3D Window", WS_EX_TOPMOST, 0, 0, width, height, 0, 0, hInstance, 0);
	
	if (!hwnd)
	{
		::MessageBoxA(0, "Create Window() - Failed", 0,0);
		return false;
	}

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	//Init D3D
	HRESULT hResult = 0;
	//Step 1: Create the IDirect3D9 object
	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if(!d3d9)
	{
		::MessageBoxA(0, "Direct3DCentral9() - FAILED", 0, 0);
		return false;
	}

	//Step 2: Check for Hardware Vertex Processing

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);
	int vp = 0;
	if(caps.DevCaps &D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//Step 3: Fill out d3d structure

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = windowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//Step 4: Create device

	hResult = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd, vp, &d3dpp, device);

	if(FAILED(hResult))
	{
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hResult = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd, vp, &d3dpp, device);
		if (FAILED(hResult))
		{
			d3d9->Release();
			::MessageBoxA(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release();

	return true;
}

void d3d::Game_Main(void *parms=NULL)
{
	//do main game proccessing here
}


int d3d::EnterMsgLoop(bool(*ptr_display)())
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if(::PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageA(&msg);
		}
		else
		{
			ptr_display();
		}
		Game_Main();
	}

	return msg.wParam;
}