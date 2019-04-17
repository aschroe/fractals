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

HBRUSH DrawingBoard::Fill::White;
HBRUSH DrawingBoard::Fill::Black;

DrawingBoard::ColorScheme DrawingBoard::ColorScheme::Black;
DrawingBoard::ColorScheme DrawingBoard::ColorScheme::BlackNone;
DrawingBoard::ColorScheme DrawingBoard::ColorScheme::NoneBlack;
DrawingBoard::ColorScheme DrawingBoard::ColorScheme::RGB;
DrawingBoard::ColorScheme DrawingBoard::ColorScheme::ClassiX;
DrawingBoard::ColorScheme DrawingBoard::ColorScheme::CMYK;
DrawingBoard::ColorScheme DrawingBoard::ColorScheme::ClassiXBlack;


DrawingBoard::DrawingBoard(HWND clientWindow) {
  // Now create a bitmap for that window of the same size
  HDC dc = GetDC(clientWindow);
  
  bitmapDC = CreateCompatibleDC(dc);
  GetClientRect(clientWindow, &clientRect);
  bitmap = CreateCompatibleBitmap(dc, clientRect.right, clientRect.bottom);
  SelectObject(bitmapDC, bitmap);
  
  ReleaseDC(clientWindow, dc);

  Pen::Initialize();
  Fill::Initialize();
  ColorScheme::Initialize();  

  SelectColorScheme(ColorScheme::Black);
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
  SelectPen(colorScheme->colors[currentColor%(colorScheme->colors.size())]);
}

void DrawingBoard::SelectColorScheme(const ColorScheme& scheme) {
  colorScheme = &scheme;
  currentColor = -1;
  SelectNextPenColor();
  Clear(); // Clear the board according to the newly selected color scheme
}

void DrawingBoard::Clear() const {
  FillRect(bitmapDC, &clientRect, colorScheme ? colorScheme->background : Fill::White);
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

void DrawingBoard::Fill::Initialize()
{
  White = CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
  Black = CreateSolidBrush(RGB(0x00,0x00,0x00));
}


void DrawingBoard::ColorScheme::Initialize() {
  Black = { Fill::White , { Pen::Black } };
  BlackNone = { Fill::White, { Pen::Black, Pen::None } };
  NoneBlack = { Fill::White, { Pen::None, Pen::Black } };
  RGB = { Fill::White, { Pen::Red, Pen::Green, Pen::Blue } };
  ClassiX = { Fill::White, { Pen::CxOrange, Pen::CxRed, Pen::CxYellow } };
  ClassiXBlack = { Fill::Black, { Pen::CxOrange, Pen::CxRed, Pen::CxYellow } };
  CMYK = { Fill::White, { Pen::Cyan, Pen::Magenta, Pen::Yellow, Pen::Key } };
}