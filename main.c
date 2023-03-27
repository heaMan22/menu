#include <stdio.h>
#include <string.h>

int main(){
  scanf("%s", cmd);
  if(strcmp(cmd, "help") == 0){
    printf("this is help cmd\n");
  }
  else if(strcmp(cmd, "q") == 0){
    return 0;
  }
  else{
    printf("wrong command\n");
  }
}
