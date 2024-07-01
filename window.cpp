#include <windows.h>

void SetFullscreen(HWND hwnd, HMONITOR hMonitor)
{
    MONITORINFO mi = { sizeof(mi) };
    if (!GetMonitorInfo(hMonitor, &mi))
    {
        return;
    }

    DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
    if (dwStyle & WS_OVERLAPPEDWINDOW)
    {
        MONITORINFO monitorInfo = { sizeof(monitorInfo) };
        if (GetMonitorInfo(hMonitor, &monitorInfo))
        {
            SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(hwnd, HWND_TOP,
                         monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
                         monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
                         monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
                         SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
    }
}

int main()
{
    // 対象ウィンドウのハンドルを取得する
    HWND hwnd = FindWindowW(NULL, L"ドルウェブ");

    if (hwnd)
    {
        // 対象スクリーンを特定する
        HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
        SetFullscreen(hwnd, hMonitor);
    }

    return 0;
}
