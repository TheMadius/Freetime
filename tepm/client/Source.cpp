#include <iostream>
#include <locale.h>
#include "Server.h"
#include "Client.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");

	size_t* use_mem;
	Client cli("127.0.0.1", 1111);
	int n;

	while (true)
	{
		cout << "���� :\n1 - �������� ����� ������������ ����������� ������\n2 - �����\n";
		cin >> n;
		switch (n)
		{
		case 1:
			cli.speak((char*)&n);
			use_mem = (size_t*)cli.listen();
			cout << "������ ����������� ������ : " << (*use_mem) / (double)(1024 * 1024 * 1024) << " Gb\n";
			break;
		case 2:
			cli.speak((char*)&n);
			exit(1);
			break;
		default:
			break;
		}
	}
}

