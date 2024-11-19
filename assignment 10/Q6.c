#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SIZE 5

typedef struct cirque {
    int arr[SIZE];
    int front, rear, count;
}cirque_t;

void cq_init(cirque_t *cq) {
    memset(cq->arr, 0, sizeof(cq->arr));
    cq->count = 0;
    cq->front = -1;
    cq->rear = -1;
}

int cq_isfull(cirque_t *cq) {
    return cq->count == SIZE;
}

int cq_isempty(cirque_t *cq) {
    return cq->count == 0;
}

void cq_push(cirque_t *cq, int val) {
    cq->rear = (cq->rear + 1) % SIZE;
    cq->arr[cq->rear] = val;
    cq->count++;
}

int cq_pop(cirque_t *cq) {
    cq->front = (cq->front + 1) % SIZE;
    cq->count--;
    return cq->arr[cq->front];
}

#define SHM_KEY 0x1234
#define SEM_KEY     0x4321

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int shmid, semid;
cirque_t *ptr;

void sigint_handler(int sig) {
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    // destroy the semaphore
    semctl(semid, 0, IPC_RMID);
    _exit(0);
}


void sigchld_handler(int sig) {
    int s;
    waitpid(-1, &s, 0);
}

int main() {
    int pid, ret;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    ret = sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = sigchld_handler;
    ret = sigaction(SIGCHLD, &sa, NULL);
    
    // create semaphore with 3 counters: 0-mutual excl, 1-empty cntr, 2-filled cntr
    semid = semget(SEM_KEY, 3, IPC_CREAT|0600);

    // initialize sema counters: 0-mutual excl=1, 1-empty cntr=SIZE, 2-filled cntr=0
    unsigned short init_cnts[] = {1, SIZE, 0};
    union semun su;
    su.array = init_cnts;
    ret = semctl(semid, 0, SETALL, su);

    shmid = shmget(SHM_KEY, sizeof(cirque_t), IPC_CREAT|0600);
    ptr = shmat(shmid, NULL, 0);
    cq_init(ptr);

    struct sembuf ops[2];
    pid = fork();
    if(pid == 0) { // child 
        
        while(1) {
            // P(sm, sf);
            ops[0].sem_num = 0;
            ops[0].sem_op = -1;
            ops[0].sem_flg = 0;
            ops[1].sem_num = 2;
            ops[1].sem_op = -1;
            ops[1].sem_flg = 0;
            ret = semop(semid, ops, 2);

            int val = cq_pop(ptr);
            printf("RD: %d\n", val);
            // V(sm, se);
            ops[0].sem_num = 0;
            ops[0].sem_op = +1;
            ops[0].sem_flg = 0;
            ops[1].sem_num = 1;
            ops[1].sem_op = +1;
            ops[1].sem_flg = 0;
            ret = semop(semid, ops, 2);

            sleep(1);
        }
    }
    else { // parent 
        sleep(1);
        while(1) {
            // P(sm, se);
            ops[0].sem_num = 0;
            ops[0].sem_op = -1;
            ops[0].sem_flg = 0;
            ops[1].sem_num = 1;
            ops[1].sem_op = -1;
            ops[1].sem_flg = 0;
            ret = semop(semid, ops, 2);

            int val = rand() % 100;
            cq_push(ptr, val);
            printf("WR: %d\n", val);
            // V(sm, sf);
            ops[0].sem_num = 0;
            ops[0].sem_op = +1;
            ops[0].sem_flg = 0;
            ops[1].sem_num = 2;
            ops[1].sem_op = +1;
            ops[1].sem_flg = 0;
            ret = semop(semid, ops, 2);
            sleep(1);
        }
    }
    return 0;
}
