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
	IplImage *tanke[4];  // ̹��ͼƬ
	IplImage *bullet[3]; // �ӵ�ͼƬ
	int posx;
	int posy;         // ̹������ 
	int dix;
	int diy;          //�ĸ�����λ��
	int speed;
	int count;        // �жϷ����ı��

	bool IsLive;      //�ж��ҷ�̹���Ƿ����

	int attack;       //����ǿ��
	int d_atk;        //������ȴ
	int timer;        //��ʱ��
	int preTime;      //��һ֡��ʱ��
};

#endif // !defined(AFX_TANKE_H__7A54D91C_21D1_4CF5_9707_87827D5F147C__INCLUDED_)
