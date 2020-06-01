#include <iostream>
#include <locale.h>
#include "Server.h"
#include "Client.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	Server ser(1111);
	ser.wait_Client();

	while (true)
	{
		int* msg;
		msg = (int*)ser.listenClient();

		switch (*msg)
		{
		case 1:
		{
			MEMORYSTATUS theStatus;
			ZeroMemory(&theStatus, sizeof(theStatus));
			theStatus.dwLength = sizeof(theStatus);
			GlobalMemoryStatus(&theStatus);
			size_t use_mem = theStatus.dwTotalPhys - theStatus.dwAvailPhys;
			ser.speak((char*)&(use_mem));
			break;
		}
		case 2:
			exit(1);
			break;
		default:
			exit(1);
			break;
		}
	}
}

