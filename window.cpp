#include <windows.h>
#include <stdio.h>

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
            SetWindowPos(hwnd, NULL,
                         monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
                         (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left)/1,
                         (monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top)/1,
                         SWP_NOOWNERZORDER | SWP_FRAMECHANGED );
            printf("SetWindowPos\n");
            printf("left: %d\n", monitorInfo.rcMonitor.left);
            printf("top: %d\n", monitorInfo.rcMonitor.top);
            printf("right: %d\n", monitorInfo.rcMonitor.right);
            printf("bottom: %d\n", monitorInfo.rcMonitor.bottom);
        }
    }
}

int main()
{
    HWND hwnd = NULL;

    // ウィンドウが見つかるまでループ
    while (hwnd == NULL)
    {
        hwnd = FindWindowW(NULL, L"ドルウェブ");
        Sleep(100); // CPUの使用率を抑えるために少し待機
    }

    //Sleep(500); // CPUの使用率を抑えるために少し待機

    // 対象スクリーンを特定する
    HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    SetFullscreen(hwnd, hMonitor);

    // ウィンドウのクライアント領域を無効にして再描画を強制する
    //InvalidateRect(hwnd, NULL, TRUE);
    //UpdateWindow(hwnd);

    return 0;
}
