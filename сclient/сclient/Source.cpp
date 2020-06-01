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
	double max,RAM;
	cli.connectSrev();

	cout << "Ввод максимального значения ОП (Гб): ";
	cin >> max;

	while (true)
	{
		cout << "Меню :\n1 - Получить объем используемой оперативной памяти\n2 - Выход\n";
		cin >> n;
		switch (n)
		{
		case 1:
			cli.speak((char*)&n);
			use_mem = (size_t*)cli.listen();
			RAM = (*use_mem) / (double)(1024 * 1024 * 1024);
			cout << "Занято оперативной памяти : " << RAM << " Gb\n";
			if (RAM > max)
			{
				cout << "Допустимый уровень превышен!!!!!!\n";
			}
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

