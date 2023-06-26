#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*
admin->totalsales,add new item,delete item
customer->order,delate,total bill
*/

typedef struct node//Declaration of the node
{
    char foodname[50];
    int quantity;
    int price,data;

    struct node *rptr;
}node;
node *newnode,*heada=NULL,*headc=NULL,*heads=NULL;//global declaration

void display(node *head)
{
    if(head==NULL)//if menu is empty
    {
        printf("\n empty menu");
        return;
    }
    printf("\n\t\t\tSN\t\tFOODNAME\t\tQUANTITY\t\tPRICE\n");
    while(head!=NULL)
    {
      printf("\n\t\t\t%d\t\t%s\t\t%d\t\t%d\n",head->data,head->foodname,head->quantity,head->price);
      head=head->rptr;
    }
}

node *deleateA_item(node *head)//deleting items from the main menu
{
    node *temp=head,*perv=NULL;
    int item;
    display(head);//displaying items from the main menu
    printf("\nenter the item serial number to delete\n");
    scanf("%d",&item);
    if(head==NULL)//if menu is empty
        printf("list is empty\n");
    else
    {
    while(temp!=NULL)//traversing the main menu
    {
        if(item==temp->data)//if multiple nodes
        {
           if(item==head->data)//if it is 1st node
           {

             head=temp->rptr;
             free(temp);
             display(head);
             return head;
           }

           else{
            perv->rptr=temp->rptr;
            printf(" %s item deleted successfully\n\n",temp->foodname);
            free(temp);
            display(head);
           }
        }
        perv=temp;
        temp=temp->rptr;
    }
    }
    return head;
}

node *total_sales(node *head)//todays total sales
{
int total_price=0;
    if(head==NULL)//is no sales
    {
        printf("\n\n\t\t\t\t\t!!NO SALES OF THE DAY !!\n\n");
        return NULL;
    }
    else{
       node *temps=head;
       printf("\n\t\t\tFOODNAME\tQUANTITY\tPRICE\n");
       while(temps!=NULL)//traversing sales upto end
       {
        printf("\n\t\t\t%s\t\t%d\t\t%d",temps->foodname,temps->quantity,temps->price);
        total_price+=temps->price;//adding amount of each item
        temps=temps->rptr;
    }
    }
    printf("\n\n\t\t  ** toatal sales today upto now is %d **\n",total_price);
    return head;
}

int count=10;
node *add_item(node *first,char name[],int price,int data)//adding new item to the main menu list
{

    node *newnode,*temp;
    newnode=(node*)malloc(sizeof(node));
    strcpy(newnode->foodname,name);
    newnode->price=price;
    newnode->quantity=1;
    newnode->data=data;
    newnode->rptr=NULL;
     if(first==NULL)//if node is empty
     first=newnode;
        else
        {
            temp=first;
            while(temp->rptr!=NULL)
                temp=temp->rptr;
            temp->rptr=newnode;

        }

       return first;
}


void mainmenu()//main menu
{
    printf("\n\t\t\t\t***************************\n");
    printf("\n\t\t\t\tWELCOME TO THE RESTAURANT\n");
    printf("\n\t\t\t\t****************************\n");
    printf("\n1:customer menu");
    printf("\n2:admin menu");
    printf("\n3:EXIT");
    printf("\nenter your choice->");
}

void admin_menu()//admin menu
{
    printf("\n\t\t\t\t 1. View total sales\n");
    printf("\t\t\t\t 2. Add new items in the order menu\n");
    printf("\t\t\t\t 3. Delete items from the order menu\n");
    printf("\t\t\t\t 4. Display order menu\n");
    printf("\t\t\t\t 5. Back To Main Menu \n\n");
    printf("\t\t\t\t   Enter Your Choice --->");
}

void admin()//admin section
{
    int pass;
  int flag=0;
    printf("\n\t\t password :");
    scanf("%d",&pass);
    if(flag==0)
    {
        if(pass==1234)//security checking
            flag=1;
    }
    if(flag==1)
    {
    printf("\n\t\t\t\t***************************\n");
    printf("\n\t\t\t\tWELCOME TO ADMIN SECTION\n");
    printf("\n\t\t\t\t****************************\n");
    while(1){
      admin_menu();
        int opt;
         scanf("%d",&opt);
         if(opt==5)//back to main menu
            break;
            char foodname[20];
           int price,quantity,data;
         switch(opt)
         {
             case 1:heads=total_sales(heads);
                       break;
             case 2:
                    printf("\nenter the Food details into the menu: ");//new items details
                    printf("\n Food name : "); scanf("%s",foodname);
                    printf("\n price:");  scanf("%d",&price);
                    printf("\n enter serial number equal to ->%d:\n",count);
                    scanf("%d",&data);
                    count++;
                    heada=add_item(heada,  foodname   ,price,data);//passing argument to add_item fuction
                 break;
            case 3:heada=deleateA_item(heada);
                break;
            case 4:display(heada);
                   break;
            default :printf("\ninvalid input");
         }
    }

    }
    else{
        printf("\n!!!wrong password!!!");
        return;
    }

}
node *creating_custmer(node *headc)//creating customer nodes
{
    display(heada);
    node *tempa=heada;
    int quantity;
    newnode=(node*)malloc(sizeof(node));
    printf("\nenter the serial nor to order:");
    scanf("%d",&newnode->data);
    printf("\nenter the quantity:");
    scanf("%d",&quantity);
    while(tempa!=NULL)//traversing main menu
    {
        if(newnode->data==tempa->data)//checking the serial number of an item equal to the main menu item
            break;
        tempa=tempa->rptr;
    }
    if(tempa==NULL)
    printf("\n\t\t item is out of order PLZ order next!!!");

    else{
      strcpy(newnode->foodname,tempa->foodname);
       newnode->price=quantity*(tempa->price);
       newnode->quantity=quantity;
       newnode->rptr=NULL;
       if(headc==NULL)              //if customer buying first item
            headc=newnode;
       else{                        //if customer already purchased new item then traversing upto end of the item
        node *tail=headc;
        while(tail->rptr!=NULL)
            tail=tail->rptr;
        tail->rptr=newnode;
       }
    }
    return headc;
}

node* deleatec_item(node *head)       //deleting the customer item using serial number
{
 node *tempc=headc,*prev=NULL;
    if(headc==NULL)                       //to check the customer nodes if empty it will execute
        printf("\not ordered any thing");
    else
    {
     int item,flag=0;
     display(headc);
    printf("\nenter the serial number to delete from the item:");
    scanf("%d",&item);
    if(tempc->rptr==NULL && tempc->data==item)     //if it is first node
    {
    printf("\n%s item is deleated from the list",tempc->foodname);
    free(tempc);
    return NULL;

    }
    if(headc->data==item)//if two nodes present
    {
    printf("\n%s item is deleted from the list",tempc->foodname);
    free(tempc);
    headc=headc->rptr;//pointing to the next node
    return headc;

    }

    while(tempc!=NULL)//traversing customer nodes
    {
        if(item==tempc->data)
        {
            flag=1;


             break;
        }
            prev=tempc; //assigning to node to prev pointer and pointing next node
        tempc=tempc->rptr;
    }
    if(flag==1)
    {
      prev->rptr=tempc->rptr;
    printf("\n%s item is deleated from the list",tempc->foodname);
    free(tempc);
    }else
   printf("\ninvalid input");
    }
   printf("\nupdated list\n "); display(headc);
    return headc;

}
node *total_bill(node *head)//total bill of the customer
{
    int totalbill=0;
  node *tempc=head;
  if(tempc==NULL)
  printf("\nempty list");
  else{
    printf("\n\t\tFoodName\tQuantity\tPrice\n");
    while(tempc!=NULL)
    {
        printf("\n\t\t%s\t\t%d\t\t%d\n",tempc->foodname,tempc->quantity,tempc->price);
        totalbill+=tempc->price;
        tempc=tempc->rptr;
    }

  }
  printf("\n\t\t total Bill is %d ",totalbill);
  return head;
}

void custmer_menu()
{
    printf("\n\t\t\t\t 1. Place new order\n");
    printf("\t\t\t\t 2. display your order\n");
    printf("\t\t\t\t 3. Delete orders from list\n");
    printf("\t\t\t\t 4. total final bill\n");
    printf("\t\t\t\t 5. Back To Main Menu \n\n");
    printf("\t\t\t\t   Enter Your Choice --->");
}
void custmer()
{
    while(1)
 {
     custmer_menu();
          int opt;
        scanf("%d",&opt);
         if(opt==5)
            break;
         switch(opt)
         {
             case 1:headc=creating_custmer(headc);
             break;
             case 2:display(headc);
                 break;
            case 3:headc=deleatec_item(headc);
                break;
            case 4:heads=total_bill(headc);
                   break;
            default :printf("\ninvalid input");
         }
 }
}

int main()
{
    heada = add_item(heada,"Hot and Sour Soup ",60,1);
    heada = add_item(heada,"  Manchow Soup    ",80,2);
    heada = add_item(heada,"Manchurian Noodles",150,3);
    heada = add_item(heada," Fried Rice       ",120,4);
    heada = add_item(heada,"  Hakka Noodles   ",80,5);
    heada = add_item(heada,"   Eggrice        ",40,6);
    heada = add_item(heada,"      TEA         ",20,7);
    heada = add_item(heada,"    CHAPATI       ",20,8);
    heada = add_item(heada,"      PIZZA       ",20,9);

    int choice;
    while(1)
  {
    mainmenu();
   scanf("%d",&choice);
  switch(choice)
  {
   case 1:custmer();
         break;
   case 2:admin();
            break;
   case 3:exit(0);
  default :printf("\ninvalid input");
  }
 }
 return 0;
}