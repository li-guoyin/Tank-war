// GameUI.h: interface for the CGameUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEUI_H__3FE312F8_DBBE_4E83_A4EE_5D66728A989E__INCLUDED_)
#define AFX_GAMEUI_H__3FE312F8_DBBE_4E83_A4EE_5D66728A989E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include <cv.h>
# include <highgui.h>
class CGameUI  
{
public:
	void GameUIInit();
	void Drawgrass();
	void Build();
	IplImage * GetbgcloneImage();
	IplImage * GetnowImage();
	void ShowImage();
	void Setimage(IplImage *bgimg);
	CGameUI();
	virtual ~CGameUI();
private:
	IplImage *bg;
	IplImage *bgclone;
	IplImage *bgclone1;
	IplImage *grass;

};

#endif // !defined(AFX_GAMEUI_H__3FE312F8_DBBE_4E83_A4EE_5D66728A989E__INCLUDED_)
