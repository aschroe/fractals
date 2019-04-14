#include "stdafx.h"

FractalElement::FractalElement() {}

FractalElement::FractalElement(Vector position, Vector direction) : position(position), direction(direction) {}
FractalElement::FractalElement(const FractalElement & other) : position(other.position), direction(other.direction) {}

FractalElement& FractalElement::operator=(const FractalElement& other) {
  position = other.position;
  direction = other.direction;
  return *this;
}



Fractal::Fractal(const DrawingBoard& board, int branches) : board(board), branches(branches), reductionFactor(0.5f), elementQueue(500000), halfTurn(false) {
  Reset(branches);
}

void Fractal::Draw() {
  if (elementQueue.empty() && --completedTicks <= 0) {
    if (++branches > 5) {
      branches = 2;
      halfTurn = !halfTurn;
      if (!halfTurn) {
        ++branches;
      }
    }
    Reset(branches);
    return;
  }

  elementQueue.clear();

  // Swap out the queue for an emtpy one and process the queue
  for (auto& element : elementQueue.getSecondary()) {
    board.DrawLine(element.position, element.position + element.direction);
    Branch(element);
  }
}

void Fractal::Branch(const FractalElement& element) {
  const float branchAngle = 360.0f / branches;
  Vector direction = element.direction;
  Vector position = element.position + direction;

  if (direction.Length() * reductionFactor < 1.0f) {
    // Do not continue branching after the branches become to small to notice them
    return;
  }

  if (halfTurn) {
    direction = direction.Rotate(branchAngle*0.5f);
  }

  for (int i = 0; i < branches; ++i) {
    elementQueue.push_back(FractalElement(position, direction * reductionFactor));
    direction = direction.Rotate(branchAngle);
  }
}

void Fractal::Reset(int branches) {
  elementQueue.clear();
  board.Clear();
  Branch(FractalElement(board.BottomCenter(), board.Center() - board.BottomCenter()));
  completedTicks = WAIT_COMPLETED_SECONDS * FractalApp::TICKS_PER_SECOND;
}

