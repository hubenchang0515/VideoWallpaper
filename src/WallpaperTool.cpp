#include "WallpaperTool.h"
#include <Windows.h>
#include <cstdio>

// 这是一个非公开的 Windows Message
// 参考：https://www.codeproject.com/articles/Draw-Behind-Desktop-Icons-in-Windows-plus

static HWND pm = nullptr;
static HWND icon = nullptr;     // 图标层
static HWND paper = nullptr;    // 壁纸层

static BOOL CALLBACK findWorkerW(HWND hwnd, LPARAM Lparam)
{
    if (FindWindowEx(hwnd, nullptr, L"SHELLDLL_DefView", nullptr))
    {
        icon = hwnd;
        paper = FindWindowEx(nullptr, hwnd, L"WorkerW", nullptr);
    }
    return TRUE;
}

void SetWallpaperWindow(WId win)
{
    if (pm == NULL) 
    {
        pm = FindWindow(L"Progman", NULL);				                    // 找到 Program Manager 窗口
        SendMessageTimeout(pm, 0x52C, NULL, NULL, SMTO_NORMAL, 500, NULL);  // 发送 0x52C
        EnumWindows(findWorkerW, NULL);                                     // 查找 WorkerW
    }

    if (paper)
    {
        SetParent(reinterpret_cast<HWND>(win), paper);			            // 将 win 设为 WorkerW 的子窗口
    }
    else
    {
        SetParent(reinterpret_cast<HWND>(win), pm);			                // 将 win 设为 pm 的子窗口
    }
}

void DetachWallpaperWindow(WId win)
{
    SetParent(reinterpret_cast<HWND>(win), NULL);   // 分离窗口
    SystemParametersInfo(20, 0, nullptr, 0x1);      // 刷新壁纸
}