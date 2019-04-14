#include "stdafx.h"

FractalElement::FractalElement() {}

FractalElement::FractalElement(Vector position, Vector direction) : position(position), direction(direction) {}
FractalElement::FractalElement(const FractalElement & other) : position(other.position), direction(other.direction) {}

FractalElement& FractalElement::operator=(const FractalElement& other) {
  position = other.position;
  direction = other.direction;
  return *this;
}



std::vector<FractalParameters> FractalParameters::parameterCombinations;
int FractalParameters::currentParameters = 0;

FractalParameters::FractalParameters(int branches, bool halfTurn, const DrawingBoard::ColorScheme& colorScheme) : branches(branches), halfTurn(halfTurn), colorScheme(colorScheme) {}

FractalParameters* FractalParameters::GetNext() {
  if (parameterCombinations.empty()) {
    GenerateCombinations();
    return &parameterCombinations[0];
  }

  return &parameterCombinations[++currentParameters % parameterCombinations.size()];
}

void FractalParameters::GenerateCombinations() {
  std::vector<DrawingBoard::ColorScheme*> colorSchemes = { &DrawingBoard::ColorSchemes::Black,  &DrawingBoard::ColorSchemes::BlackNone,  &DrawingBoard::ColorSchemes::RGB };
  for (auto colorScheme : colorSchemes) {
    for (int branches = 3; branches < 6; ++branches) {
      parameterCombinations.push_back(FractalParameters(branches, false, *colorScheme));
    }

    for (int branches = 2; branches < 6; ++branches) {
      parameterCombinations.push_back(FractalParameters(branches, true, *colorScheme));
    }
  }
}


Fractal::Fractal(DrawingBoard& board, int branches) : board(board), reductionFactor(0.5f), elementQueue(500000) {
  Reset(FractalParameters::GetNext());
}

void Fractal::Draw() {
  if (elementQueue.empty() && --completedTicks <= 0) {
    Reset(FractalParameters::GetNext());
    return;
  }

  elementQueue.clear();

  // Swap out the queue for an emtpy one and process the queue
  for (auto& element : elementQueue.getSecondary()) {
    board.DrawLine(element.position, element.position + element.direction);
    Branch(element);
  }

  board.SelectNextPenColor();
}

void Fractal::Branch(const FractalElement& element) {
  const float branchAngle = 360.0f / params->branches;
  Vector direction = element.direction;
  Vector position = element.position + direction;

  if (direction.Length() * reductionFactor < 1.0f) {
    // Do not continue branching after the branches become to small to notice them
    return;
  }

  if (params->halfTurn) {
    direction = direction.Rotate(branchAngle*0.5f);
  }

  for (int i = 0; i < params->branches; ++i) {
    elementQueue.push_back(FractalElement(position, direction * reductionFactor));
    direction = direction.Rotate(branchAngle);
  }
}

void Fractal::Reset(const FractalParameters* params) {
  this->params = params;
  elementQueue.clear();
  board.Clear();
  board.SelectColorScheme(params->colorScheme);
  Branch(FractalElement(board.BottomCenter(), board.Center() - board.BottomCenter()));
  completedTicks = WAIT_COMPLETED_SECONDS * FractalApp::TICKS_PER_SECOND;
}

