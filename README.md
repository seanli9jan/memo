# memo
***

## MCU read text file without file system

**0 - feature.mk**
* BOOL_LIB : use bool with stdbool library or not
* BUILD_PY : build main.c or func.c (main.py call)

**1 - tool/create_data.py**
* convert array (tool/data.txt) to 4 byte header file (lib/data.h)

**2 - main.c**
* print data.h array by using pointer to structure

**3 - main.py**
* print data.h array by using c pointer and python classes
