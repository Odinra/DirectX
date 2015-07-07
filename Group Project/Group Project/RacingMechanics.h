#ifndef _RACINGMECHANICS_H_
#define _RACINGMECHANICS_H_
#include "d3dUtility.h"

class Racing
{
private:
	D3DXVECTOR3 velocity(D3DXVECTOR3, D3DXVECTOR3, DWORD, DWORD);
	D3DXVECTOR3 acceleration(D3DXVECTOR3, D3DXVECTOR3, DWORD, DWORD);
	float dx, dy, dz;
	D3DXVECTOR3 Velocity;
	D3DXVECTOR3 Acceleration;

public:
	Racing()
	{
		dx = 0; dy = 0; dz = 0;
	}
	double Accelerate();
	double Deaccelerate();
};
#endif
