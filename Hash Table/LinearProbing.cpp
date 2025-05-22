#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define size 10

struct data{
	char strings[100];
	int hashKey;
}*hashTable[size+1]={NULL};

int hashFunction(char strings[]){ //hashfunction : convert karakter pertama menjadi angka lalu modulo by size
	int hashKey;
	
	if(strings[0]>='A' && strings[0]<='Z'){
		hashKey = strings[0]-'A';
	}
	else if(strings[0]>='a' && strings[0]<='z'){
		hashKey = strings[0]-'a';
	}
	
	//division by table size
	hashKey%=size;
	return hashKey;
}

void insertHashTable(char strings[]){
	int hashKey = hashFunction(strings);
	struct data *newData = (struct data*)malloc(sizeof(struct data));
	
	strcpy(newData->strings, strings);
	newData->hashKey = hashKey;
	
	int id;
	if(hashTable[hashKey] == NULL){
		hashTable[hashKey] = newData;
	}
	else{
		id = (hashKey+1)%size;
		while(id != hashKey){
			if(hashTable[id] == NULL){
				hashTable[id] = newData;
				return;
			}
			id++;
			id%=size;
		}
		printf("Hash Table is full\n");
	}
}

void printHashTable(){
	for(int i=0;i<size;i++){
		printf("[%d] ", i);
		if(hashTable[i] == NULL){
			printf("NULL\n");
		}
		else{
			printf("%s (%d)\n", hashTable[i]->strings, hashTable[i]->hashKey);
		}
	}
	printf("\n");
}

void findData(dataS[]){
	for(int i=0;i<size;i++){
		while(hashTable[i] != NULL){
			
		}
	}
}

int main(){
	int menu;
	char nama[100];
	char dataS;
	do{
		printf("Hash table with Linear Probing\n");
		printf("=================================\n");
		printf("1. Insert new data\n");
		printf("2. Find Data\n");
		printf("Insert menu: \n");
		scanf("%d", &menu); getchar();
		
		switch(menu){
			case 1:
				printf("Insert nama: ");
				scanf("%s", &nama);
				insertHashTable(nama);
				printHashTable();
				break;
			case 2:
				printf("Insert data to be searched: ");
				scanf("%s", dataS); getchar;
				findData(dataS);
				break;
		}
	}while(menu == 1 || menu == 2);
}
