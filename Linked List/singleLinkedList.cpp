#include<stdio.h>
#include<stdlib.h>

struct node{
	int number;
	struct node *next;
}*head=NULL, *tail=NULL;

//create new node
struct node *createNewNode(int number)
{
	struct node *newNode=(struct node*)malloc(sizeof(struct node));
	//(*newNode).number=number;
	newNode->number=number;
	newNode->next=NULL;
	return newNode;
}

void pushHead(struct node *newNode)
{
	if(head==NULL)//jika linked list masih kosong
		head=tail=newNode;
	else
	{
		newNode->next=head;
		head=newNode;
	}
}

void pushTail(struct node *newNode)
{
	if(head==NULL)
		head=tail=newNode;
	else
	{
		tail->next=newNode;
		tail=newNode;
	}
}

void pushBefore(struct node *newNode, int number2)
{
	struct node *ptr=head, *preptr;
	if(head==NULL)//kalau linked list kosong, angka before ga diperhatikan, langsung insert angka baru
		head=tail=newNode;
	else
	{
		while(ptr!=NULL && ptr->number!=number2)
		{
			preptr=ptr;
			ptr=ptr->next;
		}
		
		if(ptr!=NULL)
		{
			if(ptr==head)
				pushHead(newNode);
			else
			{
				preptr->next=newNode;
				newNode->next=ptr;
			}
		}
		else
		{
			printf("Number before is not found\n");
		}
	}
}

void pushAfter(struct node *newNode, int number2)
{
	struct node *ptr=head;
	if(head==NULL)//kalau linked list kosong, angka before ga diperhatikan, langsung insert angka baru
		head=tail=newNode;
	else
	{
		while(ptr!=NULL && ptr->number!=number2)
		{
			ptr=ptr->next;
		}
		
		if(ptr!=NULL)
		{
			if(ptr==tail)
				pushTail(newNode);
			else
			{
				newNode->next=ptr->next;
				ptr->next=newNode;
			}
		}
		else
		{
			printf("Number before is not found\n");
		}
	}
}


void printLinkedList()
{
	struct node *ptr=head;
	while(ptr!=NULL)
	{
		if(ptr==tail)//data terakhir
			printf("[%d]->NULL\n", ptr->number);
		else
			printf("[%d]->", ptr->number);
		ptr=ptr->next;
	}
}

int main()
{
	int menu, number, number2;
	struct node *newNode;
	do{
		system("cls");
		printf("Single Linked List\n");
		printf("==================\n\n");
		printLinkedList();
		printf("1. Push Head\n");
		printf("2. Push Tail\n");
		printf("3. Push After\n");
		printf("4. Push Before\n");
		printf("5. Pop Node\n");
		printf("6. Exit\n");
		printf("Insert menu: "); scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				printf("Enter number you want to insert: ");
				scanf("%d", &number);
				newNode=createNewNode(number);
				pushHead(newNode);
				break;
			case 2:
				printf("Enter number you want to insert: ");
				scanf("%d", &number);
				newNode=createNewNode(number);
				pushTail(newNode);
				break;
			case 3:
				printf("Enter number you want to insert: ");
				scanf("%d", &number);
				printf("The number will be inserted after: ");
				scanf("%d", &number2);
				newNode=createNewNode(number);
				pushAfter(newNode, number2);
				break;
			case 4:
				printf("Enter number you want to insert: ");
				scanf("%d", &number);
				printf("The number will be inserted before: ");
				scanf("%d", &number2);
				newNode=createNewNode(number);
				pushBefore(newNode, number2);
				break;
			case 5:
				break;
		}
		
	}while(menu!=6);
	return 0;
}
