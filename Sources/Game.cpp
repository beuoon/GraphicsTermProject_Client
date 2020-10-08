#include <Game.hpp>

#define _USE_MATH_DEFINES

#include <iostream>

#include <GL/GL.h>
#include <GL/freeglut.h>
#include <math.h>

using namespace std;

const UINT Game::WINDOW_WIDTH = 1000, Game::WINDOW_HEIGHT = 1000;
const UINT Game::FPS = 144;
const char *Game::WINDOW_TITLE = "OTP";

Game::Game() : camera(Vector4d(-5, 0, 5, 0)), client(SERVER_IP, PORT) {
	camera.rotate(-M_PI/4., 0);
	//map.push_back(new Cube(Vector3d(0, 0, 0), Size3d(5, 5, 5)));

	map.push_back(new Cube(Vector3d(0, -5, 0), Size3d(10, 1, 10)));
	map.push_back(new Cube(Vector3d(0, 5, 0), Size3d(10, 1, 10)));
	map.push_back(new Cube(Vector3d(5, 0, 0), Size3d(1, 10, 10)));
	map.push_back(new Cube(Vector3d(-5, 0, 0), Size3d(1, 10, 10)));
	map.push_back(new Cube(Vector3d(0, 0, 5), Size3d(10, 10, 1)));
	map.push_back(new Cube(Vector3d(0, 0, -5), Size3d(10, 10, 1)));


	//glBegin(GL_POLYGON);
	//{
	//	glColor3f(0.0, 1.0, 0);
	//	glVertex3d(-0.5, 0.5, 0);
	//	glVertex3d(-0.5, -0.5, 0);
	//	glVertex3d(0.5, -0.5, 0);
	//	glVertex3d(0.5, 0.5, 0);
	//}
	//glEnd();
}
Game::~Game() {
	for (auto obj : map)
		delete obj;
	map.clear();
}

void Game::run() {
	bRun = true;

	//try {
	//	client.init();
	//}
	//catch (const char *error) {
	//	cout << error << endl;
	//	glutLeaveMainLoop();
	//	return;
	//}

	//while (client.checkConnect()) {
	//	string msg;
	//	cin >> msg;
	//	if (msg == "end")
	//		break;
	//	Sleep(1000);
	//}
	int currFrameClock, prevFrameClock = clock();
	int frameClock;

	while (bRun) {
		currFrameClock = clock();
		frameClock = currFrameClock - prevFrameClock;
		prevFrameClock = currFrameClock;

		update(frameClock);

		//Sleep(1000/144);
	}

	//client.close();
	glutLeaveMainLoop();
}
void Game::stop() {
	bRun = false;
}
void Game::update(int frameClock) {
	double speed = 2 * (frameClock / 1000.0); // 1초에 2씩 이동
	Vector3d moveVec;

	if (keyboardState['w'])	moveVec.z += speed;
	if (keyboardState['s'])	moveVec.z -= speed;
	if (keyboardState['d'])	moveVec.x += speed;
	if (keyboardState['a'])	moveVec.x -= speed;
	if (keyboardState[' '])	moveVec.y += speed;
	if (specialKeyboardState[GLUT_KEY_SHIFT_L])	moveVec.y -= speed;

	camera.move(moveVec);

	for (auto obj : map)
		obj->update();

	if (keyboardState['f']) stop();
}
void Game::render() {
	if (keyboardState['q'])	glEnable(GL_LIGHT0);
	if (keyboardState['e'])	glDisable(GL_LIGHT0);
	camera.render();

	for (auto obj : map)
		obj->render();
}

void Game::onRecv(const char *buff, const int &len) {
}

void Game::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);

	render();

	glutSwapBuffers();
}
void Game::keyboard(unsigned char key, int x, int y) {
	keyboardState[key] = true;
}
void Game::keyboardUp(unsigned char key, int x, int y) {
	keyboardState[key] = false;
}
void Game::specialKeyboard(int key, int x, int y) {
	if (0 <= key && key < 256)
		specialKeyboardState[key] = true;
}
void Game::specialKeyboardUp(int key, int x, int y) {
	if (0 <= key && key < 256)
		specialKeyboardState[key] = false;
}
void Game::mouse(int button, int state, int x, int y) {
}
void Game::mouseEntry(int state) {
	if (state != GLUT_LEFT) {
		bCheckMouseCenter = false;
	}
}
void Game::mouseDrag(int x, int y) {
	const int centerX = WINDOW_WIDTH/2, centerY = WINDOW_HEIGHT/2;

	if (GetForegroundWindow() != FindWindow(NULL, Game::WINDOW_TITLE))
		return;

	if (!bCheckMouseCenter) {
		bCheckMouseCenter = true;
		glutWarpPointer(centerX, centerY);
		return;
	}

	xAngle = (centerX - x)*M_1_PI/60.;
	yAngle = -(centerY - y)*M_1_PI/60.;
	
	camera.rotate(xAngle, yAngle);

	glutWarpPointer(centerX, centerY);
}
