#include <stdio.h>
#include "functions.h"

int main()
{
    // създаваме листа с данни от бинарния файл
    NODE* root = create_list();

    printf("Welcome!\n");

    int option;
    // безкраен цикъл
    for(;;)
    {
        printf("\nMenu:\n");
        printf("Option 1: view the list\n");
        printf("Option 2: add route\n");
        printf("Option 3: edit duration of a route\n");
        printf("Option 4: delete route\n");
        printf("Option 5: find fastest route\n");
        printf("Option 6: find shortest route\n");
        printf("Option 0: save changes and exit the program\n");
        printf("Choose an option: ");

        scanf("%d",&option);

        if(option==1)
        {
            // тази функция принтира на екрана целия лист
            printList(root);
        }
        else if(option == 2)
        {
            // чрез тази функция, потребителят може да добави нов елемент в листа
            root = add_new(root);
        }
        else if(option==3)
        {
            // чрез тази функция, потребителят може да промени елемент в листа
            change_entry(root);
        }
        else if(option==4)
        {
            // чрез тази функция, потребителят може да изтрие елемент в листа
            root = delete_node(root);
        }
        else if(option==5)
        {
            // чрез тази функция, потребителят може да търси най-бързия маршрут
            findFastestRoute(root);
        }
        else if(option==6)
        {
            // чрез тази функция, потребителят може да търси най-краткия маршрут
            findShortestRoute(root);
        }
        else if(option==0)
        {
            // тази функция запазва на ново файла, като презаписва информацията ако има някакви промени
            exitProgramm(root);
        }
        else
        {
            printf("Incorrect input! Try again!\n");
        }
    }
}
