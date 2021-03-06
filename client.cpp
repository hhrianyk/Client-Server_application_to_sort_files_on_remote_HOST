#include <windows.h> 
#include <stdio.h> 
#include <locale.h>
HANDLE hEvent; 
HANDLE hMFile;

char Ev[] = "MyEvent";   ///���������� ��䳿
char Fn[] = "MyFile";  /// ���������� ����� �������� �����
LPVOID StartMFile;  /// ��'��� � ������
char Buf[100];    /// ����� �����
 
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	/// �������� ��䳿
	hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, (LPCWSTR)Ev);
	if (!hEvent)  { 
		printf("ERROR: ���� �� �������\n"); 
		system("pause");
			return 0;
	}
	/// �������� �����
	hMFile=OpenFileMapping(FILE_MAP_READ, TRUE, (LPCWSTR)Fn);
	if (!hMFile)
	{
		printf("ERROR: ���� �� �����	\n"); 
		system("pause");
			return 0;
	}
	StartMFile = MapViewOfFile(hMFile, FILE_MAP_READ, 0, 0, 100);
	// ��������� ���������� �ᒺ��������� ���������
	CloseHandle	(hMFile);
	if (!StartMFile)
	{
		printf("ERROR: ��������y ����� 	\n"); 
		system("pause");
			return 0;
	}
	printf("CLIENT Started\n"); 
		do {
			WaitForSingleObject(hEvent, INFINITE);///���������� ��䳿
			CopyMemory (Buf, StartMFile, 100);///���������� ����� 
			printf("%s 	\n", Buf);
			
		} while (strcmp(Buf, "Stop") != 0);
		printf("Server �������� ���� ������	\n");
		system("pause");
		UnmapViewOfFile	(StartMFile);
		return 0;
}
