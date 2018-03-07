// Mange.cpp: implementation of the CMange class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mange.h"
# include <stdio.h>
# include <time.h>
//# include "Timer.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMange::CMange()
{
	imgbg = cvLoadImage(".\\resource\\map\\map02.jpg");
	destorywall = cvLoadImage(".\\resource\\map\\destorywall.png");
	Didestorywall = cvLoadImage(".\\resource\\map\\destorywall1.png");
	cvNamedWindow("坦克大战");
	gameui.Setimage(imgbg);
	controlnumber = 0;
	number = 0;
	gradescore = 0;
	flag = 0;
	gameover = false;
	Start();
}

CMange::~CMange()
{
	cvReleaseImage(&imgbg);
	cvReleaseImage(&destorywall);
	cvReleaseImage(&Didestorywall);
	cvDestroyWindow("坦克大战");
}

void CMange::Run()
{
	
	while(1)
	{
		cvWaitKey(20);
		switch(m_state)
		{
		case GameState::GameStart:
			//PlaySound(TEXT(".\\resource\\music\\start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);// 重复播放
			PlaySound(TEXT(".\\resource\\music\\start.wav"), NULL, SND_FILENAME | SND_ASYNC); //只播放一次
			startui.Build();
			startui.Draw();
			startui.ShowstartImg();
			if (GetAsyncKeyState('H') & 0x8000)
			{
				PlaySound(TEXT(".\\resource\\music\\anjian.wav"), NULL, SND_FILENAME | SND_ASYNC);
				GameRunInit();
			}
			if(GetAsyncKeyState(VK_ESCAPE) & 0x8000) 
			{
				return;
			}
			break;
		case GameState::GameRunning:
			if (number <= 7)
			{
				controlnumber = (controlnumber++)%300;
			}
			if (controlnumber % 70 == 0 && number <= 7)
			{
				AddEnemyTanke();
			}
			if (GetAsyncKeyState(' ') & 0x8000)
			{
				PlaySound(TEXT(".\\resource\\music\\zantin.wav"), NULL, SND_FILENAME | SND_ASYNC);
				cvWaitKey(0);
			}
			gameui.Build();
			DiTankeupdata();
			Tankeupdata();
			BulletUpdata();
			EffectUpdate();
			ThCrash();
			BuffCrash();
			if (Tanke.NeedClear() == false || gameover == true)
			{
				PlaySound(TEXT(".\\resource\\music\\gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
				End();
			}
			gameui.Drawgrass();
			gameui.ShowImage();break;
		case GameState::GameEnd:
			endui.ShowImage(this);
			if(GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				Start();
				number = 0;
				gradescore = 0;
				gameover = false;
			}
			if(GetAsyncKeyState(VK_ESCAPE) & 0x8000) 
			{
				return ;
			}break;		
		}	
	}
}

void CMange::Tankeupdata()
{
	IplImage *temp = gameui.GetnowImage();
	
	Tanke.Move(temp->height,temp->width,temp);
	Tanke.Draw(temp);
	Tanke.Attack(this);

}

void CMange::DiTankeupdata()  //敌方坦克更新
{
	int i;
	IplImage *temp1 = gameui.GetnowImage();
	for (i=0;i<m_enemyDitanke.size();i++)
	{
		m_enemyDitanke[i]->Move(temp1->height,temp1->width,temp1);
	}
	for(i=0;i<m_enemyDitanke.size();i++)
	{
		m_enemyDitanke[i]->Draw(temp1);
	}
	for (i=0;i<m_enemyDitanke.size();i++)
	{
		m_enemyDitanke[i]->Attack(this);
	}
	for(i=0;i<m_enemyDitanke.size();i++)
	{
		if (m_enemyDitanke[i]->NeedClear() == true)
		{
			m_boomeffect.push_back(new CBoomEffect(m_enemyDitanke[i]->GetnowDTkposx(),m_enemyDitanke[i]->GetnowDTkposy()));
			m_enemyDitanke.erase(m_enemyDitanke.begin() + i);
		}
	}
}

void CMange::GameRunInit()  //游戏初始化
{
	int i;
	m_state = GameState::GameRunning;
	//初始化敌方坦克
	for (i=0;i<m_enemyDitanke.size();i++)
		delete m_enemyDitanke[i];
	m_enemyDitanke.clear();

	//初始化子弹
	for (i=0;i<m_bullets.size();i++)  delete m_bullets[i];  //我方子弹
	for (i=0;i<m_enemybullets.size();i++)  delete m_enemybullets[i];  //敌方子弹
	m_bullets.clear();
	m_enemybullets.clear();

	//初始化效果
	for (i=0;i<m_boomeffect.size();i++)
		delete m_boomeffect[i];
	m_boomeffect.clear();

	//初始化我方飞机
	Tanke.InitMyTk();
	//初始化地图
	gameui.GameUIInit();
	//初始化buff
	m_buff.InitBuff();
	//
	endui.InitEndUI();
}

void CMange::AddEnemyTanke()
{
	m_enemyDitanke.push_back(new CDiTanke(m_gamersc.ditankegray,m_gamersc.ditankebule,m_gamersc.ditankegold,m_gamersc.zidan));
	number ++;
}

void CMange::CreatBullet(IplImage *img, int posx, int posy, int dix, int diy, int type, int atk,int count)
{
	if (type == 0)  //等于0时 创建我方子弹
	{
		m_bullets.push_back(new CBullet(img,posx,posy,dix,diy,atk,count));
	}
	else  m_enemybullets.push_back(new CBullet(img,posx,posy,dix,diy,atk,count));
}

void CMange::BulletMove()
{
	int i;
	for (i=0;i<m_bullets.size();i++)  
		m_bullets[i]->Move();
	for (i=0;i<m_enemybullets.size();i++)  
		m_enemybullets[i]->Move();
}

void CMange::BulletClear()
{
	int i;
	for (i=0;i<m_bullets.size();i++ )
	{
		if (m_bullets[i]->NeedClear() == true)
		{
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin()+i);
		}
	}
	for (i=0;i<m_enemybullets.size();i++ )
	{
		if (m_enemybullets[i]->NeedClear() == true)
		{
			delete m_enemybullets[i];
			m_enemybullets.erase(m_enemybullets.begin()+i);
		}
	}
}

void CMange::BulletDraw()
{
	int i;
	for (i=0;i<m_bullets.size();i++) 
		m_bullets[i]->Draw(gameui.GetnowImage());
	for (i=0;i<m_enemybullets.size();i++) 
		m_enemybullets[i]->Draw(gameui.GetnowImage());
}

void CMange::GameRrsourceInit()
{
	m_gamersc.InitResourceImage();
	Tanke.SetImageInit(m_gamersc.mytanke,m_gamersc.zidan);
	for (int i=0;i<m_enemyDitanke.size();i++)  //敌方坦克容器传参数
	{
		m_enemyDitanke.push_back(new CDiTanke(m_gamersc.ditankegray,m_gamersc.ditankebule,m_gamersc.ditankegold,m_gamersc.zidan));
	}
}

void CMange::GameRrsourceRelease()
{
	m_gamersc.ReleaseResource();
}

void CMange::BulletUpdata()
{
	BulletMove();
	BulletDraw();
	BulletClear();
}

void CMange::ThCrash()
{
	int i,j;

	//我方子弹与敌方子弹的碰撞检测.

	for (i=0 ; i< m_enemybullets.size() ; i++)
	{
		int px1 = m_enemybullets[i]->Getposx() + m_enemybullets[i]->GetbulletImage()->width/2;
		int py1 = m_enemybullets[i]->Getposy() + m_enemybullets[i]->GetbulletImage()->height/2;
		for (j=0 ; j< m_bullets.size() ; j++)
		{
			int px2 = m_bullets[j]->Getposx() + m_bullets[j]->GetbulletImage()->width/2;
			int py2 = m_bullets[j]->Getposy() + m_bullets[j]->GetbulletImage()->height/2;

			if (abs(px2 - px1) < m_enemybullets[i]->GetbulletImage()->width/2 + m_bullets[j]->GetbulletImage()->width/2 &&
				abs(py1 - py2) < m_enemybullets[i]->GetbulletImage()->height/2 + m_bullets[j]->GetbulletImage()->height/2)
			{
				m_bullets[j]->NeedDestory();
				m_enemybullets[i]->NeedDestory();
				break;
			}
		}
	}

	//我方子弹与敌方坦克碰撞

	for (i=0 ;i < m_bullets.size() ; i++)
	{
		int px1 = m_bullets[i]->Getposx() + m_bullets[i]->GetbulletImage()->width/2;
		int py1 = m_bullets[i]->Getposy() + m_bullets[i]->GetbulletImage()->height/2;
		for (j=0;j < m_enemyDitanke.size() ; j++)
		{
			int px2 = m_enemyDitanke[j]->GetnowDTkposx() + m_enemyDitanke[j]->GetnowImage()->width/2;
			int py2 = m_enemyDitanke[j]->GetnowDTkposy() + m_enemyDitanke[j]->GetnowImage()->height/2;
			if (abs(px2 - px1) < m_bullets[i]->GetbulletImage()->width/2 + m_enemyDitanke[j]->GetnowImage()->width/2 &&
				abs(py2 - py1) < m_bullets[i]->GetbulletImage()->height/2 + m_enemyDitanke[j]->GetnowImage()->height/2)
			{
				m_enemyDitanke[j]->TakeDamage();
				PlaySound(TEXT(".\\resource\\music\\blast.wav"), NULL, SND_FILENAME | SND_ASYNC);
				number -= 1;
				gradescore = gradescore + 50;
				m_bullets.erase(m_bullets.begin()+i );
				break;
			}
		}
	}

	//敌方子弹与我方坦克相碰撞

	for (i=0 ; i<m_enemybullets.size() ; i++)
	{
		int px1 = m_enemybullets[i]->Getposx() + m_enemybullets[i]->GetbulletImage()->width/2;
		int py1 = m_enemybullets[i]->Getposy() + m_enemybullets[i]->GetbulletImage()->height/2;
		
		    int px2 = Tanke.Getnowposx() + Tanke.GetnowMytkImg()->width/2;
		    int py2 = Tanke.Getnowposy() + Tanke.GetnowMytkImg()->height/2;
		if (abs(px2 - px1) < m_enemybullets[i]->GetbulletImage()->width/2 + Tanke.GetnowMytkImg()->width/2 &&
			abs(py2 - py1) < m_enemybullets[i]->GetbulletImage()->height/2 + Tanke.GetnowMytkImg()->height/2)
		{
			Tanke.TakeDamage();
			//PlaySound(TEXT(".\\resource\\music\\blast.wav"), NULL, SND_FILENAME | SND_ASYNC);
			m_enemybullets.erase(m_enemybullets.begin() + i);
		}
	}

	//敌方坦克与我方坦克碰撞

	for (i=0 ; i<m_enemyDitanke.size() ; i++)
	{
		int px1 = m_enemyDitanke[i]->GetnowDTkposx() + m_enemyDitanke[i]->GetnowImage()->width/2;
		int py1 = m_enemyDitanke[i]->GetnowDTkposy() + m_enemyDitanke[i]->GetnowImage()->height/2;

		int px2 = Tanke.Getnowposx() + Tanke.GetnowMytkImg()->width/2;
		int py2 = Tanke.Getnowposy() + Tanke.GetnowMytkImg()->height/2; 
		if (abs(px2 - px1) <10+ m_enemyDitanke[i]->GetnowImage()->width/2 + Tanke.GetnowMytkImg()->width/2 &&
			abs(py2 - py1) <10+m_enemyDitanke[i]->GetnowImage()->height/2 + Tanke.GetnowMytkImg()->height/2)
		{
			m_enemyDitanke[i]->Removeupdata();
		}
	}

	//敌方坦克与敌方坦克碰撞

	/*for (i=0; i<m_enemyDitanke.size() ; i++)
	{
		int px1 = m_enemyDitanke[i]->GetnowDTkposx() + m_enemyDitanke[i]->GetnowImage()->width/2;
		int py1 = m_enemyDitanke[i]->GetnowDTkposy() + m_enemyDitanke[i]->GetnowImage()->height/2;
		for (j=0 ;j<m_enemyDitanke.size() ; j++)
		{
			int px2 = m_enemyDitanke[j]->GetnowDTkposx() + m_enemyDitanke[j]->GetnowImage()->width/2;
		    int py2 = m_enemyDitanke[j]->GetnowDTkposy() + m_enemyDitanke[j]->GetnowImage()->height/2;
			if(i == j)  continue;
			if (abs(px2 - px1) < m_enemyDitanke[i]->GetnowImage()->width/2 + m_enemyDitanke[j]->GetnowImage()->width/2  &&
				abs(py2 - py1) < m_enemyDitanke[i]->GetnowImage()->height/2 + m_enemyDitanke[j]->GetnowImage()->height/2 )
			{
				m_enemyDitanke[i]->Removeupdata();
				break;
			}
		}
	}*/

	//我方子弹与墙体相碰撞
	for (i=0 ; i<m_bullets.size() ; i++)
	{
		IplImage *temp;
		temp = gameui.GetbgcloneImage();
		int px = m_bullets[i]->Getposx(); //+ m_bullets[i]->GetbulletImage()->width/2;
		int py = m_bullets[i]->Getposy(); // + m_bullets[i]->GetbulletImage()->height/2;
		//左上角像素
		int b0 = CV_IMAGE_ELEM(temp,uchar,py,px*3+0);
		int g0 = CV_IMAGE_ELEM(temp,uchar,py,px*3+1);
		int r0 = CV_IMAGE_ELEM(temp,uchar,py,px*3+2);

		//右上角像素
		int b1 = CV_IMAGE_ELEM(temp,uchar,py,(px + m_bullets[i]->GetbulletImage()->width)*3+0);
		int g1 = CV_IMAGE_ELEM(temp,uchar,py,(px + m_bullets[i]->GetbulletImage()->width)*3+1);
		int r1 = CV_IMAGE_ELEM(temp,uchar,py,(px + m_bullets[i]->GetbulletImage()->width)*3+2);

		//左下角像素
		int b2 = CV_IMAGE_ELEM(temp,uchar,(py + m_bullets[i]->GetbulletImage()->height),px*3+0);
		int g2 = CV_IMAGE_ELEM(temp,uchar,(py + m_bullets[i]->GetbulletImage()->height),px*3+1);
		int r2 = CV_IMAGE_ELEM(temp,uchar,(py + m_bullets[i]->GetbulletImage()->height),px*3+2);

		//右下角像素
		int b3 = CV_IMAGE_ELEM(temp,uchar,(py + m_bullets[i]->GetbulletImage()->height),(px + m_bullets[i]->GetbulletImage()->width)*3+0);
		int g3 = CV_IMAGE_ELEM(temp,uchar,(py + m_bullets[i]->GetbulletImage()->height),(px + m_bullets[i]->GetbulletImage()->width)*3+1);
		int r3 = CV_IMAGE_ELEM(temp,uchar,(py + m_bullets[i]->GetbulletImage()->height),(px + m_bullets[i]->GetbulletImage()->width)*3+2);
		if(px<1) px = px + 60;
		if(py<1) py = py + 60;
		if(px>890)  px = px - 80;
		//if(py>890)  py = py - 80;
		if (b0>100 || g0>100 || r0>100 ||b1>100 || g1>100 || r1>100 || b2>100 || g2>100 || r2>100 || b3>100 || g3>100 || r3>100)
		{
			PlaySound(TEXT(".\\resource\\music\\hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
			m_bullets[i]->NeedDestory();
		}
		if (b0>40&&b0<180 || g0>40&&g0<180 || r0>40&&r0<180)
		{
			DestoryWall(px,py,Tanke.GetnowCount(),temp);
			m_bullets[i]->NeedDestory();
			m_bullets.erase(m_bullets.begin() + i);
			
		}
		else if (b1>40&&b1<180 || g1>40&&g1<180 || r1>40&&r1<180)
		{
			DestoryWall(px ,py,Tanke.GetnowCount(),temp);//+ m_bullets[i]->GetbulletImage()->width
			m_bullets[i]->NeedDestory();
			m_bullets.erase(m_bullets.begin() + i);
		}
		else if (b2>40&&b2<180 || g2>40&&g2<180 || r2>40&&r2<180)
		{
			DestoryWall(px,py ,Tanke.GetnowCount(),temp);//+ m_bullets[i]->GetbulletImage()->height
			m_bullets[i]->NeedDestory();
			m_bullets.erase(m_bullets.begin() + i);
		}
		else if(b3>40&&b3<180 || g3>40&&g3<180 || r3>40&&r3<180)	
		{
			DestoryWall(px ,py + m_bullets[i]->GetbulletImage()->height,Tanke.GetnowCount(),temp);//+ m_bullets[i]->GetbulletImage()->width
			m_bullets[i]->NeedDestory();
			m_bullets.erase(m_bullets.begin() + i);
		}
	}

	//敌方子弹与墙碰撞
	for (i=0;i<m_enemybullets.size();i++)
	{
		IplImage *temp;
		temp = gameui.GetbgcloneImage();
		int px = m_enemybullets[i]->Getposx(); 
		int py = m_enemybullets[i]->Getposy(); 
		//左上角像素
		int b0 = CV_IMAGE_ELEM(temp,uchar,py,px*3+0);
		int g0 = CV_IMAGE_ELEM(temp,uchar,py,px*3+1);
		int r0 = CV_IMAGE_ELEM(temp,uchar,py,px*3+2);
		
		//右上角像素
		int b1 = CV_IMAGE_ELEM(temp,uchar,py,(px + m_enemybullets[i]->GetbulletImage()->width)*3+0);
		int g1 = CV_IMAGE_ELEM(temp,uchar,py,(px + m_enemybullets[i]->GetbulletImage()->width)*3+1);
		int r1 = CV_IMAGE_ELEM(temp,uchar,py,(px + m_enemybullets[i]->GetbulletImage()->width)*3+2);
		
		//左下角像素
		int b2 = CV_IMAGE_ELEM(temp,uchar,(py + m_enemybullets[i]->GetbulletImage()->height),px*3+0);
		int g2 = CV_IMAGE_ELEM(temp,uchar,(py + m_enemybullets[i]->GetbulletImage()->height),px*3+1);
		int r2 = CV_IMAGE_ELEM(temp,uchar,(py + m_enemybullets[i]->GetbulletImage()->height),px*3+2);
		
		//右下角像素
		int b3 = CV_IMAGE_ELEM(temp,uchar,(py + m_enemybullets[i]->GetbulletImage()->height),(px + m_enemybullets[i]->GetbulletImage()->width)*3+0);
		int g3 = CV_IMAGE_ELEM(temp,uchar,(py + m_enemybullets[i]->GetbulletImage()->height),(px + m_enemybullets[i]->GetbulletImage()->width)*3+1);
		int r3 = CV_IMAGE_ELEM(temp,uchar,(py + m_enemybullets[i]->GetbulletImage()->height),(px + m_enemybullets[i]->GetbulletImage()->width)*3+2);
		
		if(px<1) px = px + 60;
		if(py<1) py = py + 60;
		if(px>850)  px = px - 30;
		if(py>850)  py = py - 30;
		if (b0>100 || g0>100 || r0>100 ||b1>100 || g1>100 || r1>100 || b2>100 || g2>100 || r2>100 || b3>100 || g3>100 || r3>100)
		{
			m_enemybullets[i]->NeedDestory();
		}
		if (b0>40&&b0<100 || g0>40&&g0<100 || r0>40&&r0<100)
		{
			DidestoryWall(px + m_enemybullets[i]->GetbulletImage()->width/2,py + m_enemybullets[i]->GetbulletImage()->height/2,temp);
			m_enemybullets[i]->NeedDestory();
			m_enemybullets.erase(m_enemybullets.begin() + i);
			
		}
		else if (b1>40&&b1<100 || g1>40&&g1<100 || r1>40&&r1<100)
		{
			DidestoryWall(px + m_enemybullets[i]->GetbulletImage()->width/2 ,py + m_enemybullets[i]->GetbulletImage()->height/2,temp);
			m_enemybullets[i]->NeedDestory();
			m_enemybullets.erase(m_enemybullets.begin() + i);
		}
		else if (b2>40&&b2<100 || g2>40&&g2<100 || r2>40&&r2<100)
		{
			DidestoryWall(px + m_enemybullets[i]->GetbulletImage()->width/2,py + m_enemybullets[i]->GetbulletImage()->height/2 ,temp);
			m_enemybullets[i]->NeedDestory();
			m_enemybullets.erase(m_enemybullets.begin() + i);
		}
		else if(b3>40&&b3<100 || g3>40&&g3<100 || r3>40&&r3<100)	
		{
			DidestoryWall(px + m_enemybullets[i]->GetbulletImage()->width/2 ,py + m_enemybullets[i]->GetbulletImage()->height/2,temp);
			m_enemybullets[i]->NeedDestory();
			m_enemybullets.erase(m_enemybullets.begin() + i);
		}
	}

	//di方子弹与老鬼相碰撞

	for (i=0 ; i<m_enemybullets.size() ; i++)
	{
		int px = m_enemybullets[i]->Getposx() + m_enemybullets[i]->GetbulletImage()->width/2;
		int py = m_enemybullets[i]->Getposy() + m_enemybullets[i]->GetbulletImage()->height/2;

		if ((px > 400 && px <500) && (py >810 && py<890))
		{
			gameover = true;
		}
	}

	//wo方子弹与老鬼相碰撞

	for (i=0 ; i<m_bullets.size() ; i++)
	{
		int px = m_bullets[i]->Getposx() + m_bullets[i]->GetbulletImage()->width/2;
		int py = m_bullets[i]->Getposy() + m_bullets[i]->GetbulletImage()->height/2;
		if ((px > 400 && px <500) && (py >810 && py<890))
		{
			gameover = true;
		}
	}

}

void CMange::DestoryWall(int posx, int posy,int count,IplImage *bg)
{
	for (int i=0 ; i<destorywall->height ; i++)
	{
		for (int j=0 ; j<destorywall->width ; j++)
		{
			int b = CV_IMAGE_ELEM(destorywall,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(destorywall,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(destorywall,uchar,i,j*3+2);

			switch (count)
			{
			case 1:
				CV_IMAGE_ELEM(bg,uchar,i+posy-15,(j+posx-25)*3+0) = b;
				CV_IMAGE_ELEM(bg,uchar,i+posy-15,(j+posx-25)*3+1) = g;
				CV_IMAGE_ELEM(bg,uchar,i+posy-15,(j+posx-25)*3+2) = r;break;
			case 2:
				if(posy > 890) posy = posy - 10;
				CV_IMAGE_ELEM(bg,uchar,i+posy-40,(j+posx-25)*3+0) = b;
				CV_IMAGE_ELEM(bg,uchar,i+posy-40,(j+posx-25)*3+1) = g;
				CV_IMAGE_ELEM(bg,uchar,i+posy-40,(j+posx-25)*3+2) = r;break;
			case 3:
				CV_IMAGE_ELEM(bg,uchar,i+posy-35,(j+posx-15)*3+0) = b;
				CV_IMAGE_ELEM(bg,uchar,i+posy-35,(j+posx-15)*3+1) = g;
				CV_IMAGE_ELEM(bg,uchar,i+posy-35,(j+posx-15)*3+2) = r;break;
			case 4:
				CV_IMAGE_ELEM(bg,uchar,i+posy-35,(j+posx-20)*3+0) = b;
				CV_IMAGE_ELEM(bg,uchar,i+posy-35,(j+posx-20)*3+1) = g;
				CV_IMAGE_ELEM(bg,uchar,i+posy-35,(j+posx-20)*3+2) = r;break;
			}
		}
	}
}

void CMange::EffectUpdate()
{
	int i;
	for (i=0;i<m_boomeffect.size();i++)
	{
		m_boomeffect[i]->Draw(gameui.GetnowImage());
	}
	for (i=0;i<m_boomeffect.size();i++)
	{
		if (m_boomeffect[i]->NeedClear() == true)
		{
			delete m_boomeffect[i];
			m_boomeffect.erase(m_boomeffect.begin() + i);
		}
	}
}

void CMange::Start()
{
	m_state = GameState::GameStart;
}

void CMange::End()
{
	m_state = GameState::GameEnd;
}

void CMange::DidestoryWall(int posx, int posy, IplImage *bg)
{
	for (int i=0 ; i<Didestorywall->height ; i++)
	{
		for (int j=0 ; j<Didestorywall->width ; j++)
		{
			int b = CV_IMAGE_ELEM(Didestorywall,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(Didestorywall,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(Didestorywall,uchar,i,j*3+2);
			if(posx > 865) posx = posx - 30;
			if(posy > 865) posy = posy - 30;
			if(posx < 5 )  posx = posx + 30;
			if(posy < 5 )  posy = posy + 30;
			CV_IMAGE_ELEM(bg,uchar,i+posy-10,(j+posx-10)*3+0) = b;
			CV_IMAGE_ELEM(bg,uchar,i+posy-10,(j+posx-10)*3+1) = g;
			CV_IMAGE_ELEM(bg,uchar,i+posy-10,(j+posx-10)*3+2) = r;
		}
	}
}

int CMange::GetNowGrade()  //返回分数
{
	return gradescore;
}

void CMange::BuffCrash()
{
	IplImage *temp = gameui.GetnowImage();
	m_buff.Updata();
	m_buff.Draw(temp);
	if (m_buff.GetBuffAppear() == true)
	{
		int px = m_buff.Getposx();
		int py = m_buff.Getposy();
		int px1 = Tanke.Getnowposx() + Tanke.GetnowMytkImg()->width/2;
		int py1 = Tanke.Getnowposy() + Tanke.GetnowMytkImg()->height/2;
 		if ((px1 > px && px1< px + 50) && (py1 > py && py1 < py + 50))
		{
			PlaySound(TEXT(".\\resource\\music\\add.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gradescore += 200;
			m_buff.Disappear();
			m_buff.InitTimer();
			m_buff.Rand();
		}
	}
}

