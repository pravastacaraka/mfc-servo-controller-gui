#include "pch.h"
#include "framework.h"
#include "ServoController.h"
#include "ServoControllerDlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CServoControllerDlg dialog

CServoControllerDlg::CServoControllerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVOCONTROLLER_DIALOG, pParent)
	, m_port(0)
	, m_angle_s0(90)
	, m_y1_s0(593)
	, m_y2_s0(2396)
	, m_interpolation_s0(0)
	, m_angle_s1(0)
	, m_y1_s1(770)
	, m_y2_s1(1500)
	, m_interpolation_s1(0)
	, m_angle_s2(0)
	, m_y1_s2(2439)
	, m_y2_s2(649)
	, m_interpolation_s2(0)
	, m_angle_s3(0)
	, m_y1_s3(2416)
	, m_y2_s3(626)
	, m_interpolation_s3(0)
	, m_a1(0)
	, m_a2(0)
	, m_a3(0)
	, m_px(0)
	, m_py(0)
	, m_orientation(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServoControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ECPORT, m_port);
	DDX_Text(pDX, IDC_ECANGLE_S0, m_angle_s0);
	DDX_Text(pDX, IDC_ECY1_S0, m_y1_s0);
	DDX_Text(pDX, IDC_ECY2_S0, m_y2_s0);
	DDX_Text(pDX, IDC_ECINTERPOLATION_S0, m_interpolation_s0);
	DDX_Text(pDX, IDC_ECANGLE_S1, m_angle_s1);
	DDX_Text(pDX, IDC_ECY1_S1, m_y1_s1);
	DDX_Text(pDX, IDC_ECY2_S1, m_y2_s1);
	DDX_Text(pDX, IDC_ECINTERPOLATION_S1, m_interpolation_s1);
	DDX_Text(pDX, IDC_ECANGLE_S2, m_angle_s2);
	DDX_Text(pDX, IDC_ECY1_S2, m_y1_s2);
	DDX_Text(pDX, IDC_ECY2_S2, m_y2_s2);
	DDX_Text(pDX, IDC_ECINTERPOLATION_S2, m_interpolation_s2);
	DDX_Text(pDX, IDC_ECANGLE_S3, m_angle_s3);
	DDX_Text(pDX, IDC_ECY1_S3, m_y1_s3);
	DDX_Text(pDX, IDC_ECY2_S3, m_y2_s3);
	DDX_Text(pDX, IDC_ECINTERPOLATION_S3, m_interpolation_s3);
	DDX_Text(pDX, IDC_ECA1, m_a1);
	DDX_Text(pDX, IDC_ECA2, m_a2);
	DDX_Text(pDX, IDC_ECA3, m_a3);
	DDX_Text(pDX, IDC_ECPX, m_px);
	DDX_Text(pDX, IDC_ECPY, m_py);
	DDX_Text(pDX, IDC_ECORIENTATION, m_orientation);
	DDX_Text(pDX, IDC_ECTHETA11, m_satu);
	DDX_Text(pDX, IDC_ECTHETA21, m_dua);
	DDX_Text(pDX, IDC_ECTHETA31, m_tiga);
	DDX_Text(pDX, IDC_ECTHETA12, m_satu2);
	DDX_Text(pDX, IDC_ECTHETA22, m_dua2);
	DDX_Text(pDX, IDC_ECTHETA32, m_tiga2);
	DDX_Control(pDX, IDC_SLANGLE_S0, m_slider0);
	DDX_Control(pDX, IDC_SLANGLE_S1, m_slider1);
	DDX_Control(pDX, IDC_SLANGLE_S2, m_slider2);
	DDX_Control(pDX, IDC_SLANGLE_S3, m_slider3);
	DDX_Control(pDX, IDC_BTNOPEN, m_openPort);
	DDX_Control(pDX, IDC_BTNCLOSE, m_closePort);
	DDX_Control(pDX, IDC_MSCOMM1, m_comm);
	DDX_Control(pDX, IDC_BTNORGN, m_originPos);
	DDX_Control(pDX, IDC_BTNCTR_S0, m_center_s0);
	DDX_Control(pDX, IDC_BTNCTR_S1, m_center_s1);
	DDX_Control(pDX, IDC_BTNCTR_S2, m_center_s2);
	DDX_Control(pDX, IDC_BTNCTR_S3, m_center_s3);
	DDX_Control(pDX, IDC_BTNCALC1, m_calc_inv1);
	DDX_Control(pDX, IDC_BTNRUN1, m_run_inv1);
	DDX_Control(pDX, IDC_BTNCALC2, m_calc_inv2);
	DDX_Control(pDX, IDC_BTNRUN2, m_run_inv2);
}

BEGIN_MESSAGE_MAP(CServoControllerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNOPEN, &CServoControllerDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTNCLOSE, &CServoControllerDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTNORGN, &CServoControllerDlg::OnBnClickedBtnOrigin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLANGLE_S0, &CServoControllerDlg::OnNMCustomdrawSliderAngle_S0)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLANGLE_S1, &CServoControllerDlg::OnNMCustomdrawSliderAngle_S1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLANGLE_S2, &CServoControllerDlg::OnNMCustomdrawSliderAngle_S2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLANGLE_S3, &CServoControllerDlg::OnNMCustomdrawSliderAngle_S3)
	ON_BN_CLICKED(IDC_BTNCTR_S0, &CServoControllerDlg::OnBnClickedBtnCenter_S0)
	ON_BN_CLICKED(IDC_BTNCTR_S1, &CServoControllerDlg::OnBnClickedBtnCenter_S1)
	ON_BN_CLICKED(IDC_BTNCTR_S2, &CServoControllerDlg::OnBnClickedBtnCenter_S2)
	ON_BN_CLICKED(IDC_BTNCTR_S3, &CServoControllerDlg::OnBnClickedBtnCenter_S3)
	ON_BN_CLICKED(IDC_BTNCALC1, &CServoControllerDlg::OnBnClickedBtnCalcInv1)
	ON_BN_CLICKED(IDC_BTNCALC2, &CServoControllerDlg::OnBnClickedBtnCalcInv2)
	ON_BN_CLICKED(IDC_BTNRUN1, &CServoControllerDlg::OnBnClickedBtnRunInv1)
	ON_BN_CLICKED(IDC_BTNRUN2, &CServoControllerDlg::OnBnClickedBtnRunInv2)
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
	// Servo 0
	m_slider0.SetRange(0, 180, 1);
	m_slider0.SetPos(90);
	m_slider0.EnableWindow(FALSE);

	// Servo 1
	m_slider1.SetRange(0, 90, 1);
	m_slider1.SetPos(0);
	m_slider1.EnableWindow(FALSE);

	// Servo 2
	m_slider2.SetRange(-90, 90, 1);
	m_slider2.SetPos(0);
	m_slider2.EnableWindow(FALSE);

	// Servo 3
	m_slider3.SetRange(-90, 90, 1);
	m_slider3.SetPos(0);
	m_slider3.EnableWindow(FALSE);

	// Button Setting
	m_closePort.EnableWindow(FALSE);
	m_originPos.EnableWindow(FALSE);
	m_center_s0.EnableWindow(FALSE);
	m_center_s1.EnableWindow(FALSE);
	m_center_s2.EnableWindow(FALSE);
	m_center_s3.EnableWindow(FALSE);
	m_calc_inv1.EnableWindow(FALSE);
	m_calc_inv2.EnableWindow(FALSE);
	m_run_inv1.EnableWindow(FALSE);
	m_run_inv2.EnableWindow(FALSE);

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
		m_openPort.EnableWindow(FALSE);
		m_closePort.EnableWindow(TRUE);
		m_originPos.EnableWindow(TRUE);
		m_slider0.EnableWindow(TRUE);
		m_slider1.EnableWindow(TRUE);
		m_slider2.EnableWindow(TRUE);
		m_slider3.EnableWindow(TRUE);
		m_center_s0.EnableWindow(TRUE);
		m_center_s1.EnableWindow(TRUE);
		m_center_s2.EnableWindow(TRUE);
		m_center_s3.EnableWindow(TRUE);
		m_calc_inv1.EnableWindow(TRUE);
		m_calc_inv2.EnableWindow(TRUE);
		m_run_inv1.EnableWindow(TRUE);
		m_run_inv2.EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnClose()
{
	m_comm.put_PortOpen(FALSE);

	// Ketika port ditutup, matikan tombol 'Close Port' dan Slider; Nyalakan tombol 'Open Port'
	m_openPort.EnableWindow(TRUE);
	m_closePort.EnableWindow(FALSE);
	m_originPos.EnableWindow(FALSE);
	m_center_s0.EnableWindow(FALSE);
	m_center_s1.EnableWindow(FALSE);
	m_center_s2.EnableWindow(FALSE);
	m_center_s3.EnableWindow(FALSE);
	m_calc_inv1.EnableWindow(FALSE);
	m_calc_inv2.EnableWindow(FALSE);
	m_run_inv1.EnableWindow(FALSE);
	m_run_inv2.EnableWindow(FALSE);

	// Servo 0
	m_angle_s0 = 90;
	m_slider0.SetPos(90);
	m_slider0.EnableWindow(FALSE);

	// Servo 1
	m_angle_s1 = 0;
	m_slider1.SetPos(0);
	m_slider1.EnableWindow(FALSE);

	// Servo 2
	m_angle_s2 = 0;
	m_slider2.SetPos(0);
	m_slider2.EnableWindow(FALSE);

	// Servo 2
	m_angle_s3 = 0;
	m_slider3.SetPos(0);
	m_slider3.EnableWindow(FALSE);

	UpdateData(TRUE);
	m_port = 0;
	m_px = 0;
	m_py = 0;
	m_orientation = 0;
	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnOrigin()
{
	UpdateData(TRUE);

	// Servo 0
	m_angle_s0 = 90;
	m_slider0.SetPos(90);

	// Servo 1
	m_angle_s1 = 0;
	m_slider1.SetPos(0);

	// Servo 2
	m_angle_s2 = 0;
	m_slider2.SetPos(0);

	// Servo 3
	m_angle_s3 = 0;
	m_slider3.SetPos(0);

	UpdateData(FALSE);
}

void CServoControllerDlg::OnNMCustomdrawSliderAngle_S0(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData(TRUE);

	m_angle_s0 = m_slider0.GetPos();
	y_s0 = m_y1_s0 + (m_y2_s0 - m_y1_s0) * (m_angle_s0 - 0) / (180 - 0);
	m_interpolation_s0 = y_s0;

	UpdateData(FALSE);

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	header[0] = 0x0D;
	header[1] = 0x0A;

	hexdata[0] = '#';
	hexdata[1] = '0';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = 0x30 + ((y_s0 / 1000) % 10);
	hexdata[5] = 0x30 + ((y_s0 / 100) % 10);
	hexdata[6] = 0x30 + ((y_s0 / 10) % 10);
	hexdata[7] = 0x30 + (y_s0 % 10);
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

		ForwardKinematics();

		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CServoControllerDlg::OnNMCustomdrawSliderAngle_S1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData(TRUE);

	m_angle_s1 = m_slider1.GetPos();
	y_s1 = m_y1_s1 + (m_y2_s1 - m_y1_s1) * (m_angle_s1 - 0) / (90 - 0);
	m_interpolation_s1 = y_s1;

	UpdateData(FALSE);

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	header[0] = 0x0D;
	header[1] = 0x0A;

	hexdata[0] = '#';
	hexdata[1] = '1';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = 0x30 + ((y_s1 / 1000) % 10);
	hexdata[5] = 0x30 + ((y_s1 / 100) % 10);
	hexdata[6] = 0x30 + ((y_s1 / 10) % 10);
	hexdata[7] = 0x30 + (y_s1 % 10);
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

		ForwardKinematics();

		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CServoControllerDlg::OnNMCustomdrawSliderAngle_S2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData(TRUE);

	m_angle_s2 = m_slider2.GetPos();
	y_s2 = m_y1_s2 + (m_y2_s2 - m_y1_s2) * (m_angle_s2 - (-90)) / (90 - (-90));
	m_interpolation_s2 = y_s2;

	UpdateData(FALSE);

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	header[0] = 0x0D;
	header[1] = 0x0A;

	hexdata[0] = '#';
	hexdata[1] = '2';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = 0x30 + ((y_s2 / 1000) % 10);
	hexdata[5] = 0x30 + ((y_s2 / 100) % 10);
	hexdata[6] = 0x30 + ((y_s2 / 10) % 10);
	hexdata[7] = 0x30 + (y_s2 % 10);
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

		ForwardKinematics();

		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CServoControllerDlg::OnNMCustomdrawSliderAngle_S3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData(TRUE);

	m_angle_s3 = m_slider3.GetPos();
	y_s3 = m_y1_s3 + (m_y2_s3 - m_y1_s3) * (m_angle_s3 - (-90)) / (90 - (-90));
	m_interpolation_s3 = y_s3;

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
	hexdata[4] = 0x30 + ((y_s3 / 1000) % 10);
	hexdata[5] = 0x30 + ((y_s3 / 100) % 10);
	hexdata[6] = 0x30 + ((y_s3 / 10) % 10);
	hexdata[7] = 0x30 + (y_s3 % 10);
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

		ForwardKinematics();

		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CServoControllerDlg::OnBnClickedBtnCenter_S0()
{
	UpdateData(TRUE);
	m_angle_s0 = 90;
	m_slider0.SetPos(90);
	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnCenter_S1()
{
	UpdateData(TRUE);
	m_angle_s1 = 0;
	m_slider1.SetPos(0);
	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnCenter_S2()
{
	UpdateData(TRUE);
	m_angle_s2 = 0;
	m_slider2.SetPos(0);
	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnCenter_S3()
{
	UpdateData(TRUE);
	m_angle_s3 = 0;
	m_slider3.SetPos(0);
	UpdateData(FALSE);
}

void CServoControllerDlg::ForwardKinematics()
{
	// Kinematika 2 DoF
	/*static int teta2 = 0, teta3 = 0;

	UpdateData(TRUE);

	teta2 = m_angle_s0 + m_angle_s2;	// normalisasi
	m_px = round(m_a1 * cos((float)(m_angle_s0) * 3.14 / 180) + m_a2 * cos((float)(teta2) * 3.14 / 180));
	m_py = round(m_a1 * sin((float)(m_angle_s0) * 3.14 / 180) + m_a2 * sin((float)(teta2) * 3.14 / 180));

	UpdateData(FALSE);*/

	// Kinematika 3 DoF
	static int teta2 = 0, teta3 = 0;

	UpdateData(TRUE);

	teta2 = m_angle_s0 + m_angle_s2;	// normalisasi
	teta3 = teta2 + m_angle_s3;			// normalisasi

	m_px = round(m_a1 * cos((float)(m_angle_s0) * 3.14 / 180) + m_a2 * cos((float)(teta2) * 3.14 / 180));
	m_py = round(m_a1 * sin((float)(m_angle_s0) * 3.14 / 180) + m_a2 * sin((float)(teta2) * 3.14 / 180));
	m_px = round(m_px + m_a3 * cos((float)(teta3) * 3.14 / 180));
	m_py = round(m_py + m_a3 * sin((float)(teta3) * 3.14 / 180));

	m_orientation = teta3;
	
	UpdateData(FALSE);
}

void CServoControllerDlg::InverseKinematics1()
{
	float teta1, teta2;

	// Inverse Kinematics 2 DoF
	/*UpdateData(TRUE);

	teta2 = (pow(m_px, 2) + pow(m_py, 2) - pow((float)m_a1, 2) - pow((float)m_a2, 2)) / (2 * (float)m_a1 * (float)m_a2);
	if (teta2 >= 1.0) teta2 = 1.0;
	else if (teta2 <= -1.0) teta2 = -1.0;
	teta2 = acos(teta2);

	teta1 = ((float)m_a2 * sin(teta2)) / ((float)m_a1 + (float)m_a2 * cos(teta2));
	teta1 = atan2(m_py, m_px) - atan(teta1);

	m_satu = teta1 * (180 / 3.14);
	m_dua = teta2 * (180 / 3.14);

	UpdateData(FALSE);*/

	// Inverse kinematics 3 DoF
	UpdateData(TRUE);

	px = m_px - m_a3 * cos(m_orientation * 3.14 / 180);
	py = m_py - m_a3 * sin(m_orientation * 3.14 / 180);

	teta2 = (pow(px, 2) + pow(py, 2) - pow(m_a1, 2) - pow(m_a2, 2)) / (2 * m_a1 * m_a2);
	if (teta2 >= 1.0) teta2 = 1.0;
	else if (teta2 <= -1.0) teta2 = -1.0;
	teta2 = acos(teta2);

	teta1 = (m_a2 * sin(teta2)) / (m_a1 + (m_a2 * cos(teta2)));
	teta1 = atan2(py, px) - atan(teta1);

	m_satu = teta1 * (180 / 3.14);
	m_dua = teta2 * (180 / 3.14);
	m_tiga = m_orientation - m_dua - m_satu;

	UpdateData(FALSE);
}

void CServoControllerDlg::InverseKinematics2()
{
	float teta11, teta22;

	// Inverse Kinematics 2 DoF
	/*UpdateData(TRUE);

	teta22 = (pow(m_px, 2) + pow(m_py, 2) - pow((float)m_a1, 2) - pow((float)m_a2, 2)) / (2 * (float)m_a1 * (float)m_a2);
	if (teta22 >= 1.0) teta22 = 1.0;
	else if (teta22 <= -1.0) teta22 = -1.0;
	teta22 = -acos(teta22);

	teta11 = ((float)m_a2 * sin(teta22)) / ((float)m_a1 + (float)m_a2 * cos(teta22));
	teta11 = atan2(m_py, m_px) - atan(teta11);

	m_satu2 = teta11 * (180 / 3.14);
	m_dua2 = teta22 * (180 / 3.14);

	UpdateData(FALSE);*/

	// Inverse kinematics 3 DoF
	UpdateData(TRUE);

	px = m_px - m_a3 * cos(m_orientation * 3.14 / 180);
	py = m_py - m_a3 * sin(m_orientation * 3.14 / 180);

	teta22 = (pow(px, 2) + pow(py, 2) - pow(m_a1, 2) - pow(m_a2, 2)) / (2 * m_a1 * m_a2);
	if (teta22 >= 1.0) teta22 = 1.0;
	else if (teta22 <= -1.0) teta22 = -1.0;
	teta22 = -acos(teta22);

	teta11 = (m_a2 * sin(teta22)) / (m_a1 + m_a2 * cos(teta22));
	teta11 = atan2(py, px) - atan(teta11);

	m_satu2 = teta11 * (180 / 3.14);
	m_dua2 = teta22 * (180 / 3.14);
	m_tiga2 = m_orientation - m_dua2 - m_satu2;

	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnCalcInv1()
{
	InverseKinematics1();
}

void CServoControllerDlg::OnBnClickedBtnCalcInv2()
{
	InverseKinematics2();
}

void CServoControllerDlg::OnBnClickedBtnRunInv1()
{
	UpdateData(TRUE);

	// Inverse Kinematics 2 DoF
	//m_slider0.SetPos(m_satu);
	//m_slider0.SetPos(m_dua);

	// Inverse Kinematics 3 DoF
	m_slider0.SetPos(round(m_satu));
	m_slider2.SetPos(round(m_dua));
	m_slider3.SetPos(round(m_tiga));

	UpdateData(FALSE);
}

void CServoControllerDlg::OnBnClickedBtnRunInv2()
{
	UpdateData(TRUE);

	// Inverse Kinematics 2 DoF
	//m_slider0.SetPos(m_satu2);
	//m_slider0.SetPos(m_dua2);

	// Inverse Kinematics 3 DoF
	m_slider0.SetPos(round(m_satu2));
	m_slider2.SetPos(round(m_dua2));
	m_slider3.SetPos(round(m_tiga2));

	UpdateData(FALSE);
}
