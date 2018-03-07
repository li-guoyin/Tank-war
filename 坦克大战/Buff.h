// Buff.h: interface for the CBuff class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFF_H__C6CAED6F_A4D8_467D_B08D_310BF7E1AB0C__INCLUDED_)
#define AFX_BUFF_H__C6CAED6F_A4D8_467D_B08D_310BF7E1AB0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include <cv.h>
# include <highgui.h>

class CMange;
class CBuff  
{
public:
	void Rand();
	void InitTimer();
	void InitBuff();
	void Updata();
	void Appear();
	void Disappear();
	void Draw(IplImage *bg);
	int Getposy();
	int Getposx();
	bool GetBuffAppear();
	CBuff();
	virtual ~CBuff();
private:
	IplImage *f_buff;
	bool f_appear;
    int f_posx;
	int f_posy;

	int f_atkappear;
	int f_atkdisappear;
	int timer;
	int pretime;
};

#endif // !defined(AFX_BUFF_H__C6CAED6F_A4D8_467D_B08D_310BF7E1AB0C__INCLUDED_)
