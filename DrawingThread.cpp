#include "stdafx.h"


DrawingThread::DrawingThread(const DrawingBoard& drawingBoard) : active(true), drawingBoard(drawingBoard) {
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
  drawingBoard.SelectPen(DrawingBoard::Pen::Red);


  std::unique_lock<std::mutex> lock(mtx);


  Vector pos = drawingBoard.Center();
  Vector direction = Vector::Up * abs(pos.y);


  while (active) {
    // Draw into the bitmap
    
    
    drawingBoard.DrawLine(pos, pos+direction);
    pos += direction;
    direction = direction.Rotate(90);
    direction *= 0.99;



    FractalApp::GetInstance().UpdateWindow();


    continueDrawing.wait(lock);
  }
}
