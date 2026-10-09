#ifndef _SYS_QUEUE_H_ // 头文件防重包含开始
#define _SYS_QUEUE_H_ // 定义本头文件的防重包含宏

// 单向链表（LIST_*）最小实现
#define LIST_HEAD(name, type)                                      \
        struct name {                                              \
                struct type *lh_first; /* 指向第一个元素 */         \
        }

#define LIST_HEAD_INITIALIZER(head) { NULL } // 头结点初始为空

#define LIST_ENTRY(type)                                           \
        struct {                                                   \
                struct type *le_next;  /* 后继结点 */                \
                struct type **le_prev; /* 指向前驱 next 指针的指针 */ \
        }

#define LIST_EMPTY(head)        ((head)->lh_first == NULL) // 判空
#define LIST_FIRST(head)        ((head)->lh_first)         // 取首元

#define LIST_FOREACH(var, head, field)                              \
        for ((var) = LIST_FIRST((head)); /* 从首元开始 */            \
                 (var);                           /* 未到尾部 */      \
                 (var) = LIST_NEXT((var), field)) /* 迭代到下一个 */

#define LIST_INIT(head) do {                         \
                LIST_FIRST((head)) = NULL;          \
        } while (0) // 将链表置空

#define LIST_NEXT(elm, field)   ((elm)->field.le_next) // 取后继

#define LIST_INSERT_AFTER(listelm, elm, field) do {                      \
                LIST_NEXT((elm), field) = LIST_NEXT((listelm), field);   \
                if (LIST_NEXT((listelm), field) != NULL)                 \
                        LIST_NEXT((listelm), field)->field.le_prev =     \
                                &LIST_NEXT((elm), field);                \
                LIST_NEXT((listelm), field) = (elm);                      \
                (elm)->field.le_prev = &LIST_NEXT((listelm), field);      \
        } while (0) // 在指定元素之后插入

#define LIST_INSERT_BEFORE(listelm, elm, field) do {                     \
                (elm)->field.le_prev = (listelm)->field.le_prev;         \
                LIST_NEXT((elm), field) = (listelm);                     \
                *(listelm)->field.le_prev = (elm);                       \
                (listelm)->field.le_prev = &LIST_NEXT((elm), field);     \
        } while (0) // 在指定元素之前插入

#define LIST_INSERT_HEAD(head, elm, field) do {                          \
                if ((LIST_NEXT((elm), field) = LIST_FIRST((head))) != NULL) \
                        LIST_FIRST((head))->field.le_prev = &LIST_NEXT((elm), field); \
                LIST_FIRST((head)) = (elm);                               \
                (elm)->field.le_prev = &LIST_FIRST((head));               \
        } while (0) // 头插

#define LIST_INSERT_TAIL(head, elm, field) do {                           \
                if (LIST_FIRST((head)) == NULL) {                         \
                        LIST_FIRST((head)) = (elm);                       \
                        (elm)->field.le_prev = &LIST_FIRST((head));       \
                } else {                                                  \
                        LIST_NEXT((elm), field) = LIST_FIRST((head));     \
                        while (LIST_NEXT((LIST_NEXT((elm), field)), field)) { \
                                LIST_NEXT((elm), field) =                 \
                                        LIST_NEXT(LIST_NEXT((elm), field), field); \
                        }                                                 \
                        (LIST_NEXT((LIST_NEXT((elm), field)), field)) = (elm); \
                        (elm)->field.le_prev = &LIST_NEXT((elm), field);  \
                        (elm)->field.le_next = NULL;                      \
                }                                                         \
        } while (0) // 尾插（线性查找尾部）

#define LIST_REMOVE(elm, field) do {                                      \
                if (LIST_NEXT((elm), field) != NULL)                      \
                        LIST_NEXT((elm), field)->field.le_prev =          \
                                        (elm)->field.le_prev;             \
                *(elm)->field.le_prev = LIST_NEXT((elm), field);          \
        } while (0) // 删除指定元素

// 简化的尾队列（仅头/条目定义，操作可按需补齐）
#define TAILQ_HEAD(name, type)                             \
        struct name {                                      \
                struct type *tqh_first; /* 队首元素 */     \
                struct type **tqh_last; /* 指向尾后指针 */  \
        }

#define TAILQ_ENTRY(type)                                  \
        struct {                                           \
                struct type *tqe_next;  /* 下一个 */        \
                struct type **tqe_prev; /* 指向前驱 next 的指针 */ \
        }

#endif // 结束防重包含

