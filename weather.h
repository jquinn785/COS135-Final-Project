#ifndef WEATHER_H
#define WEATHER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char city[50];
    double hTemp;
    double lTemp;
    double precipitation;
    char date[11]; // yyyy/mm/dd - 10 characters + null character
} Weather;

Weather *loadData(int numElements);
void searchData(Weather *data, int numElements);
void sortData();
void saveData();
void freeMemory();
#endif