 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//ate 와 app
#include <fstream>
#include <iostream>
#include <string>

int main(){
    //두 파일에는 모두 abc라고 써 있었습니다. 
    std::ofstream out("test.txt.txt",std::ios::app);
    std::ofstream out2("other.txt",std::ios::out);

    out.seekp(3, std::ios::beg);//파일 위치 지정자를 앞에서 3칸 떨어진 곳으로 이동
    out2.seekp(3, std::ios::beg);

    out<<"추가";
    out2<<"추가";

    return 0;

//app을 사용한 경우 abc 바로 뒤에 '추가' 문자열이 붙어 있는 것으로 나타남.
//app 모드로 읽었을 때 현재 파일은 빈 파일이라 생각되어 위치 지정자라 움직일 곳이 없기에,
//실제로 위치 지정자는 움직이지 않고 출력.

//ate를 사용한 경우 3칸 띄어진 곳에서 '추가'라고 문자열이 출력된 반면 기존의 abc라는 데이터는 지워짐.
//ate는 기존 파일의 내용을 보존하지 않음.
}
