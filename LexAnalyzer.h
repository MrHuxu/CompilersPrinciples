/* 
 * File:   LexAnalyzer.h
 * Author: huxu
 *
 * Created on 2013年3月20日, 上午9:56
 */

#ifndef GETSTRING_H
#define	GETSTRING_H
#include "declareID.h"

void getFunction(int &m) {
    LenOfMid = 0;
    while ((msgget[m] >= 'A' && msgget[m] <= 'Z') || (msgget[m] >= 'a' && msgget[m] <= 'z') || (msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '_') {
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the function-name

void getIntegerandDouble(int &m) {
    LenOfMid = 0;
    while ((msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '.') {
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the Integer

void getChar(int &m) {
    LenOfMid = 0;
    while (msgget[m] != '"') {
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the string and character

void getKeywordandID(int &m) {
    LenOfMid = 0;
    while ((msgget[m] >= 'a' && msgget[m] <= 'z') || (msgget[m] >= 'A' && msgget[m] <= 'Z') || (msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '_') {
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the Keyword like "main" and ID like "num_1"

void getNote(int &m) {
    LenOfMid = 0;
    while (msgget[m] != '#') {
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the extra note

void getNegtive(int &m) {
    LenOfMid = 0;
    midstring[0] = '-';
    LenOfMid++;
    m++;
    while ((msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '.') {
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}

void Lex_Analyzer(char *m, int i){
    count = 0;
    for (int j = 0; j <= i - 1; j++) {
        switch (msgget[j]) { //Get the symbols lika '*' '(' etc.
            case '\n':
            {
                getNumofLine++;
                break;
            } //Get the current line number
            case '+':
            case '*':
            case '/':
            case '=':
            case '(':
            case ')':
            case ';':
            case ',':
            {
                syn[count] = msgget[j] - 20;
                token[count][0] = msgget[j];
                token[count][1] = '\0';
                line[count] = getNumofLine;
                count++;
                break;
            }
            case '-':
            {
                if (syn[count - 1] == 16 || syn[count - 1] == 18) {
                    syn[count] = msgget[j] - 20;
                    token[count][0] = msgget[j];
                    token[count][1] = '\0';
                    syn[count] = msgget[j] - 20;
                } else {
                    getNegtive(j);
                    for (int q = 0; q <= LenOfMid - 1; q++) {
                        token[count][q] = midstring[q];
                    }
                    token[count][LenOfMid] = '\0';
                    syn[count] = 26;
                    j--;
                }
                line[count] = getNumofLine;
                count++;
                break;
            }

            case '[':
            case ']':
            {
                syn[count] = msgget[j] - 60;
                token[count][0] = msgget[j];
                token[count][i] = '\0';
                line[count] = getNumofLine;
                count++;
                break;
            }
            case '{':
            case '}':
            {
                syn[count] = msgget[j] - 80;
                token[count][0] = msgget[j];
                token[count][i] = '\0';
                line[count] = getNumofLine;
                count++;
                break;
            }
            case '%':
            {
                syn[count] = msgget[j] - 10;
                token[count][0] = msgget[j];
                token[count][i] = '\0';
                line[count] = getNumofLine;
                count++;
                break;
            }
            case ':':
            {
                syn[count] = 14;
                strcpy(token[count], ":=");
                line[count] = getNumofLine;
                count++;
                j++;
                break;
            }
            case '!':
            {
                syn[count] = 15;
                strcpy(token[count], "!=");
                line[count] = getNumofLine;
                count++;
                j++;
                break;
            }
            case '<':
            case '>':
            {
                if (msgget[j + 1] == '=') {
                    syn[count] = msgget[j] - 20;
                    token[count][0] = msgget[j];
                    token[count][1] = '=';
                    token[count][2] = '\0';
                    j++;
                } else {
                    syn[count] = msgget[j] - 30;
                    token[count][0] = msgget[j];
                    token[count][1] = '\0';
                }
                line[count] = getNumofLine;
                count++;
                break;
            }
            case '#':
            {
                syn[count] = 35;
                token[count][0] = '#';
                token[count][1] = '\0';
                line[count] = getNumofLine;
                count++;
                break;
            }
            case '_':
            {
                if (msgget[j - 1] == ' ' || msgget[j - 1] == '(') {
                    getFunction(j);
                    for (int q = 0; q <= LenOfMid - 1; q++) {
                        token[count][q] = midstring[q];
                    }
                    token[count][LenOfMid] = '\0';
                    if (syn[count - 1] == 9 || syn[count - 1] == 10 || syn[count - 1] == 11) {
                        strcpy(ID[NumofSym], token[count]);
                        NumofSym++;
                    } else {
                        isDeclared = false;
                        for (int e = 0; e <= NumofSym - 1; e++) {
                            if (strcmp(ID[e], token[count]) == 0)
                                isDeclared = true;
                        }
                        if (isDeclared == false)
                            strcpy(token[count], "Error! Function Unfind!\0");
                    }
                    syn[count] = 17;
                    line[count] = getNumofLine;
                    j--;
                    count++;
                }
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                if (msgget[j - 1] == ' ') {
                    syn[count] = 18;
                    getIntegerandDouble(j);
                    for (int q = 0; q <= LenOfMid - 1; q++) {
                        token[count][q] = midstring[q];
                    }
                    token[count][LenOfMid] = '\0';
                    line[count] = getNumofLine;
                    j--;
                    count++;
                }
                break;
            }
            case '"':
            {
                syn[count] = 29;
                token[count][0] = '"';
                token[count][1] = '\0';
                line[count] = getNumofLine;
                count++;
                break;
            }
            default:
            {
                if ((msgget[j] >= 'A' && msgget[j] <= 'Z') || (msgget[j] >= 'a' && msgget[j] <= 'z')) {
                    if (msgget[j - 1] == '"') {
                        syn[count] = 19;
                        getChar(j);
                        for (int q = 0; q <= LenOfMid - 1; q++) {
                            token[count][q] = midstring[q];
                        }
                        token[count][LenOfMid] = '\0';
                        line[count] = getNumofLine;
                        j--;
                        count++; //If the last char is #, here must be a char or string
                    } else if (msgget[j - 1] == '#') {
                        getNote(j);
                        syn[count] = 36;
                        for (int q = 0; q <= LenOfMid - 1; q++) {
                            token[count][q] = midstring[q];
                        }
                        token[count][LenOfMid] = '\0';
                        line[count] = getNumofLine;
                        j--;
                        count++; //If the last char is #, here must be a note
                    } else {
                        getKeywordandID(j);
                        for (int q = 0; q <= LenOfMid - 1; q++) {
                            token[count][q] = midstring[q];
                        }
                        token[count][LenOfMid] = '\0';
                        line[count] = getNumofLine;
                        bool isKeyword = false;
                        int keyNum;
                        for (keyNum = 0; keyNum <= 13; keyNum++) {
                            if (strcmp(token[count], keyword[keyNum]) == 0) {
                                isKeyword = 1;
                                break;
                            }
                        }
                        if (isKeyword) {
                            syn[count] = keyNum;
                            count++;
                        } else {
                            if (syn[count - 1] == 9 || syn[count - 1] == 10 || syn[count - 1] == 11) {
                                strcpy(ID[NumofSym], token[count]);
                                NumofSym++;
                            } else {
                                isDeclared = false;
                                for (int e = 0; e <= NumofSym - 1; e++) {
                                    if (strcmp(ID[e], token[count]) == 0)
                                        isDeclared = true;
                                }
                                if (isDeclared == false)
                                    strcpy(token[count], "Error! Undeclared ID!\0");
                            }
                            syn[count] = 16;
                            count++; //Ok, the string leaved must be the ID
                        }
                        j--;
                    }
                } else if (msgget[j] != ' ' && msgget[j] != '.' && msgget[j] != '\t') {
                    syn[count] = 13;
                    strcpy(token[count], "Invalid Symbols!\0");
                    line[count] = getNumofLine;
                    count++;
                }
            }
        }
    }
    
    
    for (int w = 0; w <= count - 1; w++) {
        cout << w << " ( " << syn[w] << " , " << token[w] << " , " << line[w] << " )" << endl;
    }
}
#endif	/* GETSTRING_H */

