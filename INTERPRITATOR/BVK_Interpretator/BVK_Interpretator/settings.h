#pragma once

#define BSIZE	15						//размер буфера
#define NONE	-1						//другой символ
#define EOS		'\0'					//конец строки
#define NUM		256						//число
#define ID		257						//переменная
#define ARRAY	258						//массив
#define IF		259
#define ELSE	261
#define WHILE	262
#define DO		263
#define READ	264
#define WRITE	265
#define INT		266						//целочисленный тип переменной
#define INTM	267  					//целочисленный тип массива
#define INDEX	268						//метка массива для ОПС
#define MARK_JF	269						//метка перехода по "ложь" для ОПС
#define MARK_J	270						//метка безусловного перехода для ОПС
#define DONE	271						//конец файла


#define STRMAX	999						/* Размер массива лексем */
#define SYMMAX	100000						/* Размер таблицы символов */
char lexemes[STRMAX];					//массив лексем


const int SIZE = 500;				//Размер стека