#include <GVector4d.hpp>

#include <GVector3d.hpp>

Vector4d::Vector4d() : Vector4d(0.0, 0.0, 0.0, 0.0) {
}
Vector4d::Vector4d(double _x, double _y, double _z, double _w) :
	x(_x), y(_y), z(_z), w(_w) {
}

const Vector4d Vector4d::operator+(const Vector4d &_vec) const {
	Vector4d res(*this);

	res += _vec;

	return res;
}
const Vector4d Vector4d::operator-(const Vector4d &_vec) const {
	Vector4d res(*this);

	res -= _vec;

	return res;
}
const Vector4d Vector4d::operator*(const double &scala) const {
	Vector4d res(*this);

	res *= scala;

	return res;
}
const Vector4d operator*(const double &scala, const Vector4d &vec) {
	Vector4d res(vec);

	res *= scala;

	return res;
}

const Vector4d Vector4d::operator+=(const Vector4d &_vec) {
	this->x += _vec.x;
	this->y += _vec.y;
	this->z += _vec.z;
	this->w += _vec.w;

	return *this;
}
const Vector4d Vector4d::operator-=(const Vector4d &_vec) {
	this->x -= _vec.x;
	this->y -= _vec.y;
	this->z -= _vec.z;
	this->w -= _vec.w;

	return *this;
}
const Vector4d Vector4d::operator*=(const double &scala) {
	this->x *= scala;
	this->y *= scala;
	this->z *= scala;
	this->w *= scala;

	return *this;
}
Vector4d::operator Vector3d() const {
	return Vector3d(this->x, this->y, this->z);
}

double &Vector4d::operator[](int idx) {
	switch (idx) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
}
const double &Vector4d::operator[](int idx) const {
	switch (idx) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
}
