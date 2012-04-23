/** server **/
/************************************************************

  message format:

('j') join: source ip
('s') send_message: source ip, other user, message, check
('r') relay_message: source user, other ip, message
('c') connect: source ip, other user
('d') disconnect: source ip, other user
('a') check_alive: dest ip
('i') is_alive: source ip
('l') leave: source ip

   0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |command (char) | source ip   ...        ...         ...        |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | source ip     | [                                             |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 ************************************************************/
#include <stdlib.h>
#include <string.h>
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
#include "queuebone.h"
#include "sandslhash.h"

#define PORT 7890
#define PORT_LOW 7000
#define PORT_HIGH 8000

request_queue joins;
request_queue connections;
request_queue leaves;

hash_table online_pool;
hash_table conversation_bundles;

struct connection_bundle {
    pthread_t thread;
    int size;
    int capacity;
};

void *run_requests(void *);
void *fill_queue(void *);
void dump();

/*Main Thread
  */
        //dequeue request
        //if request == join:
            //add user to online pool
        //if request == leave:
            //remove user from online pool
        //if request == send_message:
            //check other user online:
                //relay message
        //if request == connect:
            //add to non-full thread
                //if no non-full threads: create new thread
void *run_requests(void *arg){
    char *ptr;
    if(size(joins) > 0){
        ptr = dequeue(joins);
        //add user to online pool
    }
    if(size(connections) > 0){
        ptr = dequeue(connections);
        //connect users
    }
    if(size(leaves) > 0){
        ptr = dequeue(leaves);
        //remove user from online pool
    }
}


int main(int argc, char **argv) {
    pthread_t request;
    pthread_create(&request, NULL, run_requests, 0);
    joins = create_queue();
    connections = create_queue();
    leaves = create_queue();
				online_pool = create_hash_table();
				conversation_bundles = create_hash_table();
				/** this is for testing. normally the queue is populated from the 
								fill_queue thread **/
    enqueue(joins, "join from 123.456.789.10");
    enqueue(joins, "join from 109.876.543.21");
    enqueue(joins, "join from www.princeton.edu/");
    enqueue(joins, "join from 222.222.222.22");
    enqueue(connections, "connect from user1 to user2");
    enqueue(connections, "connect from user5 to user8");
    dump();
    printf("dequeued %s from joins\n", dequeue(joins));
    printf("dequeued %s from joins\n", dequeue(joins));
    dump();
}

#ifdef DEBUG

void dump() {
    printf("\n\n\t\t\tQUEUE DUMP\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printq(joins, "JOINS");
    printq(connections, "CONNECTIONS");
    printq(leaves, "LEAVES");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
}

#endif

void *fill_queue(void *arg) {
				int sockfd, new_sockfd;
				struct sockaddr_in host_addr, client_addr;
				socklen_t sin_size;
				char buffer[1024];
				int yes = 1;
				if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
								printf("error creating socket\n");
				if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
								printf("error setting socket options\n");
				host_addr.sin_family = AF_INET;
				host_addr.sin_port = htons(PORT);
				host_addr.sin_addr.s_addr = 0;
				memset(&(host_addr.sin_zero), '\0', 8);
				if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
								printf("error binding to socket\n");
				//if (listen(sockfd, 
    while (1) {
        //listen on socket; enqueue legit requests
        usleep(0.1);
    }
}
