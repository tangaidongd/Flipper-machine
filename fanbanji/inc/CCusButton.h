#pragma once
#include "..\stdafx.h"

class CCusButton : public CButton
{
	DECLARE_DYNAMIC(CCusButton)

public:
	CCusButton();
	~CCusButton();

	DECLARE_MESSAGE_MAP()

protected:
	void OnMouseMove(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
private:
	bool	m_bMouseOver;

	COLORREF m_clrNormalBkText;		// �ı�����ɫ
	COLORREF m_clrCheckedBkText;	// �ı�����ɫ
	COLORREF m_clrHoverBkText;		// �ı�����ɫ
};

