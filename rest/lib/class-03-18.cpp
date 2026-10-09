



#include<cstdlib>
#define NULL 0
struct node
{
    int element;
    node* next;
};
node* creatList()
{
    return NULL;
}
node* push_front(node* head,int x)
{
    if(!head) head = (node*)malloc(sizeof(node)),head->element = x,head->next = NULL;
    else
    {
        node* tmp = (node*)malloc(sizeof(node));
        tmp->element = x;
        tmp->next = head;
        head = tmp;
    }
    return head;
}
node* push_back(node* head,int x)
{
    node* it = head;
    if(!head)
    {
        head = (node*)malloc(sizeof(node));
        head->next = NULL;
        head->element = x;
        return head;
    }
    while(it->next) it = it->next;
    it->next = (node*)malloc(sizeof(node));
    it->next->next = NULL;
    it->next->element = x;
    return head;
}

int main()
{


    return 0;
}