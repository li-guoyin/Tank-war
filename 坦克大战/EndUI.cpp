// EndUI.cpp: implementation of the CEndUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EndUI.h"
#include "Mange.h" 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEndUI::CEndUI()
{
	endImg = cvLoadImage(".\\resource\\map\\gameover.jpg");
	endImgclone = cvCloneImage(endImg);
	InitEndUI();
	char filename[40];
	for (int i=0 ; i<10 ; i++)
	{
		sprintf(filename,".\\resource\\grade\\%d.png",i);
		grade[i] = cvLoadImage(filename,1);
	}
}

CEndUI::~CEndUI()
{
	cvReleaseImage(&endImgclone);
	cvReleaseImage(&endImg);
	for (int i=0 ; i<10 ; i++)
	{
		cvReleaseImage(&grade[i]);
	}
}

void CEndUI::ShowImage(CMange *manger)
{
	GetGradeNum(manger);
	cvShowImage("坦克大战",endImg);
}

void CEndUI::GetGradeNum(CMange *manger)
{
	int i,j,k;
	int arr[10] ; //得到每个位置上的数字；
	int length = 0;
	int score = manger->GetNowGrade();
	if (score != 0)
	{
		while (score)
		{
			arr[length++] = score % 10;
			score = score/10;
		}
	}
	else arr[length++] = 0;

	int posx = 410 - length *10;
	int posy = 630;

	for ( k = length -1 ; k>=0 ;k--)
	{
		for ( i=0 ; i<grade[arr[k]]->height ; i++)
		{
			for ( j=0 ; j<grade[arr[k]]->width ; j++)
			{
				int b = CV_IMAGE_ELEM(grade[arr[k]],uchar,i,j*3+0);
				int g = CV_IMAGE_ELEM(grade[arr[k]],uchar,i,j*3+1);
				int r = CV_IMAGE_ELEM(grade[arr[k]],uchar,i,j*3+2);
				if( b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 180) continue;
				CV_IMAGE_ELEM(endImg,uchar,i + posy,(j + posx)*3+0) = b;
				CV_IMAGE_ELEM(endImg,uchar,i + posy,(j + posx)*3+1) = g;
				CV_IMAGE_ELEM(endImg,uchar,i + posy,(j + posx)*3+2) = r;
			}
		}
		posx = posx + grade[arr[k]]->width ;
	}
}

void CEndUI::InitEndUI()
{
	cvCopyImage(endImgclone,endImg,NULL);
}
