#include <iostream>
#include <string>
using namespace std;

int main(){
	cout << "Enter a message here: ";
	string mess;
	cin >> mess;
	string snip = mess.substr(0, 2);

	cout << endl;

	if (snip == "Hi" || snip == "He")
		cout << "Hello World!\n";

	else
		cout << "That was a bad message.\n";

	system("PAUSE");
	return 0;
}