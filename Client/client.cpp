#include "prototype.h"
#include <iostream>

HANDLE hEvent; 
HANDLE hMFile;

char Ev[] = "MyEvent";   ///іменування події
char Fn[] = "MyFile";  /// іменування файлу передачі даних
LPVOID StartMFile;  /// об'єкт з даними
char Buf[100];    /// буфер даних

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	/// відкриття події
	hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, (LPCWSTR)Ev);
	if (!hEvent)  { 
		printf("ERROR: подія не відкрита\n"); 
		system("pause");
			return 0;
	}
	/// відкриття обєкту
	hMFile=OpenFileMapping(FILE_MAP_WRITE, TRUE, (LPCWSTR)Fn);
	if (!hMFile)
	{
		printf("ERROR: файл не відкри	\n"); 
		system("pause");
			return 0;
	}
	StartMFile = MapViewOfFile(hMFile, FILE_MAP_WRITE, 0, 0, 100);
	// закриваємо дескриптор об’єкта–більше непотрібен
	CloseHandle	(hMFile);
	if (!StartMFile)
	{
		printf("ERROR: Переглядy файлу 	\n"); 
		system("pause");
			return 0;
	}
	printf("CLIENT Started\n"); 
		do {
			WaitForSingleObject(hEvent, INFINITE);///очікування події
			CopyMemory (Buf, StartMFile, 100);///зчитування даних 
			//printf("%s 	\n", Buf);


			switch (*Buf)
			{
			case '1':SortFile(1);
				CopyMemory(StartMFile, "Успiшное завершення сортування", 100);///зчитування даних
				PulseEvent(hEvent);                      /// сигнал printListFile(StartMFile);
			break;
			case '2':SortFile(2);
				CopyMemory(StartMFile, "Успiшное завершення сортування", 100);///зчитування даних
				PulseEvent(hEvent);                      /// сигнал printListFile(StartMFile);
				break;
			case '3':SortFile(3);
				CopyMemory(StartMFile, "Успiшне завершення сортування", 100);///зчитування даних
				PulseEvent(hEvent);                      /// сигнал  
				break;
			case '4':SortFile(4);
				CopyMemory(StartMFile, "Успiшне завершення сортування", 100);///зчитування даних
				PulseEvent(hEvent);                      /// сигнал 
				break;
			case '5':
				outLFile(StartMFile);
				break;
			default:
				printf("%s 	\n", Buf);
				break;
			}
			
		} while (strcmp(Buf, "Stop") != 0);
		printf("Server завершив вашу роботу	\n");
		system("pause");
		UnmapViewOfFile	(StartMFile);
		return 0;
}

//*функція надання даних про вміст папки серверу */
void outLFile(LPVOID StartMFile)
{
	printf("Server просись вас надати iнформацiю про фали\n");
	printf("Надати/вiдмовитиp\n");
	printf("[y/n]");
	char c = _getch();
	std::string text;
	switch (c)
	{
	case 'y':

		text = outListFile();
		CopyMemory(StartMFile, text.c_str(), text.size());///запис даних у файл
		PulseEvent(hEvent);                      /// сигнал printListFile(StartMFile);
		break;
	case'n':
		CopyMemory(StartMFile, "No", 3);///запис даних у файл
		PulseEvent(hEvent);                      /// сигнал 
		break;
	}


}