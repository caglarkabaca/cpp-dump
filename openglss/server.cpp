#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "Engine.h"
#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtx/string_cast.hpp"
#include <string>

#define log(x) std::cout << "SERVER: "

void server_thread();

atom::Engine game;

int main()
{
    game.initWindow(800, 600, "SERVER");

    atom::Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    atom::ObjModel model(shader.copy(), "shaders/tavsikucgen.obj");
    game.models.push_back(&model);

    std::thread server(server_thread);
    game.loop();

    server.join();
    return 0;
}

void server_thread()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Sunucu adresi ve portu belirleme
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    // Sunucuya bağlanma
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    while (1)
    {
        log() << glm::to_string(game.models[0]->ModelMatrix) << '\n';
        char bf[1024];
        game.models[0]->serialize(0, bf);
        int val = write(sock, bf, sizeof(bf));
        // log() << "sizeof " << sizeof(bf) << " writted " << val << " bytes" << '\n';
        // log() << bf << '\n';

        val = write(sock, &game.models[0]->ModelMatrix[0][0], sizeof(game.models[0]->ModelMatrix));

        int wait = 0;
        do
        {
            char bf[2];
            wait = read(sock, bf, sizeof(bf));
            // log() << "got response " << bf << '\n';
        } while (wait <= 0);
    }

    // Soketi kapatma
    close(sock);
}