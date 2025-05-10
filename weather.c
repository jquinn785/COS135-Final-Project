#include <weather.h>

Weather *loadData(int numElements)
{
    FILE *file = fopen("weatherData.csv", "r");
    // Can't find file
    if (file == NULL)
    {
        printf("Could not open file\n");
        exit(1);
    }
    // Allocate memory for one Weather element times the number of elements there are.
    Weather *data = malloc(sizeof(Weather) * numElements);

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

void searchData(Weather *data, int numElements)
{
    int choice;
    char buffer[1024];

    printf("Search by:\n");
    printf("1. City\n2. High Temp\n3. Low Temp\n4. Precipitation\n5. Date\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Enter city: ");
        // Read user input and store the char array in strInput. Use fgets to account for two word+ cities like New York.
        fgets(buffer, sizeof(buffer), stdin);
        // Set the null terminator at the first instance of the newline character
        buffer[strcspn(buffer, "\n")] = 0;
        for (int i = 0; i < numElements; i++)
        {
            // If the users string matches the city in a element of the weather data array then print that elemnet.
            if (strcmp(data[i].city, buffer) == 0)
                printf("%s %.1fF %.1fF %.1fin %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    case 2:
        printf("Enter high temperature: ");
        // Read the user input
        fgets(buffer, sizeof(buffer), stdin);
        // Set the null terminator at the first instance of the newline character
        buffer[strcspn(buffer, "\n")] = 0;
        // Convert the char array to a float
        float num = atof(buffer);
        for (int i = 0; i < numElements; i++)
        {
            // If the users high temperature matches the high temperature element then print the whole weather element
            if (data[i].hTemp == num)
                printf("%s %.1fF %.1fF %.1fin %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
        // For case 3 and 4 repeat what was done in case 2. For case 5 repeat what was done in case 1.
    case 3:
        printf("Enter low temperature: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        float num = atof(buffer);
        for (int i = 0; i < numElements; i++)
        {
            if (data[i].lTemp == num)
                printf("%s %.1fF %.1fF %.1fin %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    case 4:
        printf("Enter precipitation: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        float num = atof(buffer);
        for (int i = 0; i < numElements; i++)
        {
            if (data[i].precipitation == num)
                printf("%s %.1fF %.1fF %.1fin %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    case 5:
        printf("Enter date (yyyy/mm/dd): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        for (int i = 0; i < numElements; i++)
        {
            if (strcmp(data[i].date, buffer) == 0)
                printf("%s %.1fF %.1fF %.1fin %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    default:
        printf("Please choose a number 1-5.\n");
    }
}

void sortData()
{
}

void saveData()
{
}

void freeMemory()
{
}