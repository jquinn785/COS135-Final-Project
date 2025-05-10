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
    char date[12]; // yyyy/mm/dd - 10 characters + null character + new line charcter
} Weather;

Weather *loadData(int numElements);
void searchData(Weather *data, int numElements);
void setOrder();
void setField();
int compare(const void *a, const void *b);
void sortData(Weather *data, int numElements, int saveElements);
#endif