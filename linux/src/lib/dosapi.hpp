#include<ctime>
#include<unistd.h>
#include<thread>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

int tcpflood(const char* ip, int port, const char* packet);
int synflood(const char* ip, int port);
int udpflood(const char* ip, int port, const char* packet);