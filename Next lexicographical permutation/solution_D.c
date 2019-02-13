#include "something.h"

int main()
{
    FILE *myfile = fopen("in.txt" , "r");
    FILE *outputfile = fopen("out.txt", "a");
   
   if (myfile == NULL) {
       fputs("bad input", outputfile);  
       return 0;
   }

    char s[12];
    fgets(s,12,myfile); 
    int N;
    fscanf(myfile,"%d",&N); 
    
    int len = 0;
    for (int i = 0; s[i] != '\n'; i++) {
        len++;
    }
    
    for(int i = 0; i < len; i++) { //проверяем, является ли введенная строка перестановкой
       if((int)s[i] >= '0' && (int)s[i] <= '9') {
            for(int j = i + 1; j < len; j++) {
                if((int)s[i] == (int)s[j]) {
                    fputs("bad input", outputfile);  
                    return 0;
                }
       }
    } else {
            fputs("bad input", outputfile);  
           return 0;
       }
   }
    
    while(N && NextPermutation(s, len)) { //пока перестановка есть и мы не вывели N штук
       fputs(s, outputfile);
       N--;
   }
    
    fclose (myfile);
    fclose (outputfile);
    return 0;
}
