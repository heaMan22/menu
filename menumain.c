/*
 * 菜单可以根据用户的需要来提供一些帮助
 *  因此要匹配用户的输入
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "linklist.h"

/*
 * 将数据结构与操作分离
 */
typedef struct{
  tLinkTableNode *next;

  char *name;
  char *recall;
}cmd_info;

tLinkTableNode *head;
tLinkTableNode* Init();
/*cmd_info cmds[] = {*/
  /*{"help", "this is help command."},*/
  /*{"q", "quit"}*/
/*};*/

int main(){
  /*printf("hello, world\n");*/
  char input[1024];
  /*int i;*/
  head = Init();
  while(1){
    scanf("%s", input);
    cmd_info *pcmd = (cmd_info*)head;
    bool bmatch = false;

    while(pcmd){
      if(strcmp(pcmd->name, input) == 0){
        printf("%s\n", pcmd->recall);
        bmatch = true;
        break;
      }
      pcmd = (cmd_info*)GetLinkTableNode((tLinkTableNode*)pcmd);
    }
    if(bmatch == false)
      printf("unknown command. help for more info.\n");
  }
}

tLinkTableNode* Init(){
  cmd_info *pcmd;
  pcmd = (cmd_info*)malloc(sizeof(cmd_info));
  pcmd->name = "help";
  pcmd->recall = "this is help command";
  pcmd->next = NULL;
  return pcmd;
}
