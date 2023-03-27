typedef struct linkNode{
  struct linkNode *next;
}linkNode;

linkNode* linkNode_insert(linkNode *head, linkNode *node);
linkNode* linkNode_next(linkNode *cur);
