#include <stdio.h>
#include <iostream>

#define clear() printf("\033[H\033[J") // Gör att "clear()" rensar konsolen

typedef struct
{
    char source[25];
    char target[25];
    char weight[4];
} interaction;

int main()
{
    FILE* fp = fopen("thrones.csv", "r"); // Öppnar filen

    // Skriver ut ett errormeddelande och avslutar programmet om filen inte kan läsas
    if (fp == NULL)
    {
        puts("Error: File not found.");
        return 1;
    }

    interaction interactions[354]; // En AoS för att lagra all data från filen

    char buffer[100];
    char input = ' ';
    char* line;
    int i = 0;
    
    fgets(buffer, sizeof(interactions), fp); // Läser alla rader i filen

    // Lägger in all data i CSV filen i alla variabler i structen "interaction"
    while (fgets(buffer, sizeof(interactions), fp) )
    {
        line = strtok(buffer, ",");
        strcpy(interactions[i].source, line);
        line = strtok(NULL, ",");
        strcpy(interactions[i].target, line);
        line = strtok(NULL, "\n");
        strcpy(interactions[i].weight, line);

        i++;
    }
    
    puts("What information do you want to get?\n");
    puts("(L) List of names, (R) Relationships, (Q) Quit\n");

    // Läser av vad användaren trycker på för tangent och tar bort "enter" som input
    scanf("%c", &input);
    fflush(stdin);

    if (tolower(input) == 'l') // Vad som händer om man trycker på 'l'
    {

        clear();
        puts("These are all the names:\n");

        // Skriver ut alla namn från "source" i CSV filen
        for(int i = 0; i < 353; i++)
        {
            if (strcmp(interactions[i].source, interactions[i - 1].source)) // Kollar om namnet är samma som namnet innan för att inte skriva samma sake flera gånger.
            {
                printf("%s\n", interactions[i].source);
            }
                // printf("%s\n", interactions[i].weight);
        }
    }
    else if (tolower(input) == 'r') // Vad som händer om man trycker på 'r'
    {
        char name_input[25];
        char weight_sort[4];

        clear();
        puts("Who's relations do you want to see?\n");
        puts("There are all the names you can choose from:\n\n");

        // Listar alla namn från "source" så att man vet vilka namn man
        // har att välja mellan
        for (int i = 0; i < 353; i++)
        {
            if (strcmp(interactions[i].source, interactions[i - 1].source)) // Kollar om namnet är samma som namnet innan för att inte skriva samma sake flera gånger.
            {
                printf("%s\n", interactions[i].source);
            }
        }

        // Läser av vilket namn man skriver in
        scanf("%s", name_input);
        fflush(stdin);
        
        clear();

        // Skriver ut alla namn som den angivna personen har interagerat
        // med och hur mångar gånger de har interagerat med varandra.
        for (int i = 0; i < 353; i++)
        {
            if (!strcmp(name_input, interactions[i].source))
            {
                if (strcmp(interactions[i].source, interactions[i - 1].source)) // Kollar om namnet är samma som namnet innan för att inte skriva samma sake flera gånger.
                {
                    printf("These are %s's relations:\n\n", interactions[i].source);
                }

                printf("Name: %s, Total interactions: %s\n", interactions[i].target, interactions[i].weight);
            }
        }
    }
    else if (tolower(input) == 'q') // Vad som händer om man trycker på 'q'
    {
        clear();
        puts("Quitting program...");
        exit(0); // Avslutar programmet
    }
    
    fclose(fp); // Stänger filen

    return 0;
}