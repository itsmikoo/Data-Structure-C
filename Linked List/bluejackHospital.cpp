#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();

struct patient{
	char name[30];
	int age;
	char desc[1000];
	char code[10];
	int num;
	struct patient *next;
	struct patient *prev;
}*head, *tail;

struct patient *createNewPatient(char name[30], int age, char desc[1000], char code[10], int num)
{
	struct patient *newPatient=(struct patient*)malloc(sizeof(struct patient));
	strcpy(newPatient->name, name);
	newPatient->age=age;
	strcpy(newPatient->desc, desc);
	strcpy(newPatient->code, code);
	newPatient->num = num;
	
	newPatient->next=NULL;
	newPatient->prev=NULL;
	return newPatient;
}

int changeCode(char code[]){
	if(strcmp(code, "Red")==0){
		return 1;
	}
	else if(strcmp(code, "Yellow")==0){
		return 2;
	}
	else if(strcmp(code, "Green")==0){
		return 3;
	}	
}

void insert(struct patient *newPatient){
	struct patient *ptr = head;
	if(head==NULL){
		head=tail=newPatient;
	}
	else if(head->num>newPatient->num){
		newPatient->next = head;
		head->prev = newPatient;
		head = newPatient;
	}
	else if(tail->num<=newPatient->num){
		tail->next = newPatient;
		newPatient->prev = tail;
		tail = newPatient;
	}
	else{
		while(ptr->next != NULL && ptr->num <= newPatient->num){
			ptr = ptr->next;
		}
		newPatient->next = ptr->next;
		ptr->next->prev = newPatient;
		newPatient->prev = ptr;
		ptr->next = newPatient;
	}
}

void view(){
	struct patient *ptr=head;
	int i=1;
	if(ptr!=NULL){
		printf("Patient List: \n");
		printf("----------------------------------------------------------------------------------------------------------\n");
		printf("No | Name                     | Age  | Description                                               | Code  |\n");
		while(ptr!=NULL){
			printf("%-3d| %-25s| %-5d| %-58s| %-6s|\n", i, ptr->name, ptr->age, ptr->desc, ptr->code);
			i++;
			ptr=ptr->next;
		}
		printf("----------------------------------------------------------------------------------------------------------\n");
	}
	else{
		printf("There is no queue yet!\n\n");
	}
	printf("Press any key to continue...");
	getchar(); menu();
}

void nextQueue(){
	struct patient *ptr=head;
	if(ptr!=NULL){
		printf("The next patient is:\n");
		printf("Name        : %s", ptr->name);
		printf("Age         : %d", ptr->age);
		printf("Description : %s", ptr->desc);
		printf("Code        : %s", ptr->code);
	}
	else{
		printf("There is no queue yet!\n\n");
	}
	printf("Press any key to continue...");
	getchar(); menu();
}

void inputrecord(){
	struct patient *newPatient;
	char name[30];
	int age;
	char desc[1000];
	char code[10];
	int num;
	do{
		printf("Input patient name[4-25]: ");
		scanf("%[^\n]", &name); getchar();
	}while(strlen(name)<4 || strlen(name)>25);
	do{
		printf("Input patient age[>= 0]: ");
		scanf("%d", &age); getchar();
	}while(age<0);
	do{
		printf("Input description[>= 6 characters]: ");
		scanf("%[^\n]", &desc); getchar();
	}while(strlen(desc)<6);
	do{
		printf("Input code[Red|Yellow|Green]: ");
		scanf("%s", &code); getchar();
	}while(strcmp(code, "Red")!=0 && strcmp(code, "Green")!=0 && strcmp(code, "Yellow")!=0);
	num = changeCode(code);
	printf("\nInsert success !\n");
	
	newPatient = createNewPatient(name, age, desc, code, num);
	insert(newPatient);
	
	printf("Press any key to continue...");
	getchar(); menu();
}

void menu(){
	int choice;
	do{
		system("cls");
		printf("Bluejack Hospital\n");
		printf("========================\n");
		printf("1. Insert\n");
		printf("2. View\n");
		printf("3. Next Queue\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &choice); getchar();
		switch(choice){
			case 1:
				inputrecord();
				view();
				break;
			case 2:
				view();
				break;
			case 3:
				nextQueue();
				break;
			case 4:
				break;
		}
	}while(choice!=4);
}

int main(){
	menu();
	return 0;
}
