#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <string>
using std::string;

namespace MyExcel{class Vector {
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

         string data;

    public:
        virtual string strigify();
        virtual int to_numeric();
        
        Cell(string data, int x, int y, Table* table);

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

}

#endif