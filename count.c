#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "count.h"

struct Element{
	uint64_t key;
	uint64_t value;
	char address[1000];
	struct Element *next;
};
struct Element* table[1000];

int count = 0;

struct Element* create(int tmpkey, uint64_t num, char hex[]){
	struct Element* e = (struct Element *)malloc(sizeof(struct Element));
        e->key = tmpkey;
        e->value = num;
        memcpy(e->address, hex, strlen(hex)+1);
	e->next = NULL;
        return e;
	
}

int insert(uint64_t num, char hex[]){
	uint64_t tmpkey = num % 1000;
	struct Element* curr = table[tmpkey];
	while(curr != NULL){
		if(curr->value == num){
			return count;
		}else if(curr->next == NULL){
			curr->next = create(tmpkey, num, hex);
			count++;
			return count;
		}else{
			curr = curr->next;	
		}
	}
	table[tmpkey] = create(tmpkey, num, hex);
	count++;
	return count;
}

void destroy(){
	int i;
	struct Element* ptr;
	for(i = 0; i < 1000; i++){
		while(table[i] != NULL){
			ptr = table[i];
			table[i] = table[i]->next;
			free(ptr);
		}								
	}
	return;
}

int main(int argc, char *argv[]){

	char hex[1000];
	uint64_t num;
	
	FILE *file;
	file = fopen(argv[1], "r");

	if(file == NULL){
		printf("error");
		return 0;
	}

	while(fgets(hex, 1000, file) !=NULL ){
		num = strtoul(hex, NULL, 16);
		if(strcmp(hex,"\n") != 0){
			insert(num, hex);
		}
	}
	
	printf("%d\n", count);
	fclose(file);
	destroy();
	return 0;
}
