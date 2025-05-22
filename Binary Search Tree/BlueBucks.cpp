#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct cust{
	char phoneNum[50];
	char name[50];
	char email[50];
	int points;
	
	struct cust *left, *right;
};

struct Drink{
	char drinkName[50];
	int quantity;
	int total;
}drink[100];
int i=0;

struct cust *checkCust(struct cust *user, char phoneNum[]){
    if (user == NULL) return NULL;
    if (strcmp(user->phoneNum, phoneNum) == 0) return user;
    if (strcmp(phoneNum, user->phoneNum) < 0) return checkCust(user->left, phoneNum);
    return checkCust(user->right, phoneNum);
}

struct cust *newCust(struct cust *user, char name[], char email[], char phoneNum[], int point){	
	if(user==NULL){
		struct cust *newCustomer = (struct cust*)malloc(sizeof(struct cust));
		strcpy(newCustomer->name, name);
		strcpy(newCustomer->email, email);
		strcpy(newCustomer->phoneNum, phoneNum);
		newCustomer->points = point;
		newCustomer->left = NULL;
		newCustomer->right = NULL;
		user = newCustomer;
	}
	else if(strcmp(phoneNum, user->phoneNum)<0){
		user->left = newCust(user->left, name, email, phoneNum, point);
	}
	else if(strcmp(phoneNum, user->phoneNum)>0){
		user->right = newCust(user->right, name, email, phoneNum, point);
	}
	return user;
}

struct cust* processOrder(struct cust *user){
	char phoneNum[50];
	char name[50];
	char email[50];
	int point=0, len=0, ch=0;
	char yn;
	
	do{
		printf("Input Phone Number: ");
		scanf("%s", phoneNum); getchar();
		len = strlen(phoneNum);
		ch = 0;
		for(int i=0;i<len;i++){
			if(!isdigit(phoneNum[i])) ch = 1;
		}
	}while(strlen(phoneNum)<10 || strlen(phoneNum)>13 || ch==1);
	
	struct cust *customer = checkCust(user, phoneNum);
	
	if(customer == NULL){
		do{
			printf("Input name[5-25][Mr. |Mrs. ]: ");
			scanf("%[^\n]", name); getchar();
		}while(strlen(name)<5 || strlen(name)>25 || (strncmp(name, "Mr. ", 4)!=0 && strncmp(name, "Mrs. ", 5)!= 0));
		do{
			printf("Input email[10-20][email format]: ");
			scanf("%s", email); getchar();
			len = strlen(email);
			ch = 0;
			for(int i=0;i<len;i++){
				if(email[i]== '@') ch++;
			}
		}while(len<10 || len>20 || ch!=1 || (strcmp(email+len-4, ".com")!=0 && strcmp(email+len-6, ".co.id")!=0));
		
		user = newCust(user, name, email, phoneNum, 10);
		customer = checkCust(user, phoneNum);
	}
	if(customer->points>25){
		do{
			printf("Do you want to use your points[You have %d][y|n]: ", customer->points);
			scanf(" %c", &yn); getchar();
		}while(yn != 'y'&& yn != 'n');
		if(yn == 'y'){
			do{
				printf("How much[%d left]: ", customer->points);
				scanf("%d", &point); getchar();
			}while(point%25 != 0 && point < 25);
		}
		customer->points = customer->points - point; 
	}
	point = point/25;
	printf("\nYou have %d free drink(s) left.\n", point);
	

	int temp=i;
	int total = 0;
	do{
		do{
			printf("Input drink[Cafe Latte|Caramel Macchiato|Cappucino|Cafe Mocha]: ");
			scanf("%[^\n]", drink[i].drinkName); getchar();
		}while(strcmp(drink[i].drinkName, "Cafe Latte")!=0 && strcmp(drink[i].drinkName, "Caramel Macchiato")!=0 && 
		strcmp(drink[i].drinkName, "Cappucino")!=0 && strcmp(drink[i].drinkName, "Cafe Mocha")!=0);
		do{
			printf("Input drink quantity[>=1]: ");
			scanf("%d", &drink[i].quantity); getchar();
		}while(drink[i].quantity<1);
		
		if(point>=drink[i].quantity){
			drink[i].total = 0;
			point -= drink[i].quantity;
		}
		else{
			drink[i].total = (drink[i].quantity-point)*30000;
			point = 0;
		}
		
		printf("Do you want to order more?[y|n]: ");
		scanf(" %c", &yn); getchar();
		i++;	
		
		printf("\nYou have %d free drink(s) left.\n", point);
	}while(yn == 'y');
	
	printf("\nOrder Summary:\n");
	for(int j=0; j<i-temp;j++){
		printf("%-10s - %-3d = %d\n", drink[temp+j].drinkName, drink[temp+j].quantity, drink[temp+j].total);
		total += drink[temp+j].total;
	}
	printf("Total: %d\n", total);
	printf("Points Obtained: %d\n", total/50000*3);
	customer->points += total/50000*3;
	
	return user;
}

void printHeader() {
    printf("================================================================================================================\n");
    printf("| %-25s | %-15s | %-25s | %-5s |\n", "Name", "Phone Number", "Email", "Points");
    printf("================================================================================================================\n");
}

void viewCust(struct cust *user){
	if(user == NULL) return;
	
	viewCust(user->left);
	printf("| %-25s | %-15s | %-25s | %-5d |\n", user->name, user->phoneNum, user->email, user->points);
	printf("----------------------------------------------------------------------------------------------------------------\n");
	viewCust(user->right);
}

struct cust *findPredecessor(struct cust *user){
	while(user->right!=NULL){
		user=user->right;
	}
	return user;
}


struct cust* removeCust(struct cust *user, char phoneNum[]){
	struct cust *temp;
	
	if(user==NULL){
		printf("Data invalid!\n");
	}
	else if(strcmp(phoneNum, user->phoneNum)<0){
		user->left = removeCust(user->left, phoneNum);
	}
	else if(strcmp(phoneNum, user->phoneNum)>0){
		user->right = removeCust(user->right, phoneNum);
	}
	else{
		if(user->left==NULL && user->right==NULL){
			free(user);
			user = NULL;
		}
		else if(user->right==NULL){
			temp = user;
			user=user->left;
			free(temp);
		}
		else if(user->left==NULL){
			temp = user;
			user = user->right;
			free(temp);
		}
		else{
			temp = findPredecessor(user->left);
			strcpy(user->phoneNum, temp->phoneNum);
			strcpy(user->name, temp->name);
			strcpy(user->email, temp->email);
			user->points = temp->points;
			user->left = removeCust(user->left, user->phoneNum);
		}
	}
	return user;
}

int main(){
	struct cust *root = NULL;
	char phoneNum[50];
	
	root = newCust(root, "Hailey", "hailey@gmail.com", "087532417831", 30);
	root = newCust(root, "Ben", "benna@gmail.com", "0824234789237", 25);
	
	int choice;
	do{
		system("cls");
		printf("BlueBucks\n");
		printf("==============\n");
		printf("1. Process Order\n");
		printf("2. View All Customers\n");
		printf("3. Remove Customer\n");
		printf("4. Exit\n");
		printf(">>");
		scanf("%d", &choice); getchar();
		switch(choice){
			case 1:
				root = processOrder(root);
				printf("Press enter to continue..."); getchar();
				break;
			case 2:
				if(root == NULL) {
        			printf("There is no data!\n");
    			} 
				else {
        			printHeader();
        			viewCust(root);
    			}
    			printf("Press enter to continue..."); getchar();
				break;
			case 3:
				if(root == NULL) {
        			printf("There is no data!\n");
    			} 
    			else{
    				printf("Input phone number: ");
    				scanf("%s", phoneNum); getchar();
    				root = removeCust(root, phoneNum);	
				}
				printf("Press enter to continue..."); getchar();
				break;
		}
	}while(choice != 4);
}
