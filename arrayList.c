#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "arrayList.h"







nodeDef *strpNodeNew(int nNum)
{
    nodeDef *strpNodeBuf;

    strpNodeBuf = (nodeDef *)calloc(1, sizeof(nodeDef));
    if (!strpNodeBuf) {
        return NULL;
    }
    strpNodeBuf->nCount = nNum;

    return strpNodeBuf;
}

void vNodeDel(void *vspNode)
{
    if (!vspNode) {
        return ;
    }

    free(vspNode);
}



/*--------------------------------------------------------------------------
 FUNCTION NAME: strpArrayListNew
 DESCRIPTION:   
 PARAMETER:     
 RETURN:        
 NOTE:          初始化通用链表结构
 *------------------------------------------------------------------------ */
arrayListDef *strpArrayListNew(void)
{
    arrayListDef  *strpArrayList;
    
    strpArrayList = (arrayListDef *)calloc(1, sizeof(arrayListDef));
    if (!strpArrayList) {
        return NULL;
    }
    strpArrayList->nSize = N_ARRAY_LIST_DEFAULT_SIZE;
    strpArrayList->nLen = 0;
    
    /*maybe null this*/
    strpArrayList->vDel = vNodeDel;
    strpArrayList->vpList = (void **)calloc(strpArrayList->nSize, sizeof(void *));
    if (!strpArrayList->vpList) {
        free(strpArrayList);
        return NULL;
    }

    return strpArrayList;
}

/*--------------------------------------------------------------------------
 FUNCTION NAME: vArrayListDelErr
 DESCRIPTION:   
 PARAMETER:     
 RETURN:        
 NOTE:          通用链表析构函数
 *------------------------------------------------------------------------ */
void  vArrayListDel(arrayListDef *vspArrayList)
{
    register short i;
    
    if (!vspArrayList) 
        return;

    if (vspArrayList->vDel){
        for(i = 0; i < vspArrayList->nLen; i++) {
            if (vspArrayList->vpList[i])
                vspArrayList->vDel(vspArrayList->vpList[i]);
        }
    }

    if (vspArrayList->vpList) {
        free(vspArrayList->vpList);
    }

    free(vspArrayList);
    return;
}

/*--------------------------------------------------------------------------
 FUNCTION NAME: nArrayListReset
 DESCRIPTION:   
 PARAMETER:     
 RETURN:        
 NOTE:          通用链扩容函数, 每次扩容一倍
 *------------------------------------------------------------------------ */
short  nArrayListReset(arrayListDef *vspArrayList, short nSize)
{
    void  **vspNewArray;
    short  nNewSize, nDiffSize;
    
    nNewSize = N_MAX((vspArrayList->nSize * 2), nSize);
    vspNewArray = (void **)realloc(vspArrayList->vpList, nNewSize * sizeof(void *));
    if (!vspNewArray){
        free(vspArrayList->vpList);
        return FAILURE;
    }
    
    vspArrayList->vpList = vspNewArray;
    nDiffSize = nNewSize - vspArrayList->nSize;
    if (nDiffSize) 
        memset(vspArrayList->vpList + vspArrayList->nSize, 0, nDiffSize * sizeof(void *));
    vspArrayList->nSize = nNewSize;
    
    return SUCCESS;
}

/*--------------------------------------------------------------------------
 FUNCTION NAME: nArrayListSet
 DESCRIPTION:   
 PARAMETER:     
 RETURN:        
 NOTE:          根据要插入的id来插入指定位置
 *------------------------------------------------------------------------ */
short  nArrayListSet(arrayListDef *vspArrayList, short nIdx, void *vspNewAdd)
{
    if (nIdx > vspArrayList->nSize - 1){
        if (nArrayListReset(vspArrayList, nIdx)){
            return FAILURE;
        }
    }

    if (vspArrayList->vpList[nIdx] && vspArrayList->vDel)
        vspArrayList->vDel(vspArrayList->vpList[nIdx]);
    vspArrayList->vpList[nIdx] = vspNewAdd;

    if (vspArrayList->nLen <= nIdx)
        vspArrayList->nLen = nIdx + 1;
    
    return SUCCESS;
}

/*--------------------------------------------------------------------------
 FUNCTION NAME: nArrayListAdd
 DESCRIPTION:   
 PARAMETER:     
 RETURN:        
 NOTE:          通用链表加入节点
 *------------------------------------------------------------------------ */
short  nArrayListAdd(arrayListDef *vspArrayList, void *vspNewAdd)
{
    return nArrayListSet(vspArrayList, vspArrayList->nLen, vspNewAdd);
}



int main(int argc, void **argv)
{
    register int i;
    nodeDef    *strpTryNode;
    arrayListDef  *strpNewList;

    strpNewList = strpArrayListNew();
    if (!strpNewList) {
        return -1;
    }

    for (i = 0; i < 100; i++) {
        strpTryNode = strpNodeNew(i);
        if (!strpTryNode) {
            vArrayListDel(strpNewList);
            return -1;
        }

        if (SUCCESS != nArrayListAdd(strpNewList, strpTryNode)) {
            vNodeDel(strpTryNode);
            vArrayListDel(strpNewList);
            return -1;
        }
    }


    for (i = 0; i < strpNewList->nLen; i++) {
        strpTryNode = strpNewList->vpList[i];
        if (!strpTryNode) {
            continue;
        }
        printf("idx[%d] node[%d]\n", i, strpTryNode->nCount);
    }

    vArrayListDel(strpNewList);

    return 0;
}










