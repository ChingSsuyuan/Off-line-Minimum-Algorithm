#include <stdio.h>
#include <stdlib.h>
struct node
{
    struct node* prev;
    int data;
    struct node* next;
};
struct node* addtoempty(struct node* L, int data)
{
    struct node *temp=malloc(sizeof(struct node));
    temp->prev=NULL;
    temp->data=data;
    temp->next=NULL;
    L=temp;
    return L;
};
struct node* insertatbegin(struct node* L,int data)
{
    struct node *temp=malloc(sizeof(struct node));
    temp->prev=NULL;
    temp->data=data;
    temp->next=NULL;
    temp->next=L;
    L->prev=temp;
    L=temp;
    return L;
};

struct node* insertatend(struct node* L,int data)
{   struct node *tp;
    struct node *temp=malloc(sizeof(struct node));
    temp->prev=NULL;
    temp->data=data;
    temp->next=NULL;
    tp=L;
    while (tp->next!=NULL)
    {
        tp=tp->next;
    }   
    tp->next=temp;
    temp->prev=tp;
    return L;
};
struct node* deletion(struct node* L,int x)
{
    struct node *tp=L;
    while (tp->data!=x && tp->next!=NULL)
    {
        tp=tp->next;
    }
    if (tp==NULL)
    {   
        printf("no elenmenys%d",x);
        return L;
    }
    if(tp->prev==NULL){
        L=tp->next;
        
        if(L!=NULL){L->prev=NULL;}
    }
    else{
        tp->prev->next = tp->next;
        if (tp->next != NULL) {
            tp->next->prev = tp->prev;
        }
    }
    free(tp);
    return L;
};

int main(){
    struct node* L=NULL;
    struct node* ptr;
    L=addtoempty(L,45);
    L=insertatbegin(L,80);
    L=insertatbegin(L,70);
    L=insertatend(L,99);
    L=deletion(L,99);
    ptr=L;
    while (ptr!=NULL)
    {
        printf("%d\n",ptr->data);
        ptr=ptr->next;
    }
    
    return 0;
}