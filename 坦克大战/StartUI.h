// StartUI.h: interface for the CStartUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STARTUI_H__EF53C7EB_D17B_4F19_A14B_1D27B275BBD6__INCLUDED_)
#define AFX_STARTUI_H__EF53C7EB_D17B_4F19_A14B_1D27B275BBD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include <cv.h>
# include <highgui.h>
class CStartUI  
{
public:
	void Build();
	void ShowstartImg();
	void Draw();
	CStartUI();
	virtual ~CStartUI();
private:
	IplImage *startImg;
	IplImage *startImgclone;
	IplImage *chooseImg;
	int posx;
	int posy;
};

#endif // !defined(AFX_STARTUI_H__EF53C7EB_D17B_4F19_A14B_1D27B275BBD6__INCLUDED_)
