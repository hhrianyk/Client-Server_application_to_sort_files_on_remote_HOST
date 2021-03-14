#include "prototype.h"

void sort(int,int);///функція сортування
void swap(int);/// swap file
 

char directory[] = "ClientFile\\";///адреса риректорії
struct _finddata_t* m_data = new  _finddata_t[256];
/*підготовка до сортування 
приймаються наступні праметри
1. запрос на сортування за типом
2. запрос на сортування за назвою
3. запрос на сортування за розміром
4. запрос на сортування за датою
*/
int SortFile(int a)
{
    setlocale(LC_ALL, "Russian");
    struct _finddata_t c_file;
    intptr_t hFile;
    int size = 0;
  
    // Пошук  файл у поточному каталозі
    if ((hFile = _findfirst("ClientFile\\*", &c_file)) == -1L)
        printf("No  files in current directory!\n");
    else
    {          

        do {
             char buffer[30];
 
             if (strcmp(c_file.name, ".") != 0 && strcmp(c_file.name, "..") != 0)//уникнення невідомих файлів 
             {
                 ctime_s(buffer, _countof(buffer), &c_file.time_write);
                // printf(" %-30s%.20s %20d\n", c_file.name, buffer, c_file.size);
                 ///запис у масив списку файлів
                 m_data[size++] = c_file;
            
             }
        } while (_findnext(hFile, &c_file) == 0);


        sort(a,size);                   // сортування файлі
        /*Перейменування файлів Наприклад, маючи файли a.txt (1 KByte), b.txt (3 KByte), c.txt (2 KByte),
        в результаті запиту на сортування за збільшенням розміру, у директорії клієнта файли мають отримати імена
        1_a.txt, 2_c.txt, 3_b.txt.*/
        char oldfilename[512];                // старое имя файла
        char newfilename[512];                 // новое имя файла
        for (int i = 0; i < size; i++)
        {
            sprintf(oldfilename, "%s%s", &directory, m_data[i].name);
            sprintf(newfilename, "%s%i%s%s", &directory, i, "_", m_data[i].name);
            if (rename(oldfilename, newfilename) != 0) printf("EROR ,%d\n",i);
        }
        _findclose(hFile);
        //system("pause");
    }
    return 0;
}


void sort(int a, int size)
{

    bool pr;			/// для проверки отсортирован ли массив
    do
    {
        pr = false;
        switch (a)
        {
        case 1:
            for (int i = 0; i < size; i++)	/// проходим слева направо
                if (m_data[i].attrib < m_data[i + 1].attrib) { swap(i); pr = true; }
            break;
        case 2:
            for (int i = 0; i < size; i++)	/// проходим слева направо
                if (m_data[i].name < m_data[i + 1].name) { swap(i); pr = true; }

            break;

        case 3:
            for (int i = 0; i < size; i++)	/// проходим слева направо
                if (m_data[i].size < m_data[i + 1].size) { swap(i); pr = true; }

            break;
        case 4:
            for (int i = 0; i < size; i++)	/// проходим слева направо
                if (m_data[i].time_create < m_data[i + 1].time_create) { swap(i); pr = true; }

            break;
        }
    } while (pr);

   printf("\n *Сортування завершено \n");
}


void swap(int i) /// Swap елемент
{
     _finddata_t temp;
    temp = m_data[i];
    m_data[i] = m_data[i + 1];
    m_data[i + 1] = temp;
}

/*Повертає список файлів у папці*/
std::string outListFile()
{
    struct _finddata_t c_file;
    intptr_t hFile;
    if ((hFile = _findfirst("ClientFile\\*", &c_file)) == -1L)
        printf("No  files in current directory!\n");
    else
    {
        std::string s;
        s += "Listing of files\n\n";
        s += " FILE                           DATE                       SIZE\n";
        s += " ----                           ----                        ----\n";


        do {
            char buffer[30];
            char text[512];
            if (strcmp(c_file.name, ".") != 0 && strcmp(c_file.name, "..") != 0)
            {
                ctime_s(buffer, _countof(buffer), &c_file.time_write);

                sprintf(text, " %-30s%.20s %20d\n", c_file.name, buffer, c_file.size);
                s += text;

            }
        } while (_findnext(hFile, &c_file) == 0);
        return s;
    }
}
