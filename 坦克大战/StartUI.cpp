// StartUI.cpp: implementation of the CStartUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StartUI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStartUI::CStartUI()
{
	startImg = cvLoadImage(".\\resource\\map\\mapstart.png");
	startImgclone = cvCloneImage(startImg);
	chooseImg = cvLoadImage(".\\resource\\mytanke1\\1.png");
	posx = 250;
	posy = 330;
}

CStartUI::~CStartUI()
{
	cvReleaseImage(&startImg);
	cvReleaseImage(&chooseImg);
	cvReleaseImage(&startImgclone);
}

void CStartUI::Draw()
{
	if (GetAsyncKeyState('F') & 0x8000)
	{
		PlaySound(TEXT(".\\resource\\music\\anjian.wav"), NULL, SND_FILENAME | SND_ASYNC);
		posx = 250;
		posy = 330;
	}

	if (GetAsyncKeyState('G') & 0x8000)
	{
		PlaySound(TEXT(".\\resource\\music\\anjian.wav"), NULL, SND_FILENAME | SND_ASYNC);
		posx = 250;
		posy = 390;
	}
	for (int i=0 ; i<chooseImg->height ; i++)
	{
		for (int j=0 ; j<chooseImg->width ; j++)
		{
			int b = CV_IMAGE_ELEM(chooseImg,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(chooseImg,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(chooseImg,uchar,i,j*3+2);
			if(b == 255 && g == 255 && r == 255) continue;
			CV_IMAGE_ELEM(startImg,uchar,i+posy,(j+posx)*3+0) = b;
			CV_IMAGE_ELEM(startImg,uchar,i+posy,(j+posx)*3+1) = g;
			CV_IMAGE_ELEM(startImg,uchar,i+posy,(j+posx)*3+2) = r;
		}
	}
}

void CStartUI::ShowstartImg()
{
	cvShowImage("Ì¹¿Ë´óÕ½",startImg);
	cvWaitKey(0);
}

void CStartUI::Build()
{
	cvCopyImage(startImgclone,startImg,NULL);
}
