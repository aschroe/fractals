#pragma once


class DrawingThread {
public:
  DrawingThread(HDC bitmapDC, RECT rc);


  void nextTick();

  void shutdown();

private:
  void threadDrawLoop();

  Vector Center() const;
  void DrawLine(Vector from, Vector to) const;

  /** Fills the whole bitmap with white color
   */
  void Clear() const;

  std::unique_ptr<std::thread> drawThread;
  std::condition_variable continueDrawing;
  std::mutex mtx;

  HDC bitmapDC;
  RECT rc;

  bool active;

  /** This struct is more a namespace for the pen colors
   */
  struct Pen {
    /** Creates the Pens
     */
    static void Initialize();

    static HPEN None, White, Black, Red, Green, Blue;
  };
};