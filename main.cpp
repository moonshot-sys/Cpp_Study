 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//std::string에 정의된 getline 사용
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
    std::string s;
    while (std::getline(in,s)){//getline 함수는 ifstream에 정의되어 있는 것이 아니라
                               //std::string에 정의되어 있는 함수로
                               //첫 번째 인자로 istream 객체를 받고,
                               //두 번째 인자로 입력 받은 문자열을 저장할 string 객체를 받는다.
        std::cout<<s<<std::endl;
    }
    return 0;
}//주의사항 ** while 문 조건으로 절대 in.eof()를 사용하면 안된다.
// eof 함수는 파일 위치 지시자가 파일에 끝에 도달한 이후에 true를 리턴하기 때문이다.
//in.eof()는 while 문 안에서 파일 읽기가 안전하다 라는 것을 보장하지 않는다.