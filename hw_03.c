# include <stdio.h>
# define MAX 100
# include <string.h>
# include <stdlib.h>

typedef struct polynomial{
    int degree;
    int coef;
}Polynomial;

void swap(Polynomial p[MAX],int i,int j){
    int tmp=0;
    tmp = p[i].degree;
    p[i].degree = p[j].degree;
    p[j].degree = tmp;
    tmp = p[i].coef;
    p[i].coef = p[j].coef;
    p[j].coef = tmp;
    return;
}
void intput_polynomial(Polynomial p[MAX]);
int compared(int i,int j){
    if (i-j<0)
        return -1;
    else if (i==j)
        return 0;
    else if (i-j>0)
        return 1;
    return -2;
}
void print(Polynomial p[MAX]){
    int num = p[0].degree;
    for (int i=1;i<=num;i++){
        if (p[i].coef==0&&p[i].degree==0)
            continue;
        printf("%dx^%d ",p[i].coef,p[i].degree);
        if (i!=num)
            printf("+");
    }
    printf("\n");
    return;
}
void print_specific(Polynomial p[MAX]){
    int num = p[0].degree;
    printf("please input the specific drgree\n");
    int sp=0;
    scanf("%d",&sp);
    for (int i=1;i<=num;i++){
        if (p[i].degree==sp){
            printf("%d\n",p[i].coef);
            return;
        }
    }
    return;
}
void add_rmv(Polynomial p[MAX]){
    char option[4];
    printf("add or rmv\n");
    scanf("%s",option);
    if(strcmp(option,"add")==0){
        p[0].degree+=1;
        printf("input the add term\n");
        int degree=p[0].degree;
        int coef=p[0].degree;
        scanf("%d%d",&p[degree].coef,&p[coef].degree);
        return;
    }
    else if(strcmp(option,"rmv")==0){
        printf("input the delete term\n");
        int sp=0;
        scanf("%d",&sp);
        int num = p[0].degree;
        for (int i=1;i<=num;i++){
            if (p[i].degree==sp){
                p[i].coef=0;
                p[i].degree=0;
                return;
            }}}
    return;
}
void add_pol(){
    Polynomial p1[MAX];
    Polynomial p2[MAX];
    Polynomial p3[MAX];
    intput_polynomial(p1);
    intput_polynomial(p2);
    int num1 =p1[0].degree;
    int num2 =p2[0].degree;
    int i=1;
    int j=1;
    int k=1;
    while(1){
        switch (compared(p1[i].degree,p2[j].degree)) {
            case -1:
                p3[k].degree = p2[j].degree;
                p3[k].coef = p2[j].coef;
                j++;
                k++;
                break;
            case 0:
                p3[k].degree = p1[i].degree;
                p3[k].coef = p1[i].coef + p2[j].coef;
                i++;
                j++;
                k++;
            case 1:
                p3[k].degree = p1[i].degree;
                p3[k].coef = p1[i].coef;
                i++;
                k++;
            default:
                break;
        }
        if (i==p1[0].degree+1 && j==p2[0].degree+1)
            break;
    }
    p3[0].degree = k-1;
    print(p3);
    return;
}
void sub_pol(){
    Polynomial p1[MAX];
    Polynomial p2[MAX];
    Polynomial p3[MAX];
    intput_polynomial(p1);
    intput_polynomial(p2);
    int num1 =p1[0].degree;
    int num2 =p2[0].degree;
    int i=1;
    int j=1;
    int k=1;
    while(1){
        //printf("compared = %d,i= %d,j= %d,k = %d\n",compared(p1[i].degree,p2[j].degree),i,j,k);
        switch (compared(p1[i].degree,p2[j].degree)) {
            case -1:
                p3[k].degree = p2[j].degree;
                p3[k].coef = -p2[j].coef;
                j++;
                k++;
                break;
            case 0:
                p3[k].degree = p1[i].degree;
                p3[k].coef = p1[i].coef - p2[j].coef;
                i++;
                j++;
                k++;
                break;
            case 1:
                p3[k].degree = p1[i].degree;
                p3[k].coef = p1[i].coef;
                i++;
                k++;
            default:
                break;
        }
        if (i==p1[0].degree+1 && j==p2[0].degree+1)
            break;
    }
    p3[0].degree = k-1;
    print(p3);
    //printf("%d\n",p3[0].degree);
    return;
    
}
typedef struct node {
    int coef;
    int degree;
    struct node* next;
}Node;
Node *insert(Node *head,Polynomial p[MAX],int i){
    
    Node *t= (Node*)malloc(sizeof(Node));
    t->coef = p[i].coef;
    t->degree = p[i].degree;
    t->next =NULL;
    if(head==NULL){
        head = t;
    }
    else{
        Node *tmp=head;
        while(tmp->next!=NULL)
            tmp= tmp->next;
        //t->next = tmp->next;
        tmp ->next = t;
    }
    return head;
}
void print_node(Node *p){
    while (p!=NULL) {
        printf("%dx^%d ",p->coef,p->degree);
        if (p->next!=NULL)
            printf("+");
        p = p->next;
    }
}

void mul_pol(){
    Polynomial p1[MAX];
    Polynomial p2[MAX];
    Polynomial p3[MAX];
    Node *p4=NULL;
    int k=1;
    int start[MAX];
    int s=0;
    intput_polynomial(p1);
    intput_polynomial(p2);
    // 將結果儲存到 p3
    for (int i=1;i<=p1[0].degree;i++){
        start[s]=k;
        s++;
        for (int j=1;j<=p2[0].degree;j++){
            p3[k].degree= p1[i].degree +p2[j].degree;
            p3[k].coef = p1[i].coef * p2[j].coef;
            k++;
        }}
    //sort p3
    for (int i=1; i<k; i++)
        for (int j=1; j<k; j++)
            if (p3[i].degree > p3[j].degree){
                swap(p3,i,j);
            }
    p3[0].degree = p1[0].degree*p2[0].degree;
    //print(p3);
    // p3 整理到 p4
    Node *head =p4;
    for (int i=1;i<k;i++){
        head= insert(head,p3,i);
        //head = head->next;
    }
    //print_node(head);
    p4 =head;
    while (head->next!=NULL) {
        if(head->degree==head->next->degree){
            Node *tmp = head->next;
            head->coef+=head->next->coef;
            head->next=head->next->next;
            free(tmp);
        }
        else
            head = head->next;
    }
    print_node(p4);
    return;
}
void clean(Polynomial p[MAX]){
    int num = p[0].degree;
    if (num!=0){
    for (int i=1;i<=num;i++){
        p[i].degree = 0;
        p[i].coef = 0;
    }}
    return ;
}
void intput_polynomial(Polynomial p[MAX]){
    clean(p);
    //printf("please input the polynominal\n");
    //int i=0;
    int num=0;
    printf("Number of polynomial terms:\n");
    scanf("%d",&num);
    p[0].degree = num;
    int n,m;
    printf("please input the polynominal\n");
    for(int i=1;i<=num;i++){
        scanf("%d%d",&m,&n);
        p[i].degree = n;
        p[i].coef = m;
    }
    printf("finish input\n");
    return;
}

int main(){
    
    int option=0;
    
    Polynomial **polynomial =(Polynomial**)malloc(20*sizeof(Polynomial*));
    for (int i=0; i<20; i++)
        polynomial[i] = (Polynomial*)malloc(sizeof(Polynomial)*100);
    // 初始化
    polynomial[0]->degree=0;
    int i=1;
    int sp =0;
    while(1){
        if (i>=20)
            break;
    scanf("%d",&option);
    switch (option) {
        //scanf("%d",&option);
        case 1:
            //clean(polynomial);
            intput_polynomial(polynomial[i]);
            i++;
            break;
        case 2:
            printf("select polynomial\n");
            scanf("%d",&sp);
            print(polynomial[sp]);
            break;
        case 3:
            printf("select polynomial\n");
            scanf("%d",&sp);
            print_specific(polynomial[sp]);
            break;
        case 4:
            printf("select polynomial\n");
            scanf("%d",&sp);
            add_rmv(polynomial[sp]);
            break;
        case 5:
            add_pol();
            break;
        case 6:
            sub_pol();
            break;
        case 7:
            mul_pol();
            break;
        default:
            return 0;
            break;
    }}
    
    return 0;
}
