#pragma once

#include <cmath>

#define WIDTH 480
#define HEIGHT 480
#define PX 32
#define FPS 60

using namespace std;

template<typename T>
struct Vector
{
	T x, y;

	Vector() { x = y = 0; }
    Vector(T px, T py) { setCartesian(px, py); }

    void setCartesian(float px, float py)
    {
        x = px;
        y = py;
    }

    void setPolar(float rho, float theta)
    {
        x = rho*std::cos(theta);
        y = rho*std::sin(theta);
    }

    void operator=(const Vector<T>& v)
    {
        x = v.x;
        y = v.y;
    }

    Vector<T> operator-() { return Vector<T> (-x, -y); }

    void operator+=(const Vector<T>& v)
    {
        x += v.x;
        y += v.y;
    }

    void operator-=(const Vector<T>& v)
    {
        x -= v.x;
        y -= v.y;
    }

    void operator*=(const float scalar)
	{
        x *= scalar;
        y *= scalar;
	}

	void operator/=(const float scalar)
	{
        if (!scalar) return;
        x /= scalar;
        y /= scalar;
	}

    float magnitude() const { return std::sqrt(x*x + y*y); }

    float angle() const
    {
        auto sgn = [](float num) { return std::abs(num)/num; };
        if (x == 0)
			return std::asin(sgn(y));
        return std::atan(y/x);
    }

    void normalize()
    {
        float norme = magnitude();
        Vector<T> &self(*this);
        if (norme)
            self /= norme;
    }

    void rotate(float theta)
    {
        Vector<T> tmp(magnitude(), theta+angle());
        set(tmp.x, tmp.y);
    }
};

template<typename T>
Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2)
{
    Vector<T> ret;
    ret.x = v1.x + v2.x;
    ret.y = v1.y + v2.y;
    return ret;
}

template<typename T>
Vector<T> operator-(const Vector<T>& v1, const Vector<T>& v2) { return v1 + (-v2); }

template<typename T>
Vector<T> operator*(const Vector<T>& v, const float scalar)
{
    Vector<T> ret;
    ret.x = v.x*scalar;
    ret.y = v.y*scalar;
	return ret;
}

template<typename T>
Vector<T> operator/(const Vector<T>& v, const float scalar)
{
	if (!scalar) return v;
    return v*(1/scalar);
}

/*template<typename T>
std::ostream& operator<<(std::ostream& flux, const Vector<T> vector)
{
    flux << '(' << vector.x << ", " << vector.y << ')';
    return flux;
}*/
