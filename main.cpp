#include <iostream>

// 1. 구조체 선언: 3차원 좌표를 담는 그릇
struct Vector3 {
    float x, y, z;

    // 생성자: 초기화 안 하면 쓰레기 값 들어가는 거 알지?
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // 2. 함수: 벡터 정보 출력
    void Print() {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};

// 3. 기능: 벡터 덧셈 (연산자 오버로딩은 나중에 하고, 일단 함수로)
Vector3 Add(Vector3 a, Vector3 b) {
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

int main() {
    // 테스트: 내 위치와 이동할 방향
    Vector3 myPos(0.0f, 0.0f, 0.0f);
    Vector3 moveDir(1.5f, 2.0f, -5.0f);

    // 이동 결과 계산
    Vector3 newPos = Add(myPos, moveDir);

    std::cout << "Original Position: ";
    myPos.Print();

    std::cout << "New Position: ";
    newPos.Print();

    return 0;
}