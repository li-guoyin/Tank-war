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
	void ThCrash();         //碰撞函数
	void GameRrsourceRelease();
	void GameRrsourceInit();
	void BulletDraw();      //全部子弹的绘画
	void BulletClear();     //全部子弹的清除
	void BulletMove();      //全部子弹的移动
	void CreatBullet(IplImage *img, int posx, int posy, int dix, int diy,int type,int atk,int count); //创建子弹 type是判断类型
	void AddEnemyTanke();   //增加敌方坦克
	void GameRunInit();     //初始化游戏
	void BulletUpdata();    //子弹更新
	void DiTankeupdata();   //敌方坦克更新
	void Tankeupdata();     //我方坦克更新
	void EffectUpdate();    //特效更新
	void Run(); 
	CMange();
	virtual ~CMange();
	enum GameState {  GameStart,GameRunning,GameEnd  };//枚举类型，开始 运行 结束
private:
	GameState m_state;  //执行游戏进程的条件
	CStartUI startui;
	CEndUI endui;
	CGameUI gameui;
	CInitResource m_gamersc;
	CBuff m_buff;
	CTanke Tanke;
	vector<CDiTanke*>m_enemyDitanke;  //敌方坦克容器；
	vector<CBullet*>  m_bullets;       //我方子弹容器；
	vector<CBullet*>  m_enemybullets;  //敌方子弹容器；
	vector<CBoomEffect*> m_boomeffect;
	IplImage *imgbg;    //初始地图；
	IplImage *Didestorywall;
	IplImage *destorywall;//黑块儿
	int controlnumber;  //用来随机产生坦克；
	int number;         //控制坦克的总数量；
	int gradescore;
	int flag;
	bool gameover;
};

#endif // !defined(AFX_MANGE_H__0DEFFD16_F564_4A94_8ABD_A04E2EFE0952__INCLUDED_)
