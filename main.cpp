/* 
 * File:   main.cpp
 * Author: huxu
 *
 * Created on 2013年3月15日, 下午11:16
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
char msgget[1000];
int syn[1000];
char token[1000][20];
char midstring[20];
int count1;

void getArray(int &m){
    count1 = 0;
    while(midstring[m] != ' '){
        midstring[count1] = msgget[m];
        count1++;
        m++;
    }
}

int main(int argc, char** argv) {
    FILE *fp;
    fp = fopen("test.txt", "r");
    int i = 0;
    while((msgget[i] = fgetc(fp))!=EOF){
        i++;
    }//i is the length of the array, msgget[i] is the last character of this array
    fclose(fp);
    
    int count = 0;
    for(int j = 0; j <= i - 1; j++){
        switch (msgget[j]){
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
            count++;
            break;
        }
            case '[':
            case ']':{
            syn[count] = msgget[j] - 60;
            token[count][0] = msgget[j];
            token[count][i] = '\0';
            count++;
            break;
        }
            case '{':
            case '}':{
            syn[count] = msgget[j] - 80;
            token[count][0] = msgget[j];
            token[count][i] = '\0';
            count++;
            break;      
        }
            case '%':{
            syn[count] = msgget[j] - 10;
            token[count][0] = msgget[j];
            token[count][i] = '\0';
            count++;
            break;
        }
            case ':':{
            syn[count] = 11;
            strcpy(token[count], ":=");
            count++;
            j++;
            break;
        }
            case '!':{
            syn[count] = 16;
            strcpy(token[count], "!=");
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
                count++;
                j++;
            }else{
                syn[count] = msgget[j] - 30;
                token[count][0] = msgget[j];
                token[count][1] = '\0';
                count++;
            }
            break;
        }
//            case '_':{
//            if(msgget[j - 1] = ' '){
//                syn[count] = 17;
//                getArray(j);
//                for(int q = 0; q <= count -1; q++){
//                    token[count][q] = midstring[q];
//                }
//                token[count][count1] = '\0';
//                j--;
//                count++;
//            }
//            break;
//            }
//            case '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9':{
//            if(msgget[j - 1] = ' '){
//                syn[count] = 25;
//                getArray(j);
//                for(int q = 0; q <= count -1; q++){
//                    token[count][q] = midstring[q];
//                }
//                token[count][count1] = '\0';
//                j--;
//                count++;
//            }
//            break;
//        }
//        else if((msgget[j] >= 'a' && msgget[j] <= 'z')||(msgget[j] >= 'A'&&msgget[j] <= 'Z')){
//            getArray[j];
//            if(syn[count - 1] == 10){
//                syn[count] = 23;
//                getArray(j);
//                for(int q = 0; q <= count -1; q++){
//                    token[count][q] = midstring[q];
//                }
//                token[count][count1] = '\0';
//                j--;
//                count++;
//            }else{
//                switch (midstring[0]){
//                    case 'm':{
//                        syn[count] = 0;
//                        token[count] = "main";
//                        j = j + 3;
//                        break;
//                    }case 'i':{
//                        if(midstring[1] == 'f'){
//                            syn[count] = 1;
//                        token[count] = "if";
//                        j++;
//                        break;
//                        }else{
//                            syn[count] = 9;
//                        token[count] = "int";
//                        j = j + 2;
//                        break;
//                        }
//                    }case 't':{
//                        syn[count] = 2;
//                        token[count] = "then";
//                        j = j + 3;
//                        break;
//                    }case 'e':{
//                        if(midstring[3] == 'e'){
//                            syn[count] = 3;
//                        token[count] = "else";
//                        j = j + 3;
//                        break;
//                        }else{
//                            syn[count] = 4;
//                        token[count] = "elsif";
//                        j = j + 4;
//                        break;
//                        }
//                    }case 'd':{
//                        syn[count] = 5;
//                        token[count] = "do";
//                        j++;
//                        break;
//                    }case 'w':{
//                        syn[count] = 6;
//                        token[count] = "while";
//                        j = j + 4;
//                        break;
//                    }case 'r':{
//                        syn[count] = 7;
//                        token[count] = "return";
//                        j = j + 5;
//                        break;
//                    }case 'b':{
//                        syn[count] = 8;
//                        token[count] = "break";
//                        j = j + 4;
//                        break;
//                    }
//                }
//            }
//        }
    }
 }
    cout << count << endl;
    for(int w = 0; w <= count - 1; w++){
        cout << "( " << syn[w] << " , " << token[w] << " )" << endl;
    }
}

