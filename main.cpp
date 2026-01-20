 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//getline 으로 읽어들이기
#include <fstream>
#include <iostream>
#include <string>

int main(){
    //파일 읽기 준비
    std::ifstream in("test.txt.txt");
    char buf[100];

    if(!in.is_open()){
        std::cout<<"파일을 찾을 수 없습니다!"<<std::endl;
        return 0;
    }

    while(in){
        in.getline(buf, 100, '.'); //getline 함수는 파일에서 개행문자 (\n)이 나올때까지
                              // 최대 지정한 크기 -1 만큼 읽게 된다. 
                              //이유는 buf의 맨 마지막 문자로 널 종료 문자를 넣어줘야 하기 떄문에
                              //이 경우 buf에 최대 99 글자 까지 입력을 받는다.
                              //이 밖에도 내가 지정한 문자까지 읽는 것으로 바꿀 수 있다.
                              //in.getline(buf, 100, '.');
                              //마침표가 나올 때 까지 입력 받음.
        std::cout << buf <<std::endl;
    }
    return 0;
}