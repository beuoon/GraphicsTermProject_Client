#pragma once

#include <cmath>
#include <GVector3d.hpp>
#include <GVector4d.hpp>

class Vector2d {
public:
	double x = 0.0, y = 0.0;
};

class Size3d {
public:
	Size3d() : Size3d(0.0, 0.0, 0.0) {
	}
	Size3d(double _w, double _h, double _d) :
		w(_w), h(_h), d(_d) {
	}

	double w, h, d;
};

class Matrix4d {
public:
	double *operator[](int idx) {
		return m[idx];
	}
	const double *operator[](int idx) const {
		return m[idx];
	}
	const Matrix4d operator*(const Matrix4d &_mat) const {
		Matrix4d mat;
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat[i][j] = 0;
				for (int k = 0; k < 4; k++)
					mat[i][j] += (*this)[i][k] * _mat[k][j];
			}
		}

		return mat;
	}
	const Vector4d operator*(const Vector4d &_vec) const {
		Vector4d vec;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				vec[i] += (*this)[i][j] * _vec[j];
		}

		return vec;
	}

	static Matrix4d GetYawMatrix(double angle) {
		Matrix4d mat = IDENTITY;
		double c = cos(angle);
		double s = sin(angle);

		mat[1][1] = c;
		mat[1][2] = s;
		mat[2][1] = -s;
		mat[2][2] = c;

		return mat;
	}
	static Matrix4d GetPitchMatrix(double angle) {
		Matrix4d mat = IDENTITY;
		double c = cos(angle);
		double s = sin(angle);

		mat[0][0] = c;
		mat[0][2] = s;
		mat[2][0] = -s;
		mat[2][2] = c;

		return mat;
	}
	static Matrix4d GetRollMatrix(double angle) {
		Matrix4d mat = IDENTITY;
		double c = cos(angle);
		double s = sin(angle);

		mat[0][0] = c;
		mat[0][1] = s;
		mat[1][0] = -s;
		mat[1][1] = c;

		return mat;
	}

	double m[4][4];
	static const Matrix4d IDENTITY;
};
