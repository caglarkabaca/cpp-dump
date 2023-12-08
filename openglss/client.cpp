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

    // atom::Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    // atom::ObjModel model(shader.copy(), "shaders/tavsikucgen.obj");
    // game.models.push_back(model);
    // game.client = true; // disables imgui

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
    char buffer[1024];
    game.models.clear();

    atom::ObjModel *mdl;
    while (1)
    {
        memset(buffer, 0, 1024);
        valread = read(client, &buffer, sizeof(buffer));
        if (valread <= 0)
            continue;
        free(mdl);
        game.models.clear();
        log() << "readed " << valread << " bytes" << '\n';
        log() << buffer << '\n';

        int id;
        char obj[1024];
        char vertexShader[1024];
        char fragmentShader[1024];
        char mvp[1024];

        char *token;

        token = strtok(buffer, "&");
        id = atoi(token);
        token = strtok(NULL, "&");
        strcpy(obj, token);
        token = strtok(NULL, "&");
        strcpy(vertexShader, token);
        token = strtok(NULL, "&");
        strcpy(fragmentShader, token);
        token = strtok(NULL, "&");
        strcpy(mvp, token);

        log() << id << '\n'
              << obj << '\n'
              << vertexShader << '\n'
              << fragmentShader << '\n'
              << mvp << '\n';

        // atom::Shader shader(vertexShader, fragmentShader);
        // mdl = new atom::ObjModel(shader.copy(), obj);
        // game.models.push_back(mdl);
        // mdl->mvp = glm::make_mat4(mvp);

        write(client, "1", sizeof("1"));
    }

    close(client);
    close(sock);
}