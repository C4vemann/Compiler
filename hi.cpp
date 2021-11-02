#include <iostream>
#include <string>
using namespace std;


class Token{
	public:
		string word;
		string group;
		int position;

		Token(){
			word = "";
			group = "NAN";
			position = -1;
		}

		Token(string w,string g,int p){
			word = w;
			group = g;
			position = p;
		}

		ostream& operator<<(ostream& os){
			    os << "Token string: " << word << "; Token Group: " << group << "; Inserted at position: " << position << ";" << endl;
			    return os;
			}


};

string doSomething(string str){
	cout << str << endl;
	if(str[0] == 'H'){
		return "H Group";
	}
	else if(str[0] == 'Y'){
		return "Y Group";
	}
	else if(str[0] == 'N'){
		return "N Group";
	}
	else if(str[0] == 's'){
		return "s Group";
	}
	else if(str[0] == 'W'){
		return "W Group";
	}
	else if(str[0] == 'm'){
		return "m Group";
	}
	else{
		return "Not a lexeme";
	}

}

int main(){
	Token * t;
	string inputs[3] = {"Hello World\n", "Now you shine\n", "Youtube men"};
	int inputIndex = 0;

	int currentPtr = 0;
	int top = inputs[inputIndex].size();

	string temp = "";

	for(int currentPtr = 0; currentPtr <= top; currentPtr++){
		string group;
		if(inputs[inputIndex][currentPtr] == ' ' ){
			cout << "Break due to space: ";
			group = doSomething(temp);
			t = new Token(temp,group,0);
			temp="";
		} else if(inputs[inputIndex][currentPtr]  == '\n'){
			cout << "Break due to new line: ";
			group = doSomething(temp);
			t = new Token(temp,group,0);
			inputIndex++;
			top = inputs[inputIndex].size();
			temp="";
			currentPtr = -1;

		} else if(currentPtr == top){
			cout << "Break due to end of input: ";
			group = doSomething(temp);
			t = new Token(temp,group,0);
			temp="";
			//return end of input token
		} else{
			temp += inputs[inputIndex][currentPtr];
		}
	}

	cout << "End of program";
}