 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//형식플래그와 조작자
#include <iostream>
#include <string>

int main(){
  int t;
  while (true){
    std::cin.setf(std::ios_base::hex, std::ios_base::basefield);
    std::cin >>t;
    std::cout << "입력 ::" << t << std::endl;
    if(std::cin.fail()){
        std::cout <<"제대로 입력해주세요"<<std::endl;
        std::cin.clear(); //플래그들을 초기화 하고
                          //std::cin.ignore(100,'n');//개행문자가 나올때까지
                          //무시한다.
    }
    if(t==0) break;
  }
}
