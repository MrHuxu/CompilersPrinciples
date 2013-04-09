#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "LexAnalyzer.h"
#include "declareID.h"

int main(int argc, char** argv) {
    FILE *fp;
    fp = fopen("test.txt", "r");
    //i is the length of the array, msgget[i - 1] is the last character of this array
    int i = 0;
    while ((msgget[i] = fgetc(fp)) != EOF) {
        i++;
    }
    fclose(fp);

    Lex_Analyzer(msgget, i);
}