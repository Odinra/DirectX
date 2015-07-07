#pragma once
#include "d3dUtility.h"
class AIs
{
public:
	unsigned previousTick;
	unsigned currentTick;
	Vertex OriginalPos;
	D3DXMATRIX MatPos, MatSize;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Speed;
	double Health;
	double Damage;
	bool inPlay;
	bool enemyInRange;
	bool good;
	bool bTex1, bTex2;
	AIs(void);
	~AIs(void);
	virtual void Draw();
	virtual void InRange();
	virtual void Movement();
	virtual void Attack(AIs* a);
	virtual void Update();
	virtual void ReInit() = 0;
	virtual void PutInPlay(){};
	IDirect3DTexture9* Tex;
	IDirect3DDevice9* Device;
	int cost;
	int killworth;
};
class Weapon: public AIs
{
public:
	Weapon(IDirect3DDevice9* Device);
	~Weapon(){}
	Weapon(){}
	virtual void ReInit()=0;
};
class Sword: public Weapon
{
public:
	Sword(IDirect3DDevice9* Device);
	~Sword(){}
	Sword(){}
	virtual void ReInit();
};
class Hammer: public Weapon
{
public:
	Hammer(IDirect3DDevice9* Device);
	~Hammer(){}
	Hammer(){}
	virtual void ReInit();
};
class FireBall: public AIs
{
public:
	FireBall(IDirect3DDevice9* Device);
	~FireBall(){}
	FireBall(){}
	virtual void ReInit(){}
	
};
class EvilFireBall: public FireBall
{
public:
	EvilFireBall(IDirect3DDevice9* Device);
	~EvilFireBall(){}
	EvilFireBall(){}
	virtual void ReInit();
	virtual void Attack(AIs* a);
	
};
class GoodFireBall: public FireBall
{
public:
	GoodFireBall(IDirect3DDevice9* Device);
	~GoodFireBall(){}
	GoodFireBall(){}
	virtual void ReInit();
	virtual void Attack(AIs* a);
};
class Mage:public AIs
{
public:
	Mage(IDirect3DDevice9* Device);
	~Mage(){}
	Mage(){}
	virtual void ReInit(){}
};
class GoodMage: public Mage
{
public:
	GoodMage(IDirect3DDevice9* Device);
	~GoodMage(){}
	virtual void ReInit();
	virtual void Update();
	virtual void Attack(AIs* A);
	virtual void InRange();
	virtual void PutInPlay();
	GoodMage(){}
	GoodFireBall* fb[3];
};
class EvilMage: public Mage
{
public:
	EvilMage(IDirect3DDevice9* Device);
	~EvilMage(){}
	virtual void ReInit();
	virtual void Update();
	virtual void Attack(AIs* A);
	virtual void InRange();
	virtual void PutInPlay();
	EvilMage(){}
	EvilFireBall* fb[3];
};
class Knight: public AIs
{
public:
	Knight(IDirect3DDevice9* Device);
	~Knight(){}
	virtual void ReInit(){}
	Knight(){}
};
class GoodKnight: public Knight
{
public:
	GoodKnight(IDirect3DDevice9* Device);
	~GoodKnight(){}
	virtual void ReInit();
	virtual void Update();
	virtual void PutInPlay();
	GoodKnight(){}
	Sword* sword;
};
class EvilKnight: public Knight
{
public:
	EvilKnight(IDirect3DDevice9* Device);
	~EvilKnight(){}
	virtual void ReInit();
	virtual void Update();
	virtual void PutInPlay();
	EvilKnight(){}
	Hammer* hammer;
};
class Peon: public AIs
{
public:
	Peon(IDirect3DDevice9* Device);
	~Peon(){}
	virtual void ReInit(){}
	Peon(){}
};
class GoodPeon: public Peon
{
public:
	GoodPeon(IDirect3DDevice9* Device);
	~GoodPeon(){}
	virtual void ReInit();
	virtual void Update();
	virtual void PutInPlay();
	GoodPeon(){}
	Sword* sword;
};
class EvilPeon: public Peon
{
public:
	EvilPeon(IDirect3DDevice9* Device);
	~EvilPeon(){}
	virtual void ReInit();
	virtual void Update();
	virtual void PutInPlay();
	EvilPeon(){}
	Hammer* hammer;
};
class GoodCastle: public AIs
{
public:
	GoodCastle(IDirect3DDevice9* Device);
	~GoodCastle(){}
	virtual void ReInit(){}
	virtual void Update();
	GoodCastle(){}
};
class EvilCastle: public AIs
{
public:
	EvilCastle(IDirect3DDevice9* Device);
	~EvilCastle(){}
	virtual void ReInit(){}
	virtual void Update();
	EvilCastle(){}
};
class COMPUTERAI
{
public:
	~COMPUTERAI(){}
	COMPUTERAI()
	{
		gold = 70;
		peonCurrent = peonLast = mageCurrent = mageLast = knightCurrent = KnightLast = time(0);
	}
	int gold;
	void upDate();
	bool bbreak;
	unsigned peonCurrent, peonLast, mageCurrent, mageLast, knightCurrent, KnightLast;

};