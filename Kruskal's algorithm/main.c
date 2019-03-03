#include <stdio.h>

int convert_from_greater_to_less(int b1, int b2, char input[]) {
    int result = 0;
    for (int i = 0; i < input.length(); i++) {
        
    }
    return result;
}

int convert_from_less_to_greater(int b1, int b2, char input[]) { //b1 is less 
    int result = 0;
    for (int i = 0; i < input.length(); i++) {
        result += input[i] * pow(b1, input.length() - i);
    }
    return result;
}

int pow (int a, int b) {
    
}

int main()
{
    FILE *myfile; // указатель на файл 
    myfile = fopen("in.txt", "r");
    
    int b1, b2;
    fgets(b1,) //TODO чтение переменных инт
    char mystring[13]; 
    if(b1 > 1 && b2 > 1 && b1 < 17 && b2 < 17) {
        fgets(mystring ,13, myfile); //остановится ли если символов меньше 12
        char first[12];  //инициализированно ли 0 ? 
        char second[11];
        int flag = 0;
        for (int i = 0; mystring[i] != '.' ; i++) {
                if(mystring[i] >= 'a' && mystring[i] <= 'g' && b1 > 10) {
                    first[i] = 'g' - (int) (mystring[i]); //нужно ли приведение типа
                } else if(mystring[i] >= 'A' && mystring[i] <= 'G' && b1 > 10) {
                    first[i] = 'G' - (int) (mystring[i]);
                } else if(mystring[i] >= '0' && mystring[i] <= '9') {
                    first[i] = mystring[i];
                } else {
                    //cout << "bad input" 
                    break; // выйдет ли из основного ифа ? 
                }
                if(mystring[i+1] == '.') {
                flag = i + 1;
            
            }
        }
        
        if(flag != 0) { //функция для переписи, аргументы second/first, mystring. Эта для second
            for (int i = flag; i < mystring.length(); i++) {
                if(mystring[i] >= 'a' && mystring[i] <= 'g' && b1 > 10) {
                    secong[i] = 'g' - (int) (mystring[i]); //нужно ли приведение типа
                } else if(mystring[i] >= 'A' && mystring[i] <= 'G' && b1 > 10) {
                    second[i] = 'G' - (int) (mystring[i]);
                } else if(mystring[i] >= '0' && mystring[i] <= '9') {
                    second[i] = mystring[i];
                } else {
                    //cout << "bad input" 
                    break; // выйдет ли из основного ифа ? 
                }
            }
        }
    else {
        //cout << "bad input"
    }
    } else{
        //cout << "bad input"
    }
    fclose(myfile);
    return 0;
}
