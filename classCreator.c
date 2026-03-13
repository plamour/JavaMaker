#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struc.h"
#include "template.h"

void editClass(JavaClass *javaClasses,JavaClass *javaClass,int *nbOfClass);


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


int getClassIndex(JavaClass *javaClasses,JavaClass *javaClass,int nbOfClasses)
{
    for (int i = 0; i < nbOfClasses; ++i)
    {
        if (&javaClasses[i] == javaClass)
        {
            return i;
        }
    }
    exit(1);
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
void showAttributesAndMother(JavaClass *javaClass)
{
    for (int i = 0; i < javaClass->nbOfAttributes; ++i)
    {
        printf("Attribute %s of type %s\n",javaClass->javaAttribute[i].nameAttribute,javaClass->javaAttribute[i].typeAttribute);
    }
    if (javaClass->mother_class)
    {
        printf("Mother class is : %s and has these attribute :\n",javaClass->mother_class->className);
        showAttributesAndMother(javaClass->mother_class);
    }
}


void showMethod(JavaClass* javaClass)
{
    for (int i = 0; i < javaClass->nbOfMethod; ++i)
    {
        JavaMethod javaMethod = javaClass->javaMethod[i];
        printf("Method %s return %s and has parameter : (",javaMethod.nameMethod,javaMethod.typeMethod);
        for (int j = 0; j < javaMethod.nbOfParameter; ++j)
        {
            printf(" %s %s ",javaMethod.typeParameter[j],javaMethod.nameParameter[j]);
            if (j != javaMethod.nbOfParameter-1)
            {
                printf(",");
            }
        }
        printf(")\n");
    }
}


void changeMotherClass(JavaClass* javaClasses, JavaClass* javaClass, int *nbOfClasses)
{
    int skip = getClassIndex(javaClasses,javaClass,*nbOfClasses);
    for (int i = 0; i < *nbOfClasses; ++i)
    {
        if (i != skip)
        {
            if (i >= skip)
            {
                printf("%d) %s\n",i-1,javaClass->className);
            } else
            {
                printf("%d) %s\n",i,javaClass->className);

            }
        }
    }
    int option = inputInteger(1,*nbOfClasses-1);
    if (option >= skip) option--;
    javaClass->mother_class = javaClasses[option];
}



void addAttributes(JavaClass* javaClass)
{
    printf(TYPE_OPTION);

    char* type = inputGetType();
    printf("What will be the name of the attribute :\n");
    char* name = inputString();
    JavaAttribute javaAttribute;
    javaAttribute.typeAttribute = type;
    javaAttribute.nameAttribute = name;

    if (!javaClass->javaAttribute)
    {
        exit(2);
    }
    javaClass->javaAttribute[javaClass->nbOfAttributes] = javaAttribute;
    javaClass->nbOfAttributes++;
}


void addParameter(JavaMethod *javaMethod)
{
    printf(TYPE_OPTION);
    char* type = inputGetType();
    printf("What will be the name of the parameter :\n");
    char* name = inputString();
    javaMethod->nameParameter[javaMethod->nbOfParameter] = name;
    javaMethod->typeParameter[javaMethod->nbOfParameter] = type;
    javaMethod->nbOfParameter++;

}

void addMethod(JavaClass *javaClass)
{
    printf(TYPE_OPTION);
    char* type = inputGetType();
    char* name;
    printf("What will be the name of the Method :\n");
    name = inputString();
    JavaMethod javaMethod;
    javaMethod.typeMethod = type;
    javaMethod.nameMethod = name;
    javaMethod.insideCode = NULL;

    javaMethod.nbOfParameter = 0;
    javaMethod.nameParameter = malloc(sizeof(char*)*MAX_PARAMETER_METHOD);
    javaMethod.typeParameter = malloc(sizeof(char*)*MAX_PARAMETER_METHOD);
    printf("Does this method has parameter ?\n(y/n):");
    char *opt = inputString();
    opt[0] = tolower(opt[0]);
    while (strcmp(opt,"y") == 0)
    {
        addParameter(&javaMethod);
        printf("Does this method has another parameter ?\n(y/n):");
        free(opt);
        opt = inputString();
        opt[0] = tolower(opt[0]);
    }
    free(opt);

    if (!javaClass->javaMethod)
    {
        exit(2);
    }
    javaClass->javaMethod[javaClass->nbOfMethod] = javaMethod;
    javaClass->nbOfMethod++;
}

void addClass(JavaClass *javaClasses,int *nbOfClass)
{
    JavaClass javaClass;
    JavaAttribute *java_attribute = malloc(sizeof(*java_attribute) * MAX_ATTRIBUTES);
    JavaMethod *java_method = malloc(sizeof(*java_method) * MAX_METHOD);
    javaClass.nbOfAttributes = 0;
    javaClass.nbOfMethod = 0;
    javaClass.javaAttribute = java_attribute;
    javaClass.javaMethod = java_method;
    javaClass.mother_class = NULL;
    printf("What the Class Name :\n");
    char* name = inputString();
    javaClass.className = name;
    javaClasses[*nbOfClass] = javaClass;
    (*nbOfClass)++;
    editClass(javaClasses,&javaClasses[*nbOfClass-1],nbOfClass);
}

void addParentClass(JavaClass *javaClasses,int *nbOfClass,JavaClass *childClass)
{
    JavaClass javaClass;
    JavaAttribute *java_attribute = malloc(sizeof(*java_attribute) * MAX_ATTRIBUTES);
    JavaMethod *java_method = malloc(sizeof(*java_method) * MAX_METHOD);
    javaClass.nbOfAttributes = 0;
    javaClass.nbOfMethod = 0;
    javaClass.javaAttribute = java_attribute;
    javaClass.javaMethod = java_method;
    javaClass.mother_class = NULL;
    printf("What the Class Name :\n");
    char* name = inputString();
    javaClass.className = name;
    javaClasses[*nbOfClass] = javaClass;
    childClass->mother_class = &javaClasses[*nbOfClass];
    (*nbOfClass)++;
    editClass(javaClasses,&javaClasses[*nbOfClass-1],nbOfClass);
}

void editClass(JavaClass *javaClasses,JavaClass *javaClass,int *nbOfClass)
{
    printf(CLASS_OPTION);
    int option = inputInteger(1, 6);
    while (option !=6)
    {
        switch (option)
        {
        case 1:
            addAttributes(javaClass);
            break;
        case 2:
            addMethod(javaClass);
            break;
        case 3:
            showAttributesAndMother(javaClass);
            break;
        case 4:
            showMethod(javaClass);
            break;
        case 5:
            if (*nbOfClass < 1)
            {
                printf("There only one class (this one) !\nDo you wish to create the parent class ?\n(Y/n): ");
                char *opt = inputString();
                opt[0] = tolower(opt[0]);
                if (strcmp(opt,"y") == 0)
                {
                    free(opt);
                    addParentClass(javaClasses,nbOfClass,javaClass);
                } else
                {
                    free(opt);
                }
            } else
            {
                printf("\nDo you wish to create the parent class ?\n(Y/n): ");
                char *opt = inputString();
                opt[0] = tolower(opt[0]);
                if (strcmp(opt,"y") == 0)
                {
                    free(opt);
                    addParentClass(javaClasses,nbOfClass,javaClass);
                } else
                {
                    free(opt);
                    changeMotherClass(javaClasses,javaClass,nbOfClass);
                }

            }
            break;
        default:
            break;
        }
        system("clear");
        printf(CLASS_OPTION);
        option = inputInteger(1, 6);
    }
}