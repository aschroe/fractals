#include "stdafx.h"

HPEN DrawingThread::Pen::None;
HPEN DrawingThread::Pen::White;
HPEN DrawingThread::Pen::Black;
HPEN DrawingThread::Pen::Red;
HPEN DrawingThread::Pen::Green;
HPEN DrawingThread::Pen::Blue;


DrawingThread::DrawingThread(HDC bitmapDC, RECT rc) : active(true), bitmapDC(bitmapDC), rc(rc)
{
  drawThread.reset(new std::thread([this](){ threadDrawLoop(); }));
}

void DrawingThread::nextTick()
{
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
  Pen::Initialize();
  Clear();

  SelectObject(bitmapDC, Pen::Black);


  std::unique_lock<std::mutex> lock(mtx);


  Vector pos = Center();
  Vector direction = Vector::Up * abs(Center().y);


  while (active) {
    // Draw into the bitmap
    
    
    DrawLine(pos, pos+direction);
    pos += direction;
    direction = direction.Rotate(90);
    direction *= 0.99;



    FractalApp::GetInstance().UpdateWindow();


    continueDrawing.wait(lock);
  }
}

Vector DrawingThread::Center() const
{
  return Vector(rc.right/2.0, rc.bottom/2.0);
}

void DrawingThread::DrawLine(Vector from, Vector to) const {
  MoveToEx(bitmapDC, from.XPos(), from.YPos(), NULL);
  LineTo(bitmapDC, to.XPos(), to.YPos());
}

void DrawingThread::Clear() const
{
  static HBRUSH white = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
  FillRect(bitmapDC, &rc, white);
}

void DrawingThread::Pen::Initialize()
{
  None = CreatePen(PS_NULL, 1, RGB(0,0,0));
  White = CreatePen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0xFF));
  Black = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
  Red = CreatePen(PS_SOLID, 1, RGB(0xFF, 0x00, 0x00));
  Green = CreatePen(PS_SOLID, 1, RGB(0x00, 0xFF, 0x00));
  Blue = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0xFF));
}
