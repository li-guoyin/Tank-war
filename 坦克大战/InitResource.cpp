// InitResource.cpp: implementation of the CInitResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InitResource.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInitResource::CInitResource()
{

}

CInitResource::~CInitResource()
{

}

void CInitResource::InitResourceImage()
{
	int i;
	char filename[40];
	char filename1[40];
	char filename2[40];
	char filename3[40];
	char filename4[40];
	for ( i = 0; i < 4; i++)
	{
		sprintf(filename, ".\\resource\\mytanke1\\%d.png", i);
		mytanke[i] = cvLoadImage(filename, 1);
	}
	for ( i = 0; i < 4; i++)
	{
		sprintf(filename1, ".\\resource\\ditankegray\\%d.png", i);
		ditankegray[i] = cvLoadImage(filename1, 1);
	}
	for ( i = 0; i < 4; i++)
	{
		sprintf(filename2, ".\\resource\\ditankebule\\%d.png", i);
		ditankebule[i] = cvLoadImage(filename2, 1);
		
	}
	for ( i = 0; i < 4; i++)
	{
		sprintf(filename3, ".\\resource\\ditankegold\\%d.png", i);
		ditankegold[i] = cvLoadImage(filename3, 1);
	}
	for ( i = 0; i < 3; i++)
	{
		sprintf(filename4,".\\resource\\bullt\\%d.png",i);
		zidan[i] = cvLoadImage(filename4,1);
	}
}

void CInitResource::ReleaseResource()
{
	int i;
	for (i=0;i<4;i++)
		cvReleaseImage(&mytanke[i]);
	for (i=0;i<4;i++)
		cvReleaseImage(&ditankegray[i]);
	for (i=0;i<4;i++)
		cvReleaseImage(&ditankebule[i]);
	for (i=0;i<4;i++)
		cvReleaseImage(&ditankegold[i]);
	for (i=0;i<3;i++)
		cvReleaseImage(&zidan[i]);
}
