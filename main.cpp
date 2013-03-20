#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "getString.h"
#include "declareID.h"

int main(int argc, char** argv) {
    FILE *fp;
    fp = fopen("test.txt", "r");
    int i = 0;
    while((msgget[i] = fgetc(fp))!=EOF){
        i++;
    }//i is the length of the array, msgget[i - 1] is the last character of this array
    fclose(fp);
    
    int count = 0;
    for(int j = 0; j <= i - 1; j++){
        switch (msgget[j]){                     //Get the symbols lika '*' '(' etc.
            case '\n':{
                getNumofLine++;
                break;
            }                                   //Get the current line number
            case '+':
            case '*':
            case '/':
            case '=':
            case '(':
            case ')':
            case ';':
            case ',':{
            syn[count] = msgget[j] - 20;
            token[count][0] = msgget[j];
            token[count][1] = '\0';
                line[count] = getNumofLine;
            count++;
            break;
         }
            case '-':{
                if(syn[count - 1] == 16 || syn[count - 1] == 18){syn[count] = msgget[j] - 20;
                token[count][0] = msgget[j];
                token[count][1] = '\0';
                syn[count] = msgget[j] - 20;
                }else{
                    getNegtive(j);
                    for(int q = 0; q <= LenOfMid -1; q++){
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
            case ']':{
            syn[count] = msgget[j] - 60;
            token[count][0] = msgget[j];
            token[count][i] = '\0';
                line[count] = getNumofLine;
            count++;
            break;
        }
            case '{':
            case '}':{
            syn[count] = msgget[j] - 80;
            token[count][0] = msgget[j];
            token[count][i] = '\0';
                line[count] = getNumofLine;
            count++;
            break;      
        }
            case '%':{
            syn[count] = msgget[j] - 10;
            token[count][0] = msgget[j];
            token[count][i] = '\0';
                line[count] = getNumofLine;
            count++;
            break;
        }
            case ':':{
            syn[count] = 14;
            strcpy(token[count], ":=");
                line[count] = getNumofLine;
            count++;
            j++;
            break;
        }
            case '!':{
            syn[count] = 15;
            strcpy(token[count], "!=");
                line[count] = getNumofLine;
            count++;
            j++;
            break;
        }
            case '<':
            case '>':{
            if(msgget[j + 1] == '='){
                syn[count] = msgget[j] - 20;
                token[count][0] = msgget[j];
                token[count][1] = '=';
                token[count][2] = '\0';
                j++;
            }else{
                syn[count] = msgget[j] - 30;
                token[count][0] = msgget[j];
                token[count][1] = '\0';
            }
                line[count] = getNumofLine;
                count++;
            break;
        }
            case '#':{
            syn[count] = 35;
            token[count][0] = '#';
            token[count][1] = '\0';
                line[count] = getNumofLine;
            count++;
            break;
        }
            case '_':{
            if(msgget[j - 1] == ' ' || msgget[j-1] == '(' ){
                getFunction(j);
                for(int q = 0; q <= LenOfMid -1; q++){
                    token[count][q] = midstring[q];
                }
                token[count][LenOfMid] = '\0';
                if(syn[count - 1] == 9 || syn[count - 1] == 10 || syn[count - 1] == 11){
                strcpy(ID[NumofSym], token[count]);
                NumofSym++;
                }else{
                    isDeclared = false;
                    for(int e = 0; e <= NumofSym - 1; e++){
                            if(strcmp(ID[e],token[count]) == 0)
                                isDeclared = true;
                        }
                        if(isDeclared == false)
                            strcpy(token[count],"Error! Function Unfind!\0");
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
            case '9':{
            if(msgget[j - 1] == ' '){
                syn[count] = 18;
                getIntegerandDouble(j);
                for(int q = 0; q <= LenOfMid -1; q++){
                    token[count][q] = midstring[q];
                }
                token[count][LenOfMid] = '\0';
                line[count] = getNumofLine;
                j--;
                count++;
            }
            break;
        }
            case '"':{
                syn[count] = 29;
                token[count][0] = '"';
                token[count][1] = '\0';
                line[count] = getNumofLine;
                count++;
                break;
            }
            default:{
        if((msgget[j] >= 'A' && msgget[j] <= 'Z') || (msgget[j] >= 'a' && msgget[j] <= 'z')){
                if(msgget[j - 1] == '"'){
                    syn[count] = 19;
                        getChar(j);
                        for(int q = 0; q <= LenOfMid -1; q++){
                        token[count][q] = midstring[q];
                        }
                        token[count][LenOfMid] = '\0';
                line[count] = getNumofLine;
                        j--;
                        count++;                //If the last char is #, here must be a char or string
                }else if(msgget[j - 1] == '#'){
                    getNote(j);
                    syn[count] = 36;
                    for(int q = 0; q <= LenOfMid -1; q++){
                        token[count][q] = midstring[q];
                        }
                        token[count][LenOfMid] = '\0';
                line[count] = getNumofLine;
                        j--;
                        count++;                //If the last char is #, here must be a note
                }else{
                    getKeywordandID(j);
                    for(int q = 0; q <= LenOfMid - 1; q++){
                    token[count][q] = midstring[q];
                }
                token[count][LenOfMid] = '\0';
                line[count] = getNumofLine;
                bool isKeyword = false;
                int keyNum;
                for(keyNum = 0; keyNum <= 13; keyNum++){
                    if(strcmp(token[count], keyword[keyNum]) == 0){
                        isKeyword = 1;
                        break;
                    }
                }if(isKeyword){
                    syn[count] = keyNum;
                    count++;
                }else{
                    if(syn[count - 1] == 9 || syn[count - 1] == 10 || syn[count - 1] == 11){
                        strcpy(ID[NumofSym], token[count]);
                        NumofSym++;
                    }else{
                        isDeclared = false;
                        for(int e = 0; e <= NumofSym - 1; e++){
                            if(strcmp(ID[e],token[count]) == 0)
                                isDeclared = true;
                        }
                        if(isDeclared == false)
                            strcpy(token[count],"Error! Undeclared ID!\0");
                    }
                    syn[count] = 16;
                    count++;                    //Ok, the string leaved must be the ID
                }
                j--;
                }
            }else if(msgget[j] != ' ' && msgget[j] != '.' && msgget[j] != '\t'){
            syn[count] = 13;
            strcpy(token[count],"Invalid Symbols!\0");
            line[count] = getNumofLine;
            count++;
            }
        }
    }
 }
    for(int w = 0; w <= count - 1; w++){
        cout << w << " ( " << syn[w] << " , " << token[w] << " , " << line[w] << " )" << endl;
    }
}