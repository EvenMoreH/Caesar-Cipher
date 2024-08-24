#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char excluded[] = "!@#$\%^&*()_+-=[]{}|\\/?,.\"\'";
const char num[] = "01234567890123456789012345";
const char replacement[] = " ";
const char space[] = " ";
char cryptoSpace[1];

const char outputFolderStr[] = "../output/";
const char outputExtensionStr[] = ".txt";

char tempString[2001];
char fromFile[2001];
char input[2001];
char output[2001];
char customFileName[129];


// Substitution cipher modifier
int c = 0;
// Required for start from the beginning calculations
int mod;

bool sp;
char temp;
int cryptoSp;

void clearBuffer();
void cipherSpace(bool sp);
int readCipher();
int writeCipher();
int secretFile();

int main() {

    printf("\nSelect encryption offset:\n[Number between -25 and 25]\n> ");
    scanf(" %3i", &c);

    if (c < -25 || c > 25)
    {
        printf("\n\nERROR - Try Again\n\n");
        clearBuffer();
    }

    printf("\nWould you like to encrypt spaces?\n[Y/N]?\n> ");
    scanf(" %c", &temp);
    temp = tolower(temp);
    if (temp == 'y')
    {
        cipherSpace(true);
    }
    else
    {
        cipherSpace(false);
        printf("\nSpaces will be left as they are.\n");
    }
    clearBuffer();

    readCipher();
    strcpy(input, fromFile);

    int length = strlen(input);

    for (int u = 0; u < length; u++)
    {
        input[u] = toupper(input[u]);
    }

    // Loops through whole input and removes special characters by shifting left by 1 if character is found
    char* excludeSpecialCharacters;
    for (int r = 0; r < 26; r++)
    {
        while ((excludeSpecialCharacters = strchr(input, excluded[r])) != NULL)
        {
            strcpy(excludeSpecialCharacters, excludeSpecialCharacters + 1);
        }
    }


    printf("\nFollowing text will be encrypted, please wait...\n%s\n", input);

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (input[i] == alpha[j])
            {
                // To start from 1st letter
                int mod = j + c;
                if (j + c >= 26)
                {
                    mod = mod - 26;
                }
                else if (j + c < 0)
                {
                    mod = mod + 26;
                }
                output[i] = alpha[mod];
                mod = j + c;
            }
            else if (input[i] == space[0])
            {
                if (cryptoSp == 1)
                {
                    output[i] = cryptoSpace[0];
                }
                else
                {
                    output[i] = space[0];
                }
            }
            else if (input[i] == num[j])
            {
                output[i] = num[j];
            }
        }
    }


    printf("\nEncrypted message:\n%s\n\n", output);

    system("pause");

    printf("\nWould you like write the cipher to the file?\n[Y/N]?\n> ");
    scanf(" %c", &temp);
    temp = tolower(temp);
    if (temp == 'y')
    {
        clearBuffer();
        printf("\nName your Cipher file:\n> ");
        scanf(" %128[^\n]", &customFileName);
        writeCipher();
        secretFile();
    }
    printf("\n");

    system("pause");

    return 0;
}

// Clear the input buffer
void clearBuffer() {
    int clearBuffer;
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF)
    { }
}

void cipherSpace(bool sp) {
    if (sp == 1)
    {
        printf("\nInput a character to be used instead of space:\n> ");
        scanf(" %1c", &cryptoSpace[0]);
        cryptoSp = 1;
    }
}

int readCipher() {
    const char* inputTXT = "../include/input.txt";
    FILE* inputFile = fopen(inputTXT, "r");

    if (inputFile == NULL) {
        perror("\nUnable to open file");
        return 1;
    }

    while (fscanf(inputFile, "%2000[^\n]\n", &fromFile) != EOF)
    {
        strcat(tempString, fromFile);
        strcat(tempString, " ");
    }
    strcpy(fromFile, tempString);

    // To remove last white space
    int terminator = strlen(fromFile);
    fromFile[terminator - 1] = '\0';

    fclose(inputFile);
}

int writeCipher() {
    char outputTXT[129];
    char outputFolderStrTemp[129];
    char outputExtensionStrTemp[129];

    strcpy(outputFolderStrTemp, outputFolderStr);
    strcpy(outputExtensionStrTemp, outputExtensionStr);

    strcat(outputFolderStrTemp, customFileName);
    strcat(outputFolderStrTemp, outputExtensionStrTemp);
    strcpy(outputTXT, outputFolderStrTemp);

    FILE* outputFile = fopen(outputTXT, "w");

    if (outputFile == NULL) {
        perror("\nUnable to open file");
        return 1;
    }

    fprintf(outputFile, output);

    fclose(outputFile);
}

int secretFile() {
    char secretFolderStrTemp[129];
    char secretTXT[129];
    char secretExtensionStr[] = "-secret.txt";

    strcpy(secretFolderStrTemp, outputFolderStr);
    strcat(secretFolderStrTemp, customFileName);
    strcat(secretFolderStrTemp, secretExtensionStr);
    strcpy(secretTXT, secretFolderStrTemp);

    FILE* outputSecretFile = fopen(secretTXT, "w");

    if (outputSecretFile == NULL) {
        perror("\nUnable to open file");
        return 1;
    }

    char convertedC[5];
    sprintf(convertedC, "%d", c);


    fprintf(outputSecretFile, "> Substitution Cipher modifier: ");
    fprintf(outputSecretFile, convertedC);
    fprintf(outputSecretFile, "\n");
    fprintf(outputSecretFile, "> Character used instead of Space: ");
    fprintf(outputSecretFile, cryptoSpace);
    fprintf(outputSecretFile, "\n");
    fprintf(outputSecretFile, "> Original text:");
    fprintf(outputSecretFile, "\n");
    fprintf(outputSecretFile, input);

    fclose(outputSecretFile);
}