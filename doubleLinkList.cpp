#include <bits/stdc++.h> 
using namespace std; 
  
// A linked list node  
class Node  
{  
    public: 
    int val;  
    Node* next;  
    Node* prev;  
};

void push_left(struct Node** head_ref, int new_data){
      struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
      new_node->val = new_data;
      
      new_node->prev = NULL;
      new_node->next = (*head_ref);
      
      if((*head_ref) != NULL)
          (*head_ref)->prev = new_node;
      
      (*head_ref) = new_node;
}

//O(N) push
void push_right(struct Node** head_ref, int new_data){
      struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
      struct Node* tail = *head_ref;
      
      new_node->val = new_data;
      new_node->next = NULL;
      
      if(*head_ref == NULL){
          new_node->prev = NULL;
          *head_ref = new_node;
          return;
      }
      
      while(tail->next != NULL)
          tail = tail->next;
      
      new_node->prev = tail;
      tail->next = new_node;
      return;
}

void insert(struct Node** head_ref, int data_after,int new_data){
     if(*head_ref == NULL){
      cout<<"Cannot insert"<<endl;    
      return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* search = *head_ref;
    new_node->val = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;
    while(search != NULL){
        if(search->val == data_after){
            new_node->next = search->next;
            search->next = new_node;
            new_node->prev = search;
            new_node->next->prev = new_node;
            return;
        }
        search = search->next;
    }
    cout<<"Data to insert cannot be insert after "<<data_after<<endl;
    return;
}
void printList(Node* node)  {  
    if(node == NULL){
        cout<<"Cannot print list because list is empty!"<<endl;
        return;
    }
    Node* last;  
    cout<<"\nTraversal in forward direction \n";  
    while (node != NULL)  
    {  
        cout<<" "<<node->val<<" ";  
        last = node;  
        node = node->next;  
    }  
  
    cout<<"\nTraversal in reverse direction \n";  
    while (last != NULL)  
    {  
        cout<<" "<<last->val<<" ";  
        last = last->prev;  
    }  
    cout<<endl;
}  

/* Driver program to test above functions*/
int main()  
{  
    /* Start with the empty list */
    Node* head = NULL;  
  
    // Insert 6. So linked list becomes 6->NULL  
    push_right(&head, 6);  
  
    // Insert 7 at the beginning. So  
    // linked list becomes 7->6->NULL  
    push_left(&head, 7);  
  
    // Insert 1 at the beginning. So  
    // linked list becomes 1->7->6->NULL  
    push_left(&head, 1);  
  
    // Insert 4 at the end. So linked  
    // list becomes 1->7->6->4->NULL  
    push_right(&head, 4);  
  
    // Insert 8, after 7. So linked  
    // list becomes 1->7->8->6->4->NULL  
    insert(&head,7, 8);  
  
    cout << "Created List is: ";  
    printList(head);  
  
    return 0;  
}  