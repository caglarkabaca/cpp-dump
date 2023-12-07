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
void camera_move()
{
    while (true)
    {
        glm::vec3 camPos = glm::vec3(4, 3, 3) + glm::vec3(sin(glfwGetTime()) * 7, sin(glfwGetTime()) * 4, 0.f);

        game.View = glm::lookAt(
            camPos,            // Camera is at (4,3,3), in World Space
            glm::vec3(0.f),    // and looks at the origin
            glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
        );
    }
}

int main()
{

    std::thread camera_thread(camera_move);

    game.initWindow(800, 600, "SERVER");
    std::thread server(server_thread);
    game.loop();

    camera_thread.join();
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
        int val = write(sock, (void *)&game.View[0][0], sizeof(float) * 16);
        log() << "writted " << val << " bytes" << '\n';

        int wait = 0;
        do
        {
            char bf[2];
            wait = read(sock, bf, sizeof(bf));
            log() << "got response " << bf << '\n';
        } while (wait <= 0);
    }

    // Soketi kapatma
    close(sock);
}