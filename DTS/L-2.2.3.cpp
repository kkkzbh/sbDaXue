

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *createlist(); /*裁判实现，细节不表*/
struct ListNode *mergelists(struct ListNode *list1, struct ListNode *list2);
void printlist( struct ListNode *head )
{
    struct ListNode *p = head;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    struct ListNode  *list1, *list2;

    list1 = createlist();
    list2 = createlist();
    list1 = mergelists(list1, list2);
    printlist(list1);

    return 0;
}

/* 你的代码将被嵌在这里 */

typedef struct ListNode node;

struct ListNode *mergelists(struct ListNode *list1, struct ListNode *list2)
{
    node* ita = list1;
    node* itb = list2;
    node* head = (node*)malloc(sizeof(node));
    node* it = head;
    it->next = NULL;
    while(ita && itb)
    {
        if(ita->data < itb->data)
        {
            it->next = ita;
            ita = ita->next;
            it = it->next;
        }
        else
        {
            it->next = itb;
            itb = itb->next;
            it = it->next;
        }
    }
    while(ita)
    {
        it->next = ita;
        ita = ita->next;
        it = it->next;
    }
    while(itb)
    {
        it->next = itb;
        itb = itb->next;
        it = it->next;
    }
    it = head;
    head = head->next;
    free(it);
    return head;
}