// Tanke.h: interface for the CTanke class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TANKE_H__7A54D91C_21D1_4CF5_9707_87827D5F147C__INCLUDED_)
#define AFX_TANKE_H__7A54D91C_21D1_4CF5_9707_87827D5F147C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include <cv.h>
# include <highgui.h>
# include "Bullet.h"

class CMange;
class CTanke  
{
public:
	void InitMyTk();
	void RepeatLive();
	int GetnowCount();
	void TakeDamage();
	bool NeedClear();
	int Getnowposy();
	int Getnowposx();
	IplImage * GetnowMytkImg();
	void SetImageInit(IplImage * pImg[],IplImage *pImagezidan[]);
	void Attack(CMange *manger);
	void Move(int hight,int width,IplImage *bg);
	void Draw(IplImage *bg);
	CTanke();
	virtual ~CTanke();
private:
	CBullet bullt;
	IplImage *tanketi;
	IplImage *bulletti;
	IplImage *tanke[4];  // 坦克图片
	IplImage *bullet[3]; // 子弹图片
	int posx;
	int posy;         // 坦克坐标 
	int dix;
	int diy;          //哪个方向位移
	int speed;
	int count;        // 判断方向打的标记

	bool IsLive;      //判断我方坦克是否活着

	int attack;       //攻击强度
	int d_atk;        //攻击冷却
	int timer;        //计时器
	int preTime;      //上一帧的时间
};

#endif // !defined(AFX_TANKE_H__7A54D91C_21D1_4CF5_9707_87827D5F147C__INCLUDED_)
