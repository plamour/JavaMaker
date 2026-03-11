#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struc.h"
#include "template.h"

void freeEverything(JavaClass* java_class)
{
    for (int i = 0; i <= java_class->nbOfAttributes; ++i)
    {
        free(java_class->javaAttribute[i].nameAttribute);
        free(java_class->javaAttribute[i].typeAttribute);
    }
    free(java_class->className);
    free(java_class->javaAttribute);
    free(java_class);
}

int inputInteger(int from, int to)
{
    int option;
    scanf("%d", &option);
    while (option < from || option > to)
        scanf("%d", &option);
    return option;
}

char* inputString()
{
    char* s = malloc(sizeof(char) * 64);
    scanf("%63s", s);
    return s;
}


void addAttributes(JavaClass* java_class)
{
    printf(TYPE_OPTION);

    int option = inputInteger(1, 6);
    char* type;
    char* name;

    switch (option)
    {
    case 1: type = strdup("int");
        break;
    case 2: type = strdup("double");
        break;
    case 3: type = strdup("float");
        break;
    case 4: type = strdup("long");
        break;
    case 5: type = strdup("double");
        break;
    case 6:
        printf("Write the custom type :\n");
        type = inputString();
        break;
    default: exit(1);
    }
    printf("What will be the name of the attribute :\n");
    name = inputString();
    JavaAttribute java_attribute;
    java_attribute.typeAttribute = type;
    java_attribute.nameAttribute = name;

    if (!java_class->javaAttribute)
    {
        exit(2);
    }
    java_class->javaAttribute[java_class->nbOfAttributes] = java_attribute;
    java_class->nbOfAttributes++;
}

void writeAttributes(JavaClass *java_class,FILE *file)
{
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        JavaAttribute java_attribute = java_class->javaAttribute[i];
        fprintf(file,ATTRIBUTES_TEMPLATE,java_attribute.typeAttribute,java_attribute.nameAttribute);
    }
}


void writeConstructor(JavaClass* java_class, FILE* file)
{

}

void writeJavaClass(JavaClass* java_class)
{
    FILE *file;
    char *filename = malloc(sizeof(char)*64);
    snprintf(filename,sizeof(char)*64,"%s.java",java_class->className);
    file = fopen(filename,"wx");
    fprintf(file,IMPORT);
    fprintf(file,CLASS,java_class->className);
    writeAttributes(java_class,file);
    writeConstructor(java_class,file);






    free(filename);
    fclose(file);
    freeEverything(java_class);
}


int main(void)
{
    JavaClass* java_class = malloc(sizeof(*java_class));
    JavaAttribute* java_attribute = malloc(sizeof(*java_attribute) * MAX_ATTRIBUTES);
    java_class->nbOfAttributes = 0;
    java_class->javaAttribute = java_attribute;
    java_class->mother_class = NULL;
    printf("What the Class Name :\n");
    char* name = inputString();
    java_class->className = name;
    while (1)
    {
        printf(FIRST_OPTION);
        int option = inputInteger(1, 3);
        switch (option)
        {
        case 1:
            addAttributes(java_class);
            break;
        case 2:
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
