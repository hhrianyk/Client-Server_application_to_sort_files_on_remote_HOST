#include <windows.h> 
#include <stdio.h> 
#include <locale.h>
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
	hMFile=OpenFileMapping(FILE_MAP_READ, TRUE, (LPCWSTR)Fn);
	if (!hMFile)
	{
		printf("ERROR: файл не відкри	\n"); 
		system("pause");
			return 0;
	}
	StartMFile = MapViewOfFile(hMFile, FILE_MAP_READ, 0, 0, 100);
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
			printf("%s 	\n", Buf);
			
		} while (strcmp(Buf, "Stop") != 0);
		printf("Server завершив вашу роботу	\n");
		system("pause");
		UnmapViewOfFile	(StartMFile);
		return 0;
}
