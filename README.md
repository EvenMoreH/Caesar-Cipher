# Caesar-Cipher
Rough implementation of Ceasar Cipher that uses letter substitution.

## Initial build supports:
1. Read/write from/to file.
2. Letter substitution by fixed number of letters up or down the alphabet.
3. Selection if space should be replaced by chosen character or left untouched.
4. Generation of secret file that contains:
    - Letter substitution offset used for the cipher
    - Which character replaced space (if any).
    - Original text.

## How to:
1. Open input.txt file located in include folder.
2. Write plain text that should be encrypted.
    * WARNING:
        - Any special characters will be removed from input.
        - Non-english characters may cause error.
        - If '%' will be used as a space substitution, it will not be displayed in -secret file. (bug caused by C compiler >I guess...<).
        - Numbers will not be encrypted. (at least for now).
3. Start CaesarCipher.exe
4. File with chosen name will appear in output folder. (if selected).
5. File with chosen name and '-secret' extension will appear in output folder. (if selected).

## Project Tree:
📦Caesar-Cipher  
 ┣ 📂include  
 ┃ ┗ 📜input.txt  
 ┣ 📂output  
 ┣ 📂src  
 ┃ ┣ 📜CaesarCipher.c  
 ┃ ┗ 📜CaesarCipher.exe  
 ┣ 📜.gitignore  
 ┗ 📜README.md  
