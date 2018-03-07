// BoomEffect.cpp: implementation of the CBoomEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BoomEffect.h"
#include "Mange.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoomEffect::CBoomEffect()
{
	char filename[40];
	int i;
	for ( i = 0; i < 8; i++)
	{
		sprintf(filename,".\\resource\\bomb\\%d.png",i);
		boomEffect[i] = cvLoadImage(filename,1);
	}
}

CBoomEffect::~CBoomEffect()
{
	for (int i=0;i<8;i++)
       cvReleaseImage(&boomEffect[i]);
}

CBoomEffect::CBoomEffect(int posx,int posy)
{
	char filename[40];
	int i;
	for ( i = 0; i < 8; i++)
	{
		sprintf(filename,".\\resource\\bomb\\%d.png",i);
		boomEffect[i] = cvLoadImage(filename,1);
	}
	e_posx = posx;
	e_posy = posy;
	e_speed = 1;
	e_index = 0;
	e_Isclear = false;
}

void CBoomEffect::Draw(IplImage *bg)
{
	if(e_Isclear == true) return ;
	e_boomEffectti = boomEffect[e_index/e_speed];

	int posx = e_posx ;
	int posy = e_posy ;

	for (int i=0 ; i<e_boomEffectti->height ; i++)
	{
		for (int j=0 ; j<e_boomEffectti->width ; j++)
		{
			int b = CV_IMAGE_ELEM(e_boomEffectti,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(e_boomEffectti,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(e_boomEffectti,uchar,i,j*3+2);
			if(b == 255 && g == 255 && r == 255) continue;
			CV_IMAGE_ELEM(bg,uchar,i+posy,(j+posx)*3+0) = b;
			CV_IMAGE_ELEM(bg,uchar,i+posy,(j+posx)*3+1) = g;
			CV_IMAGE_ELEM(bg,uchar,i+posy,(j+posx)*3+2) = r;
		}
	}
	e_index++;
	if(e_index/e_speed > 8) e_Isclear = true;
}

bool CBoomEffect::NeedClear()
{
	return e_Isclear;
}
