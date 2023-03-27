linkNode* linkNode_insert(linkNode *head, linkNode *node){
  node->next = head;
  head = node;

  return head;
}
linkNode* linkNode_next(linkNode *cur){
  return cur ? cur->next : NULL;
}
