//
// Created by Gyebro on 2018. 01. 04..
//

#ifndef PRIMETESTER_TCPCONNECTION_H
#define PRIMETESTER_TCPCONNECTION_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>

#define DEFAULT_BUFLEN 512

using namespace std;


class TcpConnection {
private:
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    SOCKET ConnectSocket;
    struct addrinfo hints;
    struct addrinfo *result, *ptr;
    WSADATA wsaData;
    bool avail;
public:
    TcpConnection();
    void open(string hostname, string port);
    string send_data(int i);
    string send_data(string data);
    void close();
    bool available() const;
};


#endif //PRIMETESTER_TCPCONNECTION_H
