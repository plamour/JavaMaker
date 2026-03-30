#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struc.h"
#include "template.h"
#include "writer.h"
#include "creator.h"
#include "scanner.h"

void freeEverything(JavaClass* javaClasses,int *nbOfClasses)
{
    for (int i = 0; i < *nbOfClasses; ++i)
    {
        JavaClass *javaClass = &javaClasses[i];
        for (int j = 0; j < javaClass->nbOfAttributes; ++j)
        {
            free(javaClass->javaAttribute[j].nameAttribute);
            free(javaClass->javaAttribute[j].typeAttribute);
        }
        for (int j = 0; j < javaClass->nbOfMethod; ++j)
        {
            free(javaClass->javaMethod[j].nameMethod);
            free(javaClass->javaMethod[j].typeMethod);
            for (int k = 0; k < javaClass->javaMethod[j].nbOfParameter; ++k)
            {
                free(javaClass->javaMethod[j].nameParameter[k]);
                free(javaClass->javaMethod[j].typeParameter[k]);
            }
            free(javaClass->javaMethod[j].nameParameter);
            free(javaClass->javaMethod[j].typeParameter);
        }

        free(javaClass->className);
        free(javaClass->javaAttribute);
        free(javaClass->javaMethod);
    }
    free(javaClasses);
    free(nbOfClasses);
}

void listClass(JavaClass* javaClasses, const int* nbOfClasses)
{
    for (int i = 0; i < *nbOfClasses; ++i)
    {
        printf("%d) %s\n",i,javaClasses[i].className);
    }
}

int main(void)
{
    int* nbOfClasses = malloc(sizeof(int));
    *nbOfClasses = 0;
    JavaClass *javaClasses = malloc(sizeof(*javaClasses) * MAX_CLASS);;
    while (1)
    {
        printf(FIRST_OPTION);
        int option = inputInteger(1, 4);
        switch (option)
        {
        case 1:
            system("clear");
            listClass(javaClasses,nbOfClasses);
            break;
        case 2:
            system("clear");
            if (*nbOfClasses > 0)
            {
                listClass(javaClasses,nbOfClasses);
                int opt = inputInteger(0,(*nbOfClasses)-1);
                editClass(javaClasses,&javaClasses[opt],nbOfClasses);
            } else
            {
                printf("No class available, create One !\n");
            }
            break;
        case 3:
            system("clear");
            addClass(javaClasses,nbOfClasses);
            break;
        case 4:
            for (int i = 0; i < *nbOfClasses; ++i)
            {
                JavaClass *javaClass = &javaClasses[i];
                writeJavaClass(javaClass);
            }
            freeEverything(javaClasses,nbOfClasses);
            return 0;
        default:
            freeEverything(javaClasses,nbOfClasses);
            return 1;
        }
    }
}
