#ifndef WALLPAPER_TOOL_H
#define WALLPAPER_TOOL_H

#include <Windows.h>

void SetWindowGeometry(HWND win, int x, int y, int w, int h);
void SetWallpaperWindow(HWND win);
void DetachWallpaperWindow(HWND win);
HWND FindWindowByPid(DWORD pid);

#endif // WALLPAPER_TOOL_H