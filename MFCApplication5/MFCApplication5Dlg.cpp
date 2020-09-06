
// MFCApplication5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <sstream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication5Dlg 对话框



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CMFCApplication5Dlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_RECV, &CMFCApplication5Dlg::OnBnClickedBtnRecv)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication5Dlg 消息处理程序

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication5Dlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (OpenClipboard())//打开剪贴板  
	{
		CString str;
		HANDLE hClip;
		char* pBuf;
		EmptyClipboard();//清空剪贴板  
		GetDlgItemText(IDC_EDIT_SEND, str);//获取IDC_EDIT_SEND中的数据  

										   //写入数据  
		hClip = GlobalAlloc(GMEM_MOVEABLE, str.GetLength() + 1);
		pBuf = (char*)GlobalLock(hClip);
		strcpy(pBuf, str);
		GlobalUnlock(hClip);//解锁  
		SetClipboardData(CF_TEXT, hClip);//设置格式  

										 //关闭剪贴板  
		CloseClipboard();
	}
}


void CMFCApplication5Dlg::OnBnClickedBtnRecv()
{
	// TODO: 在此添加控件通知处理程序代码
	if (OpenClipboard())//打开剪贴板  
	{
		if (IsClipboardFormatAvailable(CF_TEXT))//判断格式是否是我们所需要  
		{
			HANDLE hClip;
			char* pBuf;

			//读取数据  
			hClip = GetClipboardData(CF_TEXT);
			pBuf = (char*)GlobalLock(hClip);
			GlobalUnlock(hClip);
			SetDlgItemText(IDC_EDIT_RECV, pBuf);//讲数据显示在IDC_EDIT_RECV中  
			CloseClipboard();
		}
	}
}


void CMFCApplication5Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
		std::ostringstream osConfig;
		osConfig.precision(1);

		// Computer Name
		TCHAR  infoBuf[512] = { 0 };
		DWORD  bufCharCount = 512;
		if (GetComputerName(infoBuf, &bufCharCount)) // MSDN: If the function succeeds, the return value is a nonzero value.
			osConfig << "Computer Name: " << infoBuf << std::endl;
		else
			osConfig << "!Error: failed to get computer name" << std::endl;

		// CPU 
		CString strPath = CString("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
		CRegKey regKey;
		LONG lResult;
		lResult = regKey.Open(HKEY_LOCAL_MACHINE, strPath, KEY_READ);
		if (lResult == ERROR_SUCCESS)
		{
			TCHAR chCPUName[256] = { 0 };
			DWORD dwSize = 256;
			LPCSTR name = "ProcessorNameString";
			regKey.QueryValue(chCPUName, _T("ProcessorNameString"), &dwSize);
			osConfig << "CPU Type: " << (char*)chCPUName << std::endl;
			regKey.Close();
		}
		else
			osConfig << "!Error: failed to open register for read CPU." << std::endl;

		// OS Name
		char szOsType[MAX_PATH];
		HKEY hKey;
		LPCTSTR StrKey = "Software\\Microsoft\\Windows NT\\CurrentVersion";
		if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, StrKey, NULL, KEY_READ, &hKey))
		{
			DWORD dwSize = 255;
			DWORD dwType = REG_SZ;
			LPCSTR KeyValue = "ProductName";
			if (ERROR_SUCCESS == ::RegQueryValueEx(hKey, KeyValue, 0, &dwType, (BYTE *)szOsType, &dwSize))
				osConfig << "OS : " << szOsType;
			else
				osConfig << "!Error: failed to get OS name." << std::endl;
			::RegCloseKey(hKey);
		}
		else
			osConfig << "!Error: failed to get OS name." << std::endl;

		SYSTEM_INFO si;
		GetNativeSystemInfo(&si); // MSDN: This function does not return a value.
		if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
			osConfig << " 64bits";
		else
			osConfig << " 32bits";

		OSVERSIONINFO osVer;
		osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (::GetVersionEx(&osVer)) // MSDN: If the function succeeds, the return value is a nonzero value.
			osConfig << " " << osVer.szCSDVersion << " " << std::endl;
		else
			osConfig << "!Error: failed to get OS CSD version.";

		// Memory
		MEMORYSTATUSEX statusex;
		statusex.dwLength = sizeof(statusex);
		if (GlobalMemoryStatusEx(&statusex)) // MSDN: If the function succeeds, the return value is nonzero.
		{
			osConfig << "Installed RAM: " << std::fixed << statusex.ullTotalPhys / 1024 / 1024 / 1024.0 << "GB";
			osConfig << "  Free RAM: " << std::fixed << statusex.ullAvailPhys / 1024 / 1024 / 1024.0 << "GB" << std::endl;
		}
		else
			osConfig << "!Error: failed to get RAM information." << std::endl;

		// Hard Drive
		// GetLogicalDriveStrings(sizeof(cDriveArray), cDriveArray);
		// MSDN: If the function fails, the return value is zero. 
		// If the function succeeds, the return value is the length, in characters, of the strings copied to the buffer, 
		// not including the terminating null character
		ULARGE_INTEGER free;
		ULARGE_INTEGER total;
		ULARGE_INTEGER totalfree;
		TCHAR szDriveArray[128] = { 0 };
		TCHAR *p, *pStart;
		pStart = szDriveArray;
		p = szDriveArray;
		int nLen = GetLogicalDriveStrings(sizeof(szDriveArray), szDriveArray);
		if (nLen != 0)
		{
			while ((p = _tcschr(p, _T('\0'))) && p != szDriveArray + nLen)
			{
				if (GetDiskFreeSpaceEx(pStart, &free, &total, &totalfree))  // if success, nonzero
				{
					osConfig << "[" << pStart << "]" << " Total: " << std::fixed << total.QuadPart / 1024 / 1024 / 1024.0
						<< "GB  Available: " << std::fixed << free.QuadPart / 1024 / 1024 / 1024.0 << "GB";
					if (GetDriveType(pStart) == 3)
						osConfig << " - Fixed Drive" << std::endl;
					else if (GetDriveType(pStart) == 4)
						osConfig << " - (Remote Drive)" << std::endl;
					else
						osConfig << " - Other" << std::endl;
				}
				pStart = ++p;
			}
		}
		else
			osConfig << "!Error: failed to get logical drive name." << std::endl;

		AfxMessageBox(osConfig.str().c_str());
		
		AfxMessageBox("DONE");

	}
