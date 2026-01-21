 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//파일에 쓰기
#include <fstream>
#include <iostream>
#include <string>

int main(){
    //파일 쓰기 준비
    std::ofstream out("test.txt.txt");

    std::string s;
    if(out.is_open()){
        out<< "이걸쓰자~~";
    }
    return 0;
}
//이 경우 파일이 존재한다면 파일의 내용을 다 지우고 새로운 내용으로 덮어 쓰게 된다.
//파일이 존재 하지 않으면 파일을 새롭게 생성하고 성공했다면 출력한다.
    