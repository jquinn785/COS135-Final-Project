#include <main.h>
#include <weather.h>

#define NUM_ELEMENTS 10

int main(int argc, char *argv[])
{
    Weather *data = loadData(NUM_ELEMENTS);
    int menu = 1;
    int choice;
    int saveElements;
    while (menu)
    {
        printf("1: Search Data\n2: Sort Data\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            searchData(data, NUM_ELEMENTS);
            menu = 0;
        }
        else if (choice == 2)
        {
            printf("How many elements do you want to save? ");
            scanf("%d", &saveElements);

            setOrder();
            setField();

            sortData(data, NUM_ELEMENTS, saveElements);
            menu = 0;
        }
        else
        {
            printf("Enter a number from 1-2. ");
        }
    }
    free(data);
}