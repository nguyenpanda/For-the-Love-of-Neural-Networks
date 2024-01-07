//
// Created by Hà Tường Nguyên on 11/6/23.
//

#include "Vector.h"

Vector::Vector(long double x, long double y) {
    this->y = y;
    this->x = x;
}

long double Vector::getX() const {
    return x;
}

long double Vector::getY() const {
    return y;
}

void Vector::setX(long double new_X) {
    x = new_X;
}

void Vector::setY(long double new_Y) {
    y = new_Y;
}

std::string Vector::toStr(int precision) const {
    std::stringstream ss;
    ss << std::setprecision(precision) << std::fixed << "(" << x << ", " << y << ")";
    return ss.str();
}

Polar Vector::toPolar() const {
    long double r, a;

    if (x == 0)
        a = PI_2;

    if (x < 0) {
        a = std::atan(y / x);

        if (a < 0)
            a += PI;
        else if (a > 0)
            a -= PI;
    } else
        a = std::atan(y / x);

    r = std::hypot(x, y);

    Polar new_polar(r, a);
    return new_polar;
}

Vector Vector::operator+(const Vector &vector) const {
    Vector new_vector(0, 0);

    new_vector.x = x + vector.x;
    new_vector.y = y + vector.y;

    return new_vector;
}

Vector Vector::operator+=(const Vector &vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector Vector::operator-(const Vector &vector) const {
    Vector new_vector(0, 0);

    new_vector.x = x - vector.x;
    new_vector.y = y - vector.y;

    return new_vector;
}

Vector Vector::operator-=(const Vector &vector) {
    this->x -= vector.x;
    this->y -= vector.y;
    return *this;
}

long double Vector::operator*(const Vector &vector) const {
    long double dot_product = x * vector.x + y * vector.y;
    return dot_product;
}

bool Vector::operator==(const Vector &vector) const {
    if (x * vector.y - vector.x * y) {
        return true;
    }

    return false;
}

Vector Vector::operator+(const long double scalar) const {
    return Vector(x + scalar, y + scalar);
}

Vector Vector::operator+=(const long double scalar) {
    this->x += scalar;
    this->y += scalar;
    return *this;
}

Vector Vector::operator-(const long double scalar) const {
    return Vector(x - scalar, y - scalar);
}

Vector Vector::operator-=(const long double scalar) {
    this->x -= scalar;
    this->y -= scalar;
    return *this;
}

Vector Vector::operator*(const long double scalar) const {
    return Vector(x * scalar, y * scalar);
}

Vector Vector::operator*=(const long double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector Vector::operator/(const long double scalar) const {
    return Vector(x / scalar, y / scalar);
}

Vector Vector::operator/=(const long double scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

Vector operator+(const long double scalar, Vector &vector) {
    return Vector(vector.x + scalar, vector.y + scalar);
}

Vector operator-(const long double scalar, Vector &vector) {
    return Vector(vector.x - scalar, vector.y - scalar);
}

Vector operator*(const long double scalar, Vector &vector) {
    return Vector(vector.x * scalar, vector.y * scalar);
}

Vector operator/(const long double scalar, Vector &vector) {
    return Vector(vector.x / scalar, vector.y / scalar);
}

std::ostream &operator<<(std::ostream &COUT, const Vector &vector) {
    COUT << vector.toStr();
    return COUT;
}

long double Vector::module() const {
    return std::hypot(x, y);
}

long double Vector::angle(Vector &vector, bool radian) const {
    long double cos =  *this * vector / (this->module() + vector.module());
    if (radian)
        return std::acos(cos);

    return std::acos(cos) * 180 / PI;
}

bool Vector::isTrueOrthogonal(Vector &vector) const {
    if (x * vector.x + y * vector.y == 0)
        return true;
    return false;
}

bool Vector::isOrthogonal(Vector &vector, float precision) const {
    long double angle = std::abs(this->angle(vector)) - PI_2;
    precision = std::pow(10, -precision);

    if (std::abs(angle) < precision) {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Polar::Polar(long double radius, long double argument) {
    setRadius(radius);
    setArgument(argument);
}

long double Polar::getRadius() const {
    return radius;
}

long double Polar::getArgument() const {
    return argument;
}

void Polar::setRadius(long double new_radius) {
    if (new_radius < 0) {
        throw std::invalid_argument("Radius must be non-negative.");
    }
    radius = new_radius;
}

void Polar::setArgument(long double new_argument) {
    new_argument = std::fmod(new_argument, PI2);

    if (new_argument < 0) {
        new_argument += PI2;
    }

    if (new_argument > PI) {
        new_argument -= PI2;
    }

    argument = new_argument;
}

std::string Polar::toStr(int precision) const {
    std::stringstream ss;
    ss << std::setprecision(precision) << std::fixed << radius << "∠(" << argument << ")";
    return ss.str();
}

Vector Polar::toCartesian() const {
    long double x, y;

    x = radius * std::cos(argument);
    y = radius * std::sin(argument);

    Vector new_vector(x, y);

    return new_vector;
}

Polar Polar::operator+(const Polar &polar) const {
    Vector new_vector = toCartesian() + polar.toCartesian();
    return new_vector.toPolar();
}

Polar Polar::operator-(const Polar &polar) const {
    Vector new_vector = toCartesian() - polar.toCartesian();
    return new_vector.toPolar();
}

long double Polar::operator*(const Polar &polar) const {
    return radius * polar.radius * std::cos(argument - polar.argument);
}

Polar Polar::operator+(const long double scalar) const {
    Vector new_vector = toCartesian() + Vector(scalar, scalar);
    return new_vector.toPolar();
}

Polar Polar::operator-(const long double scalar) const {
    Vector new_vector = toCartesian() - Vector(scalar, scalar);
    return new_vector.toPolar();
}

Polar Polar::operator*(const long double scalar) const {
    return Polar(radius * scalar, argument);
}

Polar Polar::operator/(const long double scalar) const {
    return Polar(radius / scalar, argument);
}

Polar operator+(const long double scalar, Polar &vector) {
    Vector new_vector = vector.toCartesian() + Vector(scalar, scalar);
    return new_vector.toPolar();
}

Polar operator-(const long double scalar, Polar &vector) {
    Vector new_vector = vector.toCartesian() - Vector(scalar, scalar);
    return new_vector.toPolar();
}

Polar operator*(const long double scalar, Polar &vector) {
    return Polar(vector.radius * scalar, vector.argument);
}

Polar operator/(const long double scalar, Polar &vector) {
    return Polar(vector.radius / scalar, vector.argument);
}

std::ostream &operator<<(std::ostream &COUT, const Polar &polar) {
    COUT << polar.toStr();
    return COUT;
}

long double Polar::module() const {
    return radius;
}