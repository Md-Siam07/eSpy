#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _WIN32_WINNT 0x501
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include<bits/stdc++.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SMTP_PORT "25"
#define DEFAULT_BUFLEN 1024

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

int main(int argc, char** argv)
{
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
    sendData(&ConnectSocket, "Content-Disposition: attachment; filename=\"details.txt\"\r\n\r\n");
    sendData(&ConnectSocket, "U2FtcGxlIFRleHQu");
    sendData(&ConnectSocket, "\r\n\r\n--977d81ff9d852ab2a0cad646f8058349--\r\n\r\n");
    sendData(&ConnectSocket, ".\r\n");

    FILE* MailFilePtr = fopen("details.txt", "r");
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
