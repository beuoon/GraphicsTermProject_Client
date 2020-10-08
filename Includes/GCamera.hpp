#pragma once

#include <GVector.hpp>
#include <GL/glut.h>

class GCamera {
public:
	GCamera(Vector4d _pos);
	GCamera(Vector4d _pos, Vector4d _dir, Vector4d _up);

	void set(Vector4d _pos, Vector4d _dir, Vector4d _up);

	void render();

	void move(Vector3d _vec);
	void rotate(double _xAngle, double _yAngle);

private:
	static const Vector4d BASE_DIR, BASE_UP;
	Vector4d pos;
	Vector3d center, dir, up;

	double xAngle = 0, yAngle = 0;
};
