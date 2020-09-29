
// ServoControllerDlg.h : header file
//

#pragma once
#include "mscomm1.h"

// CServoControllerDlg dialog
class CServoControllerDlg : public CDialogEx
{
// Construction
public:
	CServoControllerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVOCONTROLLER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CMscomm1 m_comm;

	CButton m_openPort;
	CButton m_closePort;
	CSliderCtrl m_slider;

	int m_port, m_angle, m_interpolation;
	int y, m_y1, m_y2;

	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnNMCustomdrawSliderAngle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeECAngle();
};
