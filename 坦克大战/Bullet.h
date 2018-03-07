// Bullet.h: interface for the CBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BULLET_H__6013E733_83B8_471E_A845_4DE8337AA8DB__INCLUDED_)
#define AFX_BULLET_H__6013E733_83B8_471E_A845_4DE8337AA8DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//# include "GameUI.h"
# include <cv.h>
# include <highgui.h>

class CBullet  
{
public:
	int GetAttack();
	IplImage * GetbulletImage();
	int Getposy();
	int Getposx();
	void NeedDestory();
	bool NeedClear();
	void Draw(IplImage * bg);
	void Move();
	CBullet(IplImage *img,int posx,int posy,int dix,int diy,int attack,int count);
	CBullet();
	virtual ~CBullet();
private:
	IplImage *bulletimg;
	int speed;              //子弹移动速度
	int b_posx; int b_posy; //子弹的位置
	int b_dix; int b_diy;   //子弹移动方向的控制
	int b_attack;           //子弹的攻击
	bool b_Isclear;         //子弹是否需要被清除
};

#endif // !defined(AFX_BULLET_H__6013E733_83B8_471E_A845_4DE8337AA8DB__INCLUDED_)
