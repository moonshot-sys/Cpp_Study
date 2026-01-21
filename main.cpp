//이 파일은 연습용이다.
// 틀려도 되고, 정리 안 해도 된다.

//벡터 클래스
class Vector{
    string* data;
    int capacity;
    int length;

    public:
    //생성자
    Vector(int n =1); //사용자가 인자를 지정하지 않으면 알아서 n=1이 되게 지정 
                      //Vector a() Vector a(1)과 동일한 작업.
                      //해당 인자의 기본 값을 지정해 놓은 것을 디폴트 인자 라고 한다.
                      //유의 사항으로는 클래스 내부 함수 선언에서 디폴트 인자를 명시하였다면
                      //함수 본체에서 명시하면 안되고
                      //반대로 함수 본체에서 명시하였다면
                      //클래스 내부 함수 선언에 명시하면 안된다.


    //맨 뒤에 새로운 원소를 추가한다.
    void push_back(string s);

    //임의의 위치의 원소에 접근한다.
    string operator[] (int i);

    // x 번째 위치한 원소를 제거한다.
    void remove(int x);

    //현재 벡터의 크기를 구한다.
    int size();

    ~Vector();
};

void Vector::push_back(string s){
    if (capacity <= length){
        string* temp =new string[capacity *2];
        for (int i = 0; i<length ; i++){
            temp[i] = data[i];
        } 
        delete[] data;
        data= temp;
        capacity *-2;
    }
    data[length] = s;
    length++;
}

string Vector::operator[](int i){return data[i]; }

void Vector::remove(int x){
    for (int i = x+1; i <length; i++){
        data[i - 1] = data[i];

    }
    length--;
}

int Vector::size() {return length;}

Vector::~Vector(){
    if (data){
        delete[] data;
    }
}

//스택 클래스

class Stack{
    struct Node{
        Node* prev;
        string s;

        Node(Node* prev, string s ) : prev(prev), s(s){}
    };

    Node* current; //최상위 노드들을 가리키게 한다.
    Node start; //최하위 노드를 가리키게 한다. 이는 마지막 노드에 도달하였을때 
                //그 여부를 알아야 하기 때문이다.

    public:
        Stack();

        //최상단에 새로운 원소를 추가한다.
        void push(string s);

        //최상단의 원소를 제거하고 반환한다.
        string pop();

        //최상단의 원소를 반환한다. (제거 안함)
        string peek();

        //스택이 비어있는지의 유무를 반환한다.

        bool is_empty();

        ~Stack();
};

Stack::Stack() : start(NULL,""){current =&start;}
void Stack::push(string s){
    Node* n = new Node(current, s);
    current = n;
}
string Stack::pop(){
    if (current == &start) return "";

    string s = current->s;
    Node* prev =current;
    current = current->prev;

    //Delete pooped node
    
    delete prev;
    return s;
}

string Stack::peek() {return current ->s; }
bool Stack::is_empty(){
    if(current == &start) return ture;
    return false;
}
Stack::~Stack(){
    while (current != &start){
        Node* prev =current;
        current = current->prev;
        delete prev;
    }
}

/*/ 주의 할 점은 소멸자에서 최상위 원소 부터 줄줄이 바닥에 도달할
때까지 메모리에서 해제 시켜야 완전히 Stack 객체를 소멸 시킬 수 있다./*/