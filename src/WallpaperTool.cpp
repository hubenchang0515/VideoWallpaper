#include "WallpaperTool.h"
#include <Windows.h>
#include <cstdio>

// 这是一个非公开的 Windows Message
// 参考：https://www.codeproject.com/articles/Draw-Behind-Desktop-Icons-in-Windows-plus

static int mode = 0;
static HWND pm = nullptr;
static HWND shell = nullptr;
static HWND icon = nullptr;     // 图标层
static HWND paper = nullptr;    // 壁纸层

static BOOL CALLBACK findWorkerW(HWND hwnd, LPARAM Lparam)
{
    HWND sh = FindWindowEx(hwnd, nullptr, L"SHELLDLL_DefView", nullptr);
    if (sh)
    {
        shell = sh;
        icon = hwnd;
        paper = FindWindowEx(nullptr, icon, L"WorkerW", nullptr);

        if (!paper) {
            icon = shell;
            paper = FindWindowEx(hwnd, icon, L"WorkerW", nullptr);
        }
    }
    return TRUE;
}

void SetWindowGeometry(HWND win, int x, int y, int w, int h)
{
    SetWindowPos(win, nullptr, x, y, w, h, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_DRAWFRAME);
    InvalidateRect(win, nullptr, TRUE);
    UpdateWindow(win);
    Sleep(50);
}

void SetWallpaperWindow(HWND win)
{
    SetWindowLong(win, GWL_STYLE, WS_VISIBLE | WS_CLIPSIBLINGS | WS_OVERLAPPED | WS_MINIMIZEBOX);
    SetWindowLong(win, GWL_EXSTYLE, WS_CHILD);
    SetLayeredWindowAttributes(win, 0, 255, LWA_ALPHA);

    pm = FindWindow(L"Progman", nullptr);                               // 找到 Program Manager 窗口
    SendMessageTimeout(pm, 0x52C, 0, 0, SMTO_NORMAL, 500, nullptr);     // 发送 0x52C
    EnumWindows(findWorkerW, 0);                                        // 查找 WorkerW
    SetParent(win, paper);                                              // 将 win 设为 WorkerW 的子窗口
}

void DetachWallpaperWindow(HWND win)
{
    SetParent(win, nullptr);   // 分离窗口
    SystemParametersInfo(20, 0, nullptr, 0x1);      // 刷新壁纸
}

// 用于传递数据给回调函数的结构体
struct EnumData {
    DWORD targetPid;
    HWND hWnd;
};

// EnumWindows 的回调函数
static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    EnumData* data = (EnumData*)lParam;
    DWORD windowPid = 0;

    // 获取该窗口所属的进程 ID
    GetWindowThreadProcessId(hWnd, &windowPid);

    // 如果 PID 匹配 且 是主窗口（没有所有者）
    if (windowPid == data->targetPid && GetWindow(hWnd, GW_OWNER) == NULL && IsWindowVisible(hWnd)) {
        data->hWnd = hWnd;
        return FALSE; // 找到目标，停止枚举
    }

    return TRUE; // 继续枚举
}

HWND FindWindowByPid(DWORD pid) {
    EnumData data;
    data.targetPid = pid;
    data.hWnd = NULL;

    EnumWindows(EnumWindowsProc, (LPARAM)&data);

    return data.hWnd;
}