#include "stdafx.h"

namespace {
  const float PI = 3.14159265359f;
}

const Vector Vector::Up(0,-1);
const Vector Vector::Left(-1,0);
const Vector Vector::Down(0,1);
const Vector Vector::Right(1,0);

Vector::Vector(float x, float y) : x(x), y(y) {}
Vector::Vector(const Vector & other) : x(other.x), y(other.y) {}
Vector::Vector() : x(0), y(0) {}

int Vector::XPos() const {
  return static_cast<int>(x+0.5);
}

int Vector::YPos() const {
  return static_cast<int>(y+0.5);
}

Vector Vector::operator+(const Vector& other) const {
  return Vector(x+other.x, y+other.y);
}

Vector Vector::operator-(const Vector& other) const
{
  return Vector(x-other.x, y-other.y);
}

Vector Vector::operator*(float f) const {
  return Vector(x*f, y*f);
}

Vector& Vector::operator+=(const Vector& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector& Vector::operator*=(float f) {
  x *= f;
  y *= f;
  return *this;
}

Vector & Vector::operator=(const Vector& other) {
  x = other.x;
  y = other.y;
  return *this;
}

Vector Vector::Rotate(float angle) const {
  float radAngle = angle*PI / 180;
  return Vector((x * cos(radAngle)) - (y * sin(radAngle)),
    (x * sin(radAngle)) + (y * cos(radAngle)));
}

float Vector::Length() const {
  return sqrt(x*x + y*y);
}
