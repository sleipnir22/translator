#pragma once

#define BSIZE	15						//������ ������
#define NONE	-1						//������ ������
#define EOS		'\0'					//����� ������
#define NUM		256						//�����
#define ID		257						//����������
#define ARRAY	258						//������
#define IF		259
#define ELSE	261
#define WHILE	262
#define DO		263
#define READ	264
#define WRITE	265
#define INT		266						//������������� ��� ����������
#define INTM	267  					//������������� ��� �������
#define INDEX	268						//����� ������� ��� ���
#define MARK_JF	269						//����� �������� �� "����" ��� ���
#define MARK_J	270						//����� ������������ �������� ��� ���
#define DONE	271						//����� �����


#define STRMAX	999						/* ������ ������� ������ */
#define SYMMAX	100000						/* ������ ������� �������� */
char lexemes[STRMAX];					//������ ������


const int SIZE = 500;				//������ �����