#pragma once



/** This class represents one single fractal element to be drawn.
 */
class Fractal {
public:
  Fractal(Vector center, Vector direction); //TODO: parameters


  /** Draws the next fractal step 
   */
  void draw(DrawingBoard& drawingBoard) const;


};