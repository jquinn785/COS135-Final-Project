#ifndef WEATHER_H
#define WEATHER_H

typedef struct
{
    char city[50];
    double hTemp;
    double lTemp;
    double precipitation;
    char date[11]; // yyyy/mm/dd - 10 characters + null character
} Weather;

void loadData();
void searchData();
void sortData();
void saveData();
#endif