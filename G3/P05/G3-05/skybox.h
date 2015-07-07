#ifndef SKYBOX_H
#define SKYBOX_H

#include "base.h"

#include "main.h"

struct TTexVertex
{
    float x, y, z;		// 3D world position
    float tu, tv;		// Texture coordinates
};
bool BuildSkybox(IDirect3DDevice9* Device);
void renderSkybox(IDirect3DDevice9* Device, Camera camera);

#endif