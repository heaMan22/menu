#include <stdio.h>
#include <string.h>
#include "linklist.h"

typedef struct cmdNode{
  linkNode next;
  char *name;
}cmdNode;

static cmdNode *cmds;

int main(){
  char cmd[1024];
  scanf("%s", cmd);

  cmdNode *cur = cmds;
  while(head){
    if(strcmp(cmd, cur->name)){
      // todo
      break;
    }
    cur = linkNode_next(cur);
  }
}
