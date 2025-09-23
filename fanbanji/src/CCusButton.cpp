#include "CCusButton.h"


IMPLEMENT_DYNAMIC(CCusButton, CButton)
CCusButton::CCusButton()
{
	m_clrNormalBkText = RGB(240, 240, 240);
	m_clrCheckedBkText = RGB(40, 150, 255);
	m_clrHoverBkText = RGB(190, 190, 190);
	m_bMouseOver = false;
}

CCusButton::~CCusButton()
{

}

BEGIN_MESSAGE_MAP(CCusButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()


void CCusButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseOver)
	{
		m_bMouseOver = TRUE;
		Invalidate();

		// using struct TRACKMOUSEEVENT to track mouse 
		TRACKMOUSEEVENT event;
		event.cbSize = sizeof(TRACKMOUSEEVENT);
		event.dwFlags = TME_LEAVE;
		event.hwndTrack = m_hWnd;
		_TrackMouseEvent(&event); // Sends WM_MOUSELEAVE message , when mouse leaves the button area
	}

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CCusButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bMouseOver = FALSE;
	CRect rt;
	GetWindowRect(&rt);
	GetParent()->ScreenToClient(&rt);
	GetParent()->InvalidateRect(rt, TRUE);
	Invalidate();
	return LRESULT();
}



void CCusButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// 获取按钮的状态
	BOOL bDisabled = (lpDrawItemStruct->itemState & ODS_DISABLED);
	BOOL bPressed = (lpDrawItemStruct->itemState & ODS_SELECTED);
	BOOL bDefault = FALSE; // 默认状态可以根据需要设置

	//Get Button Tex
	CString strText;
	GetWindowText(strText);
	// 绘制按钮的背景
	CRect rect = lpDrawItemStruct->rcItem;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	if (bPressed)
	{
		// 绘制按钮被按下时的背景
		pDC->FillSolidRect(&rect, m_clrCheckedBkText);
	}
	else if(m_bMouseOver)
	{
		pDC->FillSolidRect(&rect, m_clrHoverBkText);
	}
	else
	{
		// 绘制按钮正常状态的背景
		pDC->FillSolidRect(&rect, m_clrNormalBkText);
	}

	// 绘制边框
	//pDC->DrawEdge(&rect, EDGE_RAISED, BF_RECT);

	// 绘制文本
	pDC->SetTextColor(bDisabled ? RGB(150, 150, 150) : RGB(0, 0, 0));
	pDC->DrawText(strText, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
