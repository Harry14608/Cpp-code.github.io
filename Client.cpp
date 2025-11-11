//Gonna be real, I have no idea whats going on
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    sockaddr_in serverAddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    // Server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.4.106");
    serverAddr.sin_port = htons(54000);

    // Connect to server
    if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Unable to connect to server\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send data
    const char* msg = "Hello from Client!";
    send(sock, msg, (int)strlen(msg), 0);
    std::cout << "Message sent\n";

    closesocket(sock);
    WSACleanup();
    return 0;
}
