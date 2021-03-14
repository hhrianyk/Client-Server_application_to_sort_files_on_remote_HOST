#include <windows.h>
#include <stdio.h> 
#include <iostream>
HANDLE hEvent;
HANDLE hMFile;

char Ev[]="MyEvent";   ///���������� ��䳿
char Fn[]="MyFile";  /// ���������� ����� �������� �����
LPVOID StartMFile;  /// ��'��� � ������
char Buf[100];    /// ����� �����
char Stop[] = "Stop"; ///������� ������� �������
char Label[] = " SERVER Started	\n 1. ������ �� ���������� �� �����\n 2. ������ �� ���������� �� ������\n 3. ������ �� ���������� �� �������\n 4. ������ �� ���������� �� �����\n 5. ������ �� ��������� ������ ����\n other �� �������������\n";

int main(int argc, char* argv[])
{ 
	setlocale(LC_ALL, "Russian");
	// ������ ������� ���� 	�		������ �������
	hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, (LPCWSTR)Ev);
	if(!hEvent) {////�������� �� ���������, ���� �� ���� , �� ��������
		hEvent = CreateEvent(NULL, TRUE, FALSE, (LPCWSTR)Ev);
		if ((!hEvent)) {
			// �� ������� �������� ��䳿 
			printf("ERROR: ��������� ���� \n"); 
			system("pause");
			return 0;
		}
	}
	else {///������ �� ���������� � ��������� ������
		// ������ ���	��������
		CloseHandle	(hEvent);
		printf("ERROR: C����� ��� �������� \n");
		system("pause");
		return 0;
	}
	///�������� ����� ��� �������� �����
	hMFile = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 100, (LPCWSTR)Fn);
	if (!hMFile)
	{
		printf("ERROR: ��������� �����	\n"); 
		system("pause");
			return 0;
	}
	///³������ �����
	StartMFile=	MapViewOfFile(hMFile, FILE_MAP_WRITE,	0, 0, 100);
	if (!StartMFile)
	{
		printf("ERROR: �������� ����� 	\n"); 
		system("pause");
			return 0;
	}
	/// ������� ������ �������
	 
		do {
			printf(Label);
			std::cin >> Buf;///���� �����
			CopyMemory(StartMFile, Buf, sizeof(Buf));///����� ����� � ����

			PulseEvent(hEvent);                      /// ������ 


 
			 
			if (*Buf == '1'|| *Buf == '2'|| *Buf == '3'|| *Buf == '4') {
					WaitForSingleObject(hEvent, INFINITE);///���������� ��䳿
					CopyMemory(Buf, StartMFile, 100);///���������� ����� 
					printf("%s\n", Buf);
			}
			if(*Buf=='5'){
				WaitForSingleObject(hEvent, INFINITE);///���������� ��䳿
				CopyMemory(Buf, StartMFile, 1000);///���������� ����� 
				if (strcmp(Buf, "No") == 0)printf("\n�i��������\n");
				else printf("%s\n", Buf);
				system("pause&cls");
 
			}
			 
		} while (strcmp(Buf ,Stop) != 0);
		UnmapViewOfFile	(StartMFile); ///�������� ����������� �����
		CloseHandle	(hMFile);    ///�������� ��䳿
		return 0;
}
