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

void SetWallpaperWindow(WId win)
{
    HWND wallpaper = reinterpret_cast<HWND>(win);
    SetWindowLong(wallpaper, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowLong(wallpaper, GWL_EXSTYLE, WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE);
    SetLayeredWindowAttributes(wallpaper, 0, 255, LWA_ALPHA);

    pm = FindWindow(L"Progman", NULL);                                  // 找到 Program Manager 窗口
    SendMessageTimeout(pm, 0x52C, NULL, NULL, SMTO_NORMAL, 500, NULL);  // 发送 0x52C
    EnumWindows(findWorkerW, NULL);                                     // 查找 WorkerW
    SetParent(wallpaper, paper);                                        // 将 wallpaper 设为 WorkerW 的子窗口
}

void DetachWallpaperWindow(WId win)
{
    SetParent(reinterpret_cast<HWND>(win), NULL);   // 分离窗口
    SystemParametersInfo(20, 0, nullptr, 0x1);      // 刷新壁纸
}