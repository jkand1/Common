#ifndef _HDR_ARRAY_LIST_SHADY_H
#define _HDR_ARRAY_LIST_SHADY_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#define N_ARRAY_LIST_DEFAULT_SIZE   24

#define N_MAX(a, b) ((a) > (b) ? (a) : (b))


typedef void (*vpfnDel) (void *kv);


typedef struct {
    void        **vpList;
    short       nLen;
    short       nSize;

    vpfnDel     vDel;
}arrayListDef;


typedef struct {
    int nCount;
}nodeDef;













#endif
