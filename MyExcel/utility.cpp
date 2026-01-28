#include "utils.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


using std::string;


namespace MyExcel{
Vector::Vector(int n) : data(new string[n]), capacity(n), length(0){}
void Vector::push_back(string s){
    if(capacity <= length){
        string* temp = new string[capacity *2];
        for (int i =0; i < length; i++){
            temp[i] = data[i];

        }
        delete[] data;
        data = temp;
        capacity *=2;
    }

    data[length] = s;
    length++;
}
string Vector::operator[](int i){return data[i];}
void Vector::remove(int x){
    for (int i = x+1; i<length; i++){
        data[i-1] = data[i];
    }
    length--;
}
int Vector::size() {return length;}
Vector::~Vector(){
    if(data){
        delete[] data;
    }
}
Stack::Stack() : start(NULL,""){current = &start;}
void Stack::push(string s){
    Node* n = new Node(current,s);
    current = n;
} 
string Stack::pop(){
    if (current == &start) return "";

    string s = current->s;
    Node* prev = current;
    current = current->prev;

    //Delete popped node
    delete prev;
    return s;

}
string Stack::peek() {return current->s;}
bool Stack::is_empty(){
    if(current == &start) return true; //current = &start로 되어 있던걸 ==로 수정(if문이니까)
    return false;
    }
Stack::~Stack(){
    while (current!=&start){
        Node* prev = current;
        current = current->prev;
        delete prev;
    }
}
NumStack::NumStack() : start(NULL,0){current = &start;}
void NumStack::push(double s){
    Node* n = new Node(current, s);
    current = n;
}
double NumStack::pop(){
    if(current ==&start) return 0;
    double s = current->s;
    Node* prev = current;
    current = current->prev;

    //Delete popped node
    delete prev;
    return s;
}

double NumStack::peek() {return current->s;}
bool NumStack::is_empty(){
    if(current == &start) return true;
    return false;
}
NumStack::~NumStack(){
    while (current != &start){
        Node* prev = current;
        current = current->prev;
        delete prev;
    }
}

//일단 Table 클래스는 Cell 객체들을 2차원 배열로 보관한다.
//객체 자체를 보관하는 것이 아니라, 객체는 필요할 때마다 동적으로 생성하고
//그 객체에 대한 포인터를 2차원 배열로 보관

Cell::Cell( int x, int y, Table* table)
    :x(x), y(y), table(table) {}

StringCell::StringCell(string data, int x, int y, Table* t)
:data(data), Cell(x,y,t){}
string StringCell::stringify() {return data;}
int StringCell::to_numeric(){return 0;}
/* NumberCell */

NumberCell::NumberCell(int data, int x, int y, Table* t):
data(data), Cell(x,y,t){}

string NumberCell::stringify() {return std::to_string(data);}
int NumberCell::to_numeric() {return data;}
/*

DataCell

*/

string DateCell::stringify(){
    char buf[50];
    tm temp;
    localtime_s(&temp, &data);
    strftime(buf, 50, "%F", &temp);

    return string(buf);

}

int DateCell::to_numeric() {return static_cast<int>(data);}

DateCell::DateCell(string s, int x, int y, Table*t): Cell(x,y,t){
    //입력받는 Date 형식은 항상 yyyy-mm-dd 꼴이라 가정한다. 
    int year = atoi(s.c_str());
    int month = atoi(s.c_str() + 5);
    int day = atoi(s.c_str() + 8);
//입력 받은 문자열을 연도, 월, 일로 구분한다.
    tm timeinfo;

    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month -1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;

    data = mktime(&timeinfo);
    //이를 바탕으로 timeinfo 객체를 초기화 한다. 
    //tm클래스는 일월년 시분초 단위로 데이터를 보관하는 클래스
    //하지만 DateCell은 time_t 형태로 데이터를 보환하고 있다.
    //이 변환을 하기 위해 mktime에 timeinfo를 전달하는 것이다.
    //time_t타입은 1970년부터 현재 시간까지 몇 초가 흘렀는지 
    //보관하는 정수형 변수.

}
ExprCell::ExprCell(string data, int x, int y, Table* t):
data(data), Cell(x,y,t){parse_expression();} //생성자 시작시 계산 시작 할 수 있도록 코드 작성
                                             

int ExprCell::to_numeric(){
    double result = 0;
    NumStack stack;

    for (int i = 0; i < exp_vec.size(); i++){//이 for문을 통해 각각의 토큰(exp_vec의 원소들)에 접근할 수s 있다.
      //parse_expression 함수를 통해 입력 받은 중위 표기법으로 되어 있는
      //수식이 후위 표기법으로 변환되어 있고
      //그 결과가 exp_vec에 저장되어 있다.
      //exp_vec은 벡터 클래스 객체로,각각의 원소가
      //후위 표기법으로 변환된 수식의 각각의 토큰이 된다.
        string s = exp_vec[i];

        //셀 일 경우
        if(isalpha(s[0])){
            stack.push(table->to_numeric(s));
        }
        //숫자 일 경우(한 자리라 가정 )
        else if (isdigit(s[0])){
            stack.push(atoi(s.c_str()));
            //각각의 토큰에 대해서 셀 이름(A3, B2)이나 숫자일 경우 스택에 push한다.
        }else{//연산자를 만날 경우 스택에서 두번 pop을 해서 해당하는 피연산자들에 해당 연산자를 적용해
              //다시 스택에 push하게 된다.
            double y = stack.pop();
            double x = stack.pop();
            switch (s[0]){
                case '+':
                    stack.push(x+y);
                    break;
                case '-':
                    stack.push(x-y);
                    break;
                case '*':
                    stack.push(x*y);
                    break;
                case '/':
                    stack.push(x/y);
                    break;
            }
        }
    }
    return stack.pop(); //모든 계산이 끝나면 스택에 최종 결과값을 pop하며 이를 return
}
int ExprCell::precedence(char c){
    switch(c){
        case '(':
        case '[':
        case '{':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return 0;
}
string ExprCell::stringify() {
   return std::to_string(to_numeric());
}
void ExprCell::parse_expression(){
    Stack stack;

    //수식 전체를 ()로 둘러 사서 exp_vec에 남아있는 연산자들이 push되게
    //해준다.
    data.insert(0,"(");
    data.push_back(')');

    for (int i =0; i<data.length(); i++){
        if(isalpha(data[i])){
            exp_vec.push_back(data.substr(i,2));
            i++;
        }else if(isdigit(data[i])){
            exp_vec.push_back(data.substr(i,1));
        }else if (data[i] =='(' || data[i] == '[' || data[i] =='{'){//Parenthesis
            stack.push(data.substr(i,1));
        }else if (data[i] == ')' || data[i] == ']' || data[i]=='}'){
            string t = stack.pop();
            while (t != "(" && t != "[" && t != "{"){
                exp_vec.push_back(t);
                t = stack.pop();
            }
        }else if(data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/'){
                while (!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i])){
                    exp_vec.push_back(stack.pop());
                }
                stack.push(data.substr(i,1));
            }
        }
    }


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

void Table::reg_cell(Cell* c, int row, int col){
    if (!(row < max_row_size && col <max_col_size)) return;

    if(data_table[row][col]){
        delete data_table[row][col];
    }
    data_table[row][col] = c;

}

int Table::to_numeric(const std::string& s){
    //Cell 이름으로 받는다.
    int col = s[0] - 'A'; /*col과 row 위치 뒤집혀 있었음 그래서 26이 아닌 2+3*(4+5-2)=23이 나옴. */
    int row = atoi(s.c_str() + 1)-1; // atoi(s.c_str() + 1 -1) 문자열의 맨 처음부터 읽기 시작했던 코드로 작성되어 있었는데
                                     // 문자열 주소를 한 칸 뒤로 옮겨서 숫자로 바꾼뒤 나중에 수학적으로 1을 빼는 코드로 변경

    if (row < max_row_size && col < max_col_size){
        if(data_table[row][col]){
            return data_table[row][col]->to_numeric();
        }
    }
    return 0;
}
int Table::to_numeric(int row, int col){
    if(row <max_row_size && col < max_col_size && data_table[row][col]){
        return data_table[row][col]->to_numeric();
    }
    return 0;
}
string Table::stringify(const string& s){
    //Cell 이름으로 받는다.
    int col = s[0] - 'A';
    int row = atoi(s.c_str() + 1)-1;

    if (row < max_row_size && col <max_col_size){
        if(data_table[row][col]){
            return data_table[row][col]->stringify();
        }
    }
    return 0;
}
string Table::stringify(int row, int col){
    if(row <max_row_size && col < max_col_size && data_table[row][col]){
        return data_table[row][col]->stringify();
    }
    return "";
}
std::ostream& operator<<(std::ostream& o, Table& table){
    o<<table.print_table();
    return o;
}

TxtTable::TxtTable(int row, int col) : Table(row, col){}
//텍스트로 표를 깨끗하게 출력해준다.

string TxtTable::print_table(){
    string total_table;

    int* col_max_wide = new int[max_col_size];
    for (int i = 0; i< max_col_size; i++){
        unsigned int max_wide =2;
        for (int j = 0; j < max_row_size; j++){
            if(data_table[j][i] && data_table[j][i]->stringify().length() > max_wide){
                max_wide = data_table[j][i]->stringify().length();
            }
        }
        col_max_wide[i] = max_wide;
    }
    //맨 상단에 열 정보 표시
    total_table += "    ";
    int total_wide = 4;
    for (int i = 0; i <max_col_size;i++){
        if(col_max_wide[i]){
            int max_len = std::max(2, col_max_wide[i]);
            total_table += " | " + col_num_to_str(i);
            total_table += repeat_char(max_len - col_num_to_str(i).length(), ' ');
            total_wide += (max_len+3);
        }
    }

    total_table +="\n";

    for(int i = 0; i<max_row_size; i++){
        total_table += repeat_char(total_wide, '-');
        total_table +="\n" + std::to_string(i+1);
        total_table += repeat_char(4- std::to_string(i+1).length(),' ');

        for (int j =0; j<max_col_size; j++){
            if(col_max_wide[j]){
                int max_len = std::max(2,col_max_wide[j]);

                string s ="";
                if(data_table[i][j]){
                    s=data_table[i][j]->stringify();
                }
                total_table += " | " +s;
                total_table += repeat_char(max_len - s.length(), ' ');
            }
        }
        total_table += "\n";
        
    }

    return total_table;
}
string TxtTable::repeat_char(int n, char c){
    string s ="";
    for (int i = 0; i<n;i++) s.push_back(c);

    return s;
}

//숫자로 된 열 번호를A,B....Z,AA,AB,.... 이런순으로 매겨준다.

string TxtTable::col_num_to_str(int n){
    string s = "";
    if(n<26){
        s.push_back('A' + n);

    }else {
        char first = 'A' + n/26 -1;
        char second = 'A' + n %26;

        s.push_back(first);
        s.push_back(second);
    }
    return s;
}

HtmlTable::HtmlTable(int row, int col):Table(row,col){}

string HtmlTable::print_table(){
    string s = "<table border='1' cellpadding='10'";
    for (int i =0; i <max_row_size; i++){
        s+="<tr>";
        for (int j=0; j<max_col_size; j++){
            s+="<td>";
            if(data_table[i][j]) s += data_table[i][j]->stringify();
            s+="</td>";
        }
        s +="</tr>";
    }
    s+="</table>";
    return s;
}

CSVTable::CSVTable(int row, int col):Table(row,col){}
string CSVTable::print_table(){
    string s ="";
    for(int i = 0; i<max_row_size; i++){
        for (int j =0; j<max_col_size; j++){
            if(j>=1) s += ",";
            //CSV 파일 규칙에 따라 문자열에 큰따옴표가 포함되어 있다면 ""로
            //치환한다.
            string temp;
            if(data_table[i][j]) temp = data_table[i][j]->stringify();

            for (int k =0; k<temp.length(); k++){
                if(temp[k]=='"'){
                    //k의 위치에 "를 한 개 더 집어넣는다.
                    temp.insert(k,1,'"');

                    //이미 추가된 "를 다시 확인하는 일이 없게 하기 위해
                    //k를 한 칸 더 이동시킨다.
                    k++;
                }
            }
            temp ='"'+temp+'"';
            s+=temp;
        }
        s+='\n';
    }
    return s;
    }
    
}

int main(){
   MyExcel::TxtTable table(5,5);

    // (0, 0)은 A1, (0, 1)은 B1 ...
    table.reg_cell(new MyExcel::NumberCell(2, 1, 1, &table), 1, 1); // B1에 2
    table.reg_cell(new MyExcel::NumberCell(3, 1, 2, &table), 1, 2); // C1에 3
    table.reg_cell(new MyExcel::NumberCell(4, 2, 1, &table), 2, 1); // B2에 4
    table.reg_cell(new MyExcel::NumberCell(5, 2, 2, &table), 2, 2); // C2에 5
    // 수식 셀 등록
    table.reg_cell(new MyExcel::ExprCell("B2 + B3 * (C2+C3-2)",3,3,&table),3,2);
    table.reg_cell(new MyExcel::StringCell("B2 + B3 * (C2+C3-2) = ",3,2,&table),3,1);

    std::cout<<table;
}