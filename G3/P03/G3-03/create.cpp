#include "base.h"
//#include "main.h"

D3DXMATRIX World;

bool d3d::DrawBasicScene(IDirect3DDevice9* device, float scale)
{
	static IDirect3DVertexBuffer9* floor		= 0;
	static IDirect3DVertexBuffer9* wwall		= 0;
	static IDirect3DVertexBuffer9* nwall		= 0;
	static IDirect3DVertexBuffer9* swall		= 0;
	static IDirect3DVertexBuffer9* ewall		= 0;
	static IDirect3DVertexBuffer9* roof			= 0;
	static IDirect3DVertexBuffer9* mirror1		= 0;
	static IDirect3DVertexBuffer9* mirror2		= 0;
	static IDirect3DVertexBuffer9* mirror3		= 0;
	static IDirect3DVertexBuffer9* door			= 0;
	static IDirect3DTexture9*      tex			= 0;
	static IDirect3DTexture9*      wtex1		= 0;
	static IDirect3DTexture9*      rtex1		= 0;
	static IDirect3DTexture9*      mtex			= 0;
	static IDirect3DTexture9*      dtex			= 0;

	HRESULT hr = 0;

	if( device == 0 )
	{
		if( floor && tex && wtex1 && wwall && ewall && nwall && swall)
		{
			// they already exist, destroy them
			d3d::Release<IDirect3DVertexBuffer9*>(floor);
			d3d::Release<IDirect3DVertexBuffer9*>(wwall);
			d3d::Release<IDirect3DVertexBuffer9*>(ewall);
			d3d::Release<IDirect3DVertexBuffer9*>(nwall);
			d3d::Release<IDirect3DVertexBuffer9*>(swall);
			d3d::Release<IDirect3DVertexBuffer9*>(roof);
			d3d::Release<IDirect3DTexture9*>(tex);
			d3d::Release<IDirect3DTexture9*>(wtex1);
			d3d::Release<IDirect3DTexture9*>(rtex1);
		}
	}
	else if( !floor && !tex && !wtex1 && !wwall && !ewall && !nwall && !swall && !roof)
	{
		//FLOOR
-		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex), 0, d3d::Vertex::FVF, D3DPOOL_MANAGED, &floor, 0);

		Vertex* v = 0;
		floor->Lock(0, 0, (void**)&v, 0);

		v[0] = Vertex(-20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[1] = Vertex(-20.0f, -2.5f,  30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Vertex( 20.0f, -2.5f,  30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v[3] = Vertex(-20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[4] = Vertex( 20.0f, -2.5f,  30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v[5] = Vertex( 20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		floor->Unlock();

		D3DXCreateTextureFromFile(
			device,
			"floor.png",
			&tex);

		//WEST WALL
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&wwall,0);

		Vertex* v1 = 0;
		wwall->Lock(0, 0, (void**)&v1, 0);

		v1[0] = Vertex(-20.0f,  20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v1[1] = Vertex(-20.0f, 20.0f,  30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v1[2] = Vertex( -20.0f, -2.5f,  30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v1[3] = Vertex(-20.0f, 20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v1[4] = Vertex( -20.0f, -2.5f,  30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v1[5] = Vertex( -20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		wwall->Unlock();

		//EAST WALL
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&ewall,0);

		Vertex* v2 = 0;
		ewall->Lock(0, 0, (void**)&v2, 0);
		v2[0] = Vertex(20.0f,  20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v2[1] = Vertex(20.0f, 20.0f,  -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v2[2] = Vertex( 20.0f, -2.5f,  -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v2[3] = Vertex(20.0f, 20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v2[4] = Vertex( 20.0f, -2.5f,  -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v2[5] = Vertex( 20.0f, -2.5f, 30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		ewall->Unlock();

		//SOUTH WALL
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&swall,0);

		Vertex* v3 = 0;
		swall->Lock(0, 0, (void**)&v3, 0);
		v3[0] = Vertex(20.0f,  20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v3[1] = Vertex(-20.0f, 20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v3[2] = Vertex(-20.0f, -2.5f,  -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v3[3] = Vertex(20.0f, 20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v3[4] = Vertex(-20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v3[5] = Vertex(20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
		swall->Unlock();

		//NORTH WALL
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&nwall,0);

		Vertex* v4 = 0;
		nwall->Lock(0, 0, (void**)&v4, 0);

		v4[0] = Vertex(-20.0f,  20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v4[1] = Vertex(20.0f, 20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v4[2] = Vertex(20.0f, -2.5f,  30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v4[3] = Vertex(-20.0f, 20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v4[4] = Vertex(20.0f, -2.5f, 30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v4[5] = Vertex(-20.0f, -2.5f, 30.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		nwall->Unlock();

		D3DXCreateTextureFromFile(
			device,
			"walls.png",
			&wtex1);

		//mirror 1
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&mirror1,0);

		Vertex* v6 = 0;
		mirror1->Lock(0, 0, (void**)&v6, 0);

		v6[0] = Vertex(-5.0f,  5.0f, 18.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v6[1] = Vertex(5.0f, 5.0f, 18.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v6[2] = Vertex(5.0f, -2.5f,  18.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v6[3] = Vertex(-5.0f, 5.0f, 18.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v6[4] = Vertex(5.0f, -2.5f, 18.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v6[5] = Vertex(-5.0f, -2.5f, 18.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		mirror1->Unlock();

		D3DXCreateTextureFromFile(device,"mirror.png",&mtex);

		//mirror 2
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&mirror2,0);

		Vertex* v7 = 0;
		mirror2->Lock(0, 0, (void**)&v7, 0);

		v7[0] = Vertex(18.0f,  5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v7[1] = Vertex(18.0f, 5.0f,  -5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v7[2] = Vertex(18.0f, -2.5f,  -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v7[3] = Vertex(18.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v7[4] = Vertex(18.0f, -2.5f,  -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v7[5] = Vertex(18.0f, -2.5f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		mirror2->Unlock();

		D3DXCreateTextureFromFile(device,"mirror.png",&mtex);

		//mirror 3
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&mirror3,0);

		Vertex* v8 = 0;
		mirror3->Lock(0, 0, (void**)&v8, 0);

		v8[0] = Vertex(-18.0f,  5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v8[1] = Vertex(-18.0f, 5.0f,  5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v8[2] = Vertex(-18.0f, -2.5f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v8[3] = Vertex(-18.0f, 5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v8[4] = Vertex(-18.0f, -2.5f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v8[5] = Vertex(-18.0f, -2.5f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		mirror3->Unlock();

		D3DXCreateTextureFromFile(device,"mirror.png",&mtex);

		//door
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&door,0);

		Vertex* v9 = 0;
		door->Lock(0, 0, (void**)&v9, 0);

		v9[0] = Vertex(5.0f,  8.0f, -19.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v9[1] = Vertex(0.0f, 8.0f, -19.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v9[2] = Vertex(0.0f, -2.5f, -19.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v9[3] = Vertex(5.0f, 8.0f, -19.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v9[4] = Vertex(0.0f, -2.5f, -19.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v9[5] = Vertex(5.0f, -2.5f, -19.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		door->Unlock();

		D3DXCreateTextureFromFile(device,"door.png",&dtex);

		// roof
		device->CreateVertexBuffer(6 * sizeof(d3d::Vertex),0, d3d::Vertex::FVF,D3DPOOL_MANAGED,&roof,0);

		Vertex* v5 = 0;
		roof->Lock(0, 0, (void**)&v5, 0);

		v5[0] = Vertex(-20.0f, 20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v5[2] = Vertex( 20.0f, 20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v5[1] = Vertex( 20.0f, 20.0f, -20.0f,0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v5[3] = Vertex(-20.0f, 20.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v5[4] = Vertex(-20.0f, 20.0f, -20.0f,0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
		v5[5] = Vertex( 20.0f, 20.0f, -20.0f,0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		roof->Unlock();

		D3DXCreateTextureFromFile(device,"floor.png",&rtex1);
	}

	else
	{
		// Pre-Render Setup
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		//Lights

		D3DXCOLOR c = d3d::WHITE;
		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
		D3DLIGHT9 Spot = d3d::InitSpotLight(&pos, &dir, &c);
		device->SetLight(0, &Spot);

		D3DXVECTOR3 pos1(0.0f, 34.0f, 0.0f);
		D3DLIGHT9 light1 = d3d::InitPointLight(&pos1, &c);

		device->SetLight(0, &light1);

		
		device->LightEnable(0, true);
		device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		device->SetRenderState(D3DRS_SPECULARENABLE, true);

		// Render
		D3DXMATRIX T, R, P, S;
		D3DXMatrixScaling(&S, scale, scale, scale);

		// draw floor
		D3DXMatrixIdentity(&T);
		T = T * S;
		device->SetTransform(D3DTS_WORLD, &T);
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, tex);
		device->SetStreamSource(0, floor, 0, sizeof(Vertex));
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//draw west wall
		device->SetStreamSource(0, wwall, 0, sizeof(Vertex));
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, wtex1);
		D3DXMatrixTranslation(&World, 0.0f, -2.0f, 0.0f);
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//draw east wall
		device->SetStreamSource(0, ewall, 0, sizeof(Vertex));
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, wtex1);
		D3DXMatrixTranslation(&World, 0.0f, -2.0f, 0.0f);
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//draw north wall
		device->SetStreamSource(0, nwall, 0, sizeof(Vertex));
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, wtex1);
		D3DXMatrixTranslation(&World, 0.0f, -2.0f, 0.0f);
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//draw south wall
		device->SetStreamSource(0, swall, 0, sizeof(Vertex));
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, wtex1);
		D3DXMatrixTranslation(&World, 0.0f, -2.0f, 0.0f);
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//draw door
		device->SetStreamSource(0, door, 0, sizeof(Vertex));
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, dtex);
		D3DXMatrixTranslation(&World, 0.0f, -2.0f, 0.0f);
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//draw roof
		device->SetStreamSource(0, roof, 0, sizeof(Vertex));
		device->SetMaterial(&d3d::WHITE_MTRL);
		device->SetTexture(0, rtex1);
		D3DXMatrixTranslation(&World, 0.0f, -2.0f, 0.0f);
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	}
		
	return true;
}
