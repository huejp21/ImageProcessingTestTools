#pragma once


// CAviChildFrame 프레임입니다.

class CAviChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CAviChildFrame)
protected:
	CAviChildFrame();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CAviChildFrame();

protected:
	DECLARE_MESSAGE_MAP()
};


