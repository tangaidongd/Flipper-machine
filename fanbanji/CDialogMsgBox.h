#pragma once


// CDialogMsgBox 对话框

class CDialogMsgBox : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMsgBox)

public:
	CDialogMsgBox(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogMsgBox();

	enum { IDD = IDD_DIALOG_CUS_MSG };

public:
	void SetDisplayMsg(CString strMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
