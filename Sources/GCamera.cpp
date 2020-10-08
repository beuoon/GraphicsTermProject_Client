#include <GCamera.hpp>

const Vector4d GCamera::BASE_DIR(0, 0, -1, 0);
const Vector4d GCamera::BASE_UP(0, 1, 0, 0);

GCamera::GCamera(Vector4d _pos) : GCamera(_pos, BASE_DIR, BASE_UP) {
}
GCamera::GCamera(Vector4d _pos, Vector4d _dir, Vector4d _up) {
	set(_pos, _dir, _up);
}

void GCamera::set(Vector4d _pos, Vector4d _dir, Vector4d _up) {
	pos = _pos;
	dir = _dir;
	up = _up;
}

void GCamera::render() {
	Matrix4d mat = Matrix4d::GetPitchMatrix(xAngle) * Matrix4d::GetYawMatrix(yAngle);
	dir = mat * BASE_DIR;
	up = mat * BASE_UP;
	center = pos + dir;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, pos.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z);
}

void GCamera::move(Vector3d _vec) {
	Vector3d xAxis = dir.cross(up);
	Vector3d yAxis(0, 1, 0);
	Vector3d &zAxis = dir;

	pos += _vec.x * xAxis;
	pos += _vec.y * yAxis;
	pos += _vec.z * zAxis;
}
void GCamera::rotate(double _xAngle, double _yAngle) {
	xAngle += _xAngle;
	yAngle += _yAngle;
}
