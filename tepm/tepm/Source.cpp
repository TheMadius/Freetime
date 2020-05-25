#include <iostream>
#include <locale.h>
#include "Server.h"
#include "Client.h"

using namespace std;

void client()
{
	Client cli("127.0.0.1", 1111);
	
	size_t* use_mem;

	use_mem = (size_t *)cli.listen();

	cout << "Занято оперативной памяти : "<< (*use_mem)/(double)(1024*1024*1024) << " Gb";

}

int main()
{
	setlocale(LC_ALL, "ru");
	MEMORYSTATUS theStatus;
	ZeroMemory(&theStatus, sizeof(theStatus));
	theStatus.dwLength = sizeof(theStatus);
	GlobalMemoryStatus(&theStatus);

	thread t(client);

	Server ser(1111);

	ser.wait_Client();

	size_t use_mem = theStatus.dwTotalPhys - theStatus.dwAvailPhys;

	ser.speak((char*)&(use_mem));

	t.join();
}

