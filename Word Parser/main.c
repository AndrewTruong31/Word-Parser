#include "text.h"


int strcmpvoid( const void *a, const void *b ){
  char *ptr_a, *ptr_b;
  ptr_a = (char *)a;
  ptr_b = (char *)b;
  return strcasecmp( ptr_a, ptr_b );
}

int main(){

    FILE *fp; 
    struct node_struct *head;

    fp = fopen("test1.txt", "r");
    if (fp != NULL){
        head = txt2words(fp);
        head = sort(head,strcmpvoid);
        remove_repeats(head,strcmpvoid);

        ftext(fp,head);
        printf("\n%d", length(head));
        
        free_list(head,0);
    }else printf("Could not open file");

}
