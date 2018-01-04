//
// Created by Gyebro on 2018. 01. 04..
//

#include "tcpconnection.h"

TcpConnection::TcpConnection() {
    avail = false;
}

void TcpConnection::open(string hostname, string port) {
    avail = true;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup failed with error: " << iResult << endl;
        avail = false;
    }
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    iResult = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &result);
    if ( iResult != 0 ) {
        cout << "getaddrinfo failed with error: " << iResult << endl;
        WSACleanup();
        avail = false;
    }
    ptr=result;
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                           ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        avail = false;
    }
    // Connect to server.
    iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        cout << "Unable to connect to server!\n";
        WSACleanup();
        avail = false;
    }
}

string TcpConnection::send_data(int i) {
    return send_data(to_string(i));
}

string TcpConnection::send_data(string data) {
    if (!avail) return "";
    data += "\r\n";
    iResult = send(ConnectSocket, data.c_str(), (int)data.length(), 0);
    if (iResult == SOCKET_ERROR) {
        cout << "Send failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        WSACleanup();
        avail = false;
    }
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if ( iResult > 0 ) {
        return string(recvbuf, iResult-2);
    } else if ( iResult == 0 ) {

    } else {
        cout << "recv failed with error: " << WSAGetLastError();
    }
    avail = false;
    return "";
}

void TcpConnection::close() {
    closesocket(ConnectSocket);
    WSACleanup();
    avail = false;
}

bool TcpConnection::available() const {
    return avail;
}
