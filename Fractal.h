#pragma once

#include "MultiPassVector.h"
#include "DualContainer.h"

/** This class represents one single fractal element to be drawn.
 */
class FractalElement {
public:
  FractalElement();
  FractalElement(Vector position, Vector direction); //TODO: parameters
  FractalElement(const FractalElement& other);

  FractalElement& operator=(const FractalElement& other);

  Vector position;
  Vector direction;
};


/** This class represents a compelte fractal to be drawn the elements to be drawn are stored in the elementQueue
 */
class Fractal {
public:
  static const int WAIT_COMPLETED_SECONDS = 5; // how many seconds to wait before continuing with the next fractal

  Fractal(const DrawingBoard& board, int branches);

  /** Draws the next fractal level in one step
   */
  void Draw();

  /** Generates branches for the given fractal element
   */
  void Branch(const FractalElement& element);

private:
  /** Starts a new fractal
   */
  void Reset(int branches);

  const DrawingBoard& board;
  DualContainer<MultiPassVector<FractalElement>> elementQueue; // The combination of MultiPassVector with DualContainer should prevent allocation lag spikes
  int branches; // Number of branching points from the current position
  float reductionFactor; // by how much the length is reduced on each branching point
  int completedTicks; // used to count down how many ticks the completed picture has been shown
  bool halfTurn;
};


