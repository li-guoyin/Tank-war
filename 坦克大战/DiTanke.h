// DiTanke.h: interface for the CDiTanke class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DITANKE_H__45EFCB05_6AA0_45AF_AF28_1CA75F997EE5__INCLUDED_)
#define AFX_DITANKE_H__45EFCB05_6AA0_45AF_AF28_1CA75F997EE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include "cv.h"
# include "highgui.h"

class CMange;

class CDiTanke  
{
public:
	void TakeDamage();
	bool NeedClear();
	CDiTanke(IplImage *pImagegray[],IplImage *pImagebule[],IplImage *pImagegold[],IplImage *pImagebullet[]);
	IplImage * GetnowImage();
	void Attack(CMange *manger);
	int GetnowDTkposy();
	int GetnowDTkposx();
	void Removeupdata();
	void Move(int height,int width,IplImage *bg);
	void Draw(IplImage * bg);
	CDiTanke();
	virtual ~CDiTanke();
private:
	//static IplImage *m_enemybullet;
	IplImage *m_ditanke;
	IplImage *m_bulletti;
	IplImage *m_bullet[3];
	IplImage *m_ditankegray[4];
	IplImage *m_ditankebule[4];
	IplImage *m_ditankegold[4];
	int m_posx;
	int m_posy;
	int m_dix;
	int m_diy;
	int Pdirection;   //判断坦克类型
	bool m_Isclear;

	int count;       //控制子弹方向
	int m_timer;
	int m_preTime;
	int m_atk;       //时间间隔

};

#endif // !defined(AFX_DITANKE_H__45EFCB05_6AA0_45AF_AF28_1CA75F997EE5__INCLUDED_)
