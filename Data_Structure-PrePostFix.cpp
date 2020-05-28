#include <bits/stdc++.h>
#include <cstdlib>
#include <windows.h>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <deque>
#define size 30

using namespace std;

int precedence(char ch);
void prefix(char ch[]);
void postfix(char ch[]);
void EvaluatePostfix(char ch[]);
void EvaluatePrefix(char ch[]);
char post[size];
char pre[size];


int main()
{
    char infix[size];
    char choice;

    while(true)
    {
        cout<<"\nEnter the infix expression: ";
        cin>>infix;
        postfix(infix);
        cout<<"\nThe postfix expression: "<<post<<endl;
        prefix(infix);
        cout<<"\nThe prefix expression: "<<pre<<endl<<endl;
        EvaluatePostfix(post);
        EvaluatePrefix(pre);

        cout<<"Do you want to execute again?\n";
        while(true)
        {
            cout<<"Press [Y/N]: ";
            cin>>choice;
            if(choice=='N' || choice=='n')
                exit(0);
            else if(choice=='Y' || choice=='y')
            {
                system("cls");
                break;
            }
        }
    }
    return 0;
}

int precedence(char ch)
{
    if(ch=='(' || ch==')')
        return 0;
    else if(ch=='+' || ch=='-')
        return 1;
    else if(ch=='*')
        return 2;
    else if(ch=='/')
        return 3;
    else if(ch=='^')
        return 4;
}

void postfix(char ch[])
{
    stack <char> st;
    char *temp;
    int c=0;
    temp= ch;

    while(*temp!= '\0')
    {

        if(isalnum(*temp))
            post[c++]=*temp;
        else if(*temp == '(')
            st.push(*temp);
        else if(*temp == ')')
        {
            while(!st.empty() && st.top() != '(')
            {
                post[c++]=st.top();
                st.pop();
            }
            st.pop();
        }
        else
        {
            while(!st.empty() && st.top()!='(' && precedence(st.top()) >= precedence(*temp))
            {
                post[c++]=st.top();
                st.pop();
            }
            st.push(*temp);
        }
        temp++;
    }

    if(!st.empty())
    {
        do
        {
            if(st.top()!='(')
                post[c++]=st.top();
            st.pop();
        }
        while(!st.empty());
    }
}

void prefix(char ch[])
{
    stack <char> st1;
    strrev(ch);
    char *temp1;
    int k=0;
    temp1=ch;
    while( *temp1!= '\0')
    {
        if(isalnum(*temp1))
            pre[k++]=*temp1;
        else if(*temp1 == ')')
            st1.push(*temp1);
        else if(*temp1 == '(')
        {
            while(!st1.empty() && st1.top()!= ')')
            {
                pre[k++]=st1.top();
                st1.pop();
            }
            st1.pop();
        }
        else
        {
            while(!st1.empty() && st1.top()!=')' && precedence(st1.top()) >= precedence(*temp1) )
            {
                pre[k++]=st1.top();
                st1.pop();
            }
            st1.push(*temp1);
        }
        temp1++;
    }

    if(!st1.empty())
    {
        while(!st1.empty())
        {
            if(st1.top()!=')')
                pre[k++]=st1.top();
            st1.pop();
        }
    }
    strrev(pre);
    strrev(ch);
}

void EvaluatePostfix(char ch[])
{
    stack <double> st2;
    char *temp2;
    double a,b,x,num,value;
    temp2 = ch;

    cout<<"Postfix Evaluation: "<<endl;
    while(*temp2 != '\0')
    {
        if(isdigit(*temp2))
        {
            num= *temp2 - 48;
            st2.push(num);
        }
        else if(isalpha(*temp2))
        {
            cout<<"Enter the value of "<<*temp2<<": ";
            cin>>value;
            st2.push(value);
        }
        else
        {
            a = st2.top();
            st2.pop();
            b = st2.top();
            st2.pop();
            switch(*temp2)
            {
            case '+':
                x = a + b;
                break;
            case '-':
                x = b - a;
                break;
            case '*':
                x = a * b;
                break;
            case '/':
                x = b / a;
                break;
            case '^':
                x = pow(b,a);
            }
            st2.push(x);
        }
        temp2++;
    }
    cout<<"The result of the expression "<<ch<<" is= "<<st2.top()<<endl<<endl;
}

void EvaluatePrefix(char ch[])
{
    deque <double> q1;
    char *temp2;
    double a,b,x,num,value;
    strrev(ch);
    temp2 = ch;
    cout<<"Prefix Evaluation: "<<endl;
    while(*temp2 != '\0')
    {
        if(isdigit(*temp2))
        {
            num= *temp2 - 48;
            q1.push_back(num);
        }
        else if(isalpha(*temp2))
        {
            cout<<"Enter the value of "<<*temp2<<": ";
            cin>>value;
            q1.push_back(value);
        }
        else
        {
            a = q1.back();
            q1.pop_back();
            b = q1.back();
            q1.pop_back();
            switch(*temp2)
            {
            case '+':
                x = a + b;
                break;
            case '-':
                x = a - b;
                break;
            case '*':
                x = a * b;
                break;
            case '/':
                x = a / b;
                break;
            case '^':
                x = pow(a,b);
                break;
            }
            q1.push_back(x);
        }
        temp2++;
    }
    strrev(ch);
    cout<<"The result of the expression "<<ch<<" is= "<<q1.front()<<endl<<endl;
}
