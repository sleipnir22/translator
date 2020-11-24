
#include <iostream>
#include "Lexer.h"
int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream f;
	string path = "text.txt";
	f.open(path);
	string textToBeTranslated;
	if (!f.is_open())
	{
		cout << "не удалось открыть файл" << endl;
	}
	else
	{
		char ch;
		while (f.get(ch))
		{
			textToBeTranslated.push_back(ch);
		}
	}

	Lexer* lexer = new Lexer(textToBeTranslated);
	auto tokens = lexer->get_tokens();
	
	tokens[1].get_info();

	//cout << textToBeTranslated;
	return 0;
}