#ifndef H_SOMETHING
#define H_SOMETHING

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000


int get_hash(char *input) {
    int len = strlen(input);
    
    int sum_ASCII = 0;
    for(int i = 0; i < len; i++) 
        sum_ASCII += (int)input[i] / 256;
    
    return sum_ASCII / len;
}

int string_equivalence(char *s, char *c) {
    int len_s = strlen(s);
    int len_c = strlen(c);
    
    if(len_s != len_c)
        return 0;

    for(int i = 0; i < len_s; ++i) 
        if(s[i] != c[i])
            return 0;
    
    return 1;
}

typedef struct list {
    char v[MAXSIZE];
    struct list *next;
} list;

void add_beg(list* head, char *v, int len) {
	list *temp = head->next;
	
	head->next = (list *) malloc (sizeof (list));
	head->next->next = temp;
	
	for(int i = 0; i < len; i++)
	    head->next->v[i] = v[i];
}

int find(char *word, list *head) {
	struct list *current = head;

	if (head == NULL)
		exit(0);
	
	while (current->next) {
		if (string_equivalence(current->v, word)) 
			return 1;
		else 
			current = current->next;
	}
	
    return 0;	
} 

#endif