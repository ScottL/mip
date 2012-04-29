#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#include "sandslhash.h"
#include "queuebone.h"
#include "minpikaqueue.h"
#include "mip.h"

struct connection_bundle {
    pthread_t thread;
    int num;
    int capacity;
};

struct socket{
    int sockfd;
    int num;
    int capacity;
};

typedef struct connection_bundle *CONN_BUNDLE;
typedef struct socket *SOCKET;

struct socket_bundle {
    pthread_t sthread;
    //SOCKET *sockets; //array of sockets
    int cap;
    int num_sockets;
    int size;
    int port_low;
    int port_high;
    int req_buf_length; //how much to read in at a time (shorter for join/leave)
};

typedef struct socket_bundle *SOCKETS;

void dump_string(const unsigned char *data_buffer, const unsigned int length) {
    unsigned int i;
    for (i = 0; i < length; i++) {
        printf("%c", data_buffer[i]);
    }
    printf("\n");
}

void *run_socket_bundles(void *sockets_v) {
    SOCKETS sockets = (SOCKETS)sockets_v;
    int sockfds[sockets->cap];
    int i;
    while (1) {
        for (i = 0; i < sockets->cap + 1; i++) {
            struct sockaddr_in host_addr, client_addr;
            int new_sockfd;
            socklen_t sin_size;
            char unsigned buffer[sockets->req_buf_length];
            int yes = 1;
            if ((sockfds[i] = socket(PF_INET, SOCK_STREAM, 0)) == -1)
                printf("error creating socket: run_socket_bundle()\n");
            if (setsockopt(sockfds[i], SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
                printf("error setting socket options: run_socket_bundle()\n");
            host_addr.sin_family = AF_INET;
            host_addr.sin_port = htons(i + sockets->port_low);
            host_addr.sin_addr.s_addr = 0;
            memset(&(host_addr.sin_zero), '\0', 8);
            if (bind(sockfds[i], (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
                printf("error binding to socket %d: run_socket_bundle()\n", i + sockets->port_low);
            if (listen(sockfds[i], 15) == -1)
                printf("error listenig on socket %d: run_socket_bundle()\n", i);
            printf("listening on socket %d\n", i + sockets->port_low);
            while (1) {
                printf("0\n");
                sin_size = sizeof(struct sockaddr_in);
                usleep(1);
                new_sockfd = accept(sockfds[i], (struct sockaddr *)&client_addr, &sin_size);
                if (new_sockfd == -1)
                    printf("error accepting socket connection\n");
                printf("server: received connection from %s port %d\n",
                        inet_ntoa(client_addr.sin_addr),
                        ntohs(client_addr.sin_port));
                unsigned int recv_length = 0;
                while (recv_length <= 0) {
                    printf("1\n");
                    recv_length = recv(new_sockfd, &buffer, sockets->req_buf_length, 0);
                }
                dump_string(buffer, recv_length);
                close(new_sockfd);
                usleep(1);
            }
            usleep(1);
        }
        usleep(1);
    }
}

int compare_threads(const void *a, const void *b) {
    CONN_BUNDLE ca = (CONN_BUNDLE)a;
    CONN_BUNDLE cb = (CONN_BUNDLE)b;
    return ca->num > cb->num;
}

int compare_sockets(const void *a, const void *b) {
    SOCKET sa = (SOCKET)a;
    SOCKET sb = (SOCKET)b;
    return sa->num > sb->num;
}

int compare_socket_bundles(const void *a, const void *b) {
    return -1;
}

char string_socket(void *b) {
   SOCKET sb = (SOCKET)b;
   printf("socket.. num: %d\n", sb->num); 
}

void *run_requests(void *);
void *fill_queue(void *);
int compare_sockets(const void *, const void *);
int compare_threads(const void *, const void *);
void dump();
