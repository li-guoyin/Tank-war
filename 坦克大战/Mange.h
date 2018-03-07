// Mange.h: interface for the CMange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANGE_H__0DEFFD16_F564_4A94_8ABD_A04E2EFE0952__INCLUDED_)
#define AFX_MANGE_H__0DEFFD16_F564_4A94_8ABD_A04E2EFE0952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

# include "GameUI.h"
# include "Tanke.h"
# include "DiTanke.h"
# include "InitResource.h"
# include "Bullet.h"
# include "BoomEffect.h"
# include "StartUI.h"
# include "EndUI.h"
# include "Buff.h"
# include <vector>
using namespace std;

class CMange  
{
public:
	int GetNowGrade();
	void End();
	void Start();
	void DestoryWall(int posx,int posy,int count,IplImage *bg);
	void DidestoryWall(int posx,int posy,IplImage *bg);
	void BuffCrash();
	void ThCrash();         //��ײ����
	void GameRrsourceRelease();
	void GameRrsourceInit();
	void BulletDraw();      //ȫ���ӵ��Ļ滭
	void BulletClear();     //ȫ���ӵ������
	void BulletMove();      //ȫ���ӵ����ƶ�
	void CreatBullet(IplImage *img, int posx, int posy, int dix, int diy,int type,int atk,int count); //�����ӵ� type���ж�����
	void AddEnemyTanke();   //���ӵз�̹��
	void GameRunInit();     //��ʼ����Ϸ
	void BulletUpdata();    //�ӵ�����
	void DiTankeupdata();   //�з�̹�˸���
	void Tankeupdata();     //�ҷ�̹�˸���
	void EffectUpdate();    //��Ч����
	void Run(); 
	CMange();
	virtual ~CMange();
	enum GameState {  GameStart,GameRunning,GameEnd  };//ö�����ͣ���ʼ ���� ����
private:
	GameState m_state;  //ִ����Ϸ���̵�����
	CStartUI startui;
	CEndUI endui;
	CGameUI gameui;
	CInitResource m_gamersc;
	CBuff m_buff;
	CTanke Tanke;
	vector<CDiTanke*>m_enemyDitanke;  //�з�̹��������
	vector<CBullet*>  m_bullets;       //�ҷ��ӵ�������
	vector<CBullet*>  m_enemybullets;  //�з��ӵ�������
	vector<CBoomEffect*> m_boomeffect;
	IplImage *imgbg;    //��ʼ��ͼ��
	IplImage *Didestorywall;
	IplImage *destorywall;//�ڿ��
	int controlnumber;  //�����������̹�ˣ�
	int number;         //����̹�˵���������
	int gradescore;
	int flag;
	bool gameover;
};

#endif // !defined(AFX_MANGE_H__0DEFFD16_F564_4A94_8ABD_A04E2EFE0952__INCLUDED_)
