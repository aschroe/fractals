#pragma once



class FractalApp {
public:
  static const int TICKS_PER_SECOND = 2; //TODO: Figure out a good number for this parameter


  FractalApp();

  static FractalApp& GetInstance();

  /** Constructs the main window and opens it maximized
   */
  void Initialize(HINSTANCE hInstance);

  /** Runs the main thread's message loop to dispatch windows evetns
   */
  void RunMessageLoop();

  /** Redraw the client area
   */
  void UpdateWindow();

private:
  static FractalApp* instance;
  static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

  std::unique_ptr<DrawingThread> drawingThread;
  std::unique_ptr<DrawingBoard> drawingBoard;

  HWND window;
  UINT_PTR timerId;
};
