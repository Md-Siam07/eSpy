#include<stdio.h>
#include<graphics.h>
int main()
{
    int gd= DETECT;
    int gm;
    initwindow(500,300,"");
    POINT cursor;
    GetCursorPos(&cursor);
    int x= cursor.x;
    int y= cursor.y;
    printf("%d %d",x,y);
}
