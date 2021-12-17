
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char stack[20];
int top=-1;

void push(char i){
    top++;
    stack[top]=i;
    return;
}

char pop(){
    if(top ==-1)
        return -1;
    else
        return stack[top--];
    
}
int priority(char i){
    if(i == '(')
        return 0;
    if(i == '+'|| i=='-')
        return 1;
    if(i =='*' || i=='/')
        return 2;
    return -1;
}
int main(){
    char string[20];
    char *s,x;
    scanf("%s",string);
    s = string;
    while(*s != '\0'){
        if(isalnum(*s))
            printf("%c",*s);
        else if(*s =='(')
            push(*s);
        else if(*s ==')'){
            while((x = pop()) != '(')
                printf("%c", x);
        }
        else{
            while(priority(stack[top])>= priority(*s))
                printf("%c",pop());
            push(*s);
        }
        s++;
    }
    while(top !=-1){
        printf("%c",pop());
    }
    printf("\n");
}
