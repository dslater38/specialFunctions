#include "stdafx.h"
#include "resource.h"
#include <sstream>
#include <Windowsx.h>
#include <thread>

extern void *hModule;
static HWND hDlg{ nullptr };

static HWND find_main_window(unsigned long process_id);
static
INT_PTR
CALLBACK
DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

static bool createTraceDialog();
static bool ensureWindow();
static bool sendString(const char *str);
static std::string initialStr{};

LRESULT Trace(LPCOMPLEXSCALAR result, LPCMCSTRING s)
{
	std::stringstream ss{};
	ss << "ThreadID: " << GetCurrentThreadId() << " hex: " << std::hex << GetCurrentThreadId() << std::endl;
	OutputDebugString(ss.str().c_str());
	result->real = result->imag = 0;
	std::string str{ s->str };
	str += "\r\n";
	sendString(str.c_str());
	return 0L;
}

static
bool
createTraceDialog()
{
	if (!hDlg && hModule)
	{
		std::thread tr{ [] {
			HWND hwnd = CreateDialog(reinterpret_cast<HINSTANCE>(hModule), MAKEINTRESOURCE(IDD_FORMVIEW), find_main_window(GetCurrentProcessId()), DialogProc);
			if (!hwnd)
				return;
			//{
			//	hDlg = hwnd;
			//}
			MSG msg;
			BOOL bRet = FALSE;
			while( (bRet = GetMessage(&msg, hwnd, 0, 0)) != 0 )
			{
				if (bRet == -1)
				{
					hDlg = nullptr;
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		} };
		for (auto i = 0; i < 100; ++i)
		{
			if (hDlg)
				break;
		}
		tr.detach();
	}
	return (hDlg != nullptr);
}

static
std::stringstream ss{};

static
bool sendString(const char *str)
{

	ss << str << std::endl;
	auto h = GetDlgItem(hDlg, IDC_EDIT1);
	OutputDebugString("Before Edit_SetText\n");

	auto s = std::string{ str };

	if (initialStr.empty())
	{
		initialStr = std::move(s);
		ensureWindow();
	}
	else
	{
		auto len = Edit_GetTextLength(h);
		Edit_SetSel(h, len, len);
		Edit_ReplaceSel(h, s.c_str());
	}
	//auto r =  Edit_SetText(h, ss.str().c_str());
	OutputDebugString("After Edit_SetText, SUCCESS\n");
	return true;
}

static
bool clearAll()
{
	ss.str(std::string{});
	return Edit_SetText(GetDlgItem(hDlg, IDC_EDIT1), ss.str().c_str());
}

static
bool
ensureWindow()
{
	if (!hDlg)
		return createTraceDialog();
	return true;
}


struct handle_data {
	unsigned long process_id;
	HWND best_handle;
};

static
BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

static
BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle)) {
		return TRUE;
	}
	data.best_handle = handle;
	return FALSE;
}

static
HWND find_main_window(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.best_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.best_handle;
}

static
WNDPROC oldEditProc = nullptr;

static
INT_PTR
CALLBACK
EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_RBUTTONDOWN:
			break;
		case WM_INITMENUPOPUP:
		{
			auto popupMenu = reinterpret_cast<HMENU>(wParam);
			auto hMenu = LoadMenu((HINSTANCE)hModule, MAKEINTRESOURCE(IDR_MENU1));
			auto h = GetSubMenu(hMenu, 0);
			MENUITEMINFO info{ 0 };
			if (GetMenuItemInfo(h, ID_EDIT_SAVE, FALSE, &info))
			{
				InsertMenuItem(popupMenu, ID_COPY, FALSE, &info);
			}
		}
	}

	return CallWindowProc(oldEditProc, hwnd, msg, wParam, lParam);
}

static
INT_PTR
CALLBACK
DialogProc(HWND hDlg_, UINT msg, WPARAM wParam, LPARAM lParam)
{
	std::stringstream ss{};
	ss << std::hex <<  "hwnd: " << hDlg_ << "msg: " << msg << std::endl;
	OutputDebugString(ss.str().c_str());
	switch (msg)
	{
		case WM_DESTROY:
			initialStr.clear();
			hDlg = nullptr;
			break;
		case WM_CREATE:
			//hDlg = hDlg_;
			// ShowWindow(hDlg_, SW_SHOW);
			return 0;
			break;
		case WM_SETFONT:
			return 0L;
			break;
		//case WM_INITMENUPOPUP:
		//{
		//	
		//	//auto h = GetSubMenu(hMenu, 0);

		//}
		//case WM_RBUTTONDOWN:
		//{
		//	// Display the shortcut menu. Track the right mouse 
		//	// button. 
		//	auto hPopup = reinterpret_cast<HMENU>(wParam);
		//	
		//	return 0L;
		//	//POINT pt{ GET_X_LPARAM(lParam) , GET_Y_LPARAM(lParam) };


		//	//TrackPopupMenu(h,
		//	//			   TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		//	//			   pt.x, pt.y, 0, hDlg_		, NULL);

		//}
		//break;
		case WM_INITDIALOG:
			{
				auto h = GetDlgItem(hDlg_, IDC_EDIT1);
				if (h)
				{
					oldEditProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(h, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(EditProc)));
				}
			}
			if (!initialStr.empty())
			{
				auto h = GetDlgItem(hDlg_, IDC_EDIT1);
				auto success = SendMessage(h, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(initialStr.c_str()));
				Edit_SetSel(h, static_cast<int>(initialStr.size()), static_cast<int>(initialStr.size()) );
			}
			return 0L;
			break;
		case WM_SHOWWINDOW:
			hDlg = hDlg_;
			return 0L;
			break;
		case WM_CLOSE:
			DestroyWindow(hDlg_);
			return 0L;
			break;
		case WM_SIZE:
		{
			RECT rc;
			GetClientRect(hDlg_, &rc);
			MoveWindow(GetDlgItem(hDlg_, IDC_EDIT1), 0, 0, rc.right-rc.left,rc.bottom-rc.top,TRUE);
			return 0L;
			break;
		}
		case WM_COMMAND:
		{
			std::stringstream ss{};
			ss << "msg: WM_COMMAND HIWORD " << std::hex << HIWORD(wParam) << " LOWORD: " << LOWORD(wParam) << " LPARAM: " << lParam  << std::endl;
			OutputDebugString(ss.str().c_str());

		}
			return 0L;
			break;
		default:
			return 0L;
	}
	// return DefDlgProc(hDlg_, msg, wParam, lParam);
	return 0L;
}
