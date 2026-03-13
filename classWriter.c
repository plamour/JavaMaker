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
    for (int i = 0; i < java_class->nbOfAttributes; ++i)
    {
        free(java_class->javaAttribute[i].nameAttribute);
        free(java_class->javaAttribute[i].typeAttribute);
    }
    for (int i = 0; i < java_class->nbOfMethod; ++i)
    {
        free(java_class->javaMethod[i].nameMethod);
        free(java_class->javaMethod[i].typeMethod);
        for (int j = 0; j < java_class->javaMethod[i].nbOfParameter; ++j)
        {
            free(java_class->javaMethod[i].nameParameter[j]);
            free(java_class->javaMethod[i].typeParameter[j]);
        }
        free(java_class->javaMethod[i].nameParameter);
        free(java_class->javaMethod[i].typeParameter);
    }

    free(java_class->className);
    free(java_class->javaAttribute);
    free(java_class->javaMethod);
    free(java_class);
}

void writeEqual(JavaClass *java_class, FILE *file)
{
    char equals[2048];
    char firstLetter = tolower(java_class->className[0]);
    char firstLetterStr[2] = { firstLetter, '\0' };
    snprintf(equals,sizeof(char)*2048,EQUALS,java_class->className,firstLetter);

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
    if (java_class->mother_class)
    {
        strcat(equals," && super.equals(o)");
    }
    strcat(equals,";\n\t}");
    fprintf(file,equals);
}

void writeToString(JavaClass *java_class, FILE *file)
{
    char toString[1024];
    snprintf(toString,sizeof(char)*1024,TO_STRING);
    if (java_class->mother_class)
    {
        strcat(toString,"super.toString() + \" \" + ");
    }
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
        char *upperCase = strdup(java_attribute.nameAttribute);
        upperCase[0] = toupper(upperCase[0]);
        fprintf(file,DEFAULT_GETTER,java_attribute.typeAttribute,upperCase,java_attribute.nameAttribute);
        fprintf(file,DEFAULT_SETTER,upperCase,java_attribute.typeAttribute,java_attribute.nameAttribute,java_attribute.nameAttribute,java_attribute.nameAttribute);
        free(upperCase);
    }


}

void writeConstructor(JavaClass *java_class, FILE *file)
{
    //First the Default Constructor
    fprintf(file,DEFAULT_CONSTRUCTOR_TEMPLATE,java_class->className);
    //Second Constructor with parameter
    char constructor[1024];
    snprintf(constructor,sizeof(char)*1024,"\tpublic %s(",java_class->className);

    if (java_class->mother_class)
    {
        for (int i = 0; i < java_class->mother_class->nbOfAttributes; ++i)
        {
            JavaAttribute java_attribute = java_class->mother_class->javaAttribute[i];
            if (i == java_class->mother_class->nbOfAttributes-1)
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
        if (java_class->nbOfAttributes > 0)
        {
            strcat(constructor,",");
        }
    }


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
    strcat(constructor,") {\n\t\t");

    if (java_class->mother_class)
    {
        strcat(constructor,"super(");
        for (int i = 0; i < java_class->mother_class->nbOfAttributes; ++i)
        {
            strcat(constructor,java_class->mother_class->javaAttribute[i].nameAttribute);
            if (i != java_class->mother_class->nbOfAttributes-1)
            {
                strcat(constructor,",");
            }
        }
        strcat(constructor,");");

    }
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
}
void writeMethod(JavaClass *java_class ,FILE *file)
{
    for (int i = 0; i < java_class->nbOfMethod; ++i)
    {
        JavaMethod java_method = java_class->javaMethod[i];
        char method[1024];
        snprintf(method,sizeof(char)*1024,"\n\tpublic %s %s(",java_method.typeMethod,java_method.nameMethod);
        for (int j = 0; j < java_method.nbOfParameter; ++j)
        {
            if (j != java_method.nbOfParameter-1)
            {
                strcat(method,java_method.typeParameter[j]);
                strcat(method," ");
                strcat(method,java_method.nameParameter[j]);
                strcat(method,",");
            } else
            {
                strcat(method,java_method.typeParameter[j]);
                strcat(method," ");
                strcat(method,java_method.nameParameter[j]);
                strcat(method,"){\n\t\t");
            }
        }
        fprintf(file,method);
        if (java_method.insideCode)
        {
            fprintf(file,java_method.insideCode);
        }
        fprintf(file,"\n\t}\n");
    }
}
void writeJavaClass(JavaClass *java_class)
{
    FILE *file;
    char *filename = malloc(sizeof(char)*64);
    snprintf(filename,sizeof(char)*64,"%s.java",java_class->className);
    file = fopen(filename,"w");
    fprintf(file,IMPORT);
    if (java_class->mother_class)
    {
        fprintf(file,CLASS_EXTEND,java_class->className,java_class->mother_class->className);

    } else
    {
        fprintf(file,CLASS,java_class->className);

    }
    writeAttributes(java_class,file);
    writeConstructor(java_class,file);
    writeGetterAndSetter(java_class,file);
    writeEqual(java_class,file);
    writeMethod(java_class,file);
    fprintf(file,"\n}");
    free(filename);
    fclose(file);
    freeEverything(java_class);
}