#include "server.h"
#include "anet.h"

void initServer(void)
{
        listenServer(8888);
}

void listenServer(int port)
{
        anetTcpServer(server.neterr, port, NULL, server.tcp_backlog);
}
