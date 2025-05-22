#include <stdio.h>
#include <stdlib.h>

struct node{
	int val;
	struct node *left, *right;
	int height;
};

int max(int a, int b){
	if(a>=b) return a;
	else return b;
}

int getHeight(struct node *curr){
	if(curr==NULL) return 0;
	else return curr->height;
}

int getBFactor(struct node *curr){
	return getHeight(curr->left) - getHeight(curr->right);
}

struct node *rightRotate(struct node *a){
	struct node *b = a->left;
	struct node *c = b->right;
	b->right = a;
	a->left = c;
	
	a->height = max(getHeight(a->left), getHeight(a->right))+1;
	b->height = max(getHeight(b->left), getHeight(b->right))+1;
	
	return b;	
}

struct node *leftRotate(struct node *a){
	struct node *b = a->right;
	struct node *c = b->left;
	b->left = a;
	a->right = c;
	
	a->height = max(getHeight(a->left), getHeight(a->right))+1;
	b->height = max(getHeight(b->left), getHeight(b->right))+1;
	
	return b;	
}

struct node *insertAVL(struct node *curr, int val){
	if(curr==NULL){
		struct node *newNode = (struct node*)malloc(sizeof(struct node));
		newNode->val = val;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 1;
		curr = newNode; //atau blh langsung return newNode;
	}
	else if(val < curr->val){
		curr->left = insertAVL(curr->left, val);
	}
	else if(val > curr->val){
		curr->right = insertAVL(curr->right, val);
	}
	
	curr->height=max(getHeight(curr->left), getHeight(curr->right))+1; //gbs curr->left->height, curr->right->height krn bisa aja isinya NULL, nnti error
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

void inorder(struct node *curr){
	if(curr!=NULL){
		inorder(curr->left);
		printf("%d(%d) ", curr->val, curr->height);
		inorder(curr->right);
	}
}

struct node *findPredecessor(struct node *curr){
	while(curr->right!=NULL){
		curr = curr->right;
	}
	return curr;
}

struct node *deleteAVL(struct node *curr, int val){
	if(curr==NULL){
		printf("Data is not found");
	}
	else if(val < curr->val){
		curr->left = deleteAVL(curr->left, val);
	}
	else if(val > curr->val){
		curr->right = deleteAVL(curr->right, val);
	}
	else{
		struct node *temp=NULL;
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
			curr->val = temp->val;
			curr->left = deleteAVL(curr->left, temp->val); 
		}
	}
	
	curr->height=max(getHeight(curr->left), getHeight(curr->right))+1; //gbs curr->left->height, curr->right->height krn bisa aja isinya NULL, nnti error
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

int main(){
	struct node *root = NULL;
	root = insertAVL(root, 10);
	root = insertAVL(root, 20);
	root = insertAVL(root, 30);
	inorder(root);
	puts("");
	root = insertAVL(root, 25);
	root = insertAVL(root, 27);
	inorder(root);
	puts("");
	root = deleteAVL(root, 25);
	root = deleteAVL(root, 20);
	inorder(root);
	return 0;
}
