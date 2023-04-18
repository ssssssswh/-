#include <iostream>
#include <string>
#include <algorithm>
#include <cmath> 
using namespace std;
const int MAX = 30;
const int DONE = 1;
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
 
//栈定义 
template <class T>
class Stack{
public:
	Stack(int MaxStackSize=10);
	~Stack() { delete [] stack;}
	bool IsEmpty() const {return top==-1;}
	bool IsFull() const {return top==MaxTop;}
	T Top() const;
	Stack<T>& Add(const T& x);
	Stack<T>& Del(T& x);
	void MakeEmpty(){top=-1;} //清空栈
	void print(){
		for(int i; i < top + 1; i ++){
			cout<<stack[i]<<'\t';
		}
		cout<<endl;
	}
private:
	int top;//栈顶
	int MaxTop;//最大的栈顶值
	T *stack;//堆栈元素数组
};
template<class T>
Stack<T>::Stack(int MaxStackSize){
	MaxTop=MaxStackSize-1;
	stack=new T[MaxStackSize];
	top=-1;
}
template<class T>
Stack<T>& Stack<T>::Add(const T& x){
	if(IsFull())
	{cout<<"no memory;"<<endl;return *this;}
	top=top+1;
	stack[top]=x;
	return *this;    
}
template<class T>
Stack<T>& Stack<T>::Del(T& x){
	if(IsEmpty())
	{cout<<"no element"<<endl;return *this;}
	x=stack[top];
	top=top-1;
	return *this;
}
template<class T>
T Stack<T>::Top() const{
	return stack[top];
}
 
//判断一个字符是否为数字
bool isNum(char c){
	if((c > '0'||c == '0')&&(c < '9'||c == '9'))
		return true;
	else
		return false;
}
 
//删除字符串中的空格 
void deleteBlank(string &s){
	string::iterator i = s.begin();
	while ((i=find(i, s.end(), ' '))!=s.end())
        s.erase(i);
} 
 
//计算器
class Calculator{
public:
	Calculator(string s);
	~Calculator();
	int outPriority(char);      //返回栈外优先级
	int inPriority(char);       //返回栈内优先级 
	bool judgePri(char, char);  //判断优先级 前一个为栈外符号，后一个为栈内符号 若前大于后返回1，否则返回0 
	int judgePri(char);         //判断运算符  若是'#'返回 -1，若是')'返回 0，否则返回 1 
	void dealNum(); 	    //处理数据	
	int calculate();            //计算 
	void setString(string const s){
		this->s = '#' + s + '#';
		deleteBlank(this->s);   //删除字符串中的空格 
	}
private:
	Stack<char> *s_sym;         //符号栈 
	Stack<int> *s_num;          //数据栈 
	string s;
};
Calculator::Calculator(string s){
	this->s = '#' + s + '#';
	deleteBlank(this->s);
	s_sym = new Stack<char>(MAX);
	s_num = new Stack<int>(MAX);
} 
Calculator::~Calculator(){
	delete s_sym;
	delete s_num;
}
int Calculator::outPriority(char symble){
	switch(symble){
		case '#':
			return 0;
		case '(':
			return 8;
		case '+':
			return 2;
		case '-':
			return 2;
		case '*':
			return 4;
		case '/':
			return 4;
		case '%':
			return 4;
		case '^':
			return 6;
		case ')':
			return 1;
		default:
			throw 1;
	}
}
int Calculator::inPriority(char symble){
	switch(symble){
		case '#':
			return 0;
		case '(':
			return 1;
		case '+':
			return 3;
		case '-':
			return 3;
		case '*':
			return 5;
		case '/':
			return 5;
		case '%':
			return 5;
		case '^':
			return 7;
		case ')':
			return 8;
		default:
			throw 1;
	}
}
bool Calculator::judgePri(char out, char in){
	if(outPriority(out) > inPriority(in))
		return true;
	else 
		return false;
} 
int Calculator::judgePri(char symble){
	if(symble == '#')
		return -1;
	else if(symble == ')')
		return 0;
	else
		return 1;
}
void Calculator::dealNum(){
	//将数据栈中的前两个弹出进行计算，结果放回数据栈，符号栈弹出顶部元素 
	char _temp = 0; 
	int dtemp1 = 0;
	int dtemp2 = 0; 
	s_sym->Del(_temp);
	s_num->Del(dtemp1);
	s_num->Del(dtemp2); 
	switch(_temp){
		case '+':
			dtemp2 += dtemp1;
			break;
		case '-':
			dtemp2 = dtemp2 - dtemp1;
			break;
		case '*':
			dtemp2 = dtemp2 * dtemp1;
			break;
		case '/':
			if(dtemp1 == 0)
				throw 0;
			else
				dtemp2 = dtemp2 / dtemp1;
			break;
		case '%':
			dtemp2 = dtemp2 % dtemp1;
			break;
		case '^':
			dtemp2 = pow(dtemp2,dtemp1);
			break;
		default:
			throw 1;
	}
	s_num->Add(dtemp2);
}
int Calculator::calculate(){  
	for(int i = 0; i < s.size(); i ++){   //遍历字符串 
		if(isNum(s[i])){
			int temp = (int)(s[i]) - 48;  //char强制类型转换为int ascii 码数值，减 48 转换为对应整数值 
			int _temp = 0;
			if(i > 0 && isNum(s[i - 1])){
				s_num->Del(_temp);
				temp = _temp * 10 + temp;
			}
			s_num->Add(temp);
		}else{ 
			char temp = s[i];
			if(s_sym->IsEmpty()){
				s_sym->Add(temp);
			}else{
				if(judgePri(temp, s_sym->Top())){
					s_sym->Add(temp);  
				}else   if(judgePri(temp) == 1){          //栈外优先级小于栈内优先级，且不为 '#' 和 ')' 
					while(!judgePri(temp, s_sym->Top())){ //当栈外优先级比栈内优先级低时，执行栈内符号运算 
						dealNum();
					}
					s_sym->Add(temp);
				
				}else if (judgePri(temp) == -1){
					while(s_sym->Top() != '#'){
						dealNum();
					}
					int result = s_num->Top();
					s_sym->MakeEmpty();
					s_num->MakeEmpty();
					return result;
				}
				else if(judgePri(temp) == 0){
					while(s_sym->Top() != '('){
						dealNum();
					}
					s_sym->Del(temp);
				}
			}
		}
	}
}
 
int main(int argc, char** argv) {
	try{
		string s = "";
		Calculator c(s);
		while(DONE){
			s = "";
			cout<<"请输入一个表达式"<<endl;
			getline(cin, s);   
			c.setString(s);
			int result = 0;
		    result = c.calculate();
	    	cout<<c.calculate()<<endl;
	    	system("pause");
	    	system("cls");
		}
	}
    catch(int i){
    	if(i == 0)
    		cout<<"除数不能为0！";
    	else if(i == 1)
    		cout<<"存在无法识别的符号！"<<endl;
	} 
	return 0;
}
