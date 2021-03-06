#include <windows.h>
#include <stdio.h> 
#include <iostream>
HANDLE hEvent;
HANDLE hMFile;

char Ev[]="MyEvent";   ///іменування події
char Fn[]="MyFile";  /// іменування файлу передачі даних
LPVOID StartMFile;  /// об'єкт з даними
char Buf[100];    /// буфер даних
char Stop[] = "Stop"; ///компнда зупиник серверає
int main(int argc, char* argv[])
{ 
	setlocale(LC_ALL, "Russian");
	// спроба відкрити подію 	–		ознака сервера
	hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, (LPCWSTR)Ev);
	if(!hEvent) {////перевірка на існування, якщо не існує , то створити
		hEvent = CreateEvent(NULL, TRUE, FALSE, (LPCWSTR)Ev);
		if ((!hEvent)) {
			// не вдалося створити події 
			printf("ERROR: Створення подій \n"); 
			system("pause");
			return 0;
		}
	}
	else {///інакще не створювати і завершити роботу
		// сервер вже	запущено
		CloseHandle	(hEvent);
		printf("ERROR: Cервер вже запущено \n");
		system("pause");
		return 0;
	}
	///створити обєкту для передачі даних
	hMFile = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 100, (LPCWSTR)Fn);
	if (!hMFile)
	{
		printf("ERROR: Створення файлу	\n"); 
		system("pause");
			return 0;
	}
	///Відкрити обєкту
	StartMFile=	MapViewOfFile(hMFile, FILE_MAP_WRITE,	0, 0, 100);
	if (!StartMFile)
	{
		printf("ERROR: Перегляд файлу 	\n"); 
		system("pause");
			return 0;
	}
	/// початок роботи сервера
	printf(" SERVER Started	\n"); 
		do {
			std::cin >> Buf;///ввод даних
			CopyMemory(StartMFile, Buf, sizeof(Buf));///запис даних у файл
			PulseEvent(hEvent);                      /// сигнал 
		} while (strcmp(Buf ,Stop) != 0);
		UnmapViewOfFile	(StartMFile); ///закриття відображення файлу
		CloseHandle	(hMFile);    ///закриття події
		return 0;
}
