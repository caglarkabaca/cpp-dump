#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>

#include <string>

#include "Engine.h"

#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

#define log(x) std::cout << "CLIENT: "

void client_thread();

atom::Engine game;

int main()
{
    std::thread client(client_thread);
    game.client = true;
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

    while (1)
    {
        memset(buffer, 0, 1024);
        valread = read(client, &buffer, sizeof(buffer));
        if (valread <= 0)
            continue;
        // log() << "readed " << valread << " bytes" << '\n';
        // log() << buffer << '\n';

        int id;
        char obj[1024];
        char vertexShader[1024];
        char fragmentShader[1024];

        char *token;
        token = strtok(buffer, "&");
        id = atoi(token);
        token = strtok(NULL, "&");
        strcpy(obj, token);
        token = strtok(NULL, "&");
        strcpy(vertexShader, token);
        token = strtok(NULL, "&");
        strcpy(fragmentShader, token);

        float mvp[128];
        valread = read(client, mvp, sizeof(mvp));

        // log() << id << '\n'
        //       << obj << '\n'
        //       << vertexShader << '\n'
        //       << fragmentShader << '\n'
        //       << mvp << '\n';

        // atom::Shader shader(vertexShader, fragmentShader);
        // mdl = new atom::ObjModel(shader.copy(), obj);
        // game.models.push_back(mdl);
        // mdl->mvp = glm::make_mat4(mvp);

        if (id < game.models.size())
        {
            game.models[id]->ModelMatrix = glm::make_mat4(mvp);
            // log() << glm::to_string(game.models[id]->ModelMatrix) << '\n';
        }
        else
        {
            bool isIn = false;
            for (atom::ModelBlueprint blueprint : game.appendQueue)
            {
                if (blueprint.id == id)
                {
                    isIn = true;
                    break;
                }
            }
            if (!isIn)
            {
                game.appendQueue.push_back(atom::ModelBlueprint{
                    .id = id,
                    .vertexShader = std::string(vertexShader),
                    .fragmentShader = std::string(fragmentShader),
                    .obj = std::string(obj)});
            }
        }

        write(client, "1", sizeof("1"));
    }

    close(client);
    close(sock);
}