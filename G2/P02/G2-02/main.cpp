#include "base.h"
/*****************************************************************************
//ADJUST ALL SPEED HERE
******************************************************************************/

float DTime = 0.0015f;
//
// Globals
//

IDirect3DDevice9* Device = 0;

Camera TheCamera(Camera::AIRCRAFT);

const int Width  = 900;
const int Height = 600;

D3DXVECTOR3 p;
D3DXVECTOR3 t;

ID3DXMesh* roomMesh;
ID3DXMesh* ceilingMesh;
ID3DXMesh* bedFrameMesh;		//1
ID3DXMesh* bedMattressMesh;		//2
ID3DXMesh* bedPillow1Mesh;		//3
ID3DXMesh* floorMesh;			//4
ID3DXMesh* basketBallMesh;		//5
ID3DXMesh* baseBallMesh;		//6
ID3DXMesh* toyBoxMesh;			//7
ID3DXMesh* toyBoxLidMesh;		//8
ID3DXMesh* lightBulbMesh;		//9
ID3DXMesh* windowMesh;			//10
ID3DXMesh* buildingBlock1Mesh;	//13
ID3DXMesh* buildingBlock2Mesh;	//14
ID3DXMesh* buildingBlock3Mesh;	//15


D3DMATERIAL9 mtrlWhite = d3d::WHITE_MTRL;
D3DMATERIAL9 mtrlBlack = d3d::BLACK_MTRL;
D3DMATERIAL9 mtrlRed = d3d::RED_MTRL;
D3DMATERIAL9 mtrlGreen = d3d::GREEN_MTRL;
D3DMATERIAL9 mtrlBlue = d3d::BLUE_MTRL;
D3DMATERIAL9 mtrlYellow = d3d::YELLOW_MTRL;
D3DMATERIAL9 mtrlCyan = d3d::CYAN_MTRL;
D3DMATERIAL9 mtrlMagenta = d3d::MAGENTA_MTRL;
D3DMATERIAL9 mtrlMe = d3d::ME_MTRL;
D3DMATERIAL9 mtrlWood = d3d::WOOD_MTRL;
D3DMATERIAL9 mtrlLightBulb = d3d::LIGHTBULB_MTRL;
D3DMATERIAL9 mtrlBasketball = d3d::BASKETBALL_MTRL;
D3DMATERIAL9 mtrlWallpaper = d3d::WALLPAPER_MTRL;
D3DMATERIAL9 mtrlPeru = d3d::PERU_MTRL;

D3DXMATRIX ceilingMatrix, bedFrameMatrix, bedMattressMatrix, bedPillow1Matrix, floorMatrix, 
	basketBallMatrix, baseBallMatrix, toyBoxMatrix, toyBoxLidMatrix, lightBulbMatrix,
	windowMatrix, moonMatrix, clockMatrix, buildingBlock1Matrix, buildingBlock2Matrix,
	buildingBlock3Matrix, blahblah, bb2, bb3;

D3DXMATRIX World;


//
// Framework functions
//
bool Setup()
{
	D3DXCOLOR c = d3d::LIGHTBULB;
	D3DXVECTOR3 pos(0.0f, 33.0, 0.0f);
	D3DLIGHT9 LightBulb = d3d::InitPointLight(&c, &pos);

	Device->SetLight(0, &LightBulb);
	Device->LightEnable(0, true);

	D3DXCreateBox(Device, 100, 70, 120, &roomMesh, 0);
	D3DXCreateBox(Device, 100, 1, 120, &floorMesh, 0);
	D3DXMatrixTranslation(&floorMatrix, 0, -34, 0);
	D3DXCreateBox(Device, 100, 1, 120, &ceilingMesh, 0);
	D3DXMatrixTranslation(&ceilingMatrix, 0, 34, 0);
	D3DXCreateBox(Device, 65, 20, 35, &bedFrameMesh, 0);
	D3DXMatrixTranslation(&bedFrameMatrix, -17.499, -24.999, 42.499);
	D3DXCreateBox(Device, 62.5, 10, 32.5, &bedMattressMesh, 0);
	D3DXMatrixTranslation(&bedMattressMatrix, -17.249, -9.999, 42.249);
	D3DXCreateBox(Device, 18.333, 3, 27.5, &bedPillow1Mesh, 0);
	D3DXMatrixTranslation(&bedPillow1Matrix, -39.249, -3.599, 42.249);
	D3DXCreateSphere(Device, 3.9625, 180, 180, &basketBallMesh, 0);
	D3DXMatrixTranslation(&basketBallMatrix, 45, -29.6, 0);
	D3DXCreateSphere(Device, 1.432, 180, 180, &baseBallMesh, 0);
	D3DXMatrixTranslation(&baseBallMatrix, 42, -32.1, 5);
	D3DXCreateBox(Device, 10, 7.7, 20, &toyBoxMesh, 0);
	D3DXMatrixTranslation(&toyBoxMatrix, -44, -29.999, -20);
	D3DXCreateBox(Device, 11, 1.7, 21, &toyBoxLidMesh, 0);
	D3DXMatrixTranslation(&toyBoxLidMatrix, -44, -25.999, -20);
	D3DXCreateSphere(Device, .9, 180, 180, &lightBulbMesh, 0);
	D3DXMatrixTranslation(&lightBulbMatrix, 0, 33, 0);
	D3DXCreateBox(Device, 30, 45, 1, &windowMesh, 0);
	D3DXMatrixTranslation(&windowMatrix, 0, 0, -59);
	D3DXCreateBox(Device, 1.458, 1.458, 1.458, &buildingBlock1Mesh, 0);
	D3DXMatrixTranslation(&buildingBlock1Matrix, 0, -32.8, -55);
	D3DXCreateBox(Device, 1.458, 1.458, 1.458, &buildingBlock2Mesh, 0);
	D3DXMatrixTranslation(&buildingBlock2Matrix, 0, -31.3, -55.5);
	D3DXMatrixRotationY(&bb2, 32);
	buildingBlock2Matrix = bb2 * buildingBlock2Matrix;
	D3DXCreateBox(Device, 1.458, 1.458, 1.458, &buildingBlock3Mesh, 0);
	D3DXMatrixTranslation(&buildingBlock3Matrix, 0, -29.8, -56);
	D3DXMatrixRotationY(&bb3, 75);
	buildingBlock3Matrix = bb3 * buildingBlock3Matrix;

	D3DXMatrixTranslation(&World, 0.0f, 0.0f, 0.0f);

	//D3DXVECTOR3 camStart(0.0f, 15.0f, 0.0f);
	//TheCamera.setPosition(&camStart);
	//
	// Set camera.
	//

	//D3DXVECTOR3 pos(0.0f, 1.5f, -15.3f);
	//D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	//D3DXMATRIX V;
	//D3DXMatrixLookAtLH(&V, &pos, &target, &up);

	//Device->SetTransform(D3DTS_VIEW, &V);
	//
	// Set projection matrix.
	//
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.25f, // 45 - degree
			(float)Width / (float)Height,
			0.01f,
			1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	//Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255,255,255));

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return true;
}

void Cleanup()
{
	

}

bool Display()
{


	if( Device )
	{
		

		//
		//Update: Update the camera
		//
		if(::GetAsyncKeyState('W') & 0x8000f)
			TheCamera.walk(1.0 * DTime);
		if(::GetAsyncKeyState('S') & 0x8000f)
			TheCamera.walk(-1.0 * DTime);
		if(::GetAsyncKeyState('A') & 0x8000f)
			TheCamera.strafe(-1.0 * DTime);
		if(::GetAsyncKeyState('D') & 0x8000f)
			TheCamera.strafe(1.0 * DTime);
		if(::GetAsyncKeyState('F') & 0x8000f)
			TheCamera.fly(-1.0 * DTime);
		if(::GetAsyncKeyState('R') & 0x8000f)
			TheCamera.fly(1.0 * DTime);

		if(::GetAsyncKeyState(VK_UP) & 0x8000f)
			TheCamera.pitch(-.20 * DTime);
		if(::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			TheCamera.pitch(.20 * DTime);
		if(::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			TheCamera.yaw(-.20 * DTime);
		if(::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			TheCamera.yaw(.20 * DTime);
		if(::GetAsyncKeyState(VK_HOME) & 0x8000f)
			TheCamera.roll(.20 * DTime);
		if(::GetAsyncKeyState(VK_END) & 0x8000f)
			TheCamera.roll(-.20 * DTime);
		
		//
		// Render
		//
		D3DXMatrixTranslation(&blahblah, 0,0,0);
		Device->SetMaterial(&mtrlWallpaper);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();
		roomMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlPeru);
		Device->SetTransform(D3DTS_WORLD, &floorMatrix);
		floorMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlWhite);
		Device->SetTransform(D3DTS_WORLD, &ceilingMatrix);
		ceilingMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlWood);
		Device->SetTransform(D3DTS_WORLD, &bedFrameMatrix);
		bedFrameMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlBlue);
		Device->SetTransform(D3DTS_WORLD, &bedMattressMatrix);
		bedMattressMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlCyan);
		Device->SetTransform(D3DTS_WORLD, &bedPillow1Matrix);
		bedPillow1Mesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlBasketball);
		Device->SetTransform(D3DTS_WORLD, &basketBallMatrix);
		basketBallMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlWhite);
		Device->SetTransform(D3DTS_WORLD, &baseBallMatrix);
		baseBallMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlRed);
		Device->SetTransform(D3DTS_WORLD, &toyBoxMatrix);
		toyBoxMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlMagenta);
		Device->SetTransform(D3DTS_WORLD, &toyBoxLidMatrix);
		toyBoxLidMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlLightBulb);
		Device->SetTransform(D3DTS_WORLD, &lightBulbMatrix);
		lightBulbMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlBlack);
		Device->SetTransform(D3DTS_WORLD, &windowMatrix);
		windowMesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlWood);
		Device->SetTransform(D3DTS_WORLD, &buildingBlock1Matrix);
		buildingBlock1Mesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlCyan);
		Device->SetTransform(D3DTS_WORLD, &buildingBlock2Matrix);
		buildingBlock2Mesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);
		Device->SetMaterial(&mtrlYellow);
		Device->SetTransform(D3DTS_WORLD, &buildingBlock3Matrix);
		buildingBlock3Mesh->DrawSubset(0);
		Device->Present(0, 0, 0, 0);

		Device->SetTransform(D3DTS_WORLD, &blahblah);
		Device->Present(0,0,0,0);
		D3DXMATRIX V, T;
		TheCamera.getViewMatrix(&V);
		Device->SetTransform(D3DTS_VIEW, &V);
		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}

	return true;
}

//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	::MessageBox(0, "\nW - Move Forward\n S - Move Backward\n A - Strafe Left\n D - Strafe Right\n R - Move Up\n F - Move Down\n Up Arrow Key - Look Up\n Down Arrow Key - Look Down\n Left Arrow Key - Turn Left\n Right Arrow Key - Turn Right", "Instructions", 0);
	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}

