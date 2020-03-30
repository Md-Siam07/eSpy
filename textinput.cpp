#include<stdio.h>
#include<string.h>
#include<graphics.h>
#define MAX_INPUT_LEN 80

int main()
{
    int gm;
    int gd= DETECT;
    initgraph(&gd,&gm,"");
    char c;
    char inputbuf[MAX_INPUT_LEN];
    int input_pos = 0;
    int the_end = 0;
do
{
   outtextxy (0,0, inputbuf);
   c = getch();
   switch (c)
   {
        case 8: /* backspace */
          if (input_pos)
          {
             input_pos--;
             inputbuf[input_pos] = 0;
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
             inputbuf[input_pos] = 0;
          }
   }
} while (!the_end);
    char input[80];
    strcpy(input,inputbuf);
    printf("Your input: %s",inputbuf);
}
