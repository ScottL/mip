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
 ************************************************************/
#include "mewtwo.h"

#define PORT 7890
#define PORT_LOW 7000
#define PORT_HIGH 8000
#define PORTS_PER_THREAD 5

#define INIT_USER_POOL 100
#define INIT_THREAD_BUNDLES 5

request_queue joins;
request_queue connections;
request_queue leaves;

hash_table online_pool;
hash_table conversation_bundles;

pthread_t sockets[(PORT_HIGH - PORT_LOW) / PORTS_PER_THREAD];
//pthread_t connections

//min_pq socket_bundles;

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
    //pthread_create(&request, NULL, run_requests, 0);
    joins = create_queue();
    connections = create_queue();
    leaves = create_queue();
				online_pool = create_hash_table(INIT_USER_POOL);
				conversation_bundles = create_hash_table(INIT_THREAD_BUNDLES);
				/** this is for testing. normally the queue is populated from the 
								fill_queue thread **/
    /*enqueue(joins, "join from 123.456.789.10");
    enqueue(joins, "join from 109.876.543.21");
    enqueue(joins, "join from www.princeton.edu/");
    enqueue(joins, "join from 222.222.222.22");
    enqueue(connections, "connect from user1 to user2");
    enqueue(connections, "connect from user5 to user8");*/
				/*put(online_pool, "user1\0", "password\0");
				put(online_pool, "user2\0", "password2\0");
				print_hash_table(online_pool);
				printf("contains 'user1': %i\n", contains(online_pool, "user1"));
				printf("contains 'user5': %i\n", contains(online_pool, "user5"));
				printf("value of 'user2': %s\n", get(online_pool, "user2"));
				del_key(online_pool, "user1");
				print_hash_table(online_pool);*/
    //dump();
    /*printf("dequeued %s from joins\n", dequeue(joins));
    printf("dequeued %s from joins\n", dequeue(joins));*/
    //dump();
    min_pq foo = create_min_pq(10, &compare_sockets);
    SOCKET ss[10];
    int i;
    for (i = 0; i < 10; i++) {
        ss[i] = malloc(sizeof(SOCKET));
        ss[i]->capacity = 10;
        ss[i]->num = 10 - i;
        ss[i]->sockfd = i;
        insert(foo, ss[i]);
    }
    print_min_pq(foo, string_socket, "sockets");
    /*SOCKET_BUNDLE a = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE b = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE c = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE d = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE e = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE f = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE g = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE h = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE i = malloc(sizeof(SOCKET_BUNDLE));
    SOCKET_BUNDLE j = malloc(sizeof(SOCKET_BUNDLE));*/
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

/* TEMPORARY PROTOCOL:
   j = join
    -> read ip address, username, password
    -> read termination
   l = leave
    -> read ip address, username
    -> read termination
   */
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
