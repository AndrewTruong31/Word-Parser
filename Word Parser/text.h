#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Name: Andrew Truong
* Student #: 1049488
* Email: atruon03@uoguelph.ca
*/

struct node_struct{
    void *data;
    struct node_struct *next;
        
};


struct node_struct *txt2words(FILE *fp);
struct node_struct *search(struct node_struct *list, char *target, int (*compar)(const void*, const void*));
struct node_struct *copy(struct node_struct *start, struct node_struct *end);
void ftext(FILE *fp, struct node_struct *list);
struct node_struct *sort(struct node_struct *list, int (*compar) (const void*, const void*));
void remove_repeats(struct node_struct *list, int (*compar) (const void*, const void*));
int length(struct node_struct *list);
void free_list(struct node_struct *list, int free_data);

char *get_word( char **in );
int checkLegal(char in);
int checkWordSize(char *in);
void printList(struct node_struct *ptr);
void freeList(struct node_struct *ptr);
int checkCharacter(char in);
void split(struct node_struct *in, struct node_struct **out1, struct node_struct **out2);
struct node_struct *sorted(struct node_struct *a, struct node_struct *b, int (*compar) (const void*, const void*));




