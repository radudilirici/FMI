#include <iostream>

using namespace std;

class Stack{

private:
    int st[100];
    int top;

public:
    Stack();
    ~Stack();
    void push(int i);
    void init();
    int pop();

};

Stack::Stack()
{
    top = 0;
}

Stack::~Stack()
{
    cout<<"\nObject destroyed\n";
}

void Stack::init()
{
    top = 0;
}

void Stack::push(int i = 4)
{
    if (top == 100)
        return;
    st[top] = i;
    top++;
}

int Stack::pop()
{
    if (top == 0)
        return 0;
    top--;
    return st[top];
}

void f(int i, int *pi, int &ri)
{
    i = 0;
    (*pi) = 10;
    ri++;
}

int f(int &ri)
{
    ri++;
    return ri;
}

int f(int i, int j)
{
    return i + j;
}

int main()
{
    Stack myStack;
    myStack.push(3);
    myStack.push(12);
    myStack.push();
    cout<<myStack.pop()<<"\n";
    cout<<myStack.pop()<<"\n";
    cout<<myStack.pop()<<"\n";
    cout<<myStack.pop()<<"\n";

    int i = 1;
    f(i, &i, i);
    f(1, 2);
    f(i);
    cout<<"\n"<<i<<"\n";
    return 0;
}
