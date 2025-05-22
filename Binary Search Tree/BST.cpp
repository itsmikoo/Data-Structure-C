#include <stdio.h>
#include <stdlib.h>

struct node{
	int val;
	struct node *left, *right;
};

struct node *findPredecessor(struct node *curr){
	while(curr->right!=NULL){
		curr=curr->right;
	}
	return curr;
}

struct node *insertBST(struct node *curr, int val){
	if(curr==NULL){
		struct node *newNode = (struct node*)malloc(sizeof(struct node));
		newNode->val = val;
		newNode->left = NULL;
		newNode->right = NULL;
		curr = newNode;
	}
	else if(val<curr->val){
		curr->left = insertBST(curr->left, val);
	}
	else if(val>curr->val){
		curr->right = insertBST(curr->right, val);
	}
	return curr;
}

struct node *deleteBST(struct node *curr, int val){
	struct node *temp;
	
	if(curr==NULL){
		printf("Data is not found\n");
	}
	else if(val<curr->val){
		curr->left = deleteBST(curr->left, val);
	}
	else if(val>curr->val){
		curr->right = deleteBST(curr->right, val);
	}
	else{
		if(curr->left==NULL && curr->right==NULL){
			free(curr);
			curr = NULL;
		}
		else if(curr->right==NULL){ //punya hanya anak kiri
			temp = curr;
			curr=curr->left;
			free(temp);
		}
		else if(curr->left==NULL){ //punya hanya anak kanan
			temp = curr;
			curr = curr->right;
			free(temp);
		}
		else{ //punya both anak kiri and anak kanan
			temp = findPredecessor(curr->left);
			curr->val = temp->val;
			curr->left = deleteBST(curr->left, curr->val);
		}
	}
	return curr;
}

void inOrder(struct node *curr){
	if(curr!=NULL){
		inOrder(curr->left);
		printf("%d ", curr->val);
		inOrder(curr->right);
	}
}

int main(){
	struct node *root = NULL;
	root = insertBST(root, 20);
	root = insertBST(root, 10);
	root = insertBST(root, 30);
	root = insertBST(root, 25);
	inOrder(root);
	printf("\n");
	root = deleteBST(root, 10);
	inOrder(root);
	printf("\n");
	
	return 0;
}
