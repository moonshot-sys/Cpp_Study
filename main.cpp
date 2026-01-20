 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//조작자의 사용
#include <iostream>
#include <string>

int main(){
  int t;
  while (true){
    std::cin >> std::hex >> t; //거창하게 하지 않고 hex가 cin에서 수를 받는 방식을 바꾸었다.
                               //이처럼 스트림을 조작하여 입력 혹은 출력 방식을 바꿔주는 함수를 조작자라고 부른다.
                               //hex는 함수다!!. 
                               //앞선 형식플래그 hex와 이 hex는 이름만 같지 아예 다른 것이다.
                               //그래서 ios_base::hex로 사용한것이다.
                               //형식 플래그 hex는 ios_base에 선언되어 있는 단순한 상수 '값'이다.
                               //반면 조작자 hex의 경우 ios에 정의되어 있는 '함수'이다.
                               //이 조작자 hex의 정의를 살펴보자면, ios_base 객체를 레퍼런스로 받고, 다시 그 객체를 리턴하도록 정의
                               //std::ios_base& hex(std::ios_base& str); 
    std::cout << "입력:: " << t << std::endl;
    if(std::cin.fail()){
        std::cout<<"제대로 입력해주세요"<<std::endl;
        std::cin.clear();//플래그들을 초기화 하고
        std::cin.ignore(100, 'n'); //개행 문자가 나올때까지 무시한다.
    }
    if(t==0) break;
  }
}
