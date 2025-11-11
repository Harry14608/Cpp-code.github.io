
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET listenSocket = INVALID_SOCKET, clientSocket = INVALID_SOCKET;
    sockaddr_in serverAddr;
    char buffer[512];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Create a socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket\n";
        WSACleanup();
        return 1;
    }

    // Bind to port 54000
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.4.106");
    serverAddr.sin_port = htons(54000);

    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Listen for connection
    listen(listenSocket, SOMAXCONN);
    std::cout << "Waiting for connection...\n";

    // Accept client
    clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected!\n";

    // Receive data
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << "\n";
    }

    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
