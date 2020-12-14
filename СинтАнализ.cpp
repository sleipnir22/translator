#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
using namespace std;

void f1(), f2(), f3(), f4(), f5(), f6(), f7(), f8(), f9();
typedef void (*semf)();
const semf funcArr[] = { f1,f2,f3,f4,f5,f6,f7,f8,f9 }; // Массив семантических функций
int i = 0; //– номер очередного символа входного текста;
string st; //– анализируемая строка символов;
string ops; // - ОПС

const int M[5][6] =     //Mатрица функций
{   {0,0,1,0,2,0},      //
    {3,4,4,4,4,4},      //
    {0,0,5,0,6,0},      //
    {4,7,4,4,4,4},      //
    {0,0,8,0,9,0},      //
};

const char nterm[]{ 'S','U','T','V','F' }; //Массив нетерминалов
const char term[]{ '+','*','(',')','a',';' }; //Массив терминалов


int nt(char ch)
{
    int i = 0;
    while (i < sizeof(nterm))
    {
        if (ch == nterm[i])
            return i;
        else
            ++i;
    }
    return -1;
}

int t(char ch)
{
    int i = 0;
    while (i < sizeof(term))
    {
        if (ch == term[i])
            return i;
        else
            ++i;
    }
    return -1;
}

stack<char> stack1, stack2;

void f1()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('V');
    stack1.push(')');
    stack1.push('S');  
    stack1.push('(');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}

void f2()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push('a');
}

void f3()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('T');
    stack1.push('+');

    stack2.push('+');
    stack2.push(' ');
    stack2.push(' ');
}

void f4()
{
    stack1.pop();
}

void f5()
{
    stack1.pop();
    stack1.push('V');
    stack1.push(')');
    stack1.push('S');
    stack1.push('(');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}

void f6()
{
    stack1.pop();
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push('a');
}

void f7()
{
    stack1.pop();
    stack1.push('V');
    stack1.push('F');
    stack1.push('*');

    stack2.push('*');
    stack2.push(' ');
    stack2.push(' ');
}

void f8()
{
    stack1.pop();
    stack1.push(')');
    stack1.push('S');
    stack1.push('(');


    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}

void f9()
{
    stack1.pop();
    stack1.push('a');

    stack2.push('a');
}


void show_stack(stack<char> s)
{
    stack<char> s1 = s;
    int n = s1.size();
    for (int i = 0; i < n; i++)
    {
        cout << s1.top();
        s1.pop();
    }
    cout << endl;
}



const int S[6][9] =                 //Матрица функций
{
    {1,3,4,5,6,4,5,7,8},
    {2,2,9,9,9,9,9,9,9},
    {4,11,12,12,12,12,12,12,12},
    {13,13,13,14,13,13,13,13,13},
    {15,15,15,15,16,15,15,15,10},
    {4,4,10,10,10,10,10,10,10}
};

int main()
{
    setlocale(LC_ALL, "ru");
    const string path = "tfest.txt"; //Путь к файлу

    ifstream fin;
    fin.open(path);
    if (!fin.is_open())
    {
        cout << "BLM!" << endl;
    }
    else
    {
        fin >> st;
        st += ';';
        int k = 0,s = 0;
        char sch = 'S';
        stack1.push(';');
        stack1.push('S');
        show_stack(stack1);
        stack2.push(' ');
        stack2.push(' ');
        while (stack1.top() != ';')
        {
            if ((t(stack1.top()) + 1) && sch != st[i])
                break;
            if (stack2.top() != ' ')
            {
               ops += stack2.top();
            }
            stack2.pop();


            if (sch == st[i])
            {
                i++;
                stack1.pop();
                sch = stack1.top();
            }
            else
            {
                int ns = nt(sch);
                if (ns >= 0)
                    s = ns;

                int j = t(st[i]);
                if (j >= 0 && s >= 0)
                {
                    k = M[s][j];
                    k--;
                    if (k >= 0)
                    {
                        funcArr[k]();
                    }
                    else
                        break;
                }
                else
                    break;
            }
            show_stack(stack1);
            sch = stack1.top();
        }
        if (i + 1 == st.length() && stack1.size() == 1)
        {
            cout << endl << "Строка распознана" << endl;
            cout << endl << "ОПС: " << ops << endl;
        }
        else
            cout << endl << "Строка не распознана" << endl;
    }
    fin.close();
}

