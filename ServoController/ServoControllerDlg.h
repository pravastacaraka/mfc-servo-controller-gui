
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
	CButton m_originPos;
	CSliderCtrl m_slider0, m_slider1, m_slider2, m_slider3;

	int m_port;
	int y_s0, m_angle_s0, m_y1_s0, m_y2_s0, m_interpolation_s0;
	int y_s1, m_angle_s1, m_y1_s1, m_y2_s1, m_interpolation_s1;
	int y_s2, m_angle_s2, m_y1_s2, m_y2_s2, m_interpolation_s2;
	int y_s3, m_angle_s3, m_y1_s3, m_y2_s3, m_interpolation_s3;

	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnOrigin();
	afx_msg void OnNMCustomdrawSliderAngle_S0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderAngle_S1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderAngle_S2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderAngle_S3(NMHDR *pNMHDR, LRESULT *pResult);

	int m_a1, m_a2;
	int m_px, m_py;

	afx_msg void ForwardKinematics();
};
