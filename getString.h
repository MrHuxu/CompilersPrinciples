/* 
 * File:   getString.h
 * Author: huxu
 *
 * Created on 2013年3月20日, 上午9:56
 */

#ifndef GETSTRING_H
#define	GETSTRING_H
#include "declareID.h"

void getFunction(int &m){
    LenOfMid = 0;    
    while((msgget[m] >= 'A' && msgget[m] <= 'Z') || (msgget[m] >= 'a' && msgget[m] <= 'z') || (msgget[m] >= '0' && msgget[m] <= '9') ||msgget[m] == '_'){
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the function-name

void getIntegerandDouble(int &m){
    LenOfMid = 0;    
    while((msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '.'){
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the Integer

void getChar(int &m){
    LenOfMid = 0;
    while(msgget[m] != '"'){
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the string and character

void getKeywordandID(int &m){
    LenOfMid = 0;
    while((msgget[m] >= 'a' && msgget[m] <= 'z') || (msgget[m] >= 'A' && msgget[m] <= 'Z') ||(msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '_'){
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the Keyword like "main" and ID like "num_1"

void getNote(int &m){
    LenOfMid = 0;
    while(msgget[m] != '#'){
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}//Get the extra note

void getNegtive(int &m){
    LenOfMid = 0;
    midstring[0] = '-';
    LenOfMid++;m++;
    while((msgget[m] >= '0' && msgget[m] <= '9') || msgget[m] == '.'){
        midstring[LenOfMid] = msgget[m];
        LenOfMid++;
        m++;
    }
}
#endif	/* GETSTRING_H */

