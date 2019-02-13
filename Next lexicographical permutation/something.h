#ifndef H_SOMETHING
#define H_SOMETHING

#include <stdio.h>

int NextPermutation(char *s, int len) 
{
    int f, l;
    f = len - 2;
    l = len - 1;
    while(((int)s[f] >= (int)s[f + 1]) && (f >= 0)) //ищем с конца где нарушается упорядоченность
        f--;
    if(f < 0) //упорядочена по убыванию, больше перестановок нет
        return 0;
    while((int)s[l] <= (int)s[f]) //ищем первое число больше отмеченного f
        l--;
    char temp;
    temp = s[f]; //меняем местами эти два числа
    s[f] = s[l];
    s[l] = temp;
    l = len - 1;
    for (f++; f < l; f++, l--) { //оставшиеся числа упорядочим в порядке возрастания
        temp = s[f];  //они были упорядочены по убыванию, достаточно перевернуть отрезок
        s[f] = s[l]; 
        s[l] = temp;
        return 1; //следущая перестановка существует
    }
}

#endif