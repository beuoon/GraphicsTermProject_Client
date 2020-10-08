#include <GVector3d.hpp>

#include <GVector4d.hpp>

Vector3d::Vector3d() : Vector3d(0.0, 0.0, 0.0) {
}
Vector3d::Vector3d(double _x, double _y, double _z) :
	x(_x), y(_y), z(_z) {
}

const Vector3d Vector3d::operator-(const Vector3d &_vec) {
	Vector3d res(*this);

	res.x -= _vec.x;
	res.y -= _vec.y;
	res.z -= _vec.z;

	return res;
}
const Vector3d Vector3d::cross(const Vector3d &_vec) {
	Vector3d vec1(*this), vec2(_vec);
	Vector3d res;

	res.x = vec1.y*vec2.z - vec1.z*vec2.y;
	res.y = vec1.x*vec2.z - vec1.z*vec2.x;
	res.z = vec1.x*vec2.y - vec1.y*vec2.x;

	return res;
}
Vector3d::operator Vector4d() const {
	return Vector4d(this->x, this->y, this->z, 0);
}
