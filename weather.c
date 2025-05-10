#include "weather.h"

// This file contains all indicual functions required for the program to run. A function to laod the data, a function to search the data, and the functions requried to sort the data.

// Loads the entries of the weatherData.csv file into the weather data struct array and returns the array. Takes the number of elements in the csv file, where that is the number of entries.
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

// Asks the user what field they want to search and then what specifcally they want to search, and prints the search. Takes the data that is loaded into memory and the number of elements in the data.
void searchData(Weather *data, int numElements)
{
    FILE *file = fopen("searchResults.txt", "w");
    if (file == NULL)
    {
        printf("Could not open file\n");
        exit(1);
    }

    int choice;
    float num;
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
                fprintf(file, "City: %s High: %.1f F Low: %.1f F Precipitation: %.1f in Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    case 2:
        printf("Enter high temperature: ");
        // Read the user input
        fgets(buffer, sizeof(buffer), stdin);
        // Set the null terminator at the first instance of the newline character
        buffer[strcspn(buffer, "\n")] = 0;
        // Convert the char array to a float
        num = atof(buffer);
        for (int i = 0; i < numElements; i++)
        {
            // If the users high temperature matches the high temperature element then print the whole weather element
            if (data[i].hTemp == num)
                fprintf(file, "City: %s High: %.1f F Low: %.1f F Precipitation: %.1f in Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
        // For case 3 and 4 repeat what was done in case 2. For case 5 repeat what was done in case 1.
    case 3:
        printf("Enter low temperature: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        num = atof(buffer);
        for (int i = 0; i < numElements; i++)
        {
            if (data[i].lTemp == num)
                fprintf(file, "City: %s High: %.1f F Low: %.1f F Precipitation: %.1f in Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    case 4:
        printf("Enter precipitation: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        num = atof(buffer);
        for (int i = 0; i < numElements; i++)
        {
            if (data[i].precipitation == num)
                fprintf(file, "City: %s High: %.1f F Low: %.1f F Precipitation: %.1f in Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    case 5:
        printf("Enter date (yyyy/mm/dd): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        for (int i = 0; i < numElements; i++)
        {
            if (strcmp(data[i].date, buffer) == 0)
                fprintf(file, "City: %s High: %.1f F Low: %.1f F Precipitation: %.1f in Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    default:
        printf("Please choose a number 1-5.\n");
    }
    fclose(file);
}

char order;
int field;

// Allows the user to set the order for sorting. This will be called from the main function.
void setOrder()
{
    printf("Do you want to sort in ascending or descending order? ");
    scanf("%c", &order);
}

// Allows the user to set the field for sorting. This will be called from the main function.
void setField()
{
    printf("Sort by:\n");
    printf("1. City\n2. High Temp\n3. Low Temp\n4. Precipitation\n");
    printf("Enter your choice: ");
    scanf("%d", &field);
}
// Comparison function for uisng the quick sort function. Returns a -1, 0, or 1 depending on if two elements should be behind, equal, or ahead of another respivtively, while also considering if the order is ascending or descending. Takes two const void pointers which will be type casted to be weather pointers. This is for qsort.
int compare(const void *a, const void *b)
{
    Weather *weather1 = a;
    Weather *weather2 = b;

    float val1;
    float val2;
    char charVal1;
    char charVal2;

    switch (field)
    {
    case 1:
        return strcmp(weather1->city, weather2->city);
    case 2:
        val1 = weather1->hTemp;
        val2 = weather2->hTemp;
        break;
    case 3:
        val1 = weather1->lTemp;
        val2 = weather2->lTemp;
        break;
    case 4:
        val1 = weather1->precipitation;
        val2 = weather2->precipitation;
        break;
    default:
        return 0;
    }

    if (order == 'a')
    {
        if (val1 < val2)
        {
            return -1;
        }
        else if (val1 > val2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if (order == 'd')
    {
        if (val1 < val2)
        {
            return 1;
        }
        else if (val1 > val2)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

// Sorts the Weather struct array with qsort and the previous Comparison function. Then it prints the first x elements of the array determined by saveElements.
void sortData(Weather *data, int numElements, int saveElements)
{
    qsort(data, numElements, sizeof(Weather), compare);
    if (numElements >= saveElements)
    {
        FILE *file = fopen("sortedResults.txt", "w");
        if (file == NULL)
        {
            printf("Could not open file\n");
            exit(1);
        }
        for (Weather *ptr = data; ptr < data + saveElements; ptr++)
        {
            fprintf(file, "City: %s High: %.1f F Low: %.1f F Precipitation: %.1f in Date: %s\n", ptr->city, ptr->hTemp, ptr->lTemp, ptr->precipitation, ptr->date);
        }
        fclose(file);
    }
    else
    {
        printf("Error. Save less elements.");
    }
}
