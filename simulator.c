#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "scheduler.h"
#include "simulator.h"


int main()
{
    /* struct*/
    diskScheduleDetails diskData;

    FILE* ptrR;
    int nRead;
    int input;
    char quit[] = "QUIT";
    char file[11]; // Assume the input file name is no longer than 10 characters

    /* Child Threads */
    pthread_t childThreads[6];

    do
    {
        int i = 0;
        int code = 65;
        int rqCylinderList[100];
        int totRequest = 0;

        /* Get input file from the user*/
        printf("\n Disk Scheduler Simulation <Input file>  : ");
        scanf("%s",file);

        if(!( strcmp(quit,file) == 0 ) )
        {
                /* Open the File Reader */
            ptrR = fopen( file, "r");

            if( ptrR == NULL )
            {
                perror(" Error opening the File!!");
            }
            else
            {
                nRead = fscanf(ptrR, "%d %d %d", &diskData.totCylinder, &diskData.currPosi, &diskData.prevPosi);

                /* When Successfully read the main requirements*/
                if( nRead == 3 )
                {
                    while(!feof(ptrR))
                    {
                        fscanf(ptrR, "%d", &input);
                        diskData.rqCylinderList[i]= input;
                        i++;
                        totRequest++;
                    }

                    diskData.totRequest = totRequest;

                }

                /* Error Checking while Reading file */
                if( ferror(ptrR) )
                {
                    perror("Error reading from file\n");
                }

                /* Close the File Reader*/
                fclose(ptrR);
                ptrR = NULL;


                printf("\n For %s: ", file);

                i = 0; /* Reset the i */

                while(code <= 70)
                {
                    diskData.code = (char) code;

                    /* Creating a thread */
                    int success = pthread_create(&childThreads[i],NULL,doThreadDiskSchedule,&diskData);

                    if(success == 0)
                    {
                        /* Allows you to wait for just a current thread for a set amount of time */
                        sleep(2);

                        printf("\n Successfully created Thread %c \n",code);
                    }
                    else /* Error checking*/
                    {
                        perror("\n Error in Creating child Threads!!");
                    }

                    i++;
                    code++;

                }

                printf("\n\n"); /* Give space*/

            }

        }
        else
        {
            i = 0; /* Reset the i*/

            for(int code=65; code<=70; code++)
            {
                int joined = pthread_join(childThreads[i],NULL);

                if(joined == 0)
                {
                    printf("\n Thread %c has terminated", code);
                }
                else
                {
                    perror(" Invalid join of thread!!");
                }

                i++;
            }

            printf("\n\n The App is Exiting. \n");
        }

    }
    while( !( strcmp(quit,file) == 0 ) ); /* loop until user enters QUIT */

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);


    return 0;
}


void selectScheduleAlgorithm(diskScheduleDetails diskData, char code)
{
    switch(code)
    {
        case 'A' :
            firstComeFirstServe(diskData.currPosi,diskData.rqCylinderList,diskData.totRequest);
            break;

        case 'B' :
            shortestSeekTimeFirst(diskData.totRequest,diskData.rqCylinderList,diskData.currPosi);
            break;

        case 'C' :
            scan(diskData.totCylinder,diskData.currPosi,diskData.prevPosi,diskData.totRequest,diskData.rqCylinderList);
            break;

        case 'D' :
            cScan(diskData.totCylinder,diskData.currPosi,diskData.prevPosi,diskData.totRequest,diskData.rqCylinderList);
            break;

        case 'E' :
            look(diskData.totCylinder,diskData.currPosi,diskData.prevPosi,diskData.totRequest,diskData.rqCylinderList);
            break;

        case 'F' :
            cLook(diskData.totCylinder,diskData.currPosi,diskData.prevPosi,diskData.totRequest,diskData.rqCylinderList);
            break;

        default :
            printf("\n Invalid Code!!");

    }
}


/* Function to select each thread an algorithm*/

void *doThreadDiskSchedule(void *diskDa)
{

    diskScheduleDetails diskData = *(diskScheduleDetails*)diskDa;

    char code = diskData.code;

    pthread_mutex_lock(&mutex);
    selectScheduleAlgorithm(diskData,code);
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
