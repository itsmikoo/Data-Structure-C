#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Slang{
	char word[100];
	char desc[100];
	
	struct Slang *left, *right;
};

int checkWord(char word[]){
	int len;
	len = strlen(word);
	
	if(len<=1) return 1;
	for(int i=0; i<len; i++) {
        if(word[i]==' ') return 1;
    }
    return 0;
}

int checkDesc(char desc[]){
	int count=0, len;
	len = strlen(desc);
	
	for(int i=0; i<len-1; i++){
		if(desc[i]==' ' && (desc[i+1]!=' ' && desc[i+1]!='\0')){
			count++;
		}
	}
	if(count>=2) return 0;
	return 1;
}

struct Slang *insertBST(struct Slang *curr, char word[], char desc[]){
	if(curr==NULL){
		struct Slang *newSlang = (struct Slang*)malloc(sizeof(struct Slang));
		strcpy(newSlang->word, word);
		strcpy(newSlang->desc, desc);
		
		newSlang->left = NULL;
		newSlang->right = NULL;
		curr = newSlang;
		printf("Successfully released new slang word.\n");
	}
	else if(strcmp(word, curr->word)<0){
		curr->left = insertBST(curr->left, word, desc);
	}
	else if(strcmp(word, curr->word)>0){
		curr->right = insertBST(curr->right, word, desc);
	}
	else if(strcmp(word, curr->word)==0){
		strcpy(curr->desc, desc);
		printf("Successfully updated a slang word.\n");
	}
	
	return curr;
}

struct Slang *releaseNewSlang(struct Slang *root){
	char word[100];
	char desc[100];
	
	do{
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", &word); getchar();
	}while(checkWord(word)==1);
	do{
		printf("Input a new slang word description [Must be more than 2 words]: ");
		scanf("%[^\n]", &desc); getchar();
	}while(checkDesc(desc)==1);
	
	
	root = insertBST(root, word, desc);
	return root;
}

int searchSlang(struct Slang *curr, char word[]){
	if(curr==NULL) return 1;
	
	if(strcmp(curr->word, word)==0){
		printf("\nSlang word  : %s\n", curr->word);
        printf("Description : %s\n", curr->desc);
        return 0;
	}
	if (searchSlang(curr->left, word) == 0) return 0;
	if (searchSlang(curr->right, word) == 0) return 0;
	return 1;
}

int idx;
int viewSlang(struct Slang *curr, char word[]){
	if(curr==NULL) return 0;
	
	int count = 0;
	count += viewSlang(curr->left, word);
	if(strncmp(curr->word, word, strlen(word))==0){
		printf("%d. %s\n", ++idx, curr->word);
		count++;
	}
	count += viewSlang(curr->right, word);
	
	return count;
}

void viewAllSlang(struct Slang *curr){
	if(curr==NULL) return;
	viewAllSlang(curr->left);
	printf("%d. %s\n", ++idx, curr->word);
	viewAllSlang(curr->right);
}


int main(){
	int choice, check;
	char word[100];
	struct Slang *root = NULL;
	do{
		system("cls");
		idx = 0;
		printf("Boogle Menu\n");
		printf("=================================\n");
		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang words\n");
		printf("5. Exit\n");
		printf(">>");
		scanf("%d", &choice); getchar();
		
		switch(choice){
			case 1:
				root = releaseNewSlang(root);
				break;
			case 2:
				do{
					printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
					scanf("%[^\n]", &word); getchar();
				}while(checkWord(word)==1);
				check = searchSlang(root, word);
				if(check==1) printf("\nThere is no word \"%s\" in the dictionary.\n", word);
				break;
			case 3:
				if(root==NULL){
					printf("There is no slang word yet in the dictionary.");
				}
				else{
					printf("Input a prefix to be searched: ");
					scanf("%s", &word); getchar();
					check = viewSlang(root, word);
					if(check==0) printf("\nThere is no prefix \"%s\" in the dictionary.\n", word);
				}
				break;
			case 4:
				if(root==NULL){
					printf("There is no slang word yet in the dictionary.\n");
				}
				else{
					printf("List of all slang words in the dictionary:\n");
					viewAllSlang(root);
				}
				break;
			case 5:
				printf("Thank you... Have a nice day :)\n");
				break;
			default:
				printf("Enter a valid number\n");
		}
		printf("\nPress enter to continue..."); getchar();
	}while(choice != 5);
}
