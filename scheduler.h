#ifndef SCHEDULER_H
#define SCHEDULER_H

void firstComeFirstServe(int curPosition, int array[] ,int totRequest);
void shortestSeekTimeFirst(int totRequest, int array[], int curPosition);
void scan(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[]);
void cScan(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[]);
void look(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[]);
void cLook(int totCylinder, int curPosi, int prevPosi, int totRequest, int array[]);

void display(char stringArray[], int result);
void sortArray(int array[], int size);
void createTempArray(int tempArray[], int array[], int size);
int getIndex(int tempArray[], int size, int curPosi);


#endif
