#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <Game.hpp>

using namespace std;

Game game;

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000/Game::FPS, timer, 0);
}

#ifdef _DEBUG
int main(int argc, char **argv)
#else
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
#endif
{
	game.setOnRecv([](const char *buff, const int &len) {
		game.onRecv(buff, len);
	});
	thread gameThread(&Game::run, &game);

	glutInit(&__argc, __argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(Game::WINDOW_TITLE);

	glutWarpPointer(Game::WINDOW_WIDTH/2, Game::WINDOW_HEIGHT/2);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Light
	GLfloat ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos[] = { 0.0f, 0.f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 40.0);

	glutDisplayFunc([]() { game.display(); });
	glutKeyboardFunc([](unsigned char key, int x, int y) { game.keyboard(key, x, y); });
	glutKeyboardUpFunc([](unsigned char key, int x, int y) { game.keyboardUp(key, x, y); });
	glutSpecialFunc([](int key, int x, int y) { game.specialKeyboard(key, x, y); });
	glutSpecialUpFunc([](int key, int x, int y) { game.specialKeyboardUp(key, x, y); });
	glutMouseFunc([](int button, int state, int x, int y) { game.mouse(button, state, x, y); });
	glutEntryFunc([](int state) { game.mouseEntry(state); });
	glutPassiveMotionFunc([](int x, int y) { game.mouseDrag(x, y); });

	glutTimerFunc(0, timer, 0);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();

	game.stop();
	if (gameThread.joinable())
		gameThread.join();

	return 0;
}