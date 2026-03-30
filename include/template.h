#ifndef TEMPLATE_H
#define TEMPLATE_H

#define IMPORT \
    "import java.io.*;\nimport java.util.*;\n"
#define CLASS \
    "public class %s {\n"
#define CLASS_EXTEND \
    "public class %s extends %s {\n"
#define TYPE_OPTION \
    "1) int\n2) double\n3) float\n4) long\n5) boolean\n6) Custom\n"
#define FIRST_OPTION \
    "1) List Class\n2) Rework one class\n3) Add Class\n4) Generate class\n"
#define CLASS_OPTION \
    "1) Add Attribute\n2) Add Method\n3) Show Attributes And Mother\n4) Show Methods\n5) Choose Mother Class\n6) Exit\n"
#define MAX_ATTRIBUTES \
    512
#define MAX_METHOD \
    512
#define MAX_PARAMETER_METHOD \
    32
#define MAX_CLASS \
    128
#define ATTRIBUTES_TEMPLATE \
    "\tprivate %s %s;\n"
#define DEFAULT_CONSTRUCTOR_TEMPLATE \
    "\tpublic %s() {\n\t}\n\n"
#define DEFAULT_GETTER \
    "\tpublic %s get%s() {\n\t\treturn this.%s;\n\t}\n"
#define DEFAULT_SETTER \
    "\tpublic void set%s(%s %s) {\n\t\tthis.%s = %s;\n\t}\n"
#define EQUALS \
    "\tpublic boolean equals(Object o) {\n\t\tif (o == null) return false;\n\t\tif(!(o instanceof %s %c)) return false;\n\t\treturn "
#define TO_STRING \
    "\tpublic String toString() {\n\t\treturn "
#define CLASS_TITLE \
    "\t(Class : %s)\n"


#endif