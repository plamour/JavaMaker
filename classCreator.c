#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struc.h"
#include "template.h"

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
    char s[64];
    scanf("%63s", s);
    return strdup(s);
}

char* inputGetType()
{
    int option = inputInteger(1, 6);
    char* type;
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
    return type;
}





void addAttributes(JavaClass* java_class)
{
    printf(TYPE_OPTION);

    char* type = inputGetType();
    printf("What will be the name of the attribute :\n");
    char* name = inputString();
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


void addParameter(JavaMethod *java_method)
{
    printf(TYPE_OPTION);
    char* type = inputGetType();
    printf("What will be the name of the parameter :\n");
    char* name = inputString();
    java_method->nameParameter[java_method->nbOfParameter] = name;
    java_method->typeParameter[java_method->nbOfParameter] = type;
    java_method->nbOfParameter++;

}

void addMethod(JavaClass *java_class)
{
    printf(TYPE_OPTION);

    char* type = inputGetType();
    char* name;
    printf("What will be the name of the Method :\n");
    name = inputString();
    JavaMethod java_method;
    java_method.typeMethod = type;
    java_method.nameMethod = name;
    java_method.insideCode = NULL;

    java_method.nbOfParameter = 0;
    java_method.nameParameter = malloc(sizeof(char*)*MAX_PARAMETER_METHOD);
    java_method.typeParameter = malloc(sizeof(char*)*MAX_PARAMETER_METHOD);
    printf("Does this method has parameter ?\n(y/n):");
    char *opt = inputString();
    opt[0] = tolower(opt[0]);
    while (strcmp(opt,"y") == 0)
    {
        addParameter(&java_method);
        printf("Does this method has another parameter ?\n(y/n):");
        opt = inputString();
        opt[0] = tolower(opt[0]);
    }

    if (!java_class->javaMethod)
    {
        exit(2);
    }
    java_class->javaMethod[java_class->nbOfMethod] = java_method;
    java_class->nbOfMethod++;
}