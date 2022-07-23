#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

struct mesg_buffer {
    long mesg_type;
    pid_t process_id;
    short mesg_text[1000];
} message;


void printArray(short []);
void handler();

int main(){
    while(1){     
        for(int i=0;i<1000;i++){
            message.mesg_text[i]=rand()%100;
        }
        key_t key;
        int msgid;
        key = ftok("progfile", 65);
        msgid = msgget(key, 0666 | IPC_CREAT);
        message.mesg_type = 1;

        pid_t pid = getpid();
        message.process_id = pid;

        printf("Process ID:%d\n",pid);
        printf("Before Sorting:\n");
        printArray(message.mesg_text);
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Client msgsend msgid: %d\n",msgid);
        handler();
        sleep(10);
    }
    return 0;

}

void printArray(short array[1000]){
    printf("Elements of array:\n");
    for(int i=0; i<1000; i++){
        printf("array[%d]= %hd\n",i, array[i]);
    }
    printf("\n");
}

void handler(){
    short sortedArray[1000];
    char filename[50];
    sprintf(filename, "%d", (short)message.process_id);
    char extension[] = ".txt";
    strcat(filename, extension);
    FILE *file;
    if( (file = fopen(filename, "r")) ) {
        printf("Reading From a File:\n");
        for (int i = 0; i < 1000; i++)
        {
            fscanf(file, "%hd", &sortedArray[i]);
        }
        fclose(file);  
        printArray(sortedArray); 
    }
    else{
        //printf("File Does not exist.\n");
    }
    
}