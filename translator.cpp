// translator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Lexer.h"
#include "Parser.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream f;
	string path = "text.txt";
	f.open(path);
	string textToBeTranslated;
	cout << textToBeTranslated;
	if (!f.is_open())
	{
		cout << "Vive la France!" << endl;
	}
	else
	{
		char ch;
		while (f.get(ch))
		{
			textToBeTranslated.push_back(ch);
		}
	}

	Lexer lexer(textToBeTranslated);
	Parser* parser = new Parser(lexer);
	auto ops = parser->make_ops();

	cout << endl;

	for (int i = 0; i < ops.ops_tokens.size(); i++)
	{
		ops.ops_tokens[i].get_info();;
	}
	cout << endl;

	for (int i = 0; i < ops.ops_varArr.size(); i++)
	{
		cout << ops.ops_varArr[i] << " ";
	}
	return 0;
}