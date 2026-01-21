#include <string>
using std::string;

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
    int to_numberic(const string& s);

    //행 및 열번호로 셀을 호출한다.
    int to_numberic(const string& s);

    //해당 셀의 문자열을 반환한다.
    string stringify(const string& s);
    string string(int row, int col);

    virtual std::string print_table() =0;

};
//일단 Table 클래스는 Cell 객체들을 2차원 배열로 보관한다.
//객체 자체를 보관하는 것이 아니라, 객체는 필요할 때마다 동적으로 생성하고
//그 객체에 대한 포인터를 2차원 배열로 보관
Cell::Cell(string daa, int x, int y, Table* table)
    :data(data), x(x), y(y), table(table) {}

string Cell::strigify() {return data;}
int Cell::to_numeric() {return 0;}

Table::Table(int max_row_size, int max_col_size) 
    : max_row_size(max_row_size), max_col_size(max_col_size){
        data_table = new Cell**[max_row_size];
        for (int i = 0; i <max_row_size; i++){
            data_table[i] = new Cell*[max_col_size];
            for (int j=0; j<max_col_size; j++){
                data_table[i][j] = NULL;
            }
        }
    }

Table::~Table(){
    for(int i = 0; i < max_row_size; i ++){
        for(int j = 0; j <max_col_size; j++){
            if(data_table[i][j]) delete data_table[i][j];
        }
    }
    for(int i = 0; i <max_row_size; i++){
        delete[] data_table[i];
    }
    delete[] data_table;
}

void Table::reg_cell