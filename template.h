#ifndef TEMPLATE_H
#define TEMPLATE_H

#define IMPORT \
    "import java.io.*;\nimport java.util.*;\n"
#define CLASS \
    "public class %s {\n"
#define TYPE_OPTION \
    "1) int\n2) double\n3) float\n4) long\n5) boolean\n6) Custom\n"
#define FIRST_OPTION \
    "1) Add Attributes\n2) Add Method\n3) Create class\n"
#define MAX_ATTRIBUTES \
    512
#define ATTRIBUTES_TEMPLATE \
    "\tprivate %s %s;\n"

#endif