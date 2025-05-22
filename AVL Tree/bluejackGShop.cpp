#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Game{
	char title[50];
	char genre[50];
	int stock;
	int height;
	
	struct Game *left, *right;
};

int max(int a, int b){
	if(a>=b) return a;
	else return b;
}

int getHeight(struct Game *curr){
	if(curr==NULL) return 0;
	else return curr->height;
}

int getBFactor(struct Game *curr){
	return getHeight(curr->left) - getHeight(curr->right);
}

struct Game *rightRotate(struct Game *a){
	struct Game *b = a->left;
	struct Game *c = b->right;
	b->right = a;
	a->left = c;
	
	a->height = max(getHeight(a->left), getHeight(a->right))+1;
	b->height = max(getHeight(b->left), getHeight(b->right))+1;
	
	return b;	
}

struct Game *leftRotate(struct Game *a){
	struct Game *b = a->right;
	struct Game *c = b->left;
	b->left = a;
	a->right = c;
	
	a->height = max(getHeight(a->left), getHeight(a->right))+1;
	b->height = max(getHeight(b->left), getHeight(b->right))+1;
	
	return b;	
}

struct Game *insertAVL(struct Game *curr, char title[], char genre[], int stock){
	if(curr==NULL){
		struct Game *newGame = (struct Game*)malloc(sizeof(struct Game));
		strcpy(newGame->title, title);
		strcpy(newGame->genre, genre);
		newGame->stock = stock;
		newGame->height = 1;
		
		newGame->left = NULL;
		newGame->right = NULL;
		curr = newGame;
	}
	else if(strcmp(title, curr->title)<0){
		curr->left = insertAVL(curr->left,  title, genre, stock);
	}
	else if(strcmp(title, curr->title)>0){
		curr->right = insertAVL(curr->right,  title, genre, stock);
	}
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right))+1;
	int bFactor = getBFactor(curr);
	
	if(bFactor>1 && getBFactor(curr->left)>=0){
		return rightRotate(curr);		
	}
	else if(bFactor>1 && getBFactor(curr->left)<0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	else if(bFactor<-1 && getBFactor(curr->right)<=0){
		return leftRotate(curr);
	}
	else if(bFactor<-1 && getBFactor(curr->right)>0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

int checkTitle(struct Game *curr, char title[]){
	if (curr == NULL) return 0;
	if(strcmp(curr->title, title)==0) return 1;
	if (checkTitle(curr->left, title)) return 1;
	if (checkTitle(curr->right, title)) return 1;
	return 0;
}

struct Game *insertGame(struct Game *root){
	char title[50];
	char genre[50];
	int stock;
	int height;
	int check, len;
	
	do{
		printf("Input game title[5-25][unique]: ");
		scanf("%[^\n]", &title); getchar();
		len = strlen(title);
	}while(len<5 || len>25 || checkTitle(root, title)==1);
	do{
		printf("Input game type[Action|RPG|Adventure|Card Game]: ");
		scanf("%[^\n]", &genre); getchar();
	}while(strcmp(genre, "Action")!=0 && strcmp(genre, "RPG")!=0 && strcmp(genre, "Adventure")!=0 && strcmp(genre, "Card Game")!=0);
	do{
		printf("Input game stock[>= 1]: ");
		scanf("%d", &stock);
	}while(stock<1);
	
	root = insertAVL(root, title, genre, stock);
	printf("Insert Success!\n");
	return root;
}

void viewGame(struct Game *curr){
	if (curr == NULL) return;
	viewGame(curr->left);
	printf("| %-25s| %-15s| %-10d|\n", curr->title, curr->genre, curr->stock);
	viewGame(curr->right);
}

struct Game *findPredecessor(struct Game *curr){
	while(curr->right != NULL){
		curr = curr->right;
	}
	return curr;
}

struct Game *deleteStock(struct Game *curr, char title[]){
	if(curr==NULL){
		printf("Data is not found");
	}
	else if(strcmp(title, curr->title)<0){
		curr->left = deleteStock(curr->left, title);
	}
	else if(strcmp(title, curr->title)>0){
		curr->right = deleteStock(curr->right, title);
	}
	else{
		struct Game *temp=NULL;
		if(curr->left==NULL && curr->right==NULL){
			free(curr);
			return NULL;
		}
		else if(curr->left==NULL){
			temp = curr;
			curr = curr->right;
			free(temp);
		}
		else if(curr->right==NULL){
			temp = curr;
			curr = curr->left;
			free(temp);
		}
		else{
			temp = findPredecessor(curr->left);
			strcpy(curr->title, temp->title);
			strcpy(curr->genre, temp->genre);
			curr->stock = temp->stock;
			curr->left = deleteStock(curr->left, temp->title); 
		}
	}
	
	curr->height=max(getHeight(curr->left), getHeight(curr->right))+1; 
	int bFactor = getBFactor(curr);
	
	if(bFactor>1 && getBFactor(curr->left)>=0){
		return rightRotate(curr);		
	}
	else if(bFactor>1 && getBFactor(curr->left)<0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	else if(bFactor<-1 && getBFactor(curr->right)<=0){
		return leftRotate(curr);
	}
	else if(bFactor<-1 && getBFactor(curr->right)>0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

struct Game *updateStock(struct Game *curr){
	char title[50], update[10];
	int stc, len;
	
	printf("Input game title: ");
	scanf("%[^\n]", &title); getchar();
	
	struct Game *ptr = curr;
	while(ptr!=NULL){
		if(strcmp(title, ptr->title)==0){
			printf("Current stock: %d\n\n", ptr->stock);
			printf("Input update type[add|remove][case insensitive]: ");
			scanf("%s", &update); getchar();
			len = strlen(update);
			for(int i=0;i<len;i++){
				update[i] = tolower(update[i]);
			}
			
			if(strcmp(update, "remove")==0){
				do{
					printf("Input stock to remove[1-%d]: ", ptr->stock);
					scanf("%d", &stc); getchar();
				}while(stc<1 || stc>ptr->stock);
				ptr->stock -= stc;
				printf("Data updated successfully !\n");
				if(ptr->stock==0){
					curr = deleteStock(curr, title);
					printf("%s is removed from the warehouse !\n", title);
				}
			}
			else if(strcmp(update, "add")==0){
				do{
					printf("Input stock to add[>=1]: ");
					scanf("%d", &stc); getchar();
				}while(stc<1);
				ptr->stock += stc;
				printf("Data updated successfully !\n");
			}
			return curr;
		}
		else if(strcmp(title, ptr->title)<0){
			ptr = ptr->left;
		}
		else{
			ptr = ptr->right;
		}
	}
	printf("Game not found!\n");
	return curr;
}


int main(){
	int choice;
	struct Game *root = NULL;
	do{
		system("cls");
		printf("Bluejack GShop\n");
		printf("========================\n");
		printf("1. Insert Game\n");
		printf("2. View Game\n");
		printf("3. Update Stock\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &choice); getchar();
		
		switch(choice){
			case 1:
				root = insertGame(root);
				printf("press enter to continue..."); getchar();
				break;
			case 2:
				if(root==NULL){
					printf("Warehouse is empty !\n");
				}
				else{
					printf("| %-25s| %-15s| %-10s|\n", "Game Title", "Game Genre", "Game Stock");
					viewGame(root);
				}
				printf("press enter to continue..."); getchar();
				break;
			case 3:
				root = updateStock(root);
				printf("press enter to continue..."); getchar();
				break;
			case 4:
				break;
		}
	}while(choice!=4);
}
