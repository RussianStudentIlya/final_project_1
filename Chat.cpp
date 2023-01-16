#include <iostream>
#include "Chat.h"

void Chat::start() {
	isChatWork_ = true; /// ���� ��� ������ �� ����
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto &user : users_) // ���� �������� �� ����� ������� �������������
	{
		if (login == user.getUserLogin()) // �������� ���������� ������
			return std::make_shared<User>(user); /// ���������� ��������� �� �������� �������������
	}

	return nullptr;

}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
	for (auto &user : users_)
	{
		if (name == user.getUserName())
			return std::make_shared<User>(user); /// ���������� ��������� �� �������� ������������� �� �����
	}

	return nullptr;

}

void Chat::login() /// ����������� � ��� �� ��� ���������� ������ � ������
{
	std::string login, password;
	char operation;

	do
	{
		std::cout << "�����: ";
		std::cin >> login;
		std::cout << "������: ";
		std::cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;

			std::cout << "������ �����..." << std::endl;
			std::cout << "������� (0) ����� ����� ��� ������ ������ ����� ��������� ����: ";
			std::cin >> operation;

			if (operation == '0')
				break;

		}

	} while (!currentUser_);
}

void Chat::signUp() /// ����������� ������������ � ����
{
	std::string login, password, name;

	std::cout << "�����: ";
	std::cin >> login;
	std::cout << "������: ";
	std::cin >> password;
	std::cout << "��� ������������: ";
	std::cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>(user);
}

void Chat::showChat() const // ���������� ������������ ���������, ����������� ������������ ��� ����
{
	std::string from;
	std::string to;

	std::cout << "- - - ��� - - -" << std::endl;

	for (auto& mess : messages_)
	{
		/// ���������� ���������: �� �������� ������������, ��� ���� � ��� ����
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom()) ? "�" : getUserByLogin(mess.getFrom())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(���� (all))";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "�" : getUserByLogin(mess.getTo())->getUserName();
			}

			std::cout << "��������� ��: " << from << " ����: " << to << std::endl;
			std::cout << "�����: " << mess.getText() << std::endl;
		}
	}

	std::cout << "- - - - - - - - - - - -" << std::endl;
}

void Chat::showLoginMenu() /// ����������� ���������� ���� ��������� - ���� �������� ������
{
	currentUser_ = nullptr;

	char operation;

	do
	{
		std::cout << "\033[33m" << "(1)����" << std::endl;
		std::cout << "(2)�����������" << std::endl;
		std::cout << "(3)������������" << std::endl;
		std::cout << "(0)�����" << std::endl;
		std::cout << "\033[36m" << ">> " << "\033[0m";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '3':
			std::cout << "��� �������� ��������:" << endl;
			std::cout << "1. ������� �������� - ������, ������ ��� ������� Main.cpp � Chat.h" << endl;
			std::cout << "2. ���� ������� - ������ ��� ������� User.h � Message.h." << endl;
			std::cout << "3. Reido Aya - ������ ��� ������ Chat.cpp." << endl;
			break;
		case '0':
			isChatWork_ = false;
			break;
		default:
			std::cout << "1 ��� 2 ..." << std::endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // ���������� ���������� ���� ����, ����� ����������� ������������
{
	char operation;

	std::cout << "������, " << currentUser_->getUserName() << std::endl;

	while (currentUser_)
	{
		std::cout << "(1)�������� ��� | (2)��������� ��������� | (3)�������� ��� � ���� | (0)����� ";

		std::cout << std::endl
			<< ">> ";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << "�������� �����.." << std::endl;
			break;
		}


	}
}

void Chat::showAllUsersName() const /// ����������  ������ ������������� ����
{
	std::cout << "- - - � ���� - - -" << std::endl;
	for (auto& user : users_)
	{
		std::cout << user.getUserName();

		if (currentUser_->getUserLogin() == user.getUserLogin())
			std::cout << " (�) ";
		std::cout << std::endl;
	}
	std::cout << "- - - - - - - - -" << std::endl;
}

void Chat::addMessage() //������������ ���������
{
	std::string to, text;

	std::cout << "���� (������������ ��� ����(������� all)): ";
	std::cin >> to;
	std::cout << "���������: ";
	std::cin.ignore(); // ������������ ����� ��������� ����������� �������
	getline(std::cin, text); /// ���� ���������� ��������� � ���������

	if (!(to == "all" || getUserByName(to))) // ���� �� ������� ����� ���������� �� �����
	{
		std::cout << "����� ������������ �� ������" << to << std::endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });

}