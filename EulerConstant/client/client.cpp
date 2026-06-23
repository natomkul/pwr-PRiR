#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SV_SOCK_PATH "/tmp/sock"
#define BUF_SIZE 99

bool client()
{
    struct sockaddr_un addr;

    int sfd;
    
    if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("Client: socket");
        return false;
    }
    
    printf("Client socket fd = %d\n", sfd);

    std::memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if ((connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un))) == -1)
    {
        perror("connect:");
        close(sfd);
        return false;
    }

    char mesg[BUF_SIZE];
    char buf[BUF_SIZE];
    int numbytes;

    fgets(mesg, sizeof(mesg), stdin);

    if (send(sfd, mesg, strlen(mesg), 0) == -1)
    {
        perror("Client: send");
        close(sfd);
        return false;
    }

    if ((numbytes = recv(sfd, buf, BUF_SIZE - 1, 0)) <= 0)
    {
         perror("client recv");
         close(sfd);
         return false;
    }

    buf[numbytes] = '\0';

    printf("output: %s\n", buf);

    close(sfd);
    return true;
}

int main()
{
    bool out = client();
}
