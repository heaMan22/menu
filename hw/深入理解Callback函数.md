# SE作业三： 深入理解Callback函数
先说结论： Callback函数 = 算法解耦

以排序函数来说明。

## 一、混沌世界
最初，我们的需求只是对数组A进行排序。
``` c
#define LEN 10
static int A[LEN];

int sort(){  
  int *ar = A; // 硬编码了数组A
  int len = LEN;

  // do something to sort A...
}
```


## 二、数据结构解耦
如果需求修改为能对不同数组进行排序。如何重用之前的代码？  
只需把数据结构抽离出来，具体就是利用参数来实现。
```c
int sort(int *pA, int lenA){
  int *ar = pA; // ar不再依赖于特定的对象
  int len = lenA;

  for(int i = 0; i < len; i++){
    int index = i;
    for(int j = i + 1; j < len; j++){
      if(a[j] < a[index]){
        index = j;
      }
    }
    if(index != i){
      int tmp = a[i];
      a[i] = a[index];
      a[index] = tmp;
    }
  }
}
```

## 三、算法解耦
如果需求修改为对数组降序排序。如何重用之前的代码？  
具体的实现也是添加额外的参数，只不过这回传递的是函数指针，即回调函数。  
```c
typedef bool (*callback)(int x, int y);  

int sort(int *pA, int lenA, callback less){
  int *ar = pA;
  int len = lenA;

  for(int i = 0; i < len; i++){
    int index = i;
    for(int j = i + 1; j < len; j++){

      // 将具体的判断算法解耦
      if(less(a[j], a[index]) == true){
      /* if(a[j] < a[index]){ */
        index = j;
      }
    }
    if(index != i){
      int tmp = a[i];
      a[i] = a[index];
      a[index] = tmp;
    }
  }
}
```  

## 四、menu实践        
我们需要为链表设计一个查找节点的接口，由于容器与数据是分离的，因此具体的比较策略由外部传入。这里用到的思想其实就是第三部分的算法解耦。
```cc        
typedef struct tLinkTableNode{    
  struct tLinkTableNode *next;
}tLinkTableNode;      

typedef tLinkTableNode *tLinkTable;

// 版本一
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable,
  int Condition(tLinkTableNode * pNode));
```  
但版本一存在的问题是，我们设计的compare strategy限制了回调函数的灵活性，被比较的cmd被硬编码了（cmd从全局变量获取，或者为每个cmd写一个回调函数）。这其实就和第一部分的混沌世界一样，只不过这次抽象的对象是回调函数。    
  
所以，我们可以仿照第二部分的数据结构解耦，将被硬编码的cmd参数化来解决这个问题。
```cc    
// 版本二
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable,
  int Condition(tLinkTableNode * pNode, void *args), void *args);
```      

也可以使用面相对象的思想，增加一个接口。  
```cc      
// c++  
// 新增接口
class interface{  
 public:      
  virtual bool operator()(tLinkTableNode*) const = 0;
};    
// 具体实现
class NodeEqual: public interface{  
 public:      
  NodeEqual(std::string cmd_name);
  bool operator()(tLinkTableNode*) const;  
  std::string _cmd_name;
};    

tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable,
  const interface &pEqual){    
  tLinkTable *cur = *pLinkTable;  
  while(cur){
    if(pEqual(cur) == true){  
      //find it
    }    
    cur = cur->next;
  }
  // ...
}    

int main(){  
  tLinkTable *pLinkTable = Init();  

  NodeEqual obj("help");    
  auto pNode = SearchLinkTableNode(pLinkTable);  
  // ...
}
```

## 五、实验总结
程序的本质是数据结构和算法。从本质上看，接口设计的抽象分层就是把特定的数据结构和算法分离出来，这种抽象使得接口具有通用性和低耦合。
