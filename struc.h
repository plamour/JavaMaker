#ifndef STRUCT_H
#define STRUCT_H


typedef struct JavaAttribute
{
    char *typeAttribute;
    char *nameAttribute;
} JavaAttribute;

typedef struct JavaClass JavaClass;
struct JavaClass
{
    char *className;
    int nbOfAttributes;
    JavaAttribute *javaAttribute;
    JavaClass *mother_class;
};

#endif
