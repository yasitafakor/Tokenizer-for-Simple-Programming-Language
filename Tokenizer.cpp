
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100 // Maximum number of elements in the map 

int size = 0; // Current number of elements in the map
char keys[MAX_SIZE][100]; // Array to store the keys
int values[MAX_SIZE]; // Array to store the values
int counter = 100; //token_value0

// Function to get the index of a key in the keys array
int getIndex(char key[])
{
    for (int i = 0; i < size; i++) {
        if (strcmp(keys[i], key) == 0) {
            return i;
        }
    }
    return -1; // Key not found
}

// Function to insert a key-value pair into the map
void insert(char key[], int value)
{
    int index = getIndex(key);
    if (index == -1) { // Key not found
        strcpy(keys[size], key);
        values[size] = value;
        size++;
    }
    else { // Key found
        values[index] = value;
    }
}

// Function to get the value of a key in the map
int get(char key[])
{
    int index = getIndex(key);
    if (index == -1) { // Key not found
        return -1;
    }
    else { // Key found
        return values[index];
    }
}

int isOperator(char c) {
    char operators[13] = "+-!*/%^<>=|&";
    for (int i = 0; i < 13; ++i) {
        if (c == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int isKeyword(char word[]) {

    char keywords[15][10] = {"integer", "char", "if", "else", "while", "for", "return", "void", "boolean",
                             "array", "false", "true", "function", "print", "string"};

    int i, flag = 0;

    for(i = 0; i < 15; ++i) {
        if(strcmp(keywords[i], word) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

int isDelimeter(char c){
    char delimiters[12] = "()[]{},;:\'\"";
    for (int i = 0; i < 12; ++i) {
        if (c == delimiters[i]) {
            return 1;
        }
    }
    return 0;
}

void getToken(FILE *fp) {

    char Character_0;
    while((Character_0 = fgetc(fp)) != EOF) {
        if(Character_0 == ' ' || Character_0 == '\n' || Character_0 == '\t'){
            continue;
        }
        else if(isalpha(Character_0)) {
            ungetc(Character_0, fp);
            char word[100];
            fscanf(fp, "%[a-zA-Z0-9_]s", word);

            if(isKeyword(word)) {
                printf(" %-20s \t %-20s \t %-20s\n", word, "Keywords", word);
            } else{
                printf(" %-20s \t %-20s \t ", word, "ID");

                if(getIndex(word) > 0){
                    int temp = get(word);
                    printf("%-20d\n", temp);
                }else{
                    insert(word, counter);
                    printf("%-20d\n", counter);
                    counter++;
                }
            }

        } else if(isdigit(Character_0)) {
            ungetc(Character_0, fp);
            int number;
            fscanf(fp, "%d", &number);
            printf(" %-20d \t %-20s \t %-20d\n", number, "Number", number);

        }else if(Character_0 == '"'){
            char word[100];
            fscanf(fp, "%[^\"]s", word);
            fgetc(fp);
            printf("\"%s\"%-12c STRING %13c\"%s\" \n", word, ' ', ' ', word);
        }else if(Character_0 == '/'){
            char nextChar = fgetc(fp);
            if (nextChar == '/'){
                while((Character_0 = fgetc(fp)) != '\n'){
                    continue;
                }
            }
            else if (nextChar == '*')
            {
                while((Character_0 = fgetc(fp)) != '*'){
                    continue;
                }
                fgetc(fp);
                if ((Character_0 = fgetc(fp)) == '/'){
                    continue;
                }
            }
            else{
                printf("%-20c OPERATOR %-20c\n", Character_0, Character_0);
                ungetc(nextChar, fp);
            }

        }
        else if(isDelimeter(Character_0)){
            printf("%-20c DELIMITER %20c\n", Character_0, Character_0);
        }
        else if(isOperator(Character_0)){
            if(Character_0 == '+' || Character_0 == '-' || Character_0 == '=' || Character_0 == '&' || Character_0 == '|'){
                char nextChar = fgetc(fp);
                if (Character_0 == nextChar){
                    printf("%c%-20c OPERATOR %c%20c \n", Character_0,Character_0, nextChar, nextChar);
                }
                else{
                    printf("%-20c OPERATOR  %13c\n", Character_0, Character_0);
                    ungetc(nextChar, fp);
                }
            }
            else if (Character_0 == '<' || Character_0 == '>' || Character_0 == '!'){
                char nextChar = fgetc(fp);
                if (nextChar == '='){
                    printf("%c%-20c OPERATOR  %c%20c\n", Character_0, nextChar, nextChar, nextChar);
                }
                else{
                    printf("%-20c OPERATOR %20c\n", Character_0, Character_0);
                    ungetc(nextChar, fp);
                }
            }
            else{
                printf("%-20c OPERATOR %20c\n", Character_0, Character_0);
            }
        }else if(Character_0 == '\''){
            char word[100];
            fscanf(fp, "%[^\']s", word);
            printf(" %-20s \t %-20s \t %-20s\n", word, "Char", word);

        }
        else {
            printf("Error in input!");
        }
    }
}

int main() {

    /*char code[1000];
    printf("Enter B-minor code:\n");
    fgets(code, sizeof(code), stdin);
    getToken(code);*/

    printf(" token %-17s token_type %-12s token_value\n", "", "");
    printf("------------------------------------------------------------------------\n");

    //printf("token %-20s", " ");

    FILE *file;

    file = fopen("input.txt", "r");

    if(file == NULL){
        printf("Failed to open the file.\n");
        return 0;
    }
    getToken(file);

    fclose(file);
    return 0;
}