#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define size 1007

int bookIdx = 1;

struct Book{
	char title[100];
	char author[100];
	char isbn[20];
	char id[50];
	int pageNum;
	int hashKey;
	
	struct Book *next;
}*library[size+1]={NULL}, *head=NULL, *tail=NULL;

char* hashFunction(char author[], char title[], char isbn[]){
	char X[50], A, T;
	static char hashkey[50];
	snprintf(X, sizeof(X), "B%.5d", bookIdx++);
	A = toupper(author[0]);
	T = toupper(title[0]);
	
	snprintf(hashkey, sizeof(hashkey), "%s-%s-%c%c", X, isbn, A, T);
	return hashkey;
}

int getHash(char id[]){
	int ascii = 0;
	int len = strlen(id);
	for(int i=0;i<len;i++){
		ascii += (int)id[i];
	}
	return ascii%size;
}

int checkTitle(char title[]){
	for(int i=0;i<size;i++){
		struct Book *temp = library[i];
		while(temp!=NULL){
			if(strcmp(temp->title, title)==0){
				return 1;
			}
			temp = temp->next;
		}
	}
	return 0;
}

void viewBook(){
	int isEmpty = 1;
	
	for(int i=0;i<size;i++){
		struct Book *temp = library[i];
		if(temp){
			isEmpty = 0;
			break;
		}
	}
	
	if(isEmpty==1){
		printf("There's no book(s)\n");
	}
	else{
		printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("|%-25s|%-50s|%-25s|%-18s|%-12s|\n", "Book ID", "Book Title", "Book Author", "ISBN", "Page Number");
		printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<size;i++){
			struct Book *temp = library[i];
			while(temp != NULL){
				printf("|%-25s|%-50s|%-25s|%-18s|%-12d|\n", temp->id, temp->title, temp->author, temp->isbn, temp->pageNum);
				printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
				temp = temp->next;
			}
		}
	}
	printf("\nPress Enter to continue..."); getchar();
}

void insertBook(){
	char title[100];
	char author[100];
	char isbn[20];
	int pageNum;
	int hashKey;
	int len;
	int un;
	int ch;
	do{
		printf("Input book title[5-50][unique]: ");
		scanf("%[^\n]", title); getchar();
		len = strlen(title);
		un = checkTitle(title);
		if(un == 1){
			printf("The book title already exists\n");
		}
	}while(len < 5 || len > 50 || un == 1);
	
	do{
		printf("Input author name[3-25][Mr. |Mrs. ]: ");
		scanf("%[^\n]", author); getchar();
		len = strlen(author);
	}while(len<3 || len>25 || (strncmp(author, "Mr. ", 4) != 0 && strncmp(author, "Mrs. ", 5) != 0));
	
	do{
		printf("Input ISBN[10-13][numeric]: ");
		scanf("%s", isbn); getchar();
		len = strlen(isbn);
		ch = 0;
		for(int i=0;i<len;i++){
			if(!isdigit(isbn[i])) ch = 1;
		}
	}while(len<10 || len>13 || ch == 1);
	
	do{
		printf("Input page number[>=16]: ");
		scanf("%d", &pageNum); getchar();
	}while(pageNum<16);
	
	char* id = hashFunction(author, title, isbn);
	hashKey = getHash(id);
	
	struct Book *newBook = (struct Book*)malloc(sizeof(struct Book));
	strcpy(newBook->author, author);
	strcpy(newBook->title, title);
	strcpy(newBook->isbn, isbn);
	strcpy(newBook->id, id);
	newBook->pageNum = pageNum;
	newBook->hashKey = hashKey;
	newBook->next = NULL;
	
	if(library[hashKey]==NULL){
		library[hashKey] = newBook;
	}
	else{
		struct Book *temp = library[hashKey];
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newBook;
	}
		
	printf("\nPress Enter to continue..."); getchar();

}

void removeBook(){
	char input[100], ans;
	printf("Input book id to delete: ");
	scanf("%[^\n]", input); getchar();
	
	int hashKey = getHash(input);
	struct Book *temp = library[hashKey];
	struct Book *prev = NULL;
	
	while(temp != NULL){
		if(strcmp(temp->id, input)==0){
			printf("\nBook Id: %s\n", temp->id);
			printf("Book Title: %s\n", temp->title);
			printf("Book Author: %s\n", temp->author);
			printf("Book ISBN: %s\n", temp->isbn);
			printf("Page Number: %d\n", temp->pageNum);
			do{
				printf("Are you sure? [y|n] ");
				scanf("%c", &ans); getchar();
				if(ans == 'y'){
					break;
				}
				else if(ans == 'n'){
					return;
				}
			}while(ans != 'y' && ans != 'n');
			
			if(prev==NULL){
				library[hashKey] = temp->next;
			}
			else{
				prev->next = temp->next;
			}
			free(temp);
			printf("Delete Success!");
			printf("\nPress Enter to continue..."); getchar();
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("Book not found !\n");
	printf("\nPress Enter to continue..."); getchar();
}

int main(){
	int choice;
	do{
		system("cls");
		printf("Bluejack Library\n");
		printf("===================\n");
		printf("1. View Book\n");
		printf("2. Insert Book\n");
		printf("3. Remove Book\n");
		printf("4. Exit\n");
		printf(">>");
		scanf("%d", &choice); getchar();
		switch(choice){
			case 1:
				viewBook();
				break;
			case 2:
				insertBook();
				break;
			case 3:
				removeBook();
				break;
			case 4:
				break;
		}
	}while(choice != 4);
}
