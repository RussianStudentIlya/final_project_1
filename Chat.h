#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"
using namespace std;

/*-----»сключение-----*/
struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: user login is busy"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "error: user name is busy"; }
};
/*-----*/

class Chat {
	bool isChatWork_ = false; /// ¬лаг дл€ выхода из меню
	std::vector<User> users_; /// ƒинамический массив (вектор) текущих пользователей
	std::vector<Message> messages_; /// ƒинамический массив (вектор) сообщений
	std::shared_ptr<User> currentUser_ = nullptr; /// показывает текущего пользовател€

	void login();/// јвторизаци€ в чат по уже созданному логину и паролю
	void signUp(); /// –егистраци€ пользовател€ в чате
	void showChat() const; // показывает отправленные сообщени€, конкретному пользователю или всем
	void showAllUsersName() const; /// ѕоказывает  список пользователей чата
	void addMessage(); //‘ормировани€ сообщени€
	std::vector<User>& getAllUsers() { return users_; }
	std::vector<Message>& getAllMessage() { return messages_; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;

public:
	void start();/// запуск чата
	bool isChatWork() const { return isChatWork_; } /// проверка, работает чат или нет (если true - чат работает, если false - нет)
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showLoginMenu(); /// ќтображение стартового меню программы - ћеню верхнего уровн€
	void showUserMenu(); // отображает внутреннее меню чата, после авторизации пользовател€
};
