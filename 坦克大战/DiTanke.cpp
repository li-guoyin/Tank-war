// DiTanke.cpp: implementation of the CDiTanke class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiTanke.h"
#include "Mange.h"
# include <stdio.h>
# include <time.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiTanke::CDiTanke()
{
}
CDiTanke::CDiTanke(IplImage *pImagegray[], IplImage *pImagebule[], IplImage *pImagegold[],IplImage *pImagebullet[])
{
	m_timer = 0;
	m_atk = 2500;
	m_preTime = clock();
	m_Isclear = false;
	int i;
	for (i=0;i<4;i++)
		m_ditankegray[i] = pImagegray[i];
	for (i=0;i<4;i++)
		m_ditankebule[i] = pImagebule[i];
	for (i=0;i<4;i++)
		m_ditankegold[i] = pImagegold[i];
	for (i=0;i<3;i++)
		m_bullet[i] = pImagebullet[i];
	time_t t;
	srand((unsigned)time(&t));
	int key = rand()%3;
	if (key == 0)
	{
		m_ditanke = m_ditankegray[3];
		m_bulletti = m_bullet[0];
		Pdirection = 0;
		m_posx = 5;
		m_posy = 5;
		m_diy=2;
		m_dix=0;
	}
	else if(key == 1)
	{
		m_ditanke = m_ditankebule[3];
		m_bulletti = m_bullet[1];
		Pdirection  = 1;
		m_posx = 840;
		m_posy = 5;
		m_diy=2;
		m_dix=0;
	}
	else if (key == 2)
	{
		m_ditanke = m_ditankegold[3]; 
		m_bulletti = m_bullet[2];
		Pdirection  = 2;
		m_posx = 415;
		m_posy = 5;
		m_diy=2;
		m_dix=0;
	}
}

CDiTanke::~CDiTanke()
{
}

void CDiTanke::Draw(IplImage *bg)
{
	if(m_Isclear == true) return ;
	for (int i=0;i<m_ditanke->height;i++)
	{
		for (int j=0;j<m_ditanke->width;j++)
		{
			int b = CV_IMAGE_ELEM(m_ditanke,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(m_ditanke,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(m_ditanke,uchar,i,j*3+2);
			if(b == 255 && g == 255 && r == 255)  continue;
			CV_IMAGE_ELEM(bg,uchar,i+m_posy,(j+m_posx)*3+0) = b;
			CV_IMAGE_ELEM(bg,uchar,i+m_posy,(j+m_posx)*3+1) = g;
			CV_IMAGE_ELEM(bg,uchar,i+m_posy,(j+m_posx)*3+2) = r;
		}
	}
}

void CDiTanke::Move(int height, int width, IplImage *bg)
{
	m_posy += m_diy;
	m_posx += m_dix;
	int b0 = CV_IMAGE_ELEM(bg,uchar,m_posy,m_posx*3+0);
	int g0 = CV_IMAGE_ELEM(bg,uchar,m_posy,m_posx*3+1);
    int r0 = CV_IMAGE_ELEM(bg,uchar,m_posy,m_posx*3+2);
	
	if (b0>40||g0>40||r0>40)  Removeupdata();
	
    int b1 = CV_IMAGE_ELEM(bg,uchar,m_posy+m_ditanke->height,m_posx*3+0);
	int g1 = CV_IMAGE_ELEM(bg,uchar,m_posy+m_ditanke->height,m_posx*3+1);
    int r1 = CV_IMAGE_ELEM(bg,uchar,m_posy+m_ditanke->height,m_posx*3+2);
	
	if (b1>40||g1>40||r1>40)
	{
		Removeupdata();
	}
	
	int b2 = CV_IMAGE_ELEM(bg,uchar,m_posy,(m_posx+m_ditanke->width)*3+0);
	int g2 = CV_IMAGE_ELEM(bg,uchar,m_posy,(m_posx+m_ditanke->width)*3+1);
    int r2 = CV_IMAGE_ELEM(bg,uchar,m_posy,(m_posx+m_ditanke->width)*3+2);
	
	if (b2>40||g2>40||r2>40)
	{
		Removeupdata();
	}
	
	int b3 = CV_IMAGE_ELEM(bg,uchar,m_posy+m_ditanke->height,(m_posx+m_ditanke->width)*3+0);
	int g3 = CV_IMAGE_ELEM(bg,uchar,m_posy+m_ditanke->height,(m_posx+m_ditanke->width)*3+1);
    int r3 = CV_IMAGE_ELEM(bg,uchar,m_posy+m_ditanke->height,(m_posx+m_ditanke->width)*3+2);
	
	if (b3>40||g3>40||r3>40)
	{
		Removeupdata();
	}
	
	if (m_posx>width-10-m_ditanke->width || m_posx<5 || m_posy< 5 || m_posy>height-15-m_ditanke->height)
	{
		Removeupdata();
	}
}

void CDiTanke::Removeupdata()
{
	m_posy -= m_diy;
	m_posx -= m_dix;
	int key;
	key = rand()%4 + 1;
	if (Pdirection == 0)
	{
		if (key == 1)
		{
			m_ditanke = m_ditankegray[2];
			m_dix = -2;
			m_diy = 0;
			count = 3;
		}
		else if (key == 2)
		{
			m_ditanke = m_ditankegray[3];
			m_dix = 0;
			m_diy = 2;
			count = 2;
		}
		else if (key == 3)
		{
			m_ditanke = m_ditankegray[0];
			m_dix = 0;
			m_diy = -2;
			count = 1;
		}
		else if (key == 4)
		{
			m_ditanke = m_ditankegray[1];
			m_dix = 2;
			m_diy = 0;
			count = 4;
		}
	}
	else if(Pdirection == 1)
	{
		if (key == 1)
		{
			m_ditanke = m_ditankebule[2];
			m_dix = -2;
			m_diy = 0;
			count = 3;
		}
		else if (key == 2)
		{
			m_ditanke = m_ditankebule[3];
			m_dix = 0;
			m_diy = 2;
			count = 2;
		}
		else if (key == 3)
		{
			m_ditanke = m_ditankebule[0];
			m_dix = 0;
			m_diy = -2;
			count = 1;
		}
		else if (key == 4)
		{
			m_ditanke = m_ditankebule[1];
			m_dix = 2;
			m_diy = 0;
			count = 4;
		}
	}
	else
	{
		if (key == 1)
		{
			m_ditanke = m_ditankegold[2];
			m_dix = -2;
			m_diy = 0;
			count = 3;
		}
		else if (key == 2)
		{
			m_ditanke = m_ditankegold[3];
			m_dix = 0;
			m_diy = 2;
			count = 2;
		}
		else if (key == 3)
		{
			m_ditanke = m_ditankegold[0];
			m_dix = 0;
			m_diy = -2;
			count = 1;
		}
		else if (key == 4)
		{
			m_ditanke = m_ditankegold[1];
			m_dix = 2;
			m_diy = 0;
			count = 4;
		}
	}
}

int CDiTanke::GetnowDTkposx()
{
	return m_posx;
}



int CDiTanke::GetnowDTkposy()
{
	return m_posy;
}


//DEL void CDiTanke::Updata()
//DEL {
//DEL 	m_timer += clock() - m_preTime;
//DEL 	m_preTime = clock();
//DEL }

void CDiTanke::Attack(CMange *manger)
{
	if(m_atk < m_timer)
	{
		m_timer = 0 ;
		if (Pdirection == 0)
		{
			switch (count)
			{
			case 1:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)/2, m_posy ,2*m_dix,2*m_diy,1,100,count);break;
			case 2:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)/2, m_posy + m_ditanke->height,2*m_dix,2*m_diy,1,100,count);break;
			case 3:manger->CreatBullet(m_bulletti,m_posx , m_posy + (m_ditanke->height+m_bulletti->width)/2,2*m_dix,2*m_diy,1,100,count);break;
			case 4:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width), m_posy + (m_ditanke->height+m_bulletti->width)/2,2*m_dix,2*m_diy,1,100,count);break;
			}
			
		}
		else if (Pdirection == 1)
		{
			switch (count)
			{
			case 1:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)/2, m_posy - m_ditanke->height/2,2*m_dix,2*m_diy,1,100,count);break;
			case 2:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)/2, m_posy + m_ditanke->height+ 30,2*m_dix,2*m_diy,1,100,count);break;
			case 3:manger->CreatBullet(m_bulletti,m_posx - (m_ditanke->width)/2, m_posy + (m_ditanke->height+m_bulletti->width)/2,2*m_dix,2*m_diy,1,100,count);break;
			case 4:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)+30, m_posy + (m_ditanke->height+m_bulletti->width)/2,2*m_dix,2*m_diy,1,100,count);break;
			}
			
		}
		else if (Pdirection == 2)
		{
			switch (count)
			{
			case 1:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)/2, m_posy - m_ditanke->height/2,2*m_dix,2*m_diy,1,100,count);break;
			case 2:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)/2, m_posy + m_ditanke->height+ 30,2*m_dix,2*m_diy,1,100,count);break;
			case 3:manger->CreatBullet(m_bulletti,m_posx - (m_ditanke->width)/2, m_posy + (m_ditanke->height+m_bulletti->width)/2,2*m_dix,2*m_diy,1,100,count);break;
			case 4:manger->CreatBullet(m_bulletti,m_posx + (m_ditanke->width-m_bulletti->width)+30, m_posy + (m_ditanke->height+m_bulletti->width)/2,2*m_dix,2*m_diy,1,100,count);break;
			}
			
		}
	}
	m_timer += clock()-m_preTime;
	m_preTime = clock();
}

IplImage * CDiTanke::GetnowImage()
{
	return m_ditanke;
}



bool CDiTanke::NeedClear()
{
	return m_Isclear;
}

void CDiTanke::TakeDamage()
{
	m_Isclear = true;
}
