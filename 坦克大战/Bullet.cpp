// Bullet.cpp: implementation of the CBullet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bullet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBullet::CBullet()
{
	b_Isclear = false;
}

CBullet::~CBullet()
{
}

CBullet::CBullet(IplImage *img, int posx, int posy, int dix, int diy, int attack,int count)
{
	bulletimg = img;
	b_dix = dix ;
	b_diy = diy ;
	b_attack = attack;
	b_Isclear = false;
	b_posx = posx;
	b_posy = posy;
}

void CBullet::Move()
{
	if (b_Isclear)
	{ 
		return ;
	}
	b_posx += b_dix;
	b_posy += b_diy;
	if (b_posx<5 || b_posy<10 || b_posx >895 || b_posy>895)
	{
		b_Isclear = true;
	}
}

void CBullet::Draw(IplImage *bg)
{
	if (b_Isclear == true)  return;
	for (int i=0;i<bulletimg->height;i++)
	{
		for (int j=0;j<bulletimg->width;j++)
		{
			int b = CV_IMAGE_ELEM(bulletimg,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(bulletimg,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(bulletimg,uchar,i,j*3+2);
			if( b > 80 && b < 100 && g > 125 && g < 140 && r > 170 && r < 185) continue;
			if( b > 250 && b <= 255 && g > 250 && g <= 255 && r > 250 && r <= 255) continue;
			//if( b == 255 && g == 255 && r == 255) continue;
			CV_IMAGE_ELEM(bg,uchar,i+b_posy-10,(j+b_posx)*3+0) = b;
			CV_IMAGE_ELEM(bg,uchar,i+b_posy-10,(j+b_posx)*3+1) = g;
			CV_IMAGE_ELEM(bg,uchar,i+b_posy-10,(j+b_posx)*3+2) = r;
		}
	}
}

bool CBullet::NeedClear()
{
	return b_Isclear;
}

void CBullet::NeedDestory()
{
	b_Isclear = true;
}

int CBullet::Getposx()
{
	return b_posx;
}

int CBullet::Getposy()
{
	return b_posy;
}

IplImage * CBullet::GetbulletImage()
{
	return bulletimg;
}

int CBullet::GetAttack()
{
	return b_attack;
}
