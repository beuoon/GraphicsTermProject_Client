#pragma once

class Vector4d;

class Vector3d {
public:
	Vector3d();
	Vector3d(double _x, double _y, double _z);

	const Vector3d operator-(const Vector3d &_vec);
	const Vector3d cross(const Vector3d &_vec);
	operator Vector4d() const;

	double x, y, z;
};