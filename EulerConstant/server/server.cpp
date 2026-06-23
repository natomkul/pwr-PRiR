#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <string>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "handler.h"

#define BACKLOG 1
#define SV_SOCK_PATH "/tmp/sock"
#define BUF_SIZE 100

bool server(int p)
{
    struct sockaddr_un addr;
    int sfd;

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("Server: socket");
        return false;
    }

    printf("Server socket fd = %d\n", sfd);

    unlink("/tmp/sock"); 

    if ((bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un))) == -1) 
    {
        perror("bind");
        close(sfd);
        return false;
    }

    if ((listen(sfd, BACKLOG)) == -1)
    {
        perror("listen");
        close(sfd);
        return false;
    }

    printf("server: waiting to connect...\n");

    int cfd = accept(sfd, NULL, NULL);

    if (cfd == -1)
    {
        perror("accept");
        return false;
    }

    printf("Accepted socket fd = %d\n", cfd);

    char mesg[BUF_SIZE];
    char buf[BUF_SIZE];
    int numbytes;

    if ((numbytes = recv(cfd, buf, BUF_SIZE - 1, 0)) <= 0)
    {
        perror("server recv");
        close(sfd);
        close(cfd);
        return false;
    }

    buf[numbytes] = '\0';
   
    printf("number n: %s\n", buf);

    int x = std::stoi(buf);
 
    CountHandler* coun1 = new CountHandler(x, p);
    double output = coun1->finResult();
    
    char val[BUF_SIZE - 1];
    snprintf(val, sizeof(val), "%f", output);
    
    if (send(cfd, val, strlen(val), 0) == -1)
    {
        perror("server send");
            
        close(sfd);
        close(cfd);
        return false;
    }

    close(sfd);
    close(cfd);

    return true;

}

int main()
{
    server(5);
}
