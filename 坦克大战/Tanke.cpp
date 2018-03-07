// Tanke.cpp: implementation of the CTanke class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tanke.h"
#include "Mange.h"
# include <stdio.h>
#include <time.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTanke::CTanke()
{
	/*posy = 830;
	posx = 320;
	dix = 0;
	diy = 0;
	speed = 5;
	d_atk = 1000;
	timer = 0;
	preTime = clock();
	IsLive = true;*/
	InitMyTk();
}

CTanke::~CTanke()
{
}

void CTanke::Draw(IplImage *bg)
{
	if(IsLive == false) return ;
	for (int i=0;i<tanketi->height;i++)
	{
		for (int j=0;j<tanketi->width;j++)
		{
			int b = CV_IMAGE_ELEM(tanketi,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(tanketi,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(tanketi,uchar,i,j*3+2);
			if(b == 255 && g == 255 && r == 255)  continue;
			CV_IMAGE_ELEM(bg,uchar,i+posy,(j+posx)*3+0) = b;
			CV_IMAGE_ELEM(bg,uchar,i+posy,(j+posx)*3+1) = g;
			CV_IMAGE_ELEM(bg,uchar,i+posy,(j+posx)*3+2) = r;
		}
	}
}

void CTanke::Move(int hight, int width, IplImage *bg)
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		//PlaySound(TEXT(".\\resource\\music\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		tanketi = tanke[0];
		posy -= speed;
		dix = 0;
		diy = -speed;
		count = 1;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		//PlaySound(TEXT(".\\resource\\music\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		tanketi = tanke[3];
		posy += speed;
		dix = 0;
		diy = speed;
		count = 2;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		//PlaySound(TEXT(".\\resource\\music\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		tanketi = tanke[2];
		posx -= speed;
		dix = -speed;
		diy = 0;
		count = 3;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		//PlaySound(TEXT(".\\resource\\music\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		tanketi = tanke[1];
		posx += speed; 
		dix = speed;
		diy = 0;
		count = 4;
	}
	if (posx<0) posx = 0;
	if (posy<0) posy = 0;
	if (posx>width-1-tanketi->width)  posx = width-1-tanketi->width;
	if (posy>hight-1-tanketi->height) posy = hight-1-tanketi->height;
	
	int b0 = CV_IMAGE_ELEM(bg,uchar,posy,posx*3+0);
	int g0 = CV_IMAGE_ELEM(bg,uchar,posy,posx*3+1);
    int r0 = CV_IMAGE_ELEM(bg,uchar,posy,posx*3+2);
	
    int b1 = CV_IMAGE_ELEM(bg,uchar,posy+tanketi->height,posx*3+0);
	int g1 = CV_IMAGE_ELEM(bg,uchar,posy+tanketi->height,posx*3+1);
    int r1 = CV_IMAGE_ELEM(bg,uchar,posy+tanketi->height,posx*3+2);
	
	int b2 = CV_IMAGE_ELEM(bg,uchar,posy,(posx+tanketi->width)*3+0);
	int g2 = CV_IMAGE_ELEM(bg,uchar,posy,(posx+tanketi->width)*3+1);
    int r2 = CV_IMAGE_ELEM(bg,uchar,posy,(posx+tanketi->width)*3+2);
	
	int b3 = CV_IMAGE_ELEM(bg,uchar,posy+tanketi->height,(posx+tanketi->width)*3+0);
	int g3 = CV_IMAGE_ELEM(bg,uchar,posy+tanketi->height,(posx+tanketi->width)*3+1);
    int r3 = CV_IMAGE_ELEM(bg,uchar,posy+tanketi->height,(posx+tanketi->width)*3+2);
	
	if(b0>40||g0>40||r0>40||b2>40||g2>40||r2>40||b1>40||g1>40||r1>40||b3>40||g3>40||r3>40)
	{
		switch (count)
		{
		case 1:posy +=speed;break;
		case 2:posy -=speed;break;
		case 3:posx +=speed;break;
		case 4:posx -=speed;break;
		}
	}
}

void CTanke::Attack(CMange *manger)
{
	if (GetAsyncKeyState('J') & 0x8000 && d_atk<timer)
	{
		PlaySound(TEXT(".\\resource\\music\\fire.wav"), NULL, SND_FILENAME | SND_ASYNC);
		timer = 0;
		switch (count)
		{
		case 1:manger->CreatBullet(bulletti,posx + (tanketi->width-bulletti->width)/2, posy ,dix,diy,0,100,count);break;
		case 2:manger->CreatBullet(bulletti,posx + (tanketi->width-bulletti->width)/2, posy + tanketi->height,dix,diy,0,100,count);;break;
		case 3:manger->CreatBullet(bulletti,posx , posy + (tanketi->height+bulletti->width)/2,dix,diy,0,100,count);;break;
		case 4:manger->CreatBullet(bulletti,posx + (tanketi->width-bulletti->width), posy + (tanketi->height+bulletti->width)/2,dix,diy,0,100,count);;break;
		}
	}
	timer += clock()-preTime;
	preTime = clock();
}

void CTanke::SetImageInit(IplImage *pImg[],IplImage *pImagezidan[])
{
	int i;
	for ( i=0;i<4;i++)
	{
		tanke[i] = pImg[i];
	}
	tanketi = tanke[0];
	for (i=0;i<3;i++)
	{
		bullet[i] = pImagezidan[i];
	}
	bulletti = bullet[0]; 
}

IplImage * CTanke::GetnowMytkImg()
{
	return tanketi;
}

int CTanke::Getnowposx()
{
	return posx;
}

int CTanke::Getnowposy()
{
	return posy;
}

bool CTanke::NeedClear()
{
	return IsLive;
}

void CTanke::TakeDamage()
{
	IsLive = false;
}

int CTanke::GetnowCount()
{
	return count;
}

void CTanke::RepeatLive()
{
	IsLive = true;
}

void CTanke::InitMyTk()
{
	posy = 830;
	posx = 320;
	dix = 0;
	diy = 0;
	speed = 5;
	d_atk = 1000;
	timer = 0;
	preTime = clock();
	IsLive = true;
}
