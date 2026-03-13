#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struc.h"
#include "template.h"
#include "writer.h"
#include "creator.h"
#include "scanner.h"




int main(void)
{
    int* nbOfClass = malloc(sizeof(int));
    *nbOfClass = 0;
    JavaClass *javaClasses = malloc(sizeof(*javaClasses) * MAX_CLASS);;
    while (1)
    {
        system("clear");
        printf(FIRST_OPTION);
        int option = inputInteger(1, 3);
        system("clear");
        switch (option)
        {
        case 1:
            addAttributes(javaClasses);
            break;
        case 2:
            addMethod(javaClasses);
            break;
        case 3:
            writeJavaClass(javaClasses);
            return 0;
        case 4:
            /* TODO - < Write all classes >*/
            writeJavaClass(javaClasses);
            return 0;
        default:
            freeEverything(javaClasses);
            return 1;
        }
    }
}
