#include "pch.h"
#include "framework.h"
#include "ServoController.h"
#include "ServoControllerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CServoControllerDlg dialog

CServoControllerDlg::CServoControllerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVOCONTROLLER_DIALOG, pParent)
	, m_port(0)
	, m_angle(0)
	, m_interpolation(0)
	, m_y1(0)
	, m_y2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServoControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ECPORT, m_port);
	DDX_Text(pDX, IDC_ECANGLE, m_angle);
	DDX_Text(pDX, IDC_ECY1, m_y1);
	DDX_Text(pDX, IDC_ECY2, m_y2);
	DDX_Text(pDX, IDC_ECINTERPOLATION, m_interpolation);
	DDX_Control(pDX, IDC_BTNOPEN, m_openPort);
	DDX_Control(pDX, IDC_BTNCLOSE, m_closePort);
	DDX_Control(pDX, IDC_SLANGLE, m_slider);
	DDX_Control(pDX, IDC_MSCOMM1, m_comm);
}

BEGIN_MESSAGE_MAP(CServoControllerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNOPEN, &CServoControllerDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTNCLOSE, &CServoControllerDlg::OnBnClickedBtnClose)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLANGLE, &CServoControllerDlg::OnNMCustomdrawSliderAngle)
	ON_EN_CHANGE(IDC_ECANGLE, &CServoControllerDlg::OnEnChangeECAngle)
END_MESSAGE_MAP()


// CServoControllerDlg message handlers

BOOL CServoControllerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_slider.SetRange(0, 180, 1);
	m_slider.SetPos(90);
	m_slider.EnableWindow(FALSE);
	m_closePort.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServoControllerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServoControllerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServoControllerDlg::OnBnClickedBtnOpen()
{
	UpdateData(TRUE);

	m_comm.put_CommPort(m_port);
	m_comm.put_Settings(_T("115200, N, 8, 1"));
	m_comm.put_InputMode(0);
	m_comm.put_InputLen(1);
	m_comm.put_RTSEnable(TRUE);
	m_comm.put_RThreshold(1);
	m_comm.put_PortOpen(TRUE);

	// Ketika port berhasil dihubungkan, matikan tombol 'Open Port'; Nyalakan tombol 'Close Port' dan Slider
	if (m_comm.get_PortOpen()) 
	{
		m_slider.EnableWindow(TRUE);
		m_openPort.EnableWindow(FALSE);
		m_closePort.EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnClose()
{
	m_comm.put_PortOpen(FALSE);

	// Ketika port ditutup, matikan tombol 'Close Port' dan Slider; Nyalakan tombol 'Open Port'
	m_openPort.EnableWindow(TRUE);
	m_closePort.EnableWindow(FALSE);
	m_slider.EnableWindow(FALSE);

	UpdateData(TRUE);
	m_port = 0;
	UpdateData(FALSE);
}


void CServoControllerDlg::OnNMCustomdrawSliderAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int tmp_angle;

	UpdateData(TRUE);

	m_angle = m_slider.GetPos();
	y = m_y1 + (m_y2 - m_y1) * (m_angle - 0) / (180 - 0);
	m_interpolation = y;

	UpdateData(FALSE);

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	header[0] = 0x0D;
	header[1] = 0x0A;

	hexdata[0] = '#';
	hexdata[1] = '3';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = 0x30 + ((y / 1000) % 10);
	hexdata[5] = 0x30 + ((y / 100) % 10);
	hexdata[6] = 0x30 + ((y / 10) % 10);
	hexdata[7] = 0x30 + (y % 10);
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '0';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	if (m_comm.get_PortOpen()) 
	{
		UpdateData(TRUE);

		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));

		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CServoControllerDlg::OnEnChangeECAngle()
{
	UpdateData(TRUE);

	m_slider.SetPos(m_angle);

	UpdateData(FALSE);
}
