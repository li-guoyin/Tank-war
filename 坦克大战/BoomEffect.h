// BoomEffect.h: interface for the CBoomEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOMEFFECT_H__791691A8_2B83_4A9A_8862_ECC2B5CF00F4__INCLUDED_)
#define AFX_BOOMEFFECT_H__791691A8_2B83_4A9A_8862_ECC2B5CF00F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include <cv.h>
# include <highgui.h>

class CBoomEffect  
{
public:
	bool NeedClear();
	void Draw(IplImage *bg);
	CBoomEffect(int posx,int posy);
	CBoomEffect();
	virtual ~CBoomEffect();
private:
	IplImage *boomti;
	IplImage *boomEffect[8];
	IplImage *e_boomEffectti;
	int e_speed;       //图片更换速度
	int e_index;       //计数
	int e_posx;
	int e_posy;
	bool e_Isclear;

};

#endif // !defined(AFX_BOOMEFFECT_H__791691A8_2B83_4A9A_8862_ECC2B5CF00F4__INCLUDED_)
