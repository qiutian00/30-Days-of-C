#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAP 100

struct Stack {
    int data[CAP];
    int top;
};

static void init(struct Stack *s)    { s->top = -1; }
static bool isEmpty(struct Stack *s) { return s->top == -1; }
static bool isFull(struct Stack *s)  { return s->top == CAP - 1; }

static void push(struct Stack *s, int x) {
    if (isFull(s)) { fprintf(stderr, "stack overflow\n"); exit(1); }
    s->data[++s->top] = x;
}

static int pop(struct Stack *s) {
    if (isEmpty(s)) { fprintf(stderr, "stack underflow\n"); exit(1); }
    return s->data[s->top--];
}

static int peek(struct Stack *s) {
    if (isEmpty(s)) { fprintf(stderr, "empty stack\n"); exit(1); }
    return s->data[s->top];
}

static bool balanced(const char *s)
{
    struct Stack st; init(&st);
    for (int i = 0; s[i]; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            push(&st, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (isEmpty(&st)) return false;
            char o = (char)pop(&st);
            if ((c == ')' && o != '(') ||
                (c == '}' && o != '{') ||
                (c == ']' && o != '[')) return false;
        }
    }
    return isEmpty(&st);
}

int main(void)
{
    struct Stack s; init(&s);
    push(&s, 10); push(&s, 20); push(&s, 30);
    printf("peek = %d\n", peek(&s));
    printf("pop  = %d\n", pop(&s));
    printf("pop  = %d\n", pop(&s));

    const char *tests[] = {"(a{b[c]d}e)", "(a{b[c}d]e)", "((())", ""};
    for (int i = 0; i < 4; i++)
        printf("\"%s\" -> %s\n", tests[i], balanced(tests[i]) ? "balanced" : "unbalanced");
    return 0;
}
