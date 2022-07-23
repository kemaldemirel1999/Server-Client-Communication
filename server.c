#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
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



pthread_t workerThread_id;
   
short global_array[1000];

void *workerThreadFunc(void *vargp){
    for(int x = 0; x < 1000 - 1; x++){       
        for(int y = 0; y < 1000 - x - 1; y++){          
            if(global_array[y] > global_array[y + 1]){               
                short temp = global_array[y];
                global_array[y] = global_array[y + 1];
                global_array[y + 1] = temp;
            }
        }
    }
    for(int i=0; i<1000; i++){
        message.mesg_text[i] = global_array[i];
    }
    char filename[50];
    sprintf(filename, "%d", (int)message.process_id);
    char extension[] = ".txt";
    strcat(filename, extension);
    
    FILE *f = fopen(filename, "w+");
    for(int i=0; i<1000; i++){
        fprintf(f, "%hd\n", global_array[i]);
    }
    fclose(f);    
}

int main() {
    printf("Program Starts\n");
    while(1){
        key_t key;        
        int msgid;
        key = ftok("progfile", 65);
        msgid = msgget(key, 0666 | IPC_CREAT);
        msgrcv(msgid, &message, sizeof(message), 1, 0);

        printf("Received Process ID:%d\n",message.process_id);  
        printf("Server msgrcv msgid: %d\n",msgid);
        for(int i=0; i<1000; i++){
            global_array[i] = message.mesg_text[i];
        }
        pthread_create(&workerThread_id,NULL, workerThreadFunc, (void*)&workerThread_id);
        pthread_join(workerThread_id,NULL);

        for(int i=0; i<1000; i++){
            printf("message[%d]:%hd\n",i, message.mesg_text[i]);
        }
    
        msgctl(msgid, IPC_RMID, NULL);
    } 
    pthread_exit(NULL); 
    return 0;
}

