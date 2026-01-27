#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <string>
using std::string;

namespace MyExcel{
    class Vector {
        string* data;
        int capacity;
        int length;

        public:
        //생성자 
        Vector(int n = 1);

        //맨 뒤에 새로운 원소를 추가한다.
        void push_back(string s);

        //임의의 위치의 원소에 접근한다.
        string operator[](int i);

        // x 번째 위치한 원소에 접근한다.
        void remove(int x);

        //현재 벡터의 크기를 구한다.
        int size();

        ~Vector();
    };

    class Stack {
        struct Node{
            Node* prev;
            string s;

            Node(Node* prev, string s ): prev(prev), s(s) {}
        };

        Node* current;
        Node start;

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
    class NumStack {
        struct Node{
            Node* prev;
            double s;

            Node(Node* prev, double s ) : prev(prev), s(s){}
        };

        Node* current;
        Node start;

        public:
        NumStack();
        void push(double s);
        double pop();
        double peek();
        bool is_empty();
      
        ~NumStack(); 
    };

    class Table;
    
    class Cell{
    protected:
        int x,y;
        Table* table;

    public:
        virtual string stringify() = 0;
        virtual int to_numeric() = 0;
        
        Cell( int x, int y, Table* table);

};


    
class Table {
    protected:
    //행 및 열의 최대 크기
    int max_row_size, max_col_size;

    //데이터를 보관하는 테이블
    //Cell* 을 보관하는 2차원 배열이라 생각하면 편하다.
    Cell*** data_table;

    public:
    Table(int max_row_size, int max_col_size);
    
    ~Table();

    //새로운 셀을 row 행 col 열에 등록한다.
    void reg_cell(Cell* c, int row, int col);

    //해당 셀의 정수값을 반환한다.
    //s : 셀이름(Ex, A3, B6 과 같이)
    int to_numeric(const std::string& s);

    //행 및 열번호로 셀을 호출한다.
    int to_numeric(int row, int col);

    //해당 셀의 문자열을 반환한다.
    string stringify(const string& s);
    string stringify(int row, int col);

    virtual std::string print_table() =0;

};

class TxtTable : public Table{
    string repeat_char(int n, char c);

    //숫자로 된 배열 번호를 A,B, .... Z, AA, AB, ... 이런 순으로 매겨준다.
    string col_num_to_str(int n);

    public:
     TxtTable(int row, int col);

     //텍스트로 표를 깨끗하게 출력해준다.

     string print_table();
};

class HtmlTable : public Table{
    public:
        HtmlTable(int row, int col);

        string print_table();
};

class CSVTable : public Table{
    public:
    CSVTable(int row, int col);
    string print_table();
};
class StringCell : public Cell{
    string data;

    public:
        string stringify();
        int to_numeric();

        StringCell(string data, int x, int y, Table* t);
};
class NumberCell : public Cell{
    int data;

    public:
        string stringify();
        int to_numeric();

        NumberCell(int data, int x, int y, Table* t);
};
class DateCell : public Cell{
    time_t data;

    public:
        string stringify();
        int to_numeric();

        DateCell(string s, int x, int y, Table* t);
};
class ExprCell : public Cell{
    string data;
    string* parsed_expr;

    Vector exp_vec;

    //연산자 우선 순위를 반환합니다.
    //precednece 함수는 입력받은 연산자의 우선순위를 반환한다.
    int precedence(char c);

    //수식을 분석합니다.
    //parse_expression 함수는 수식을 분석해서 계산하기 편하게 해주는 함수다.

    void parse_expression();

    public:
    ExprCell(string data, int x, int y, Table* t);

    string stringify();
    int to_numeric();

    /*중위 표기법과 후위 표기법
    중위 표기법 : 3+4*5+4*(7-2)
    컴퓨터의 경우 이를 계산하는데 조금 어려울 수 있다.
    괄호를 우선 계산하고, *와/를 계산하고 그리고 +,-의 우선순위로 나누어서 계산해야함.
    이처럼 피연산자와 피연산자 사이에 연산자를 넣는 형태로
    수식을 표현하는 방법을 중위표기법이라고 한다.

    후위 표기법 : 345*+472-*+
    다른점 : 연산자들이 피연산자들 뒤에 있다., 괄호가 없다.
    컴퓨터가 계산하는 법.
    1.피연산자를 만나면 스택에 push한다.
    2.연산자를 만나면 스택에서 두 개를 pop 한 뒤에 그 둘에 해당 연산을 한 후 
    그 결과를 다시 스택에 push 한다.
    */
};

}

#endif