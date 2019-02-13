#include "something.h"

int main() {
	FILE *input_file = fopen("in.txt", "r");
	FILE *output_file = fopen("out.txt", "a");

	if (input_file == NULL) {
		fputs("no such file", output_file);
		return 0;
	}

    list *arr[256]; 
    for(int i = 0; i < 256; i++) {
        arr[i] = (list *) malloc (sizeof (list)); 
        arr[i]->next = NULL;
    }
    
    char target[1000];
    fgets(target, 1000, input_file); 
    int target_hash = get_hash(target);
    
	while ( !feof(input_file)) {
	  char curr[1000];
      fgets(curr, 1000, input_file); 
      add_beg(arr[get_hash(curr)], curr, strlen(curr)); 
    }
    
    fputs(find(target, arr[target_hash]) ? "YES" : "NO", output_file);
    
	fclose(input_file);
	fclose(output_file);

	return 0;
}