#include "stdafx.h"

HPEN DrawingBoard::Pen::None;
HPEN DrawingBoard::Pen::White;
HPEN DrawingBoard::Pen::Black;
HPEN DrawingBoard::Pen::Red;
HPEN DrawingBoard::Pen::Green;
HPEN DrawingBoard::Pen::Blue;

DrawingBoard::DrawingBoard(HWND clientWindow) {
  // Now create a bitmap for that window of the same size
  HDC dc = GetDC(clientWindow);
  
  bitmapDC = CreateCompatibleDC(dc);
  GetClientRect(clientWindow, &clientRect);
  bitmap = CreateCompatibleBitmap(dc, clientRect.right, clientRect.bottom);
  SelectObject(bitmapDC, bitmap);
  
  ReleaseDC(clientWindow, dc);

  Pen::Initialize();
}

const RECT& DrawingBoard::Size() const {
  return clientRect;
}


Vector DrawingBoard::Center() const
{
  return Vector(clientRect.right/2.0, clientRect.bottom/2.0);
}

Vector DrawingBoard::BottomCenter() const
{
  return Vector(clientRect.right/2.0, clientRect.bottom);
}

void DrawingBoard::DrawLine(Vector from, Vector to) const {
  MoveToEx(bitmapDC, from.XPos(), from.YPos(), NULL);
  LineTo(bitmapDC, to.XPos(), to.YPos());
}

void DrawingBoard::SelectPen(HPEN pen) const {
  SelectObject(bitmapDC, pen);
}

void DrawingBoard::Clear() const {
  static HBRUSH white = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
  FillRect(bitmapDC, &clientRect, white);
}

DrawingBoard::operator HDC() const {
  return bitmapDC;
}


void DrawingBoard::Pen::Initialize()
{
  // Create these objects only once
  None = CreatePen(PS_NULL, 1, RGB(0,0,0));
  White = CreatePen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0xFF));
  Black = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
  Red = CreatePen(PS_SOLID, 1, RGB(0xFF, 0x00, 0x00));
  Green = CreatePen(PS_SOLID, 1, RGB(0x00, 0xFF, 0x00));
  Blue = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0xFF));
}