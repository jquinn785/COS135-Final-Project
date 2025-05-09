#include <weather.h>

Weather *loadData(int lines)
{
    FILE *file = fopen("weatherData.csv", "r");
    // Can't find file
    if (file == NULL)
    {
        printf("Could not open file\n");
        exit(1);
    }
    Weather *data = malloc(sizeof(Weather) * lines);

    char buffer[1024];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        Weather weather;
        strcpy(weather.city, strtok(buffer, ","));
        weather.hTemp = atof(strtok(NULL, ","));
        weather.lTemp = atof(strtok(NULL, ","));
        weather.precipitation = atof(strtok(NULL, ","));
        strcpy(weather.date, strtok(NULL, ","));

        data[i] = weather;
        i++;
    }
    fclose(file);
    return data;
}