#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struc.h"
#include "template.h"
int isPrimaryType(const char* type)
{
    return (strcmp(type, "int") == 0 ||
            strcmp(type, "boolean") == 0 ||
            strcmp(type, "byte") == 0 ||
            strcmp(type, "char") == 0 ||
            strcmp(type, "short") == 0 ||
            strcmp(type, "long") == 0 ||
            strcmp(type, "float") == 0 ||
            strcmp(type, "double") == 0);
}

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
    case 5: type = strdup("boolean");
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
void writeEqual(JavaClass *java_class, FILE *file)
{
    char* equals = malloc(sizeof(char)*1024);
    char firstLetter = tolower(java_class->className[0]);
    char firstLetterStr[2] = { firstLetter, '\0' };
    snprintf(equals,sizeof(char)*1024,EQUALS,java_class->className,firstLetter);
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        JavaAttribute java_attribute = java_class->javaAttribute[i];
        if (isPrimaryType(java_attribute.typeAttribute))
        {
            strcat(equals,"this.");
            strcat(equals,java_attribute.nameAttribute);
            strcat(equals," == ");
            strcat(equals,firstLetterStr);
            strcat(equals,".");
            strcat(equals,java_attribute.nameAttribute);

        } else
        {
            strcat(equals,"this.");
            strcat(equals,java_attribute.nameAttribute);
            strcat(equals,".equals(");
            strcat(equals,firstLetterStr);
            strcat(equals,".");
            strcat(equals,java_attribute.nameAttribute);
            strcat(equals,")");

        }

        if (i != java_class->nbOfAttributes-1)
        {
            strcat(equals," && ");
        }


    }
    strcat(equals,";\n\t}");
    fprintf(file,equals);
    free(equals);
}

void writeToString(JavaClass *java_class, FILE *file)
{
    char* toString = malloc(sizeof(char)*1024);
    snprintf(toString,sizeof(char)*1024,TO_STRING);
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        JavaAttribute java_attribute = java_class->javaAttribute[i];
        strcat(toString,"\"");
        strcat(toString,java_attribute.nameAttribute);
        strcat(toString,": \" + this.");
        strcat(toString,java_attribute.nameAttribute);
        if (i != java_class->nbOfAttributes-1)
        {
            strcat(toString," + ");
        }
    }

    strcat(toString,";\n\t}");
    fprintf(file,toString);
    free(toString);
}

void writeAttributes(JavaClass *java_class,FILE *file)
{
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        JavaAttribute java_attribute = java_class->javaAttribute[i];
        fprintf(file,ATTRIBUTES_TEMPLATE,java_attribute.typeAttribute,java_attribute.nameAttribute);
    }
}

void writeGetterAndSetter(JavaClass *java_class,FILE *file)
{
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        JavaAttribute java_attribute = java_class->javaAttribute[i];
        char* upperCase = strdup(java_attribute.nameAttribute);
        upperCase[0] = toupper(upperCase[0]);
        fprintf(file,DEFAULT_GETTER,java_attribute.typeAttribute,upperCase,java_attribute.nameAttribute);
        fprintf(file,DEFAULT_SETTER,upperCase,java_attribute.typeAttribute,java_attribute.nameAttribute,java_attribute.nameAttribute,java_attribute.nameAttribute);
    }

}

void writeConstructor(JavaClass *java_class, FILE *file)
{
    //First the Default Constructor
    fprintf(file,DEFAULT_CONSTRUCTOR_TEMPLATE,java_class->className);
    //Second Constructor with parameter
    char *constructor = malloc(sizeof(char)*1024);
    snprintf(constructor,sizeof(char)*1024,"\tpublic %s(",java_class->className);
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        JavaAttribute java_attribute = java_class->javaAttribute[i];
        if (i == java_class->nbOfAttributes-1)
        {
            strcat(constructor,java_attribute.typeAttribute);
            strcat(constructor," ");
            strcat(constructor,java_attribute.nameAttribute);

        } else
        {
            strcat(constructor,java_attribute.typeAttribute);
            strcat(constructor," ");
            strcat(constructor,java_attribute.nameAttribute);
            strcat(constructor,",");

        }
    }
    strcat(constructor,") {");
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        JavaAttribute java_attribute = java_class->javaAttribute[i];
        strcat(constructor,"\n\t\tthis.");
        strcat(constructor,java_attribute.nameAttribute);
        strcat(constructor," = ");
        strcat(constructor,java_attribute.nameAttribute);
        strcat(constructor,";");

    }
    strcat(constructor,"\n\t}\n\n");
    fprintf(file,constructor);
    free(constructor);
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
    writeGetterAndSetter(java_class,file);
    writeEqual(java_class,file);






    fprintf(file,"\n}");
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
