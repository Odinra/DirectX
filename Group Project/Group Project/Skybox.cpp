#include "skybox.h"

LPDIRECT3DVERTEXBUFFER9		g_pSkyboxVertexBuffer	= NULL;
LPDIRECT3DTEXTURE9			g_SkyTextures[6];
D3DXMATRIX matWorld, matWorldSave, matView;



TTexVertex g_SkyboxMesh[24] =
{
	// Front quad, NOTE: All quads face inward
	{-5000.0f, -0050.0f,  5000.0f,  0.0f, 1.0f },
	{-5000.0f,  7990.0f,  5000.0f,  0.0f, 0.0f },
	{ 5000.0f, -0050.0f,  5000.0f,  1.0f, 1.0f },
	{ 5000.0f,  7990.0f,  5000.0f,  1.0f, 0.0f },
	
	// Back quad
	{ 5000.0f, -0050.0f, -5000.0f,  0.0f, 1.0f },
	{ 5000.0f,  7990.0f, -5000.0f,  0.0f, 0.0f },
	{-5000.0f, -0050.0f, -5000.0f,  1.0f, 1.0f },
	{-5000.0f,  7990.0f, -5000.0f,  1.0f, 0.0f },
	
	// Left quad
	{-5000.0f, -0050.0f, -5000.0f,  0.0f, 1.0f },
	{-5000.0f,  7990.0f, -5000.0f,  0.0f, 0.0f },
	{-5000.0f, -0050.0f,  5000.0f,  1.0f, 1.0f },
	{-5000.0f,  7990.0f,  5000.0f,  1.0f, 0.0f },
	
	// Right quad
	{ 5000.0f, -0050.0f,  5000.0f,  0.0f, 1.0f },
	{ 5000.0f,  7990.0f,  5000.0f,  0.0f, 0.0f },
	{ 5000.0f, -0050.0f, -5000.0f,  1.0f, 1.0f },
	{ 5000.0f,  7990.0f, -5000.0f,  1.0f, 0.0f },

	// Top quad
	{-5000.0f,  7990.0f,  5000.0f,  0.0f, 1.0f },
	{-5000.0f,  7990.0f, -5000.0f,  0.0f, 0.0f },
	{ 5000.0f,  7990.0f,  5000.0f,  1.0f, 1.0f },
	{ 5000.0f,  7990.0f, -5000.0f,  1.0f, 0.0f },
	
	// //Bottom quad
	{-5000.0f, -0050.0f, -5000.0f,  0.0f, 1.0f },
	{-5000.0f, -0050.0f,  5000.0f,  0.0f, 0.0f },
	{ 5000.0f, -0050.0f, -5000.0f,  1.0f, 1.0f },
	{ 5000.0f, -0050.0f,  5000.0f,  1.0f, 0.0f }
};


bool BuildSkybox(IDirect3DDevice9* Device)
{
	// Why did I use an HRESULT instead of a bool or int?  Well since DirectX is
	// written in COM the typical return values are HRESULTs.
	HRESULT hRet;


	// Create our vertex buffer ( 24 vertices (4 verts * 6 faces) )
    hRet = Device->CreateVertexBuffer( sizeof(TTexVertex) * 24, 0, D3DFVF_XYZ | D3DFVF_TEX1,
                                             D3DPOOL_MANAGED, &g_pSkyboxVertexBuffer, NULL );
    if ( FAILED( hRet ) )
		return false;

	void *pVertices = NULL;

	// Copy the skybox mesh into the vertex buffer.  I initialized the whole mesh array
	// above in global space.
	g_pSkyboxVertexBuffer->Lock( 0, sizeof(TTexVertex) * 24, (void**)&pVertices, 0 );
    memcpy( pVertices, g_SkyboxMesh, sizeof(TTexVertex) * 24 );
    g_pSkyboxVertexBuffer->Unlock();

	// Load Textures.  I created a global array just to keep things simple.  The order of the images
	// is VERY important.  The reason is the skybox mesh (g_SkyboxMesh[]) array was created above
	// in this order. (ie. front, back, left, etc.)
    hRet  = D3DXCreateTextureFromFile( Device, ("Front.jpg") , &g_SkyTextures[0] );
    hRet  = D3DXCreateTextureFromFile( Device, ("Back.jpg")  , &g_SkyTextures[1] );
    hRet = D3DXCreateTextureFromFile( Device, ("Left.jpg")  , &g_SkyTextures[2] );
    hRet = D3DXCreateTextureFromFile( Device, ("Right.jpg") , &g_SkyTextures[3] );
    hRet = D3DXCreateTextureFromFile( Device, ("Up.jpg")   , &g_SkyTextures[4] );
    hRet = D3DXCreateTextureFromFile( Device, ("Ground.jpg"), &g_SkyTextures[5] );
    if ( FAILED(hRet) )
		return false;

	// Set up a projection matrix
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 
			1000 / 800, 0.1f, 100.0f );
    Device->SetTransform( D3DTS_PROJECTION, &matProj );


	// What about the ugly seams inbetween the cube face textures?  Well we need to get rid of them
	// somehow.
    Device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
    Device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );

	////////////////////////////////Susie didn't add this
	////////////////////////////////
    Device->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_COLORVALUE( 1.0f, 1.0f, 1.0f, 1.0f ) );

	// If we get here then we succeeded!
	return true;
}

void renderSkybox(IDirect3DDevice9* Device, Camera camera)
{
	Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, false );
	Device->SetRenderState( D3DRS_LIGHTING, false );

	Device->GetTransform(D3DTS_VIEW, &matWorldSave);
		

	// Render the sky box
	Device->SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );
	Device->SetStreamSource( 0, g_pSkyboxVertexBuffer, 0, sizeof(TTexVertex));
    
	// Set the world matrix to identity for the skybox
	matView = matWorldSave;
	
	matView._41 = 0.0f; matView._42 = 0.0f; matView._43 = 0.0f;
	Device->SetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity( &matWorld );
	//camera.getViewMatrix(&matWorld);
	Device->SetTransform( D3DTS_WORLD, &matWorld );



	// Render the 6 faces of the skybox
	// DrawPrimitive is used to draw polygons when the vertices are stored in a device resource 
	// called a vertex buffer. Vertex buffers are blocks of memory allocated by the device that
	// we use to store vertex data.
	for ( ULONG i = 0; i < 6; ++i )
	{
		// Set the texture for this primitive
		Device->SetTexture( 0, g_SkyTextures[i] );

		// Render the face (one strip per face from the vertex buffer)  There are 2 primitives per face.
		Device->DrawPrimitive( D3DPT_TRIANGLESTRIP, i * 4, 2 );

	} // Next side

	Device->SetTransform(D3DTS_VIEW, &matWorldSave);

	Device->SetRenderState( D3DRS_ZWRITEENABLE, true );
	Device->SetRenderState( D3DRS_LIGHTING, true );
	Device->SetRenderState( D3DRS_SPECULARENABLE, true );
}