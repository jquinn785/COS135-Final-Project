#include <weather.h>

// Loads the entries of the weatherData.csv file into the weather data struct array and returns the array.
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

// Asks the user what field they want to search and then what specifcally they want to search, and prints the search.
void searchData(Weather *data, int numElements)
{
    FILE *file = fopen("searchResults.txt", "w");
    if (file == NULL)
    {
        printf("Could not open file\n");
        exit(1);
    }

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
                fprintf("City: %s High: %.1fF Low: %.1fF Precipitation: %.1fin Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
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
                fprintf("City: %s High: %.1fF Low: %.1fF Precipitation: %.1fin Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
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
                fprintf("City: %s High: %.1fF Low: %.1fF Precipitation: %.1fin Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
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
                fprintf("City: %s High: %.1fF Low: %.1fF Precipitation: %.1fin Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    case 5:
        printf("Enter date (yyyy/mm/dd): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        for (int i = 0; i < numElements; i++)
        {
            if (strcmp(data[i].date, buffer) == 0)
                fprintf("City: %s High: %.1fF Low: %.1fF Precipitation: %.1fin Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
        }
        break;
    default:
        printf("Please choose a number 1-5.\n");
    }
    fclose(file);
}

// Comparison function for uisng the quick sort function. Returns a -1, 0, or 1 depending on if two elements should be behind, equal, or ahead of another respivtively, while also considering if the order is ascending or descending.

// These will be defined based on user input in the main function.
int field;
char order;
int compare(const void *a, const void *b)
{
    Weather *weather1 = (Weather *)a;
    Weather *weather2 = (Weather *)b;

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

void sortData(Weather *data, int numElements, int saveElements)
{
    qsort(data, numElements, sizeof(Weather), compare);
    FILE *file = fopen("sortedResults.txt", "w");
    if (file == NULL)
    {
        printf("Could not open file\n");
        exit(1);
    }
    for (int i = 0; i < numElements; i++)
    {
        fprintf("City: %s High: %.1fF Low: %.1fF Precipitation: %.1fin Date: %s\n", data[i].city, data[i].hTemp, data[i].lTemp, data[i].precipitation, data[i].date);
    }
}
