#pragma once

#include <Client.hpp>
#include <GVector.hpp>
#include <GObject.hpp>
#include <GCamera.hpp>

#include <list>
#include <vector>

using namespace std;

constexpr auto SERVER_IP = "114.29.136.181";
constexpr auto PORT = 45678;

class Game {
public:
	static const UINT WINDOW_WIDTH, WINDOW_HEIGHT;
	static const UINT FPS;
	static const char *WINDOW_TITLE;

public:
	Game();
	~Game();

	void run();
	void stop();

	void update(int frameClock);
	void render();
	
	inline void setOnRecv(OnRecvFunc _onRecv) {
		client.setOnRecv(_onRecv);
	}
	void onRecv(const char *buff, const int &len);

	void display();
	void keyboard(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);
	void specialKeyboard(int key, int x, int y);
	void specialKeyboardUp(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouseEntry(int state);
	void mouseDrag(int x, int y);

private:
	Client client;
	GCamera camera;

	bool bRun = false;
	bool keyboardState[256] = { false, };
	bool specialKeyboardState[256] = { false, };
	bool bCheckMouseCenter = false;
	int mouseX = 0, mouseY = 0;

	double xAngle = 0, yAngle = 0;

	vector<GObject *> map;
	list<GObject *> players;
};
