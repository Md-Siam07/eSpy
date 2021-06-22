#include <stdio.h>
#include<time.h>


    int main(void)
{
    time_t start, end;
    int siam=1;
    double elapsed, prev_elapsed = 0.0;
    time(&start);  /* start the timer */
    do
    {
        time(&end);
        elapsed = difftime(end, start);
        if (elapsed >= prev_elapsed+1.0)
        {
            char nameOfScreenshot[20];
            snprintf(nameOfScreenshot, 20, "image%d.bmp", siam); // puts string into buffer
            printf("%s\n", nameOfScreenshot);
            siam++;
            prev_elapsed = elapsed;
        }
    } while(elapsed < 5.0);
}

