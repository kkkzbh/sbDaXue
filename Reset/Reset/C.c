#define _CRT_SECURE_NO_WARNINGS


//#include<stdio.h>
//
//
//
//int main()
//{
//	long long x, y;
//	scanf("%lld", &x);
//	scanf("%lld", &y);
//	printf("   s1=%lld\n", x);
//	printf("   s2=%lld\n", y);
//	printf("s1+s2=%lld", x + y);
//
//
//	return 0;
//}

//
//#include <stdio.h>
//#define HUNTHOU 10000
//typedef struct node
//{
//    int data;
//    struct node* next;
//}NODE;
//NODE* insert_after(u, num)
//NODE* u;
//int  num;
//
//{ 
//NODE* v;
//v = (NODE*)malloc(sizeof(NODE));
//v->data = num;
//u->next = v;
//return(v);
//}
//
//NODE* addint(p, q)
//NODE* p, * q;
//{  NODE* pp, * qq, * r, * s, * t;
//int total, number, carry;
//pp = p->next;  qq = q->next;
//s = (NODE*)malloc(sizeof(NODE));
//s->data = -1;
//t = s; carry = 0;
//while (pp->data != -1 && qq->data != -1)
//{
//    total = pp->data + qq->data + carry;
//    number = total % HUNTHOU;
//    carry = total / HUNTHOU;
//    t = insert_after(t, number);
//    pp = pp->next;
//    qq = qq->next;
//}
//r = (pp->data != -1) ? pp : qq; //这个选择判断很好！
//while (r->data != -1)
//{
//    total = r->data + carry;
//    number = total % HUNTHOU;
//    carry = total / HUNTHOU;
//    t = insert_after(t, number);
//    r = r->next;
//}
//if (carry) t = insert_after(t, 1);
//t->next = s;
//return(s);
//}
//NODE* inputint(void)
//{
//    NODE* s, * ps, * qs;
//    struct number {
//        int num;
//        struct number* np;
//    }  *p, * q;
//    int i, j, k;
//    long sum;
//    char c;
//    p = NULL;
//    while ((c = getchar()) != '\n')
//        if (c >= '0' && c <= '9')
//        {
//            q = (struct number*)malloc(sizeof(struct number));
//            q->num = c - '0';
//            q->np = p;
//            p = q;
//        }
//    s = (NODE*)malloc(sizeof(NODE));
//    s->data = -1;
//    ps = s;
//    while (p != NULL)
//    {
//        sum = 0;
//        i = 0;
//        k = 1;
//        while (i < 4 && p != NULL)
//        {
//            sum = sum + k * (p->num);
//            i++; p = p->np; k = k * 10;
//        }
//        qs = (NODE*)malloc(sizeof(NODE));
//        qs->data = sum;
//        ps->next = qs;
//        ps = qs;
//    }
//    ps->next = s;
//    return(s);
//}
//printint(s)
//NODE* s;
//{ if (s->next->data != -1)
//{
//    printint(s->next);
//    if (s->next->next->data == -1)
//        printf("%d", s->next->data);
//    else
//    {
//        int i, k = HUNTHOU;
//        for (i = 1;i <= 4;i++, k /= 10)
//            putchar('0' + s->next->data % (k) / (k / 10));
//    }
//}
//}
//main()
//{
//    NODE* s1, * s2, * s;
//    NODE* inputint(), * addint(), * insert_after();
//
//    s1 = inputint();
//
//    s2 = inputint();
//
//
//    printf("   s1=");
//
//    printint(s1);  putchar('\n');
//
//    printf("   s2=");
//
//    printint(s2);  putchar('\n');
//
//    s = addint(s1, s2);
//
//    printf("s1+s2=");
//    printint(s); putchar('\n');
//}

//
//#include <stdio.h>
//#include<stdlib.h>
//
//
////
//int main()
//{
//
//
//	char name[100][100];
//	char* p[100];
//	for (int i = 0;i < 100;i++)
//	{
//		p[i] = name[i];
//	}
//
//	gets(p[10]);
//	printf("%s", p[10]);
//}
//
//#include<stdio.h>
//
//int main()
//{
//
//
//	return 0;
//}