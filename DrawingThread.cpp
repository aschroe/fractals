#include "stdafx.h"


DrawingThread::DrawingThread(DrawingBoard& drawingBoard) : active(true), drawingBoard(drawingBoard) {
  drawThread.reset(new std::thread([this](){ threadDrawLoop(); }));
}

void DrawingThread::nextTick() {
  std::unique_lock<std::mutex> lock(mtx);
  continueDrawing.notify_one();
}

void DrawingThread::shutdown()
{
  {
    std::unique_lock<std::mutex> lock(mtx);
    active = false;
    continueDrawing.notify_one();
  }
  drawThread->join();
}

void DrawingThread::threadDrawLoop() {
  drawingBoard.Clear();
  std::unique_lock<std::mutex> lock(mtx);


  Vector pos = drawingBoard.Center();
  Vector direction = Vector::Up * abs(pos.y);

  Fractal f(drawingBoard, 3);

  while (active) {
    // Draw into the bitmap
    f.Draw();
    FractalApp::GetInstance().UpdateWindow();

    continueDrawing.wait(lock);
  }
}
