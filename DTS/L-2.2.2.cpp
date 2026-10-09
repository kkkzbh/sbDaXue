

#include <stdio.h>
#include <stdlib.h>

struct stud_node {
    int    num;
    char   name[20];
    int    score;
    struct stud_node *next;
};

struct stud_node *createlist();
struct stud_node *deletelist( struct stud_node *head, int min_score );

int main()
{
    int min_score;
    struct stud_node *p, *head = NULL;

    head = createlist();
    scanf("%d", &min_score);
    head = deletelist(head, min_score);
    for ( p = head; p != NULL; p = p->next )
        printf("%d %s %d\n", p->num, p->name, p->score);

    return 0;
}

/* 你的代码将被嵌在这里 */

typedef struct stud_node node;

struct stud_node *createlist()
{
    node* head = (node*)malloc(sizeof(node));
    node* it = head;
    it->next = NULL;
    int id;
    while(1)
    {
        node* tmp = (node*)malloc(sizeof(node));
        tmp->next = NULL;
        scanf("%d",&id);
        if(!id) break;
        tmp->num = id;
        scanf("%s %d",tmp->name,&tmp->score);
        it->next = tmp;
        it = it->next;
    }
    node* tmp = head;
    head = head->next;
    free(tmp);
    return head;
}
struct stud_node *deletelist( struct stud_node *head, int min_score )
{
    node* it = (node*)malloc(sizeof(node));
    node* temp = it;
    it->next = head;
    while(it->next)
    {
        if(it->next->score < min_score)
        {
            node* tmp = it->next;
            it->next = it->next->next;
            free(tmp);
        }
        else it = it->next;
    }
    head = temp->next;
    free(temp);
    return head;
}

