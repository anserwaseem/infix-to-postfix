/**
 * C++ template class stack with following features;
 * Paramterized constructor
 * getSize, which returns size of the stack.
 * isEmpty, which tells either stack is empty or not.
 * topp, which assigns the top-most value of stack to the given value.
 * push
 * pop
 * 
 * Using stack, following functions are implemented:
 * C++ isBalanced function, which takes a string as paramter and tells either it is balanced or not (by using stack).
 * C++ reverse function, which takes a string as a parameter and returns a reversed string (by using stack).
 * C++ INtoPOST function, which takes a string as a parameter and uses precedence function along with stack to convert the given INFIX expression into POSTFIX espression. 
 * 
 * @param T the type of data stored in the Stack.
 */

#include<iostream>
#include<string>
using namespace std;

template<class T>
class stack
{
	int top;
	int Size;
	T *STACK;

	/**
	 * It tells either stack is full or not.
	 * @returns true if stack is full and false otherwise.
	 */
	bool overFlow()
	{
		if (top == this->Size - 1)
			return true;
		return false;
	}
public:
	/**
	 * Default constructor.
	 * It initializes the stack at size 10 (by default).
	 */
	stack()
	{
		Size=10;
		STACK=new T[Size];
		top = -1; //initial value
		for (int i = 0; i < Size; i++)
			STACK[i] = 0;
	}

	/**
	 * Paramterized constructor.
	 * It initializes the stack at given size.
	 * @param size given size
	 */
	stack(int Size)
	{
		this->Size=Size;
		STACK=new T[this->Size];
		top = -1; //initial value
		for (int i = 0; i < this->Size; i++)
			STACK[i] = 0;
	}

	/**
	 * It tells the current size of the stack.
	 * @returns current size of the stack.
	 */
	int getSize()
	{
		return (top + 1);
	}

	/**
	 * It tells eiter stack is empty or not.
	 * @returns true if stack is empty, else it returns false.
	 */
	bool isEmpty()
	{
		if (top == -1)
			return true;
		return false;
	}
	/**
	 * It assigns the top-most value of the stack to the given paramter.
	 * @param assignTopValue template type parameter, to which the top-most value of stack will be assigned.
	 * @note it doesn't assign any value to @param assignTopValue if stack is empty.
	 */
	void topp(T& assignTopValue)
	{
		if (!isEmpty())
		{
			assignTopValue = STACK[top];
		}
	}

	/**
	 * It pushes the given template type paramter in the stack.
	 * @param element template type parameter, which'll be pushed in the stack.
	 */
	void push(T element)
	{
		top++;
		STACK[top] = element;
	}

	/**
	 * It pops top-most element from the stack.
	 * @note it shows an error message if the stack is empty.
	 */
	void pop()
	{
		if (top == -1)
		{
			cout << "cannot pop out element from empty stack.\n";
		}
		else
		{
			STACK[top] = 0;
			top--;
		}
	}

	//Destructor
	~stack()
	{
		delete[] STACK;
	}
};

/**
 * This function takes a string type expression and tells if the expression is balanced or not.
 * It uses stack and its Big-O is O(N), where N is the length of given expression.
 * @param exp string type expression, which is to be checked.
 * @returns true if the expression is balanced, else false.
 * @see implementation of stack.
 */
bool isBalanced(string exp)
{
	stack<char> s;
	if (exp[0] == ')' || exp[0] == ']' || exp[0] == '}')
		return false;
	s.push(exp[0]);
	for (int i = 1; i < exp.length(); i++)
	{
		char check;
		s.topp(check);

		if (check == '(' && exp[i] == (char)(check + 1))
			s.pop();
		else if ((check == '[' || check == '{') && exp[i] == (char)(check + 2))
			s.pop();
		else
			s.push(exp[i]);
	}
	if (s.isEmpty())
		return true;
	return false;
}

/**
 * This function takes a string type expression and reverses the string.
 * It uses stack and its Big-O is O(N), where N is the length of given string.
 * @param str constant string type expression, which is to be reversed.
 * @returns reversed string.
 * @see implementation of stack.
 */
string reverse(string const str)
{
	string revString="";
	revString.resize(10);
	stack<char> s;
	for (int i = 0; i < str.length(); i++)
	{
		s.push(str[i]);
	}
	for (int i = 0; i < str.length(); i++)
	{
		char val;
		s.topp(val);
		s.pop();
		revString[i] = val;
	}
	return revString;
}

/**
 * This function takes two character type paramters and compares there precednce.
 * Its Big-O is O(constant)
 * @param o1 operator number 1, whose precedence will be compared.
 * @param o2 operator number 2, whose precedence will be compared.
 * @returns true if precedence of o1 is greater or equal than o2, else false.
 */
bool precedence(char o1, char o2)
{
	if ((o1 == '*' || o1 == '/') && (o2 == '+' || o2 == '-'))//o1>o2
		return true;
	else if (((o1 == '*' || o2 == '/') && (o1 == '/' || o2 == '*')) || ((o1 == '+' || o2 == '-') && (o1 == '-' || o2 == '+')))//o1==o2
		return true;
	else
		return false;
}

/**
 * This function takes a string type expression and converts and INFIX expression to POSTFIX expression.
 * It uses stack and its Big-O is O(NlogN), where N is the length of given expression.
 * @param exp string type expression, which is to be converted.
 * @returns (POSTFIX) string type expression.
 * @see implementation of stack.
 * @see precedence function.
 */
string INtoPOST(string exp)
{
	stack<char> s;
	string post = "";
	int j = 0;
	for (int i = 0; i < exp.length(); i++)
	{
		char symbol = 0;
		symbol = exp[i];
		int symb= static_cast<int>(symbol);
		if ((symb >= 65 && symb <= 90) || (symb >= 97 && symb <= 122))
		{
			post.resize(j + 1);
			post[j] = exp[i];
			j++;
		}
		else
		{
			char check=0;
			s.topp(check);

			while (!s.isEmpty() && precedence(check, exp[i]))
			{
				s.topp(check);
				post.resize(j + 1);
				post[j] = check;
				j++;
				s.pop();
			}
			s.push(exp[i]);
		}
		
	}
	
	while (!s.isEmpty())
	{
		post.resize(j + 1);
		s.topp(post[j]);
		j++;
		s.pop();
	}
	return post;
}

int main()
{
	cout<<"given expression: {()[]{}}([{)}]\n";
	bool ff=isBalanced("{()[]{}}([{)}]");
	if (ff == true)
		cout << "brackets are balanced.\n\n";
	else
		cout << "brackets are not balanced.\n\n";
	
	cout<<"given expression: ({[](){}})\n";
	bool f=isBalanced("({[](){}})");
	if (f == true)
		cout << "brackets are balanced.\n\n";
	else
		cout << "brackets are not balanced.\n\n";

	cout<<"before reversal: abcdefghij\n";
	cout<<"after reversal: "<<reverse("abcdefghij")<<endl<<endl;

	cout<<"infix expression: A+B+C+D\n";
	cout<<"postfix expression: "<<INtoPOST("A+B+C+D")<<endl<<endl;
	
	cout<<"infix expression: A*B+C*D\n";
	cout<<"postfix expression: "<<INtoPOST("A*B+C*D")<<endl<<endl;

	return 0;
}