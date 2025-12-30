/*상수 포인터?*/
#include<iostream>

void swap(int*a, int *b){
    int temp =*a;
    *a=*b;
    *b=temp;
}

int main(){
    int x = 10, y=20;
    swap(&x, &y);

    std::cout << x <<" " <<y<< std::endl;
    return 0;
}
