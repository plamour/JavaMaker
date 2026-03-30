#ifndef STRUCT_H
#define STRUCT_H


typedef struct JavaAttribute
{
    char *typeAttribute;
    char *nameAttribute;

} JavaAttribute;


typedef struct JavaMethod
{
    char *typeMethod;
    char *nameMethod;
    int nbOfParameter;
    char **typeParameter;
    char **nameParameter;
    char *insideCode;

} JavaMethod;


typedef struct JavaClass JavaClass;

struct JavaClass
{
    char *className;
    int nbOfAttributes;
    int nbOfMethod;
    JavaMethod *javaMethod;
    JavaAttribute *javaAttribute;
    JavaClass *mother_class;
};





#endif
