
#pragma once
#include "..\stdafx.h"

class  CCusCheckBox : public CButton
{
	DECLARE_DYNAMIC(CCusCheckBox)

	CImage m_imgBK;
	int m_nStateCount;
	BOOL m_bChecked;
	CFont m_font;

	COLORREF m_clrNormalText;
	COLORREF m_clrUnEnableText;



	COLORREF m_clrNormalBkText;// �ı�����ɫ
	COLORREF m_clrCheckedBkText;// �ı�����ɫ

public:
	CCusCheckBox();
	virtual ~CCusCheckBox();

	BOOL GetChecked();
	void SetChecked(BOOL bChecked);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


