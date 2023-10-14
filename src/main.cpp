#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "game_engine/GameManager.hpp"
#include "game_engine/screens/Menu.hpp"
#include "util/Util.hpp"

using namespace std;

int main() {
	system("Cls");
	srand(time(0));

#ifdef UNICODE
	// Avoid conversion problems between char and WCHAR (from windows.h)
	WCHAR title[14] = { 'A', 'l', 'b', 'e', 'r', 't', '\'', 's', ' ', 'T', 'a', 'l', 'e', '\0' };

	SetConsoleTitle(&title[0]);
#else
	// Avoid conversion problems between char and TCHAR (from windows.h)
	TCHAR title[14] = { 'A', 'l', 'b', 'e', 'r', 't', '\'', 's', ' ', 'T', 'a', 'l', 'e', '\0' };

	SetConsoleTitle(&title[0]);
#endif /* UNICODE */

	GameManager gameManager = GameManager();
	Menu menu = Menu(&gameManager);
	gameManager.setActiveScreen(&menu);
	gameManager.start();

	menu.destroy(); // Every existing object currently in heap should be accessible (for deletion) from here
	FlushConsoleInputBuffer(getInputHandle());
	system("Cls");
	showConsoleCursor();
	return 0;
}
