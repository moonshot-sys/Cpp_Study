 //이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//std::ofstream 연산자 오버로딩 하기
#include <fstream>
#include <iostream>
#include <string>

class Human{
    std::string name;
    int age;

    public:
    Human(const std::string& name, int age) : name(name), age(age) {}
    std::string get_info(){
        return "Name :: " + name + "/ Age :: " + std::to_string(age);
    }

    friend std::ofstream& operator<<(std::ofstream& o, Human& h);
};
std::ofstream& operator<<(std::ofstream& o, Human& h){
    o<<h.get_info();
    return o;
}

int main(){
    //파일 쓰기 준비
    std::ofstream out("test.txt.txt");
    Human h("이재범",60);
    out<< h<< std::endl;

    return 0;
}