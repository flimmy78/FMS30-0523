#include "mtxproductid.h"

#define BRANCH_NUMBER "THE_BRANCH_NUMBER_CAN_BE_128_CHARACTERS_SO_THIS_IS_TO_TEST_THAT_EVERYTHING_WORKS_WITH_THA_LENGTH_I_need_another_28_letters000000"
#define COMMIT_NUMBER "12characters"

//VERSION_RES_PRODUCT_NAME will be defined to the correct SHA1 number
#define IDSTRING VERSION_RES_PRODUCT_NAME\
                  BRANCH_NUMBER\
                  COMMIT_NUMBER

const char g_achVersionInfo[40 + 128 + 12 + 1] __attribute__((used)) __attribute__((section (".matroxvideo"))) = IDSTRING;

//we may want to include these eventually.
/*int    g_iFileVersionMajorVersion __attribute__ ((section (".matroxvideo"))) = 1;
int    g_iFileVersionMinorVersion __attribute__ ((section (".matroxvideo"))) = 0;
int    g_iFileVersionMajorBuild   __attribute__ ((section (".matroxvideo"))) = 0;
int    g_iFileVersionBuild        __attribute__ ((section (".matroxvideo"))) = 0;

int    g_iProdVersionMajorVersion __attribute__ ((section (".matroxvideo"))) = 1;
int    g_iProdVersionMinorVersion __attribute__ ((section (".matroxvideo"))) = 0;
int    g_iProdVersionMajorBuild   __attribute__ ((section (".matroxvideo"))) = 0;
int    g_iProdVersionBuild        __attribute__ ((section (".matroxvideo"))) = 0;*/

