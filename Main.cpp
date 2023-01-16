#include <iostream>
#include "Chat.h"

int main()
{
	setlocale(LC_ALL, ""); // Для кириллицы в консоли. 
	std::cout << "Добро пожаловать в консольный чат." << std::endl;
	std::cout << "Для продолжения работы выберите одну из указанных ниже опций, нажав на соответствующую кнопку." << std::endl;
	std::cout << "=================================================================================================" << std::endl;
	Chat chat;

	chat.start();

	while (chat.isChatWork()) {

		chat.showLoginMenu();

		while (chat.getCurrentUser()) {
			chat.showUserMenu();

		}

	}

	return 0;
}



