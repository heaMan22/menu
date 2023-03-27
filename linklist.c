#include "linklist.h"

tLinkTableNode* GetLinkTableNode(tLinkTableNode *pNode){
  if(pNode)
    return pNode->next;
  return 0;
}
