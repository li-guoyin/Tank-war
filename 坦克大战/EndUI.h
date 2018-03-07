// EndUI.h: interface for the CEndUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENDUI_H__EA7E2148_706B_46D6_9238_F7D59C96B005__INCLUDED_)
#define AFX_ENDUI_H__EA7E2148_706B_46D6_9238_F7D59C96B005__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include <cv.h>
# include <highgui.h>

class CMange;
class CEndUI  
{
public:
	void InitEndUI();
	void GetGradeNum(CMange *manger);
	void ShowImage(CMange *manger);
	CEndUI();
	virtual ~CEndUI();
private:
	IplImage *endImg;
	IplImage *endImgclone;
	IplImage *grade[10];
};

#endif // !defined(AFX_ENDUI_H__EA7E2148_706B_46D6_9238_F7D59C96B005__INCLUDED_)
