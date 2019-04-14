#pragma once


class DrawingThread {
public:
  DrawingThread(const DrawingBoard& drawingBoard);


  /** Called by main thread whenever it receives the WM_TIMER message to notify the drawing thread
   *  to continue drawing the currently active fractal
   */
  void nextTick();

  /** Called by the main thread to stop the drawing thread. This method returns as soon as the thrad has ended.
   */
  void shutdown();

private:
  void threadDrawLoop();

  std::unique_ptr<std::thread> drawThread;
  std::condition_variable continueDrawing;
  std::mutex mtx;

  const DrawingBoard& drawingBoard;

  bool active;
};