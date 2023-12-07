#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>

#include "Engine.h"

#include <glm/gtc/type_ptr.hpp>

#define log(x) std::cout << "CLIENT: "

void client_thread();

atom::Engine game;

int main()
{
    std::thread client(client_thread);

    game.initWindow(800, 600, "CLIENT");
    game.loop();

    client.join();
    return 0;
}

void client_thread()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, SOMAXCONN);
    int client;
    struct sockaddr_in clientAddr;
    socklen_t clientAddr_len = sizeof(clientAddr);
    while (client == 0)
    {
        client = accept(sock, NULL, NULL);
        getsockname(client, (sockaddr *)&clientAddr, &clientAddr_len);
        log() << inet_ntoa(clientAddr.sin_addr) << " -< " << '\n';
    }

    int valread = 1;
    float buffer[128];
    while (valread > 0)
    {
        valread = read(client, buffer, sizeof(buffer));
        log() << "readed " << valread << " bytes" << '\n';
        game.View = glm::make_mat4(buffer);

        write(client, "1", sizeof("1"));
    }

    close(client);
    close(sock);
}