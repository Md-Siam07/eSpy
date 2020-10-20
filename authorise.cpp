#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
int main()
{
    char takenName[80],takenPass[16];

    scanf("%[^\n]s", takenName);
    scanf("%s", takenPass);

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
            printf("Entry successful!");
            exit(0);
        }

    }
}
