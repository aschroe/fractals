#pragma once


class Vector {
public:
  static const Vector Up;
  static const Vector Down;
  static const Vector Left;
  static const Vector Right;

  Vector();
  Vector(float x, float y);
  Vector(const Vector& other);

  int XPos() const;
  int YPos() const;


  Vector operator+(const Vector other) const;
  Vector operator*(float f) const;

  Vector& operator+=(const Vector other);
  Vector& operator*=(float f);

  Vector& operator=(const Vector& other);


  Vector Rotate(float angle) const;

  float Length() const;


  float x,y;
};
