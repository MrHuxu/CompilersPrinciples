#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
char msgget[1000];
int syn[1000];
int line[1000];
char token[1000][40];
char midstring[40];
int count1, count2;
char ID[1000][40];

void getFunction(int &m){
    count1 = 0;    
    while((msgget[m] >= 'A' && msgget[m] <= 'Z') || (msgget[m] >= 'a' && msgget[m] <= 'z') || (msgget[m] >= '0' && msgget[m] <= '9') ||msgget[m] == '_'){
        midstring[count1] = msgget[m];
        count1++;
        m++;
    }
}//Get the function-name

void getInteger(int &m){
    count1 = 0;    
    while(msgget[m] >= '0' && msgget[m] <= '9'){
        midstring[count1] = msgget[m];
        count1++;
        m++;
    }
}//Get the Integer

void getString(int &m){
    count1 = 0;
    while(msgget[m] != '"'){
        midstring[count1] = msgget[m];
        count1++;
        m++;
    }
}//Get the string and character

void getKeywordandID(int &m){
    count1 = 0;
    while((msgget[m] >= 'a' && msgget[m] <= 'z') || (msgget[m] >= 'A' && msgget[m] <= 'Z') ||(msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '_'){
        midstring[count1] = msgget[m];
        count1++;
        m++;
    }
}//Get the Keyword like "main" and ID like "num_1"

void getNote(int &m){
    count1 = 0;
    while(msgget[m] != '#'){
        midstring[count1] = msgget[m];
        count1++;
        m++;
    }
}//Get the extra note

int main(int argc, char** argv) {
    FILE *fp;
    count2 = 0;
    int getNumofLine = 1;
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
            case '-':
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
            syn[count] = 11;
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
                syn[count] = msgget[j] - 48;
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
            if(msgget[j - 1] = ' '){
                syn[count] = 17;
                getFunction(j);
                for(int q = 0; q <= count1 -1; q++){
                    token[count][q] = midstring[q];
                }
                token[count][count1] = '\0';
                line[count] = getNumofLine;
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
            if(msgget[j - 1] = ' '){
                syn[count] = 18;
                getInteger(j);
                for(int q = 0; q <= count1 -1; q++){
                    token[count][q] = midstring[q];
                }
                token[count][count1] = '\0';
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
                        getString(j);
                        for(int q = 0; q <= count1 -1; q++){
                        token[count][q] = midstring[q];
                        }
                        token[count][count1] = '\0';
                line[count] = getNumofLine;
                        j--;
                        count++;                //If the last char is #, here must be a char or string
                }else if(msgget[j - 1] == '#'){
                    getNote(j);
                    syn[count] = 36;
                    for(int q = 0; q <= count1 -1; q++){
                        token[count][q] = midstring[q];
                        }
                        token[count][count1] = '\0';
                line[count] = getNumofLine;
                        j--;
                        count++;                //If the last char is #, here must be a note
                }else{
                    getKeywordandID(j);
                    for(int q = 0; q <= count1 - 1; q++){
                    token[count][q] = midstring[q];
                }
                token[count][count1] = '\0';
                line[count] = getNumofLine;
                if(strcmp(token[count], "main")==0){
                    syn[count] = 0;
                        count++;
                }else if(strcmp(token[count], "if") == 0){
                    syn[count] = 1;
                    count++;
                } else if(strcmp(token[count], "then") == 0){
                    syn[count] = 2;
                    count++;
                } else if(strcmp(token[count], "else") == 0){
                    syn[count] = 3;
                    count++;
                } else if(strcmp(token[count], "elsif") == 0){
                    syn[count] = 4;
                    count++;
                } else if(strcmp(token[count], "do") == 0){
                    syn[count] = 5;
                    count++;
                } else if(strcmp(token[count], "while") == 0){
                    syn[count] = 6;
                    count++;
                } else if(strcmp(token[count], "return") == 0){
                    syn[count] = 7;
                    count++;
                } else if(strcmp(token[count], "break") == 0){
                    syn[count] = 8;
                    count++;
                } else if(strcmp(token[count], "int") == 0){
                    syn[count] = 9;
                    count++;
                } else if(strcmp(token[count], "char") == 0){
                    syn[count] = 10;
                    count++;                      //Check the string if it is keyword
                } else if(strcmp(token[count], "gets") == 0){
                    syn[count] = 40;
                    count++;
                } else if(strcmp(token[count], "puts") == 0){
                    syn[count] = 42;
                    count++;                    //Check the string if it is keyword
                }else{
                    if(syn[count - 1] == 9 || syn[count - 1] == 10){
                        strcpy(ID[count2], token[count]);
                        count2++;
                    }else{
                        bool isDeclared = false;
                        for(int e = 0; e <= count2 - 1; e++){
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
            }else if(msgget[j] != ' ' && msgget[j] != '\t'){
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