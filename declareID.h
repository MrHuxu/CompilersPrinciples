/* 
 * File:   declareID.h
 * Author: huxu
 *
 * Created on 2013年3月20日, 上午10:05
 */

#ifndef ID_H
#define	ID_H

using namespace std;
char msgget[1000];
int syn[1000];
int line[1000];
char token[1000][40];
char midstring[40];
int LenOfMid;
int NumofSym = 0;
char ID[1000][40];
bool isDeclared = false;
int getNumofLine = 1;
int count;
char keyword[14][10] = {"main", "if", "then", "else", "elsif", "do", "while", "return", "break", "int", "char", "double", "gets", "puts"};

#endif	/* ID_H */

