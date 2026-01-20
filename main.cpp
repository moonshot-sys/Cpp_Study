 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//조작자의 사용
#include <iostream>
#include <string>

int main(){
  std::string s;
  std::cin >>s;

  //위치 지정자를 한 칸 옮기고, 그 다음 문자를 훔쳐본다.(이 때는 움직이지 않음)
  char peek = std::cin.rdbuf()->snextc();
  if(std::cin.fail()) std::cout<<"Failed";
  std::cout<<"두 번째 단어 맨 앞글자 : " <<peek<<std::endl;
  std::cin >> s;
  std::cout<<"다시 읽으면 : "<< s << std::endl;

}
