#include "text.h"
/*
* Name: Andrew Truong
* Student #: 1049488
* Email: atruon03@uoguelph.ca
*/


struct node_struct *txt2words(FILE *fp){ /* converts the textfile into a linked list of words */
    char *word = NULL;
    char *string;
    int mem;

    struct node_struct *head, **ptr;
    ptr = &head;

    string = calloc(1,256);

    while(fgets(string, 256, fp) != NULL){ /* will copy a line of text from the file */

        while(strlen(string) > 0){ /* keeps running until there are no more words in the string */
            word = get_word(&string);
            
            *ptr = calloc(sizeof(struct node_struct),1); 
            (*ptr)->data = word;
            ptr = &(( *ptr)->next);            
        }
        *ptr = NULL;

    }

    if(feof(fp))
        printf("End of file\n");
    else 
        printf("Something went wrong\n");

    fclose(fp);
    return head;
}

int length(struct node_struct *list){ /* goes through the linked list counting every node */
    int count = 0;
    while(list){
        count ++;
        list = list->next;
    }
    return count;

}

/* Uses merge sort to sort whatever is in the linked list */
struct node_struct *sort(struct node_struct *list, int (*compar) (const void*, const void*)){
    struct node_struct *head = list;
    struct node_struct *a;
    struct node_struct *b;
    int half = 0;
    int i;

    if((head == NULL) || (head->next == NULL)){
        return list;
    }

    /* splits the linked list into 2 smaller ones */
    a = head;  
    half = (length(list)/2);

    for(i = 0; i < half-1; i ++){
        head = head->next;
    }

    b = head->next;
    head->next = NULL;

    /* recursively calls itself until there is 1 or no words left */
    a = sort(a,compar);
    b = sort(b,compar);

    list = sorted(a,b,compar);    
    

    return list;
}

/* compares the nodes and sorts them accordingly forming another linked list */
struct node_struct *sorted(struct node_struct *a, struct node_struct *b, int (*compar) (const void*, const void*)){
    struct node_struct *res = NULL;

    if(a == NULL){
        return b;
    }else if(b == NULL){
        return a;
    }

    /* uses the strcasecmp function to determine the value */
    if(compar(a->data,b->data) <= 0){
        res = a;
        res->next = sorted(a->next,b,compar);
    }else{
        res = b;
        res->next = sorted(a, b->next, compar);
    }

    return res;
}


/* removes consecutive repeated words */
void remove_repeats(struct node_struct *list, int (*compar) (const void*, const void*)){
    struct node_struct *temp;

    while(list){
        if(list->next){
            if(compar(list->data,list->next->data) == 0){
                temp = list->next;
                list->next = ((struct node_struct *)(list->next))->next;
                free(temp->data);
                free(temp);
            }
        }
        list = list->next;
    }
}

/* prints out everything in the linked list following some rules */
void ftext(FILE *fp, struct node_struct *list){
    char *word, *nextWord;
    int length = 0;
    if(list != NULL){
        while (list){
            word = list->data;
            length += strlen(word);
            /* prints a new line every 80 characters */
            if(length >= 80){
                printf("\n");
                length = 0;
            }
            if(strcmp(word,"\n") == 0) length = 0;

            /* checks if the next word exists */
            if(list->next) nextWord = (list->next)->data;

            /* checks if the last character is followed by another character*/
            if(checkCharacter((char)(word[strlen(word)-1])) && 
                checkCharacter((char)(nextWord[0]))){
                printf("%s", word);
                printf(" ");

            /* checks if it is puncuation */
            }else if((strcmp(word,",") == 0 || strcmp(word, "!") == 0 ||
                strcmp(word, "\"") == 0 || strcmp(word,".") == 0 || 
                strcmp(word, ";") == 0)){
                    if(strcmp(nextWord, "--") != 0 || strcmp(nextWord, "\"") != 0){
                        printf("%s", word );
                        printf(" ");
                   
                    }else{
                        printf("%s", word );
                    }
            
                    
            }else printf("%s" ,word);
            
            list = list->next;

        
        }
        printf("\n");
    }
}

/* copies a linked list into a shallow copy of another linked list */
struct node_struct *copy(struct node_struct *start, struct node_struct *end){
    struct node_struct *head, **ptr;
    ptr = &head;

    while(start){
        if(start == end) break;
        *ptr = malloc(sizeof(struct node_struct));
        (*ptr)->data = start->data;
        ptr = &((*ptr)->next);

        start = start->next;
    }

    return head;
}

/* searches for all instances of the target and puts them into a linked list */
struct node_struct *search(struct node_struct *list, char *target, int (*compar)(const void*, const void*)){
    struct node_struct *head, **ptr;
    head = NULL;
    ptr = &head;

    while(list){
        if(compar(target, list->data) == 0){

            *ptr = malloc(sizeof(struct node_struct));
            (*ptr)->data = list;
            ptr = &((*ptr)->next);
        }
        list = list->next;
    }
    
    *ptr = NULL;

    return head;

}

/* unused/mostly used for testing */
void printList(struct node_struct *ptr){
    int count = 0;
    if(ptr != NULL){
        while (ptr){
            printf( "%s", ptr->data );
            ptr = ptr->next;
            printf("\n");
            count ++;
        }
    }else printf("could not anything matching\n");
    printf("[%d]\n",count);
}

/* will free the linked list and/or the imbeded linked list */
void free_list(struct node_struct *ptr, int free_data){
    if (free_data != 0){
        if (ptr){
            free_list((struct node_struct*)(ptr->next)->data,0);
            free_list(ptr->next,0);
            free( ptr );
        }
    }else{
        if (ptr){
            free_list(ptr->next,0);
            free( ptr );
        }
    }
    
}

/* will get the first word in a string and return it */
char *get_word(char **in){
    char temp[256] = "";
    char *word;
    int count = 0;
    char c;
    char prev; 
    c = **in;
    *in = *in + 1;
    if (c == ' '){
        c = **in;
        *in = *in + 1;
    }
    if(c == '\n'){
        strcat(temp,"\n");
        count ++;
    }

    while(strlen(*in) > 0){
        if(checkLegal(c)){
            temp[count++] = c;
            c = **in;

            if(c == '-' || c == '\''){
                prev = c;
                c = *(*in + 1);
                if(prev == c){
                    break;
                }else c = prev;
            }else if(!checkLegal(c)){
                if(c == '\n'){
                    *in = *in + 1;
                    break;
                }else if(c != ' '){
                    break;
                }
            }
            *in = *in + 1;

        }else{
            if(c == ' '){
                break;
            }else{
                temp[count++] = c;
                break;
            }
            
        }
            
    }
    
    if(**in == '\n') *in = *in + 1;
    temp[count] = '\0';
    
    word = calloc(1,count+1);
    word = strcpy(word,temp);

    return word;
}

/* checks if a character meets set requirements */
int checkCharacter(char in){
    if((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z') ||
        (in >= '0' && in <= '9')){
            return 1;
    }else return 0;
    
}

/* checks if a character meets set requirements */

int checkLegal(char in){
    if((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z') ||
        (in >= '0' && in <= '9') || (in == '\'') || (in == '-') ||
        (in == '*')){
            return 1;
    }else return 0;
}
