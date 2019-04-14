#include "stdafx.h"

HPEN DrawingBoard::Pen::None;
HPEN DrawingBoard::Pen::White;
HPEN DrawingBoard::Pen::Black;
HPEN DrawingBoard::Pen::Red;
HPEN DrawingBoard::Pen::Green;
HPEN DrawingBoard::Pen::Blue;
HPEN DrawingBoard::Pen::CxOrange;
HPEN DrawingBoard::Pen::CxRed;
HPEN DrawingBoard::Pen::CxYellow;
HPEN DrawingBoard::Pen::Cyan;
HPEN DrawingBoard::Pen::Magenta;
HPEN DrawingBoard::Pen::Yellow;
HPEN DrawingBoard::Pen::Key;

DrawingBoard::ColorScheme DrawingBoard::ColorSchemes::Black;
DrawingBoard::ColorScheme DrawingBoard::ColorSchemes::BlackNone;
DrawingBoard::ColorScheme DrawingBoard::ColorSchemes::NoneBlack;
DrawingBoard::ColorScheme DrawingBoard::ColorSchemes::RGB;
DrawingBoard::ColorScheme DrawingBoard::ColorSchemes::ClassiX;
DrawingBoard::ColorScheme DrawingBoard::ColorSchemes::CMYK;


DrawingBoard::DrawingBoard(HWND clientWindow) {
  // Now create a bitmap for that window of the same size
  HDC dc = GetDC(clientWindow);
  
  bitmapDC = CreateCompatibleDC(dc);
  GetClientRect(clientWindow, &clientRect);
  bitmap = CreateCompatibleBitmap(dc, clientRect.right, clientRect.bottom);
  SelectObject(bitmapDC, bitmap);
  
  ReleaseDC(clientWindow, dc);

  Pen::Initialize();
  ColorSchemes::Initialize();

  SelectColorScheme(ColorSchemes::Black);
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

Vector DrawingBoard::TopCenter() const {
  return Vector(clientRect.right/2.0, 0);
}

void DrawingBoard::DrawLine(Vector from, Vector to) const {
  MoveToEx(bitmapDC, from.XPos(), from.YPos(), NULL);
  LineTo(bitmapDC, to.XPos(), to.YPos());
}

void DrawingBoard::SelectPen(HPEN pen) const {
  SelectObject(bitmapDC, pen);
}

void DrawingBoard::SelectNextPenColor() {
  ++currentColor;
  SelectPen((*colorScheme)[currentColor%colorScheme->size()]);
}

void DrawingBoard::SelectColorScheme(const ColorScheme& scheme) {
  colorScheme = &scheme;
  currentColor = -1;
  SelectNextPenColor();
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

  CxOrange = CreatePen(PS_SOLID, 1, RGB(0xFF, 0x9C, 0x00));
  CxRed = CreatePen(PS_SOLID, 1, RGB(0xD9, 0x0E, 0x11));
  CxYellow = CreatePen(PS_SOLID, 1, RGB(0xFD, 0xC3, 0x00));

  Cyan = CreatePen(PS_SOLID, 1, RGB(0x00, 0x9E, 0xEF));
  Magenta = CreatePen(PS_SOLID, 1, RGB(0xE6, 0x14, 0x84));
  Yellow = CreatePen(PS_SOLID, 1, RGB(0xFF, 0xE7, 0x00));
  Key = CreatePen(PS_SOLID, 1, RGB(0x29, 0x2D, 0x29));
}


void DrawingBoard::ColorSchemes::Initialize() {
  Black.push_back(Pen::Black);

  BlackNone.push_back(Pen::Black);
  BlackNone.push_back(Pen::None);

  NoneBlack.push_back(Pen::None);
  NoneBlack.push_back(Pen::Black);

  RGB.push_back(Pen::Red);
  RGB.push_back(Pen::Green);
  RGB.push_back(Pen::Blue);

  ClassiX.push_back(Pen::CxOrange);
  ClassiX.push_back(Pen::CxRed);
  ClassiX.push_back(Pen::CxYellow);

  CMYK.push_back(Pen::Cyan);
  CMYK.push_back(Pen::Magenta);
  CMYK.push_back(Pen::Yellow);
  CMYK.push_back(Pen::Key);
}