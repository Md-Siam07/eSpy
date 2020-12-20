#include<bits/stdc++.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<windows.h>
#include<winuser.h>

#define MAX_INPUT_LEN 80
using namespace std;

bool authentication(char takenName[], char takenPass[])
{
    FILE *fp;

    fp = fopen ("authorised_users.txt","r");
    char nameOnFile[80], passOnFile[16];

    while(fgets(nameOnFile,80,fp)!=0)
    {
        fgets(passOnFile,80,fp);

        int size1= strlen(nameOnFile);
        nameOnFile[size1-1]='\0';
        int size2= strlen(passOnFile);
        passOnFile[size2-1]='\0';

        if(strcmp(nameOnFile,takenName)==0 && strcmp(passOnFile,takenPass)==0)
        {
            //printf("successful");
            return true;

        }

    }

    return false;

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

    getch();
    closegraph();


}

void addUser()
{
    DWORD screenWidth= GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth,screenHeight,"Add user");
    setcolor(WHITE);

    char s[]= "siam";
    FILE *fp = fopen("authorised_users.txt","a");


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

    FILE *addUserFP = fopen("authorised_users.txt","a");
    fputs(name, addUserFP);
    fputs(password, addUserFP);
    fclose(addUserFP);

}

void viewSS()
{
    printf("1");
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

    rectangle(100,400,300,450);
    outtextxy(150,420,"HISTORY");
    rectangle(400,400,600,450);
    outtextxy(450,420,"ADD USER");
    rectangle(700,400,900,450);
    outtextxy(750,420,"MAIL");
    rectangle(1000,400,1200,450);
    outtextxy(1020,420,"SCREENSHOTS");
    rectangle(1000,550,1200,600);
    setcolor(RED);
    outtextxy(1050,570,"EXIT");
    int count=0;


    POINT position;
    while(1)
    {
        if(GetKeyState(VK_LBUTTON))
        {

            GetCursorPos(&position);
            printf("\n now point is %d %d",position.x,position.y);
            count++;
        }
        if(count==1) break;
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

    if(x>=1000 && x<=1200 && y>=400 && y<=470)
    {
        closegraph();
        delay(500);
        viewSS();
    }

    getch();
    closegraph();
}

void authenticate()
{
    int height=500,width=700;

    initwindow(width,height,"Authenticate",-3,-3);
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
        settextstyle(1,HORIZ_DIR,3);
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
                    inputbuf[input_pos] = c;
                    input_pos++;
                    inputbuf[input_pos] = ' ';
                }
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
        settextstyle(1,HORIZ_DIR,3);
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
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            printf("PRESSED");
            GetCursorPos(&check);
            count++;
        }
        if(count==1) break;
    }

        GetCursorPos(&check);

        //printf("%d",authenticate);
        int x,y;
        x = check.x;
        y = check.y;
        printf("1. %d %d\n", x,y);
        if(x>=270&&x<=430 && y>=320&&y<=370)
        {
            authenticate = authentication(email, password);

            if(authenticate==true)
            {

                closegraph();
                delay(500);
                viewOptions();
            }
            else if(authenticate==false)
            {
                delay(500);
                closegraph();
               // authenticationFailed();
            }
        }




}

int main()
{
    authenticate();
    return 0;
}
