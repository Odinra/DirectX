#include "AIs.h"

EvilCastle* Ecastle;
GoodCastle* Gcastle;
EvilKnight* EKnight[20];
EvilMage* EMage[20];
EvilPeon* EPeon[20];
GoodKnight* GKnight[20];
GoodMage* GMage[20];
GoodPeon* GPeon[20];
extern int GP;

extern IDirect3DVertexBuffer9* VBuffer;

AIs::AIs(void)
{						
}						
AIs::~AIs(void)
{
}
GoodMage::GoodMage(IDirect3DDevice9* D)
{
	Device = D;
	good = true;
	Pos.x = -1200;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = 3;
	Speed.y = 0;
	Speed.z = 0;
	Health = 10;
	Damage = 0;
	cost = 100;
	D3DXMatrixScaling(&MatSize, 357/11, 870/11, 1);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	inPlay = false;
	enemyInRange = false;
	for (int i = 0; i < 3; i++)
	{
		fb[i] = new GoodFireBall(Device);
		//fb[i]->Pos.x = 15;
		//fb[i]->Pos.y = -200;
		//fb[i]->Pos.z = 0;
		//fb[i]->Speed.x = 10;
		//fb[i]->Speed.y = 0;
		//fb[i]->Speed.z = 0;
		//fb[i]->Health = 1;
		//fb[i]->Damage = 20;
		//fb[i]->inPlay = false;
		//fb[i]->enemyInRange = false;
		//D3DXMatrixScaling(&fb[i]->MatSize, 379, 415, 0);
		//D3DXCreateTextureFromFile(Device, "Fireball_01.png", &fb[i]->Tex);
	}
	D3DXCreateTextureFromFile(Device, "Good mage_01.png", &Tex);
}
void GoodMage::ReInit()
	
{
	good = true;
	Pos.x = 15;
	Pos.x = -1500;
	Pos.y = -3750;
	Speed.x = 3;
	Speed.y = 0;
	Speed.z = 0;
	Health = 10;
	Damage = 0;
	inPlay = false;
	enemyInRange = false;
	for (int i = 0; i < 3; i++)
	{
		fb[i]->Pos.x = 15;
		fb[i]->Pos.y = -200;
		fb[i]->Pos.z = 0;
		fb[i]->Speed.x = 10;
		fb[i]->Speed.y = 0;
		fb[i]->Speed.z = 0;
		fb[i]->Health = 1;
		fb[i]->Damage = 20;
		fb[i]->inPlay = false;
		fb[i]->enemyInRange = false;
	}
}
EvilMage::EvilMage(IDirect3DDevice9* D)
{
	Device = D;
	good = !true;
	Pos.x = 1200;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = -3;
	Speed.y = 0;
	Speed.z = 0;
	Health = 10;
	Damage = 0;
	inPlay = false;
	enemyInRange = false;
	cost = 100;
	killworth = 50;
	previousTick = time(0);
	D3DXMatrixScaling(&MatSize, 455/10, 797/10, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	for (int i = 0; i < 3; i++)
	{
		fb[i] = new EvilFireBall(Device);
		//fb[i]->Pos.x = 135;
		//fb[i]->Pos.y = -200;
		//fb[i]->Pos.z = 0;
		//fb[i]->Speed.x = 10;
		//fb[i]->Speed.y = 0;
		//fb[i]->Speed.z = 0;
		//fb[i]->Health = 1;
		//fb[i]->Damage = 20;
		//fb[i]->inPlay = false;
		//fb[i]->enemyInRange = false;
		//D3DXMatrixScaling(&fb[i]->MatSize, 379, 415, 0);
		//D3DXCreateTextureFromFile(Device, "Fireball_01.png", &fb[i]->Tex);
	}
	D3DXCreateTextureFromFile(Device, "Evil Mage_01.png", &Tex);
}
void EvilMage::ReInit()
{
	GP += killworth;
	good = !true;
	Pos.x = 1500;
	Pos.y = -3750;
	Pos.z = 0;
	Speed.x = -3;
	Speed.y = 0;
	Speed.z = 0;
	Health = 10;
	Damage = 0;
	inPlay = false;
	enemyInRange = false;
	for (int i = 0; i < 3; i++)
	{
		fb[i]->ReInit();
		//fb[i]->Pos.x = 135;
		//fb[i]->Pos.y = -200;
		//fb[i]->Pos.z = 0;
		//fb[i]->Speed.x = 10;
		//fb[i]->Speed.y = 0;
		//fb[i]->Speed.z = 0;
		//fb[i]->Health = 1;
		//fb[i]->Damage = 20;
		//fb[i]->inPlay = false;
		//fb[i]->enemyInRange = false;
	}
}
GoodFireBall::GoodFireBall(IDirect3DDevice9* D)
{
	Device = D;
	good = true;
			Pos.x = 15;
		Pos.y = -200;
		Pos.z = 0;
		Speed.x = 8;
		Speed.y = 0;
		Speed.z = 0;
		Health = 1;
		Damage = 5;
		inPlay = false;
		enemyInRange = false;
		D3DXMatrixScaling(&MatSize, 379, 415, 0);
		D3DXCreateTextureFromFile(Device, "Fireball_01.png", &Tex);
}
void GoodFireBall::ReInit()
{
		Pos.x = 15;
		Pos.y = -2000;
		Pos.z = 0;
		Speed.x = 8;
		Speed.y = 0;
		Speed.z = 0;
		Health = 1;
		Damage = 5;
		inPlay = false;
		enemyInRange = false;
}
EvilFireBall::EvilFireBall(IDirect3DDevice9* D)
{
	Device = D;
	good = !true;
		Pos.x = 135;
		Pos.y = -2000;
		Pos.z = 0;
		Speed.x = -8;
		Speed.y = 0;
		Speed.z = 0;
		Health = 1;
		Damage = 5;
		inPlay = false;
		enemyInRange = false;
		D3DXMatrixScaling(&MatSize, 379, 415, 0);
		previousTick = time(0);
		D3DXCreateTextureFromFile(Device, "Fireball_01.png", &Tex);
}
void EvilFireBall::ReInit()
{

		Pos.x = 135;
		Pos.y = -200;
		Pos.z = 0;
		Speed.x = -8;
		Speed.y = 0;
		Speed.z = 0;
		Health = 1;
		Damage = 5;
		inPlay = false;
		enemyInRange = false;
}
EvilKnight::EvilKnight(IDirect3DDevice9* D)
{
	Device = D;
	good = !true;
	Pos.x = 1100;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = -5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	cost = 25;
	killworth = 10;
	hammer = new Hammer(Device);
	inPlay = false;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 486/10, 991/10, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	hammer->Pos.x = Pos.x -10;
	D3DXMatrixScaling(&hammer->MatSize, 354, 730, 0);
	D3DXCreateTextureFromFile(Device, "Evil knight_01.png", &Tex);
	D3DXCreateTextureFromFile(Device, "Evil hammer_01.png", &hammer->Tex);
}
void EvilKnight::ReInit()
{
	GP += killworth;
	good = !true;
	Pos.x = 1500;
	Pos.y = -3750;
	Pos.z = 0;
	Speed.x = 5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	inPlay = false;
	enemyInRange = false;
	hammer->ReInit();
	hammer->Pos.x = Pos.x -10;
}
GoodKnight::GoodKnight(IDirect3DDevice9* D)
{
	Device = D;
	good = true;
	Pos.x = -1100;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = 5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	cost = 25;
	sword = new Sword(Device);
	inPlay = false;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 412/10, 790/10, 0);
	D3DXMatrixScaling(&sword->MatSize, 284, 750, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	sword->Pos.x = Pos.x +10;
	D3DXCreateTextureFromFile(Device, "Good knight_01.png", &Tex);
	D3DXCreateTextureFromFile(Device, "Good sword_01.png", &sword->Tex);
}
void GoodKnight::ReInit()
{
	good = true;
	Pos.x = -1500;
	Pos.y = -3750;
	Pos.z = 0;
	Speed.x = 5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	inPlay = false;
	enemyInRange = false;
	sword->Pos.x = Pos.x +10;
}
GoodPeon::GoodPeon(IDirect3DDevice9* D)
{
	Device = D;
	good = true;
	Pos.x = -1000;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = 8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	cost = 5;
	sword = new Sword(Device);
	inPlay = false;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 277/10, 586/10, 0);
	D3DXMatrixScaling(&sword->MatSize, 284, 750, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	sword->Pos.x = Pos.x +10;
	D3DXCreateTextureFromFile(Device, "Good peon_01.png", &Tex);
	D3DXCreateTextureFromFile(Device, "Good sword_01.png", &sword->Tex);
}
void GoodPeon::ReInit()
{
	good = true;
	Pos.x = -1500;
	Pos.y = -3750;
	Pos.z = 0;
	Speed.x = 8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	inPlay = false;
	enemyInRange = false;
	sword->Pos.x = Pos.x +10;
}
EvilPeon::EvilPeon(IDirect3DDevice9* D)
{
	Device = D;
	good = !true;
	Pos.x = 1000;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = -8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	cost = 5;
	killworth = 3;
	inPlay = false;
	enemyInRange = false;
	hammer = new Hammer(Device);
	hammer->Pos.x = Pos.x -10;
	D3DXMatrixScaling(&MatSize, 314/10, 608/10, 0);
	D3DXMatrixScaling(&hammer->MatSize, 354, 730, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	D3DXCreateTextureFromFile(Device, "Evil peon_01.png", &Tex);
	D3DXCreateTextureFromFile(Device, "Evil hammer_01.png", &hammer->Tex);
}
void EvilPeon::ReInit()
{
	GP += killworth;
	good = !true;
	Pos.x = 1500;
	Pos.y = -3750;
	Pos.z = 0;
	Speed.x = 8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	inPlay = false;
	
	enemyInRange = false;
	hammer->Pos.x = Pos.x -10;
}
Hammer::Hammer(IDirect3DDevice9* D)
{
	Device = D;
	good = !true;
	Pos.x = 135;
	Pos.y = -200;
	Pos.z = 0;
	Speed.x = 8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	inPlay = true;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 354, 730, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	D3DXCreateTextureFromFile(Device, "Evil hammer_01.png", &Tex);
}
void Hammer::ReInit()
{

	good = !true;
	Pos.x = 135;
	Pos.y = -200;
	Pos.z = 0;
	Speed.x = 8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	inPlay = true;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 354, 730, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
}
Sword::Sword(IDirect3DDevice9* D)
{
	Device = D;
	good = true;
	Pos.x = 15;
	Pos.y = -200;
	Pos.z = 0;
	Speed.x = 5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	inPlay = true;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 284, 750, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	D3DXCreateTextureFromFile(Device, "Good sword_01.png", &Tex);
}
void Sword::ReInit()
{

	good = true;
	Pos.x = 15;
	Pos.y = -200;
	Pos.z = 0;
	Speed.x = 5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	inPlay = true;
	enemyInRange = false;
}
EvilCastle::EvilCastle(IDirect3DDevice9* D)
{
	Device = D;
	good = !true;
	Pos.x = 1200;
	Pos.y = -350;
	Pos.z = 0;
	Speed.x = 0;
	Speed.y = 0;
	Speed.z = 0;
	Health = 200;
	Damage = 0;
	inPlay = true;
	enemyInRange = false;
	bTex1 = true;
	bTex2 = true;
	D3DXMatrixScaling(&MatSize, 964/4, 783/4, 1);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	D3DXCreateTextureFromFile(Device, "Evil castle_01.png", &Tex);
	
}
void EvilCastle::Update()
{
	if (Health < 133)
		if(bTex1)
		{
			D3DXCreateTextureFromFile(Device, "Evil castle_02.png", &Tex);
			bTex1 = false;
		}
	else if (Health < 66)
		if(bTex2)
		{
			D3DXCreateTextureFromFile(Device, "Evil castle_03.png", &Tex);
			bTex2 = false;
		}

	if (Health > 0)
	{
	Movement();
	Draw();
	}
	else
	{
		::MessageBoxA(0, "You have destroyed the Evile Castle, you are victorious!", "Victory", 0);
		::PostQuitMessage(0);
	}
}
GoodCastle::GoodCastle(IDirect3DDevice9* D)
{
	Device = D;
	good = true;
	Pos.x = -1200;
	Pos.y = -325;
	Pos.z = 0;
	Speed.x = 0;
	Speed.y = 0;
	Speed.z = 0;
	Health = 200;
	Damage = 0;
	inPlay = true;
	bTex1 = true;
	bTex2 = true;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 954/4, 784/4, 1);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	D3DXCreateTextureFromFile(Device, "Good castle_01.png", &Tex);
	
}
void GoodCastle::Update()
{
	if (Health < 133)
		if(bTex1)
		{
			D3DXCreateTextureFromFile(Device, "Good castle_02.png", &Tex);
			bTex1 = false;
		}
	else if (Health < 66)
		if(bTex2)
		{
			D3DXCreateTextureFromFile(Device, "Good castle_03.png", &Tex);
			bTex2 = false;
		}

	if (Health > 0)
	{
	Movement();
	Draw();
	}
	else
	{
		::MessageBoxA(0, "The Evil army has overrun your Castle you are defeated!", "Defeat", 0);
		::PostQuitMessage(0);
	}
}
void AIs::Movement()
{
	if(inPlay && !enemyInRange)
	{
		Pos.x += Speed.x/500;
		
	}D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
}
void AIs::InRange()
{
	enemyInRange = false;
	if(inPlay)
	{
		for (int i = 0; i < 20; i++)
		{
			if(good)
			{
				if(EKnight[i]->inPlay)
				{
					if(EKnight[i]->Pos.x <= Pos.x + 75 && EKnight[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EKnight[i]);
					}
				}
				if(EMage[i]->inPlay)
				{
					if(EMage[i]->Pos.x <= Pos.x + 75 && EMage[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EMage[i]);
					}
				}
				if(EPeon[i]->inPlay)
				{
					if(EPeon[i]->Pos.x <= Pos.x + 75 && EPeon[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EPeon[i]);
					}
				}
				if(Ecastle->Pos.x <= Pos.x + 75 && Ecastle->Health > 0)
				{
					enemyInRange = true;
					Attack(Ecastle);
				}
			}
			else
			{
				if(GKnight[i]->inPlay)
				{
					if(GKnight[i]->Pos.x >= Pos.x - 75 && GKnight[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GKnight[i]);
					}
				}
				if(GMage[i]->inPlay)
				{
					if(GMage[i]->Pos.x >= Pos.x - 75 && GMage[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GMage[i]);
					}
				}
				if(GPeon[i]->inPlay)
				{
					if(GPeon[i]->Pos.x >= Pos.x - 75 && GPeon[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GPeon[i]);
					}
				}
				if(Gcastle->Pos.x >= Pos.x - 75 && Gcastle->Health > 0)
				{
					enemyInRange = true;
					Attack(Gcastle);
				}
			}
		}
	}
}
void AIs::Update()
{
	if(inPlay)
	{
		if(Health > 0)
		{
			InRange();
			Movement();
			Draw();
		}
		else
		{
			
			ReInit();
		}
	}
}
void AIs::Attack(AIs* A)
{
	A->Health -= Damage/1000;
}
void AIs::Draw()
{
	D3DXMatrixMultiply(&MatPos, &MatSize, &MatPos);
	//Device->SetTransform(D3DTS_WORLD, &MatPos);
	Device->SetStreamSource(0, VBuffer, 0, sizeof(Vertex));
	Device->SetFVF(FVF_VERTEX);
	Device->SetTexture(0, Tex);
	Device->SetTransform(D3DTS_WORLD, &MatPos);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 6, 2);
}
void EvilKnight::Update()
{
	if(inPlay)
	{
		if(Health > 0)
		{
			InRange();
			Movement();
			hammer->Pos.x = Pos.x - 40;
			hammer->Pos.y = Pos.y + 100;
			hammer->Pos.z = Pos.z + .01;
			D3DXMatrixTranslation(&hammer->MatPos, hammer->Pos.x, hammer->Pos.y, hammer->Pos.z);
			D3DXMatrixScaling(&hammer->MatSize, 354/15, 730/15, 0);
			hammer->Draw();
			Draw();
		}
		else
		{
			ReInit();
		}
	}
}
void EvilPeon::Update()
{
	if(inPlay)
	{
		if(Health > 0)
		{
			InRange();
			Movement();
			hammer->Pos.x = Pos.x - 24;
			hammer->Pos.y = Pos.y + 60;
			hammer->Pos.z = Pos.z + .01;
			D3DXMatrixTranslation(&hammer->MatPos, hammer->Pos.x, hammer->Pos.y, hammer->Pos.z);
			D3DXMatrixScaling(&hammer->MatSize, 354/20, 730/20, 0);
			hammer->Draw();
			Draw();
		}
		else
		{
			ReInit();
		}
	}
}
void GoodPeon::Update()
{
	if(inPlay)
	{
		if(Health > 0)
		{
			InRange();
			Movement();
			sword->Pos.x = Pos.x + 24;
			sword->Pos.y = Pos.y + 55;
			sword->Pos.z = Pos.z + .01;
			D3DXMatrixTranslation(&sword->MatPos, sword->Pos.x, sword->Pos.y, sword->Pos.z);
			D3DXMatrixScaling(&sword->MatSize, 284/20, 750/20, 0);
			sword->Draw();
			Draw();
		}
		else
		{
			ReInit();
		}
	}
}
void GoodKnight::Update()
{
	if(inPlay)
	{
		if(Health > 0)
		{
			InRange();
			Movement();
			sword->Pos.x = Pos.x + 35;
			sword->Pos.y = Pos.y + 85;
			sword->Pos.z = Pos.z + .01;
			D3DXMatrixTranslation(&sword->MatPos, sword->Pos.x, sword->Pos.y, sword->Pos.z);
			D3DXMatrixScaling(&sword->MatSize, 284/13, 750/13, 0);
			sword->Draw();
			Draw();
		}
		else
		{
			ReInit();
		}
	}
}
void EvilMage::Update()
{
	if(inPlay)
	{
		if(Health > 0)
		{
			InRange();
			Movement();
			for(int i = 0; i < 3; i++)
			{
				if(fb[i]->inPlay)
				{
					fb[i]->InRange();
					fb[i]->Movement();
					D3DXMatrixScaling(&fb[i]->MatSize, 379/13, 415/13, 0);
					fb[i]->Draw();
				}
			}
			Draw();
		}
		else
		{
			ReInit();
		}
	}
}
void GoodMage::Update()
{
		if(inPlay)
	{
		if(Health > 0)
		{
			InRange();
			Movement();
			for(int i = 0; i < 3; i++)
			{
				if(fb[i]->inPlay)
				{
					fb[i]->InRange();
					fb[i]->Movement();
					D3DXMatrixScaling(&fb[i]->MatSize, 379/13, 415/13, 0);
					fb[i]->Draw();
				}
			}
			
			Draw();
		}
		else
		{
			ReInit();
		}
	}
}
void EvilMage::Attack(AIs* A)
{
	currentTick = time(0);
	
	for (int i = 0; i< 3; i++)
	{	
		if(currentTick - previousTick > 1)
		{
		if(!fb[i]->inPlay)
		{
			fb[i]->Pos.x = Pos.x - 35;
			fb[i]->Pos.y = Pos.y + 55;
			fb[i]->Pos.z = Pos.z + .01;
			D3DXMatrixTranslation(&fb[i]->MatPos, fb[i]->Pos.x, fb[i]->Pos.y, fb[i]->Pos.z);
			D3DXMatrixScaling(&fb[i]->MatSize, 379/13, 415/13, 0);
			fb[i]->inPlay = true;
			previousTick = currentTick;
			return;
		}
		}
	}
	//previousTick = currentTick;
}
void GoodMage::Attack(AIs* A)
{
	currentTick = time(0);

	for (int i = 0; i< 3; i++)
	{	
		if(currentTick - previousTick > 1)
		{
			if(!fb[i]->inPlay)
			{
				fb[i]->Pos.x = Pos.x + 35;
				fb[i]->Pos.y = Pos.y + 55;
				fb[i]->Pos.z = Pos.z + .01;
				D3DXMatrixTranslation(&fb[i]->MatPos, fb[i]->Pos.x, fb[i]->Pos.y, fb[i]->Pos.z);
				D3DXMatrixScaling(&fb[i]->MatSize, 379/13, 415/13, 0);
				fb[i]->inPlay = true;
				previousTick = currentTick;
				return;
			}
		}
	}
}
void EvilMage::InRange()
{
		enemyInRange = false;
	if(inPlay)
	{
		for (int i = 0; i < 20; i++)
		{
			if(good)
			{
				if(EKnight[i]->inPlay)
				{
					if(EKnight[i]->Pos.x <= Pos.x + 225 && EKnight[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EKnight[i]);
					}
				}
				if(EMage[i]->inPlay)
				{
					if(EMage[i]->Pos.x <= Pos.x + 225 && EMage[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EMage[i]);
					}
				}
				if(EPeon[i]->inPlay)
				{
					if(EPeon[i]->Pos.x <= Pos.x + 225 && EPeon[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EPeon[i]);
					}
				}
				if(Ecastle->Pos.x <= Pos.x + 225 && Ecastle->Health > 0)
				{
					enemyInRange = true;
					Attack(Ecastle);
				}
			}
			else
			{
				if(GKnight[i]->inPlay)
				{
					if(GKnight[i]->Pos.x >= Pos.x - 225 && GKnight[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GKnight[i]);
					}
				}
				if(GMage[i]->inPlay)
				{
					if(GMage[i]->Pos.x >= Pos.x - 225 && GMage[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GMage[i]);
					}
				}
				if(GPeon[i]->inPlay)
				{
					if(GPeon[i]->Pos.x >= Pos.x - 225 && GPeon[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GPeon[i]);
					}
				}
				if(Gcastle->Pos.x >= Pos.x - 225 && Gcastle->Health > 0)
				{
					enemyInRange = true;
					Attack(Gcastle);
				}
			}
		}
	}
}
void GoodMage::InRange()
{
	enemyInRange = false;
	if(inPlay)
	{
		for (int i = 0; i < 20; i++)
		{
			if(good)
			{
				if(EKnight[i]->inPlay)
				{
					if(EKnight[i]->Pos.x <= Pos.x + 225 && EKnight[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EKnight[i]);
					}
				}
				if(EMage[i]->inPlay)
				{
					if(EMage[i]->Pos.x <= Pos.x + 225 && EMage[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EMage[i]);
					}
				}
				if(EPeon[i]->inPlay)
				{
					if(EPeon[i]->Pos.x <= Pos.x + 225 && EPeon[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(EPeon[i]);
					}
				}
				if(Ecastle->Pos.x <= Pos.x + 225 && Ecastle->Health > 0)
				{
					enemyInRange = true;
					Attack(Ecastle);
				}
			}
			else
			{
				if(GKnight[i]->inPlay)
				{
					if(GKnight[i]->Pos.x >= Pos.x - 225 && GKnight[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GKnight[i]);
					}
				}
				if(GMage[i]->inPlay)
				{
					if(GMage[i]->Pos.x >= Pos.x - 225 && GMage[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GMage[i]);
					}
				}
				if(GPeon[i]->inPlay)
				{
					if(GPeon[i]->Pos.x >= Pos.x - 225 && GPeon[i]->Health > 0)
					{
						enemyInRange = true;
						Attack(GPeon[i]);
					}
				}
				if(Gcastle->Pos.x >= Pos.x - 225 && Gcastle->Health > 0)
				{
					enemyInRange = true;
					Attack(Gcastle);
				}
			}
		}
	}
}
void EvilFireBall::Attack(AIs* A)
{
		A->Health -= Damage;
		ReInit();
}
void GoodFireBall::Attack(AIs* A)
{
		A->Health -= Damage;
		ReInit();
}
void GoodMage::PutInPlay()
{
	Pos.x = -1200;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = 3;
	Speed.y = 0;
	Speed.z = 0;
	Health = 10;
	Damage = 0;
	cost = 100;
	D3DXMatrixScaling(&MatSize, 357/11, 870/11, 1);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	inPlay = true;
	enemyInRange = false;
}
void EvilMage::PutInPlay()
{
	Pos.x = 1200;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = -3;
	Speed.y = 0;
	Speed.z = 0;
	Health = 10;
	Damage = 0;
	inPlay = true;
	enemyInRange = false;
	cost = 100;
	killworth = 50;
	previousTick = time(0);
	D3DXMatrixScaling(&MatSize, 455/10, 797/10, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
}
void EvilKnight::PutInPlay()
{
	good = !true;
	Pos.x = 1100;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = -5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	cost = 25;
	killworth = 10;
	hammer = new Hammer(Device);
	inPlay = true;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 486/10, 991/10, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	hammer->Pos.x = Pos.x -10;
	D3DXMatrixScaling(&hammer->MatSize, 354, 730, 0);
}
void GoodKnight::PutInPlay()
{
	good = true;
	Pos.x = -1100;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = 5;
	Speed.y = 0;
	Speed.z = 0;
	Health = 25;
	Damage = 10;
	cost = 25;
	sword = new Sword(Device);
	inPlay = true;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 412/10, 790/10, 0);
	D3DXMatrixScaling(&sword->MatSize, 284, 750, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	sword->Pos.x = Pos.x +10;
}
void GoodPeon::PutInPlay()
{
	good = true;
	Pos.x = -1000;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = 8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	cost = 5;
	sword = new Sword(Device);
	inPlay = true;
	enemyInRange = false;
	D3DXMatrixScaling(&MatSize, 277/10, 586/10, 0);
	D3DXMatrixScaling(&sword->MatSize, 284, 750, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
	sword->Pos.x = Pos.x +10;
}
void EvilPeon::PutInPlay()
{
	good = !true;
	Pos.x = 1000;
	Pos.y = -375;
	Pos.z = 0;
	Speed.x = -8;
	Speed.y = 0;
	Speed.z = 0;
	Health = 15;
	Damage = 5;
	cost = 5;
	killworth = 3;
	inPlay = true;
	enemyInRange = false;
	hammer = new Hammer(Device);
	hammer->Pos.x = Pos.x -10;
	D3DXMatrixScaling(&MatSize, 314/10, 608/10, 0);
	D3DXMatrixScaling(&hammer->MatSize, 354, 730, 0);
	D3DXMatrixTranslation(&MatPos, Pos.x, Pos.y, Pos.z);
}
void COMPUTERAI::upDate()
{
	peonCurrent = knightCurrent = mageCurrent = time(0);
	if(gold >= EMage[0]->cost && mageCurrent- mageLast >= 1)
	{
		bbreak = false;
		int i = 0;
		do
		{
			if(!EMage[i]->inPlay)
			{
				gold -= EMage[0]->cost;
				bbreak = true;
				mageLast = mageCurrent;
				EMage[i]->PutInPlay();
			}
			i++;
		}while( i < 20 && !bbreak);
	}	
	if(gold >= EKnight[0]->cost && knightCurrent- KnightLast >= 5)
	{
		bbreak = false;
		int i = 0;
		do
		{
			if(!EKnight[i]->inPlay)
			{
				gold -= EKnight[0]->cost;
				bbreak = true;
				KnightLast = knightCurrent;
				EKnight[i]->PutInPlay();
			}
			i++;
		}while( i < 20 && !bbreak);
	}
	if(gold >= EPeon[0]->cost && peonCurrent - peonLast >= 10)
	{
		bbreak = false;
		int i = 0;
		do
		{
			if(!EPeon[i]->inPlay)
			{
				gold -= EPeon[0]->cost;
				bbreak = true;
				peonLast = peonCurrent;
				EPeon[i]->PutInPlay();
			}
			i++;
		}while( i < 20 && !bbreak);
	}


}