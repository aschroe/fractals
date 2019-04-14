#include "stdafx.h"


FractalApp* FractalApp::instance = nullptr;

FractalApp::FractalApp() : window(NULL), bitmap(NULL), bitmapDC(NULL) {}

FractalApp& FractalApp::GetInstance() {
  return *instance;
}

void FractalApp::Initialize(HINSTANCE hInstance) {
  instance = this;

  // Setup winapi
  WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
  wcex.style         = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc   = FractalApp::WndProc;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = sizeof(LONG_PTR);
  wcex.hInstance     = hInstance;
  wcex.hbrBackground = NULL;
  wcex.lpszMenuName  = NULL;
  wcex.hCursor       = LoadCursor(NULL, IDI_APPLICATION);
  wcex.lpszClassName = "FractalWin";
  RegisterClassEx(&wcex);

  // Create window and open it maximized
  window = CreateWindow("FractalWin", "Fractals", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL);

  ShowWindow(window, SW_MAXIMIZE);

  // Now create a bitmap for that window of the same size
  HDC dc = GetDC(window);
  bitmapDC = CreateCompatibleDC(dc);
  GetClientRect(window, &clientRect);
  bitmap = CreateCompatibleBitmap(dc, clientRect.right, clientRect.bottom);
  SelectObject(bitmapDC, bitmap);
  ReleaseDC(window, dc);


  drawingThread.reset(new DrawingThread(bitmapDC, clientRect));


  // Start drawing timer
  timerId = SetTimer(window, NULL, 1000 / TICKS_PER_SECOND, NULL);
}


void FractalApp::RunMessageLoop() {
  for(MSG msg; GetMessage(&msg, NULL, 0, 0);) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

void FractalApp::UpdateWindow() {
  InvalidateRect(window, NULL, FALSE);
}


LRESULT FractalApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  auto& app = GetInstance();

  switch (message) {
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC dc = BeginPaint(hWnd, &ps);
      BitBlt(dc, 0, 0, app.clientRect.right, app.clientRect.bottom, app.bitmapDC, 0, 0, SRCCOPY);
      EndPaint(hWnd, &ps);
      return 0;
      break;
    }


    case WM_TIMER:
      app.drawingThread->nextTick();
      break;


    case WM_DESTROY:
      KillTimer(hWnd, app.timerId);
      PostQuitMessage(1);
      app.drawingThread->shutdown();
      break;
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}
