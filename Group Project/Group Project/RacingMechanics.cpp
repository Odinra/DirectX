#include "RacingMechanics.h"


//

//double Racing::Deaccelerate()
//{
//
//}



D3DXVECTOR3 Racing::velocity(D3DXVECTOR3 initialPos, D3DXVECTOR3 finalPos, DWORD initialTime, DWORD finalTime)
{
	dx = fpuSub(finalPos.x, initialPos.x), dy = fpuSub(finalPos.y, initialPos.y), dz = fpuSub(finalPos.z, initialPos.z);

	dx = fpuMul(dx, dx);
	dy = fpuMul(dy, dy);
	dz = fpuMul(dz, dz);

	Velocity.x = fpuDiv(dx, fpuSub(finalTime, initialTime));
	Velocity.y = fpuDiv(dy, fpuSub(finalTime, initialTime));
	Velocity.z = fpuDiv(dz, fpuSub(finalTime, initialTime));

	return Velocity;
}

D3DXVECTOR3 Racing::acceleration(D3DXVECTOR3 initialVelocity, D3DXVECTOR3 finalVelocity, DWORD initialTime, DWORD finalTime)
{
	dx = fpuSub(finalVelocity.x, initialVelocity.x), dy = fpuSub(finalVelocity.y, initialVelocity.y), dz = fpuSub(finalVelocity.z, initialVelocity.z);

	dx = fpuMul(dx, dx);
	dy = fpuMul(dy, dy);
	dz = fpuMul(dz, dz);

	Acceleration.x = fpuDiv(dx, fpuSub(finalTime, initialTime));
	Acceleration.y = fpuDiv(dy, fpuSub(finalTime, initialTime));
	Acceleration.z = fpuDiv(dz, fpuSub(finalTime, initialTime));

	return Acceleration;
}