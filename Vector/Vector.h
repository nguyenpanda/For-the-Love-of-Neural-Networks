//
// Created by Hà Tường Nguyên on 11/6/23.
//

#ifndef HCMUTCPP_VECTOR_H
#define HCMUTCPP_VECTOR_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "cmath"

#define PI2  6.28318530717958647693
#define PI   3.14159265358979323846
#define PI_2 1.57079632679489661923
#define PI3_4 2.35619449019234492885
#define PI_3 1.04719755119659774615
#define PI_4 0.78539816339744830962
#define PI_5 0.62831853071795864769
#define PI_6 0.52359877559829887308
#define PI_8 0.39269908169872415481
#define PI_12 0.26179938779914943654

class Polar;
class Vector;
class Coordinate;

class Coordinate {
public:
    virtual ~Coordinate() = default;

    [[maybe_unused]] [[nodiscard]] virtual long double module() const = 0;
};

class Vector : public Coordinate {
protected:
    long double x, y;
public:
    Vector(long double x, long double y);

    ~Vector() override = default;

    [[maybe_unused]] [[nodiscard]] long double getX() const;

    [[maybe_unused]] void setX(long double new_X);

    [[maybe_unused]] [[nodiscard]] long double getY() const;

    [[maybe_unused]] void setY(long double new_X);

    ////////////////////////////////////////////////////////////////////

    [[maybe_unused]] [[nodiscard]] bool operator==(const Vector &vector) const;

    [[maybe_unused]] [[nodiscard]] Vector operator+(const Vector &vector) const;

    [[maybe_unused]] Vector operator+=(const Vector &vector);

    [[maybe_unused]] [[nodiscard]] Vector operator-(const Vector &vector) const;

    [[maybe_unused]] Vector operator-=(const Vector &vector);

    [[maybe_unused]] [[nodiscard]] long double operator*(const Vector &vector) const;

    ////////////////////////////////////////////////////////////////////

    [[maybe_unused]] [[nodiscard]] Vector operator+(const long double scalar) const;

    [[maybe_unused]] Vector operator+=(const long double scalar);

    [[maybe_unused]] [[nodiscard]] Vector operator-(const long double scalar) const;

    [[maybe_unused]] Vector operator-=(const long double scalar);

    [[maybe_unused]] [[nodiscard]] Vector operator*(const long double scalar) const;

    [[maybe_unused]] Vector operator*=(const long double scalar);

    [[maybe_unused]] [[nodiscard]] Vector operator/(const long double scalar) const;

    [[maybe_unused]] Vector operator/=(const long double scalar);

    ////////////////////////////////////////////////////////////////////

    friend Vector operator+(const long double scalar, Vector& vector);

    friend Vector operator-(const long double scalar, Vector& vector);

    friend Vector operator*(const long double scalar, Vector& vector);

    friend Vector operator/(const long double scalar, Vector& vector);

    friend std::ostream &operator<<(std::ostream &COUT, const Vector &vector);

    ////////////////////////////////////////////////////////////////////

    [[maybe_unused]] [[nodiscard]] std::string toStr(int precision = 4) const;

    [[maybe_unused]] [[nodiscard]] Polar toPolar() const;

    [[maybe_unused]] [[nodiscard]] long double module() const override;

    [[maybe_unused]] [[nodiscard]] long double angle(Vector& vector, bool radian=true) const;

    [[maybe_unused]] [[nodiscard]] bool isTrueOrthogonal(Vector& vector) const;

    [[maybe_unused]] [[nodiscard]] bool isOrthogonal(Vector& vector, float precision=2) const;

    ////////////////////////////////////////////////////////////////////
};

class Polar : public Coordinate {
protected:
    long double radius, argument;
public:
    Polar(long double radius, long double argument);

    ~Polar() override = default;

    [[maybe_unused]] [[nodiscard]] long double getRadius() const;

    [[maybe_unused]] void setRadius(long double new_radius);

    [[maybe_unused]] [[nodiscard]] long double getArgument() const;

    [[maybe_unused]] void setArgument(long double new_argument);

    ////////////////////////////////////////////////////////////////////

    [[maybe_unused]] [[nodiscard]] Polar operator+(const Polar &polar) const;

    [[maybe_unused]] [[nodiscard]] Polar operator-(const Polar &polar) const;

    [[maybe_unused]] [[nodiscard]] long double operator*(const Polar &polar) const;

    ////////////////////////////////////////////////////////////////////

    [[maybe_unused]] [[nodiscard]] Polar operator+(const long double scalar) const;

    [[maybe_unused]] [[nodiscard]] Polar operator-(const long double scalar) const;

    [[maybe_unused]] [[nodiscard]] Polar operator*(const long double scalar) const;

    [[maybe_unused]] [[nodiscard]] Polar operator/(const long double scalar) const;

    ////////////////////////////////////////////////////////////////////

    friend Polar operator+(const long double scalar, Polar& vector);

    friend Polar operator-(const long double scalar, Polar& vector);

    friend Polar operator*(const long double scalar, Polar& vector);

    friend Polar operator/(const long double scalar, Polar& vector);

    friend std::ostream &operator<<(std::ostream &COUT, const Polar &polar);

    ////////////////////////////////////////////////////////////////////

    [[maybe_unused]] [[nodiscard]] std::string toStr(int precision = 4) const;

    [[maybe_unused]] [[nodiscard]] Vector toCartesian() const;

    [[maybe_unused]] [[nodiscard]] long double module() const override;
};
#endif //HCMUTCPP_VECTOR_H
