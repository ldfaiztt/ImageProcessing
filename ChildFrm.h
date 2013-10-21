
// ChildFrm.h : interface of the CChildFrame class
//

#pragma once
#include <memory>

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
// Operations
private:
   std::shared_ptr<CImage> img;
// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
	std::shared_ptr<CImage> showImg();
	void setImg(std::shared_ptr<CImage> val);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
