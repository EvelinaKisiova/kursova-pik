#include "functions.h"

// тази функция създава листа, като прочита информацията от бинарен файл и я зарежда в динамична структура
// връща указател към "корена"(върха) на листа, и не приема параметри
NODE* create_list(void)
{
    // отваряме файла за четене
    FILE* fp = fopen("data.bin","rb");
    if(fp == NULL)
    {
        // ако нямаме такъв файл
        printf("Unable to open file!\n");
        return NULL;
    }

    // тук ще записваме прочетените записи
    NODE temp;
    if(fread(&temp,sizeof(NODE),1,fp)!=1)
    {
        printf("File does not have entries!\n");
        return NULL;
    }
    // създаваме нов запис
    NODE* root = create_node(NULL,temp);

    // четем записите един по един
    for(;;)
    {
        if(fread(&temp,sizeof(NODE),1,fp)!=1)
        {
            printf("File loaded!\n");
            break;
        }
        // създаваме нови записи в динамичната памет
        root = create_node(root,temp);
    }
    fclose(fp);
    return root;
}

// тази функция създава нова структура и я добавя на върха на листа
// връща указател към "корена"(върха) на листа
// приема като параметри: старият "корен", и информацията за структурата
NODE* create_node(NODE* root, NODE temp)
{
    // заделяме памет за един елемент структура
    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    // проверяваме за грешка
    if(new_node==NULL)
    {
        printf("Memory allocation problem!\n");
        exit(2);
    }

    // записваме подадената информация като параметри в структурата
    *new_node = temp;

    // правим този елемент да е новият връх
    new_node->next = root;

    // връщаме указател към новия връх
    return new_node;
}

// тази функция принтира на екрана целия лист
// приема като параметър указателя към корена на листа
void printList(NODE* root)
{
    NODE* temp;

    // ако листа е празен
    if (root == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    printf("All entries:\n");

    // обхождаме целия лист
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        printEntry(temp);
    }
}

// принтира елемент от листа на екрана
// приема указател към съответния елемент
void printEntry(NODE* temp)
{
    printf("Route: %s - %s; distance: %.2f kilometers; duration %.2f minutes\n", temp->start_point, temp->end_point, temp->distance, temp->duration);
}

// чрез тази функция, потребителят може да промени елемент в листа
// приема като параметър указателя към корена на листа
void change_entry(NODE* root)
{
    // ако листа е празен
    if (root == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    // прочитаме от потребителя, кой елемент иска да промени като прочитаме началната и крайната точка
    char start[20];
    char end[20];

    // началната
    printf("Set new duration for a route\n");
    printf("Enter start point: ");
    fflush(stdin);
    gets(start);
    // крайната
    printf("Enter end point: ");
    fflush(stdin);
    gets(end);

    NODE* temp;

    // обхождаме целия лист
    for(temp = root; temp != NULL; temp = temp->next)
    {
        // ако намерим конкретния маршрут
        if(strcmp(temp->start_point, start) == 0 && strcmp(temp->end_point, end) == 0)
        {
            // принтираме конкретния елемент
            printf("Chosen entry:\n");
            printEntry(temp);

            // прочитаме новия времетраене
            float new_duration;
            printf("Enter new duration in minutes: ");
            scanf("%f", &new_duration);

            // ако е валидно
            if (new_duration >= 0)
            {
                temp->duration = new_duration;
                printf("Duration changed successfully!\n");
            }
            // ако е невалидно
            else
            {
                printf("Invalid duration!\n");
            }
            return;
        }
    }
    // ако не намерим такъв елемент
    printf("There is no entries matching your input!\n");
}

// чрез тази функция, потребителят може да изтрие елемент в листа
// приема като параметър указателя към корена на листа
// връща указател към "корена"(върха) на листа
NODE* delete_node(NODE* root)
{
    // ако листа е празен
    if(root==NULL)
    {
        printf("List is empty!\n");
        return NULL;
    }

    // прочитаме от потребителя, кой елемент иска да изтрие
    char start[20];
    char end[20];

    // прочитаме началната точка
    printf("Enter start point: ");
    fflush(stdin);
    gets(start);

    // прочитаме крайна точка
    printf("Enter end point: ");
    fflush(stdin);
    gets(end);

    NODE* temp;
    NODE* pre;

    // обхождаме целия лист, като запазваме кой е и предишния елемент
    for(temp=root,pre=root;temp!=NULL;pre=temp,temp=temp->next)
    {
        // ако намерим елемент, който отговаря
        if(strcmp(temp->start_point, start) == 0 && strcmp(temp->end_point, end) == 0)
        {
            printf("Chosen entry:\n");
            printEntry(temp);

            // проверяваме дали иска да изтрие върха, само тогава предишният елемент и текущият ще съвпадат
            if(temp==root)
            {
                // запазваме елемента след върха
                root=root->next;

                // освобождаваме върха
                free(temp);

                // връщаме новия връх (функ. се прекратява тук)
                return root;
            }

            // свързваме елементите, които са от двете страни на елемента, който искаме да махнем
            pre->next=temp->next;

            // освобождаме елемента
            free(temp);

            // връщаме връха (функ. се прекратява тук)
            return root;
        }
    }
    printf("There is no entry matching your input!\n");
    // връщаме връха
    return root;
}

// чрез тази функция, потребителят може да добави нов елемент в листа
// приема като параметър указателя към корена на листа
// връща указател към "корена"(върха) на листа
NODE * add_new(NODE* root)
{
    NODE new_node;

    // прочитаме началната точка на новия запис
    printf("\nEnter start point: ");
    fflush(stdin);
    gets(new_node.start_point);

    // прочитаме крайната точка на новия запис
    printf("Enter end point: ");
    fflush(stdin);
    gets(new_node.end_point);

    // обхождаме целия лист за да проверим дали няма вече такав елемент
    NODE* temp;
    for(temp = root; temp != NULL; temp = temp->next)
    {
        // ако има, прекратяваме функ. и връщаме върха на листа
        if(strcmp(temp->start_point, new_node.start_point) == 0 && strcmp(temp->end_point, new_node.end_point) == 0)
        {
            printf("The following route exists already\n");
            return root;
        }
    }

    // прочитаме информацията за новия елемент
    printf("Enter duration in minutes: ");
    scanf("%f",&new_node.duration);

    printf("Enter distance in kilometers: ");
    scanf("%f",&new_node.distance);

    // проверяме дали е валидна информацията
    if(new_node.duration <= 0 || new_node.distance <= 0)
    {
        printf("Invalid input! You have entered not positive number somewhere!\n");
        return root;
    }

    // извикваме функцията за създаване на нова структура, която връща указател към нов "корен" (връх) на листа
    // приема като параметри: старият "корен", и информацията за структурата
    root = create_node(root,new_node);

    printf("New entry added!\n");

    return root;
}

// тази функция принтира най-бързия маршрут
// приема като параметър указателя към корена на листа
void findFastestRoute(NODE* root)
{
    // ако листа е празен
    if (root == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    // търсим най-малка стойност като почваме от най-голямата
    float best_duration = FLT_MAX;

    // тук ще запазим най-бързия маршрут
    NODE* fastest_route = NULL;

    NODE* temp;
    // обхождаме целия лист и търсим маршрута с най-малкото времетраене
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        if (temp->duration < best_duration)
        {
            best_duration = temp->duration;
            fastest_route = temp;
        }
    }
    // принтира резултата
    printf("Route with the lowest duration:\n");
    printEntry(fastest_route);
}

// тази функция принтира най-краткия път
// приема като параметър указателя към корена на листа
void findShortestRoute(NODE* root)
{
    // ако листа е празен
    if (root == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    // търсим най-малка стойност като почваме от най-голямата
    float best_distance = FLT_MAX;

    // тук ще запазим най-краткия маршрут
    NODE* shortest_route = NULL;

    NODE* temp;
    // обхождаме целия лист и търсим най-кратката дистанция
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        if (temp->distance < best_distance)
        {
            best_distance = temp->distance;
            shortest_route = temp;
        }
    }
    // принтираме резулатата
    printf("Shortest route:\n");
    printEntry(shortest_route);
}

// тази функция запазва на ново файла, като презаписва информацията ако има някакви промени
// приема като параметър указателя към корена на листа
void exitProgramm(NODE* root)
{
    // отваряме файла с информацията в режим записване на бинарен файл
    FILE* fp = fopen("data.bin","wb");

    // проверяваме за проблеми
    if(fp == NULL)
    {
        printf("Unable to open file!\n");
        exit(1);
    }

    NODE* temp;
    // обхождаме целия лист и записваме информацията му в бинарния файл
    while(root!=NULL)
    {
        temp= root;
        root=root->next;
        temp->next=NULL;
        fwrite(temp,sizeof(NODE),1,fp);
        free(temp);
    }

    // успех
    exit(0);
}
