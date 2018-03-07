// Buff.cpp: implementation of the CBuff class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Buff.h"
#include "Mange.h"
# include<time.h>
# include<stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBuff::CBuff()
{
	InitBuff();
	/*timer = 0;
	pretime = clock();
	f_atkappear = 20000;
	f_atkdisappear = 30000;
	f_appear = false;
	f_buff = cvLoadImage(".\\resource\\tool\\toolstar.png");*/
}

CBuff::~CBuff()
{
	cvReleaseImage(&f_buff);
}

void CBuff::Draw(IplImage *bg)
{
	if(f_appear == false) return ;
	int i,j;
	for (i=0 ; i<f_buff->height ; i++)
	{
		for (j=0 ; j<f_buff->width ; j++)
		{
			int b = CV_IMAGE_ELEM(f_buff,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(f_buff,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(f_buff,uchar,i,j*3+2);

			CV_IMAGE_ELEM(bg,uchar,i+f_posy,(j+f_posx)*3+0) = b;
			CV_IMAGE_ELEM(bg,uchar,i+f_posy,(j+f_posx)*3+1) = g;
			CV_IMAGE_ELEM(bg,uchar,i+f_posy,(j+f_posx)*3+2) = r;
		}
	}
}

bool CBuff::GetBuffAppear()
{
	return f_appear;
}

int CBuff::Getposx()
{
	return f_posx;
}

int CBuff::Getposy()
{
	return f_posy;
}

void CBuff::Disappear()
{
	f_appear = false;
}

void CBuff::Appear()
{
	f_appear = true;
}

void CBuff::Updata()
{
	timer += clock()-pretime;
	pretime = clock();
	if (timer > f_atkappear)
	{
		Appear();
	}
	if (timer > f_atkdisappear)
	{
		timer = 0;
		Rand();
		Disappear();
	}
}

void CBuff::InitBuff()
{
	timer = 0;
	pretime = clock();
	f_atkappear = 20000;
	f_atkdisappear = 30000;
	f_posx = 350;
	f_posy = 350;
	f_appear = false;
	f_buff = cvLoadImage(".\\resource\\tool\\toolstar.png");
}



void CBuff::InitTimer()
{
	timer = 0;
}

void CBuff::Rand()
{
	time_t t;
	srand((unsigned)time(&t));
	f_posx = rand()%700+30;
	f_posy = rand()%700+30;
}
