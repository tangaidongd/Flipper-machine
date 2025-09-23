// CheckBox.cpp : 实现文件
//

#include "cusCheckBox.h"
#include "..\resource.h"
// CCusCheckBox

IMPLEMENT_DYNAMIC(CCusCheckBox, CButton)



bool ImageFromIDResource(CImage* pImg, UINT nID, LPCTSTR sTR)
{
	if (!pImg)
		return false;
	pImg->Destroy();
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nID), sTR); // type
	if (!hRsrc)
		return FALSE;

	HGLOBAL hImgData = (BYTE*)LoadResource(AfxGetResourceHandle(), hRsrc);
	if (!hImgData)
	{
		return FALSE;
	}

	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	::GlobalUnlock(hNew);
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
		::FreeResource(hImgData);
		return false;
	}
	
	pImg->Load(pStream);
	GlobalFree(hNew);
	::FreeResource(hImgData);
	return TRUE;
}

CCusCheckBox::CCusCheckBox()
{
	m_bChecked = FALSE;
	m_clrNormalText = RGB(0,0,0);
	m_clrUnEnableText = RGB(70, 70, 70);

	m_clrNormalBkText = RGB(240, 240, 240);
	//m_clrCheckedBkText =  RGB(20, 150, 150);
	m_clrCheckedBkText =  RGB(255, 255, 0);

	LOGFONT logFont;
	::ZeroMemory(&logFont,sizeof(logFont));
	logFont.lfHeight = 12;
	logFont.lfWeight = FW_NORMAL;
	lstrcpy(logFont.lfFaceName,L"宋体");
	m_font.CreateFontIndirect(&logFont);

	m_nStateCount = 2;
	ImageFromIDResource(&m_imgBK, IDB_PNG1, L"PNG");


}

CCusCheckBox::~CCusCheckBox()
{
}


BEGIN_MESSAGE_MAP(CCusCheckBox, CButton)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



void CCusCheckBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rtClient;
	GetClientRect(rtClient);

	CString strText;
	GetWindowText(strText);
	//
	HGDIOBJ hOldFont = NULL;
	if (m_font.m_hObject)
		hOldFont = dc.SelectObject(m_font.m_hObject);
	dc.SetBkMode(TRANSPARENT);
	if (!m_imgBK.IsNull())
	{
		bool bEnable = IsWindowEnabled();
		COLORREF  clrText = m_clrNormalText;
		COLORREF  clrFileBk = m_clrNormalBkText;

		int nHeight = m_imgBK.GetHeight() / m_nStateCount;
		int nStartY = (rtClient.Height() - nHeight) / 2 + 1;
		CRect rtText(m_imgBK.GetWidth() + 3, 0, rtClient.right, rtClient.bottom);

		// Enable 级别比选中高
		clrText = m_clrNormalText;
		clrFileBk = m_clrNormalBkText;

		if (!bEnable)
			clrText = m_clrUnEnableText;
		if (m_bChecked)
			clrFileBk = m_clrCheckedBkText;

		dc.FillSolidRect(rtClient, clrFileBk);
		dc.SetTextColor(clrText);
		dc.DrawText(strText, rtText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (m_bChecked)
			m_imgBK.Draw(dc.GetSafeHdc(), 0, nStartY, m_imgBK.GetWidth(), nHeight, 0, nHeight, m_imgBK.GetWidth(), nHeight);
		else
			m_imgBK.Draw(dc.GetSafeHdc(), 0, nStartY, m_imgBK.GetWidth(), nHeight, 0, 0, m_imgBK.GetWidth(), nHeight);
	}

	if (hOldFont)
		dc.SelectObject(hOldFont);
}

void CCusCheckBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bChecked = !m_bChecked;

	CButton::OnLButtonUp(nFlags, point);
}


BOOL CCusCheckBox::GetChecked()
{
	return m_bChecked;
}

void CCusCheckBox::SetChecked( BOOL bChecked )
{
	if(bChecked == m_bChecked)
		return;

	m_bChecked = bChecked;
	Invalidate();
}


