// InitResource.h: interface for the CInitResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INITRESOURCE_H__2A197CCE_34E8_4FA9_97DD_7B75EDE1B76C__INCLUDED_)
#define AFX_INITRESOURCE_H__2A197CCE_34E8_4FA9_97DD_7B75EDE1B76C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include <cv.h>
# include <highgui.h>
class CInitResource  
{
public:
	void ReleaseResource();
	void InitResourceImage();
	CInitResource();
	virtual ~CInitResource();
	IplImage * mytanke[4];
	IplImage * ditankegold[4];
	IplImage * ditankegray[4];
	IplImage * ditankebule[4];
	IplImage * zidan[3];
};

#endif // !defined(AFX_INITRESOURCE_H__2A197CCE_34E8_4FA9_97DD_7B75EDE1B76C__INCLUDED_)
