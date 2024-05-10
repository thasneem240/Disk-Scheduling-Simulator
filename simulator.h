#ifndef SIMULATOR_H
#define SIMULATOR_H

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex;

typedef struct
{
    int totCylinder;
    int currPosi;
    int prevPosi;
    int totRequest;
    int rqCylinderList[100];
	char code;

}diskScheduleDetails;


void selectScheduleAlgorithm(diskScheduleDetails diskData, char code);
void *doThreadDiskSchedule(void *diskData);

#endif
