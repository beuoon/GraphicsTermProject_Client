#pragma once

class Vector3d;

class Vector4d {
public:
	Vector4d();
	Vector4d(double _x, double _y, double _z, double _w);

	const Vector4d operator+(const Vector4d &_vec) const;
	const Vector4d operator-(const Vector4d &_vec) const;
	const Vector4d operator*(const double &scala) const;
	friend const Vector4d operator*(const double &scala, const Vector4d &vec);

	const Vector4d operator+=(const Vector4d &_vec);
	const Vector4d operator-=(const Vector4d &_vec);
	const Vector4d operator*=(const double &scala);
	operator Vector3d() const;

	double &operator[](int idx);
	const double &operator[](int idx) const;

	double x, y, z, w;
};

const Vector4d operator*(const double &scala, const Vector4d &vec);