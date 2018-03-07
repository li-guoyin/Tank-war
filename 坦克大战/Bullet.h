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
	int speed;              //�ӵ��ƶ��ٶ�
	int b_posx; int b_posy; //�ӵ���λ��
	int b_dix; int b_diy;   //�ӵ��ƶ�����Ŀ���
	int b_attack;           //�ӵ��Ĺ���
	bool b_Isclear;         //�ӵ��Ƿ���Ҫ�����
};

#endif // !defined(AFX_BULLET_H__6013E733_83B8_471E_A845_4DE8337AA8DB__INCLUDED_)
