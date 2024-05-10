#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"


/* FCFS Algorithm */
void firstComeFirstServe(int curPosition, int array[] ,int totRequest)
{
    int totalMovement = 0;
    int movement = 0;
    int i = 0;
    int tempArray[totRequest];


    /* Create a Temporary Array of disk Request */
    createTempArray(tempArray,array,totRequest);

    for(int i = 0; i < totRequest; i++)
    {
        movement = curPosition - tempArray[i];
        movement = abs(movement); /* Get the Absolute value */

        totalMovement = totalMovement + movement;

        curPosition = tempArray[i];
    }

    display("FCFS  ",totalMovement);

}

/* SSTF Algorithm */
void shortestSeekTimeFirst(int totRequest, int array[], int curPosition)
{
    int totalMovement = 0;
    int movement;
    int indexOfArray;
    int tempArray[totRequest];
    int k = 0;

    /* Create a Temporary Array of disk Request */
    createTempArray(tempArray,array,totRequest);

    while( k != totRequest)
    {
        int minMovement = 10000;

        for( int i = 0; i < totRequest; i++)
        {
            movement = curPosition - tempArray[i];
            movement = abs(movement);

            if(movement < minMovement)
            {
                minMovement = movement;
                indexOfArray = i;
            }
        }

        totalMovement = totalMovement + minMovement;
        curPosition = tempArray[indexOfArray];

        tempArray[indexOfArray] = 10000;
        k++;
    }

    display("SSTF  ",totalMovement);

}

/* SCAN Algorithm */
void scan(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[])
{
    int totalMovement = 0;
    int movement;
    int indexOfArray;
    int tempArray[totRequest];
    int i = 0;

    /* Create a Temporary Array of disk Request */
    createTempArray(tempArray,array,totRequest);

    /* Sort the tempArray in Order to do the SCAN */
    sortArray(tempArray,totRequest);

    /* Get the index of disk next to the current position of disk */
    indexOfArray = getIndex(tempArray,totRequest,curPosi);

    /* Head Moves toward smaller value*/
    if( curPosi < prevPosi)
    {
        for(i = indexOfArray-1; i >=0; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        movement = abs(curPosi-0); /* Moves the Head to 0*/

        totalMovement = totalMovement + movement;

        movement = abs(tempArray[indexOfArray]-0);

        totalMovement = totalMovement + movement;
        curPosi = tempArray[indexOfArray];

        for(i = indexOfArray+1; i < totRequest; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

    }
    else /* Head Moves toward larger value*/
    {
        for(i = indexOfArray; i < totRequest; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        movement = abs(curPosi-(totCylinder-1) ); /* Moves the Head to Max*/
        totalMovement = totalMovement + movement;

        movement = abs(tempArray[indexOfArray-1]-(totCylinder-1));
        totalMovement = totalMovement + movement;
        curPosi = tempArray[indexOfArray-1];

        for(i = indexOfArray-2; i >=0; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }
    }

    display("SCAN  ",totalMovement);

}


/* C-SCAN Algorithm */
void cScan(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[])
{
    int totalMovement = 0;
    int movement;
    int indexOfArray;
    int tempArray[totRequest];
    int i = 0;

    /* Create a Temporary Array of disk Request */
    createTempArray(tempArray,array,totRequest);

    /* Sort the tempArray in Order to do the C-SCAN */
    sortArray(tempArray,totRequest);

    /* Get the index of disk next to the current position of disk */
    indexOfArray = getIndex(tempArray,totRequest,curPosi);

    /* Head Moves toward smaller value*/
    if( curPosi < prevPosi)
    {
        for(i = indexOfArray-1; i >=0; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        movement = abs(curPosi-0); /* Moves the Head to 0*/
        totalMovement = totalMovement + movement;

        movement = abs( (totCylinder-1) - 0 ); /* Moves the Head 0 to Max */

        totalMovement = totalMovement + movement;
        curPosi = movement;/* totCylinder-1 (Max disk)*/

        for(i = totRequest-1; i >= indexOfArray; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

    }
    else /* Head Moves toward larger value*/
    {
        for(i = indexOfArray; i < totRequest; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        movement = abs(curPosi-(totCylinder-1) ); /* Moves the Head to Max*/
        totalMovement = totalMovement + movement;

        movement = abs(0-(totCylinder-1)); /* Moves the Head Max to Min */

        totalMovement = totalMovement + movement;
        curPosi = 0; // Min disk

        for(i = 0; i < indexOfArray; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }
    }

    display("C-SCAN",totalMovement);

}



/* LOOK Algorithm */
void look(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[])
{
    int totalMovement = 0;
    int movement;
    int indexOfArray;
    int tempArray[totRequest];
    int i = 0;

    /* Create a Temporary Array of disk Request */
    createTempArray(tempArray,array,totRequest);

    /* Sort the tempArray in Order to do the LOOK */
    sortArray(tempArray,totRequest);

    /* Get the index of disk next to the current position of disk */
    indexOfArray = getIndex(tempArray,totRequest,curPosi);

    /* Head Moves toward smaller value*/
    if( curPosi < prevPosi)
    {
        for(i = indexOfArray-1; i >=0; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        for(i = indexOfArray; i < totRequest; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

    }
    else /* Head Moves toward larger value*/
    {
        for(i = indexOfArray; i < totRequest; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        for(i = indexOfArray-1; i >= 0; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }
    }

    display("LOOK  ",totalMovement);

}


/* C-LOOK Algorithm */
void cLook(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[])
{
    int totalMovement = 0;
    int movement;
    int indexOfArray;
    int tempArray[totRequest];
    int i = 0;


    /* Create a Temporary Array of disk Request */
    createTempArray(tempArray,array,totRequest);

    /* Sort the tempArray in Order to do the C-LOOK */
    sortArray(tempArray,totRequest);

    /* Get the index of disk next to the current position of disk */
    indexOfArray = getIndex(tempArray,totRequest,curPosi);

    /* Head Moves toward smaller value*/
    if( curPosi < prevPosi)
    {
        for(i = indexOfArray-1; i >=0; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        for(i = totRequest-1; i >= indexOfArray; i--)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

    }
    else /* Head Moves toward larger value*/
    {
        for(i = indexOfArray; i < totRequest; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }

        for(i = 0; i < indexOfArray; i++)
        {
            movement = curPosi - tempArray[i];
            movement = abs(movement);

            totalMovement = totalMovement + movement;
            curPosi = tempArray[i]; /* Change the CurrentPosition*/
        }
    }

    display("C-LOOK",totalMovement);

}


void display(char stringArray[], int result)
{
    printf("\n %s : %d", stringArray, result);
}


/* Sort the Array in Ascending Order */

void sortArray(int array[], int size)
{
    int temp;

    for(int i=0; i<size; i++)
    {
        for(int j=i+1; j<size; j++)
        {
            if(array[j] <array[i])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}


void createTempArray(int tempArray[], int array[], int size)
{
   for(int i = 0; i < size; i++)
    {
        tempArray[i] = array[i];
    }
}

/* Get the index of disk, next to the Current disk */
int getIndex(int tempArray[], int size, int curPosi)
{
    int indexOfArray = -1;

    for(int i = 0; i < size; i++)
    {
        if(tempArray[i] > curPosi)
        {
            indexOfArray = i;
            break;
        }
    }

    return indexOfArray;
}

