#pragma once


/** This class encapsulates the bitmap, and it's memory dc and provides functions to draw into it.
 */
class DrawingBoard {
public:
  /** Creates a bitmap with the same size as the passed client window.
   */
  DrawingBoard(HWND clientWindow);

  const RECT& Size() const;


  Vector Center() const;

  Vector BottomCenter() const;
  Vector TopCenter() const;

  /** Draws a line on the bitmap with the currently selected pen
   */
  void DrawLine(Vector from, Vector to) const;

  /** Selects the given pen into the bitmap dc
   */
  void SelectPen(HPEN pen) const;

  /** Fills the whole bitmap with white color
  */
  void Clear() const;

  /** Implicit conversion to the HDC to draw into the bitmap or copy from it
   */
  operator HDC() const;

  /** This struct is more a namespace for the pen colors
  */
  struct Pen {
    /** Creates the Pens
    */
    static void Initialize();

    static HPEN None, White, Black, Red, Green, Blue;
  };

private:
  RECT clientRect;
  HDC bitmapDC;
  HBITMAP bitmap;
};

