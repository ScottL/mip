#define DEBUG debug

typedef struct node QNODE;
typedef struct queue *request_queue;

//int write_queue();
//char *read_queue();
int init(request_queue q , char *p);
void enqueue(request_queue q , char *p);
char *dequeue(request_queue q);
int size(request_queue q );
void printq(request_queue q, char *tag);
request_queue create_queue(void);
