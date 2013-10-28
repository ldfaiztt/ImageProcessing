
// ChildFrm.h : interface of the CChildFrame class
//

#pragma once
#include "MyImage.h"
#include <vector>

enum class drawType
{
	drawImg,
	drawHistogram,
};

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	std::vector<std::shared_ptr<type_statistic_map>> maps;
	int statistic_max;
	int scale_max;

protected:
	typeImgPtr img;
	drawType drwt;
// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
	typeImgPtr showImg();
	void setImg(typeImgPtr val);
	drawType getDrawType();
	void setDrawType(drawType dt);
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
