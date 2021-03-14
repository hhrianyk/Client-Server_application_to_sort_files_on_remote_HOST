#include "prototype.h"
#include <iostream>

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
	hMFile=OpenFileMapping(FILE_MAP_WRITE, TRUE, (LPCWSTR)Fn);
	if (!hMFile)
	{
		printf("ERROR: ���� �� �����	\n"); 
		system("pause");
			return 0;
	}
	StartMFile = MapViewOfFile(hMFile, FILE_MAP_WRITE, 0, 0, 100);
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
			//printf("%s 	\n", Buf);


			switch (*Buf)
			{
			case '1':SortFile(1);
				CopyMemory(StartMFile, "���i���� ���������� ����������", 100);///���������� �����
				PulseEvent(hEvent);                      /// ������ printListFile(StartMFile);
			break;
			case '2':SortFile(2);
				CopyMemory(StartMFile, "���i���� ���������� ����������", 100);///���������� �����
				PulseEvent(hEvent);                      /// ������ printListFile(StartMFile);
				break;
			case '3':SortFile(3);
				CopyMemory(StartMFile, "���i��� ���������� ����������", 100);///���������� �����
				PulseEvent(hEvent);                      /// ������  
				break;
			case '4':SortFile(4);
				CopyMemory(StartMFile, "���i��� ���������� ����������", 100);///���������� �����
				PulseEvent(hEvent);                      /// ������ 
				break;
			case '5':
				outLFile(StartMFile);
				break;
			default:
				printf("%s 	\n", Buf);
				break;
			}
			
		} while (strcmp(Buf, "Stop") != 0);
		printf("Server �������� ���� ������	\n");
		system("pause");
		UnmapViewOfFile	(StartMFile);
		return 0;
}

//*������� ������� ����� ��� ���� ����� ������� */
void outLFile(LPVOID StartMFile)
{
	printf("Server ������� ��� ������ i�������i� ��� ����\n");
	printf("������/�i�������p\n");
	printf("[y/n]");
	char c = _getch();
	std::string text;
	switch (c)
	{
	case 'y':

		text = outListFile();
		CopyMemory(StartMFile, text.c_str(), text.size());///����� ����� � ����
		PulseEvent(hEvent);                      /// ������ printListFile(StartMFile);
		break;
	case'n':
		CopyMemory(StartMFile, "No", 3);///����� ����� � ����
		PulseEvent(hEvent);                      /// ������ 
		break;
	}


}