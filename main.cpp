 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//문자열 스트림
#include <sstream>
#include <iostream>
#include <string>

int main(){
    std::istringstream ss("123"); //이는 마치 문자열을 하나의 스트림이라 생각하게 해주는
                                  //가상화 장치
                                  //문자열 123이 기록되어 있는 입력 스트림을 생섬.
                                  //즉 파일에 123이라 기록해 놓고, 거기서 입력 받는 것과 동일
    int x;
    ss>>x; //그래서 마치 파일에서 숫자를 읽어내는 것 처럼 std::istringstream을 통해서 123을 읽어낼 수 있음.
    std::cout << "입력 받은 데이터 :: " << x << std::endl;

    return 0;
}