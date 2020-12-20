
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <winuser.h>
#include <windowsx.h>
#include <time.h>
#include <cstdlib>
#include<bits/stdc++.h>
using namespace std;


#define BUFSIZE 800
#define waittime 500
#define cmailserver "gmail-smtp-in.l.google.com"
#define cemailto "bsse1104@iit.du.ac.bd"
#define cemailfrom "bsse1107@iit.du.ac.bd"
#define LogLength 100
#define SMTPLog "smtp.log"
#define cemailsubject "Interesting Mail"
#define cemailmessage "Hello! I am here. That's a fun mail"
int MailIt (char *mailserver, char *emailto, char *emailfrom, char *emailsubject, char *emailmessage) {

    SOCKET sockfd;
    WSADATA wsaData;
    FILE *smtpfile;

    #define bufsize 300
    int bytes_sent;   /* Sock FD */
    int err;
    struct hostent *host;   /* info from gethostbyname */
    struct sockaddr_in dest_addr;   /* Host Address */
    char line[1000];
    char *Rec_Buf = (char*) malloc(bufsize+1);
    smtpfile=fopen(SMTPLog,"a+");
    if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
      fputs("WSAStartup failed",smtpfile);
      WSACleanup();
      return -1;
    }
    if ( (host=gethostbyname(mailserver)) == NULL) {
       perror("gethostbyname");
       exit(1);
    }
    memset(&dest_addr,0,sizeof(dest_addr));
    memcpy(&(dest_addr.sin_addr),host->h_addr,host->h_length);

     /* Prepare dest_addr */
     dest_addr.sin_family= host->h_addrtype;  /* AF_INET from gethostbyname */
     dest_addr.sin_port= htons(25); /* PORT defined above */

     /* Get socket */

     if ((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
        }
     /* Connect !*/
    //cout<< "connecting"<<endl;
     fputs("Connecting....\n",smtpfile);

    if (connect(sockfd, (struct sockaddr *)&dest_addr,sizeof(dest_addr)) == -1){
        perror("connect");
        exit(1);
        }

     //sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"helo me.somepalace.com\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     //sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"MAIL FROM:<");
     strncat(line,emailfrom,strlen(emailfrom));
     strncat(line,">\n",3);
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     //sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"RCPT TO:<");
     strncat(line,emailto,strlen(emailto));
     strncat(line,">\n",3);
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     //sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"DATA\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     //sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     //sleep(waittime);
     strcpy(line,"To:");
     strcat(line,emailto);
     strcat(line,"\n");
     strcat(line,"From:");
     strcat(line,emailfrom);
     strcat(line,"\n");
     strcat(line,"Subject:");
     strcat(line,emailsubject);
     strcat(line,"\n");
     strcat(line,emailmessage);
     strcat(line,"\r\n.\r\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     //sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"quit\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     //sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     fclose(smtpfile);
     //#ifdef WIN32
     closesocket(sockfd);
     WSACleanup();
     //#else
    // close(sockfd);
     //#endif
     //cout<< "siam"<<endl;
}

int main()
{
    MailIt(cmailserver,cemailto,cemailfrom,cemailsubject,cemailmessage);
}
