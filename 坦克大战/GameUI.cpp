// GameUI.cpp: implementation of the CGameUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameUI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGameUI::CGameUI()
{
	grass = cvLoadImage(".\\resource\\map\\grass.png");
}

CGameUI::~CGameUI()
{
	cvReleaseImage(&grass);
	cvReleaseImage(&bgclone);
	cvReleaseImage(&bgclone1);
}

void CGameUI::Setimage(IplImage *bgimg)
{
	bg = bgimg;
	bgclone1 = cvCloneImage(bg);
	GameUIInit();
}


void CGameUI::GameUIInit()
{
	bgclone = cvCloneImage(bgclone1);
}


void CGameUI::ShowImage()
{
	cvShowImage("Ì¹¿Ë´óÕ½",bg);
}



IplImage * CGameUI::GetnowImage()
{
	return bg;
}

IplImage * CGameUI::GetbgcloneImage()
{
	return bgclone;
}

void CGameUI::Build()
{
	cvCopyImage(bgclone,bg,NULL);
}

void CGameUI::Drawgrass()
{
	IplImage * temp = GetnowImage();
	int x = 0;
	int y = 345;
	int k;
	for ( k=0;k<2;k++)
	{
		for (int i=0;i<grass->height;i++)
		{
			for (int j=0;j<grass->width;j++)
			{
				int b = CV_IMAGE_ELEM(grass,uchar,i,j*3+0);
				int g = CV_IMAGE_ELEM(grass,uchar,i,j*3+1);
				int r = CV_IMAGE_ELEM(grass,uchar,i,j*3+2);
				if(b == 255 && g == 255 && r == 255)  continue;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+0)*3+0) = b;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+0)*3+1) = g;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+0)*3+2) = r;
			}
		}
		y = y + 69;
	}
	for (int i=0;i<grass->height;i++)
	{
		for (int j=0;j<grass->width;j++)
		{
			int b = CV_IMAGE_ELEM(grass,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(grass,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(grass,uchar,i,j*3+2);
			if(b == 255 && g == 255 && r == 255)  continue;
			CV_IMAGE_ELEM(temp,uchar,i+345,(j+69)*3+0) = b;
			CV_IMAGE_ELEM(temp,uchar,i+345,(j+69)*3+1) = g;
			CV_IMAGE_ELEM(temp,uchar,i+345,(j+69)*3+2) = r;
		}
	}
	for (k=0;k<2;k++)
	{
		for (int i=0;i<grass->height;i++)
		{
			for (int j=0;j<grass->width;j++)
			{
				int b = CV_IMAGE_ELEM(grass,uchar,i,j*3+0);
				int g = CV_IMAGE_ELEM(grass,uchar,i,j*3+1);
				int r = CV_IMAGE_ELEM(grass,uchar,i,j*3+2);
				if(b == 255 && g == 255 && r == 255)  continue;
				CV_IMAGE_ELEM(temp,uchar,i+y-69,(j+276)*3+0) = b;
				CV_IMAGE_ELEM(temp,uchar,i+y-69,(j+276)*3+1) = g;
				CV_IMAGE_ELEM(temp,uchar,i+y-69,(j+276)*3+2) = r;
			}
		}
		y = y+69;
	}
	x = 345; y = 413;
	for (k=0;k<2;k++)
	{
		for (int i=0;i<grass->height;i++)
		{
			for (int j=0;j<grass->width;j++)
			{
				int b = CV_IMAGE_ELEM(grass,uchar,i,j*3+0);
				int g = CV_IMAGE_ELEM(grass,uchar,i,j*3+1);
				int r = CV_IMAGE_ELEM(grass,uchar,i,j*3+2);
				if(b == 255 && g == 255 && r == 255)  continue;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+x)*3+0) = b;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+x)*3+1) = g;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+x)*3+2) = r;
			}
		}
		x = x+69;
	}
	for (k=0;k<3;k++)
	{
		for (int i=0;i<grass->height;i++)
		{
			for (int j=0;j<grass->width;j++)
			{
				int b = CV_IMAGE_ELEM(grass,uchar,i,j*3+0);
				int g = CV_IMAGE_ELEM(grass,uchar,i,j*3+1);
				int r = CV_IMAGE_ELEM(grass,uchar,i,j*3+2);
				if(b == 255 && g == 255 && r == 255)  continue;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+694)*3+0) = b;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+694)*3+1) = g;
				CV_IMAGE_ELEM(temp,uchar,i+y,(j+694)*3+2) = r;
			}
		}
		y = y-69;
	}
}

