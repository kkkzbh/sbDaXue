

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n;

using set_node = int;

struct set
{
    bool* a;
    int sz;
};

set* create_set(int n)
{
    set* st = (set*)malloc(sizeof(set));
    st->a = (bool*)calloc(sizeof(bool),3 * n - 1);
    st->sz = 0;
    return st;
}

void insert(set* st,set_node nd)
{
    if(st->a[nd + n - 1]) {
        return;
    }
    st->a[nd + n - 1] = true;
    ++st->sz;
}

void erase(set const* st,set_node nd)
{ st->a[nd + n - 1] = false; }

bool contains(set const* st,set_node nd)
{ return st->a[nd + n - 1]; }

struct state
{
    int i;
    int* path;
    set* st;
    set* st2;
    set* st3;
};

using queue_node = state;

#define DEFAULT_SIZE 300000  // 默认队列大小 面向测试点(不过写链表可以避免该问题，或者用更方便的栈式 栈式与队列式基本等价)

struct queue
{
    queue_node* a;
    int it;
    int sz;
    int tot;
};

queue* create_queue()
{
    queue* que = (queue*)malloc(sizeof(queue));
    que->a = (queue_node*)malloc(DEFAULT_SIZE * sizeof(queue_node));
    que->it = 0;
    que->sz = 0;
    que->tot = DEFAULT_SIZE;
    return que;
}


void push(queue* que,queue_node nd)
{
    que->a[que->sz++] = nd;
    if(que->sz == que->tot) {
        que->sz = 0;
    }
    // que->a[que->sz].i = nd.i;
    // que->a[que->sz].path = (int*)malloc(n * sizeof(int));
    // memcpy(que->a[que->sz].path,nd.path,n * sizeof(int));
    // que->a[que->sz].st = create_set(n);
    // que->a[que->sz].st->sz = nd.st->sz;
    // memcpy(que->a[que->sz].st->a,nd.st->a,n * sizeof(bool));
}

void pop(queue* que)
{
    // free(que->a[que->sz].path);
    // free(que->a[que->sz].st->a);
    // free(que->a[que->sz].st);
    ++que->it;
    if(que->it == que->tot) {
        que->it = 0;
    }
}

queue_node top(queue const* que)
{ return que->a[que->it]; }

bool empty(queue const* que)
{ return que->it == que->sz; }


int main()
{
    scanf("%d",&n);

    queue* que = create_queue();
    state sa;
    sa.i = 0;
    sa.path = (int*)malloc(n * sizeof(int));
    sa.st = create_set(n);
    sa.st2 = create_set(n);
    sa.st3 = create_set(n);
    push(que,sa);
    while(!empty(que)) {
        queue_node nd = top(que);
        pop(que);
        if(nd.i == n) {
            for(int i = 0; i != n; ++i) {
                printf("%d ",nd.path[i] + 1);
            }
            goto fre;
        }
        for(int j = 0; j != n; ++j) {
            if(contains(nd.st,j) or contains(nd.st2,nd.i - j) or contains(nd.st3,nd.i + j)) {
                continue;
            }
            int* path = (int*)malloc(n * sizeof(int));
            memcpy(path,nd.path,n * sizeof(int));
            path[nd.i] = j;
            set* st = create_set(n);
            set* st2 = create_set(n);
            set* st3 = create_set(n);
            st->sz = nd.st->sz;
            st2->sz = nd.st2->sz;
            st3->sz = nd.st3->sz;
            memcpy(st->a,nd.st->a,(3 * n - 1) * sizeof(bool));
            memcpy(st2->a,nd.st2->a,(3 * n - 1) * sizeof(bool));
            memcpy(st3->a,nd.st3->a,(3 * n - 1) * sizeof(bool));
            insert(st,j),insert(st2,nd.i - j),insert(st3,nd.i + j);
            push(que,{ nd.i + 1,path,st,st2,st3 });
        }

        fre:
        free(nd.path),
        free(nd.st->a),free(nd.st);
        free(nd.st2->a),free(nd.st2);
        free(nd.st3->a),free(nd.st3);
        if(nd.i == n) {
            break;
        }
    }

    while(!empty(que)) {
        queue_node nd = top(que);
        pop(que);
        free(nd.path),
        free(nd.st->a),free(nd.st);
        free(nd.st2->a),free(nd.st2);
        free(nd.st3->a),free(nd.st3);
    }

    return 0;
}