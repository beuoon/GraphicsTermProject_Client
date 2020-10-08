#pragma once

#include <GVector.hpp>
#include <GL/glut.h>

class GObject {
public:
	GObject() {

	}

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void rotate() = 0;

	bool collision(GObject *obj) {
		  
	}

protected:
	Vector3d position;
	Size3d collisionSize;
};

class Cube : public GObject {
public:
	Cube(Vector3d _position, Size3d _size) { // + Texture
		position = _position;
		size = _size;

		collisionSize = size; 

		hs.w = _size.w/2.;
		hs.h = _size.h/2.;
		hs.d = _size.d/2.;
	}

	void update() {
	}
	void render() {
		glPushMatrix();
		glTranslated(position.x, position.y, position.z);

		glColor3f(0.2, 0.0, 1.0);

		//glBegin(GL_TRIANGLES);
		//{
		//	glVertex3d(hs.w, hs.h, hs.d);
		//	glVertex3d(hs.w, -hs.h, hs.d);
		//	glVertex3d(hs.w, -hs.h, -hs.d);
		//}
		//glEnd();
		//glBegin(GL_TRIANGLES);
		//{
		//	glVertex3d(hs.w, -hs.h, -hs.d);
		//	glVertex3d(hs.w, hs.h, -hs.d);
		//	glVertex3d(hs.w, hs.h, hs.d);
		//}
		//glEnd();

		//glBegin(GL_QUADS);
		//// Front
		//glVertex3d(hs.w, hs.h, -hs.d);
		//glVertex3d(hs.w, -hs.h, -hs.d);
		//glVertex3d(-hs.w, -hs.h, -hs.d);
		//glVertex3d(-hs.w, hs.h, -hs.d);

		glBegin(GL_QUADS);
		{
			// Front
			glNormal3f(0, 0, 1);
			glVertex3d(hs.w, hs.h, hs.d);
			glVertex3d(-hs.w, hs.h, hs.d);
			glVertex3d(-hs.w, -hs.h, hs.d);
			glVertex3d(hs.w, -hs.h, hs.d);

			// Right
			glNormal3f(1, 0, 0);
			glVertex3d(hs.w, hs.h, hs.d);
			glVertex3d(hs.w, -hs.h, hs.d);
			glVertex3d(hs.w, -hs.h, -hs.d);
			glVertex3d(hs.w, hs.h, -hs.d);

			// Back
			glNormal3f(0, 0, -1);
			glVertex3d(hs.w, hs.h, -hs.d);
			glVertex3d(hs.w, -hs.h, -hs.d);
			glVertex3d(-hs.w, -hs.h, -hs.d);
			glVertex3d(-hs.w, hs.h, -hs.d);

			// Left
			glNormal3f(-1, 0, 0);
			glVertex3d(-hs.w, hs.h, -hs.d);
			glVertex3d(-hs.w, -hs.h, -hs.d);
			glVertex3d(-hs.w, -hs.h, hs.d);
			glVertex3d(-hs.w, hs.h, hs.d);

			// Top
			glNormal3f(0, 1, 0);
			glVertex3d(-hs.w, hs.h, hs.d);
			glVertex3d(hs.w, hs.h, hs.d);
			glVertex3d(hs.w, hs.h, -hs.d);
			glVertex3d(-hs.w, hs.h, -hs.d);

			// Bottom
			glNormal3f(0, -1, 0);
			glVertex3d(hs.w, -hs.h, hs.d);
			glVertex3d(-hs.w, -hs.h, hs.d);
			glVertex3d(-hs.w, -hs.h, -hs.d);
			glVertex3d(hs.w, -hs.h, -hs.d);
		}
		glEnd();

		glPopMatrix();
	}
	void rotate() {

	}

	Size3d size;
	Size3d hs;
};