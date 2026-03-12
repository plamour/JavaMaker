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
    JavaClass *java_class = malloc(sizeof(*java_class));
    JavaAttribute *java_attribute = malloc(sizeof(*java_attribute) * MAX_ATTRIBUTES);
    JavaMethod *java_method = malloc(sizeof(*java_method) * MAX_METHOD);
    java_class->nbOfAttributes = 0;
    java_class->nbOfMethod = 0;
    java_class->javaAttribute = java_attribute;
    java_class->javaMethod = java_method;
    // FILE *file = fopen("Mom.java","r");
    // JavaClass *java_class = classScanner(file);
    // fclose(file);
    java_class->mother_class = NULL;
    printf("What the Class Name :\n");
    char* name = inputString();
    java_class->className = name;
    printf("%d",java_class->nbOfAttributes);
    while (1)
    {
        system("clear");
        printf(FIRST_OPTION);
        int option = inputInteger(1, 3);
        system("clear");
        switch (option)
        {
        case 1:
            addAttributes(java_class);
            break;
        case 2:
            addMethod(java_class);
            break;
        case 3:
            writeJavaClass(java_class);
            return 0;
        default:
            freeEverything(java_class);
            return 1;
        }
    }
}
