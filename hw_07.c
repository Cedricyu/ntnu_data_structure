#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
typedef enum{club , diamond, heart, spare}color;
typedef struct card{
    int color;
    int number;
    struct card *next;

}Card;
int tmp[52];
int total=0;
int option;
Card *insert_hand(Card *h,int num){
    Card *new = (Card *)malloc(sizeof(Card));
    new->number = num%13+1;
    new->next =NULL;
    Card *tmp =h;
    if(h==NULL){
        h=new;
        //printf("finish input\n");
        return new;
    }
    while( tmp->next !=NULL ){
        tmp = tmp->next;
    }
    tmp->next = new;
    return h;
}

void print_message(){
    printf("1) 輸入一個正整數 n，隨機產生 n 張牌加到資料中，表示發給這個人 n 張牌。\n");
    printf("2) 選擇某一花色，依發牌拿到的順序一一列出。\n");
    printf("3) 選擇某一花色，依發牌拿到的相反順序一一列出。\n");
    printf("4) 選擇某一花色，依牌色大小由小而大一一列出。\n");
    printf("5) 刪除一張牌：根據一個輸入牌的花色及大小，從該花色中找到比該牌大的牌中最小的一張牌輸出並刪除。\n");
    printf("6) 切換玩家。\n");
    printf("7) 顯示玩家牌面狀況。\n");
    printf("8) 新一輪出牌\n");
    return;
}
void print_hand(Card *h,char s){
    Card *tmp =h;
    if (tmp==NULL){
        printf("no card\n");
        return;
    }
    while(tmp!=NULL){
        printf("%c%d ",s,tmp->number);
        tmp = tmp->next;
    }
    printf("\n");
    return;
}
int color_switch(char s[]){
    if(strcmp(s,"club")==0)
        return club;
    else if(strcmp(s,"diamond")==0)
        return diamond;
    else if(strcmp(s,"heart")==0)
        return heart;
    else if(strcmp(s,"spare")==0)
        return spare;
    else
        return -1;
}
void print_hand_op(Card *h,char c){
    Card *tmp =h;
    
    if (tmp==NULL){
        printf("no card\n");
        return;
    }
    int temp[13];
    int ct=0;
    while(tmp!=NULL){
        temp[ct]=tmp->number;
        ct++;
        tmp = tmp->next;
    }
    for (int i=ct-1;i>=0;i--)
        printf("%c%d ",c,temp[i]);
    printf("\n");
    return;
}
int compare(const void *a,const void *b){
    int c = *(int*)a;
    int d = *(int*)b;
    if(c<d)
        return -1;
    else if(c==d)
        return 0;
    return 1;
}
void print_hand_sort(Card *h,char c){
    Card *tmp =h;
    
    if (tmp==NULL){
        printf("no card\n");
        return;
    }
    int temp[13];
    int ct=0;
    while(tmp!=NULL){
        temp[ct]=tmp->number;
        ct++;
        tmp = tmp->next;
    }
    qsort(temp, ct, sizeof(int), compare);
    for (int i=0;i<ct;i++)
        printf("%c%d ",c,temp[i]);
    printf("\n");
    return;
}
int random_num(){
    unsigned int a=0;
    a=(rand()%52);
    //printf("a = %d ",a);
    for (int i=0;i<total;i++){
        if(tmp[i]==a)
            return random_num();
    }
    //printf("a = %d ",a);
    return a;
}
void draw(Card **hand){
    
    int init=total;
    printf("input the number of card\n");
    int n=0;
    scanf("%d",&n);
    
    for (int i=0;i<n;i++)
       tmp[total++]= random_num();
    int f=0;
    // 初始化

    for (int i=init;i<total;i++){
        f = tmp[i]/13;
        switch (f) {
            case 0:
                hand[club] =insert_hand(hand[club],tmp[i]);
                break;
            case 1:
                hand[diamond] =insert_hand(hand[diamond],tmp[i]);
                break;
            case 2:
                hand[heart] =insert_hand(hand[heart],tmp[i]);
                break;
            case 3:
                hand[spare] =insert_hand(hand[spare],tmp[i]);
                break;
            default:
                break;
        }
        //printf("(%d %d) ",f,tmp[i]%13+1);
    }
    printf("\n");
    return;
}
Card *pop(Card *t,int target){
    Card *pre = (Card*)malloc(sizeof(Card));
    pre->next = t;
    Card *cur= t;
    //char c ='c';
    if(cur->number==target&&cur!=NULL){
        t=t->next;
        free(cur);
        //print_hand(t,c);
        return t;
    }
    while(cur!=NULL){
        if(cur->number==target){
            pre->next=cur->next;
            free(cur);
            break;
        }
        cur=cur->next;
        pre=pre->next;
    }
    return t;
}
Card *delete(Card *h,char n,int target){
    
    int cnt=0;
    Card *tmp=h;
    //char c ='c';
    // head node
    while(tmp!=NULL){
        tmp=tmp->next;
        cnt++;
    }
    if (cnt==0){
        printf("no card to delete\n");
       return NULL;
    }
    int t[cnt];
    tmp = h;
    int i=0,min=target,max=target;
    //printf("min=%d max=%d\n",min,max);
    int flag=0;
    while(tmp!=NULL){
        if(tmp->number<=min)
            min = tmp->number;
        if((tmp->number>target)&&flag==0){
            max =tmp->number;
            flag=1;
        }
        else if((tmp->number<=max)&&(tmp->number>target))
            max = tmp->number;
        t[i]=tmp->number;
        tmp=tmp->next;
        cnt++;
        i++;
    }
    // 有找到
    if (flag==1){
        //printf("max\n");
        h = pop(h,max);
        printf("%c%d\n",n,max);
    }
    else{
        //printf("min\n");
        h = pop(h,min);
        printf("%c%d\n",n,min);
    }
    //print_hand(h,c);
    return h;
}
void delete_card(Card **hand ,char deletec, int deleten){

    switch (deletec) {
        case 'c':
            hand[club] =delete(hand[club],deletec,deleten);
            break;
        case 'd':
            hand[diamond] =delete(hand[diamond],deletec,deleten);
            break;
        case 'h':
            hand[heart] =delete(hand[heart],deletec,deleten);
            break;
        case 's':
            hand[spare] =delete(hand[spare],deletec,deleten);
            break;
        default:
            break;
    }
    return ;
}
int check_win(Card **hand){
    int is_win=1;
        for(int i=0;i<4;i++){
            if(hand[i]!=NULL)
               return 0;
        }
    return is_win;
}
int main(){
    Card ***hand = (Card***)malloc(4*sizeof(Card**));
    for (int i=0; i<4; i++)
        hand[i] = (Card**)malloc(4*sizeof(Card*));
    int player=0;
    char g[] = "cdhs";
    srand(time(NULL));
    char dstr[10];
    char deletec;
    int deleten;
    for (int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        //printf("tmp1[i] = %d ",tmp[i]);
            hand[i][j]=NULL;
    }
    char c[10];
    int turn=0;
    while(1){
        //turn++;
        if(turn >2 && check_win(hand[player])){
            printf("player%d wins\n",player);
            return 0;
        }
        print_message();
        printf("player%d's turn\n",player);
        printf("input option\n");
        scanf("%d",&option);
        if(isalpha(option))
            continue;
        //printf("option = %d\n",option);
        switch (option) {
            case 1:
                draw(hand[player]);
                break;
            case 2:
                printf("input the color you want to print\n");
                scanf("%s",c);
                print_hand(hand[player][color_switch(c)],c[0]);
                break;
            case 3:
                printf("input the color you want to print\n");
                scanf("%s",c);
                print_hand_op(hand[player][color_switch(c)],c[0]);
                break;
            case 4:
                printf("input the color you want to print\n");
                scanf("%s",c);
                print_hand_sort(hand[player][color_switch(c)],c[0]);
                break;
            case 5:
                printf("input the card you want to delete\n");
                scanf("%s",dstr);
                sscanf(dstr,"%c %d",&deletec,&deleten);
                //printf("c= %cn= %d\n",deletec,deleten);
                delete_card(hand[player],deletec,deleten);
                break;
            case 6:
                player++;
                player%=2;
                turn++;
                break;
            case 7:
                //printf("choose the player\n");
                //scanf("%d",&player);
                for (int i=0;i<4;i++){
                    print_hand(hand[player][i],g[i]);
                }
                break;
            case 8:
                printf("input the card you want to delete\n");
                scanf("%s",dstr);
                sscanf(dstr,"%c %d",&deletec,&deleten);
                deleten--;
                delete_card(hand[player],deletec,deleten);
                break;
            default:
                return 0;
                break;
        }}
    return 0;
}


