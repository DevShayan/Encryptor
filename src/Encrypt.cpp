#include "../include/Encrypt.h"
#include <cstdlib>
#include <fstream>

Encrypt::Encrypt()
{
    for (int x=0; x<a; x++){
            arry[x][0] = (char)(96+x);
        for (int y=0; y<b-1; y++){
            if (x==0){
                if (y == b-2){
                    arry[x][y+1] = (char)(32);
                }
                else {
                    arry[x][y+1] = (char)(97+y);
                }
            }
            else if (x+y > 26){
                if (arry[x][y] == 'z'){
                    arry[x][y+1] = (char)(32+x);
                }
                else {
                    arry[x][y+1] = (char)(69+x+y);
                }
            }
            else {
                arry[x][y+1] = (char)(96+x+y);
            }
        }
    }
}

std::string Encrypt::encrpt(std::string& epText, std::string& ekey)
{
    int first, second;

    std::string crypted;
    crypted.resize(epText.length());

    for (unsigned int x=0; x<epText.length(); x++){
        second = 0;
        for (int y=0; y<b; y++){
            if (arry[0][y] == epText.at(x) || (arry[0][y])-32 == epText.at(x)){
                second = y;
            }
        }
        for (int z=0; z<a; z++){
            if (arry[z][0] == ekey.at(x)){
                first = z;
            }
        }
        if (second == 0){
            crypted.at(x) = epText.at(x);
        }
        else if ((arry[0][second])-32 == epText.at(x)) {
            crypted.at(x) = arry[first][second];
            crypted.at(x) -= 32;
        }
        else {
            crypted.at(x) = arry[first][second];
        }
    }
    return crypted;
}

std::string Encrypt::decrpt(std::string& dpText, std::string& dkey)
{
    std::string crypted;
    crypted.resize(dpText.length());

    int check;
    for (unsigned int x=0; x<dkey.length(); x++){
        check = 0;
        for (int y=0; y<a; y++){
            if (arry[y][0] == dkey.at(x)){
                for (int z=0; z<b; z++){
                    if (arry[y][z] == dpText.at(x)){
                        crypted.at(x) = arry[0][z];
                        check = 1;
                    }
                    else if ((arry[y][z])-32 == dpText.at(x)){
                        crypted.at(x) = arry[0][z];
                        crypted.at(x) -= 32;
                        check = 1;
                    }
                }
            }
        }
        if (check == 0){
            crypted.at(x) = dpText.at(x);
        }
    }
    return crypted;
}

void Encrypt::printCipher()
{
    system("clear");
    for (int x=0; x<a; x++){
        for (int y=0; y<b; y++){
            std::cout << arry[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Press any key to continue...\n";
    system("read dummy");
}

std::string Encrypt::setKey(std::string& pText, std::string& key)
{
    for (unsigned int q=0; q<key.length(); q++){
        if (isupper(key.at(q))){
            key.at(q) += 32;
        }
    }

    if (key.length() > pText.length()){
        key.resize(pText.length());
    }
    else {
        static int y = 0;

        for (unsigned int x=0; x<pText.length(); x++){

            key.resize(pText.length(), ' ');

            if (key.at(x) == ' '){
                key.at(x) = key.at(y);
                y++;
            }
        }
        y = 0;
    }

    return key;

}

void Encrypt::exp(std::string& edata)
{
    std::string keye, mkeye, checker;
    std::fstream efile ("data.txt", std::ios::in); /// in for checking key

    if (efile.fail()){
        std::fstream iefile ("data.txt", std::ios::out);
        std::cout << "Enter a key: ";
        std::cin >> keye;
        iefile << keye << std::endl;
        std::cout << keye; system("pause"); /// Checker
        iefile.close();
    }
    else {
        efile >> keye;
    }
    efile.close();


    mkeye = setKey(edata, keye);

    std::fstream mefile ("data.txt", std::ios::app);

    mefile << "-------------------------------------------" << std::endl;
    mefile << encrpt(edata, mkeye) << std::endl;
    mefile << "-------------------------------------------" << std::endl;
    mefile.close();
}

void Encrypt::imp()
{
    std::string line, keyi, mkeyi;
    std::fstream ifile("data.txt", std::ios::in);

    if (ifile.fail()){
        std::cout << "File not open!"; system("pause");
    }
        std::cout << "Enter a key: ";
        std::cin >> keyi;
        std::cout << std::endl;

    while (std::getline(ifile, line)){
        mkeyi = setKey(line, keyi);
        std::cout << decrpt(line, mkeyi) << std::endl;
    }
    ifile.close();
    std::cout << "Press any key to continue...\n";
    system("read dummy");
}

void Encrypt::start()
{
    system("clear");
    std::string menuInput, input, input1, w, key;
    std::cout << "To encrypt or decrypt, type 'd'\nTo feed data, type 'f': ";
    std::cin >> menuInput;
    std::cout << std::endl;

    if (menuInput == "d"){
        system("clear");
        std::cout << "To encrypt, type 'e'\nTo decrypt, type 'd': ";
        std::cin >> input;
        std::cout << std::endl;

        if (input == "e"){
            system("clear");
            std::cout << "Enter a phrase to encrypt: ";
            std::cin.ignore();
            std::getline(std::cin, w);
            std::cout << std::endl;
        }
        else if (input == "d"){
            system("clear");
            std::cout << "Enter a phrase to decrypt: ";
            std::cin.ignore();
            std::getline(std::cin, w);
            std::cout << std::endl;
        }
    }
    else if (menuInput == "f"){
        system("clear");
        std::cout << "To see saved data, type 'sd'\nTo add data, type 'ad': ";
        std::cin >> input1;

        if (input1 == "sd"){ /// Requires a key.
            imp();
        }
        else if (input1 == "ad"){  /// Requires a key in if file is empty.
            std::cout << "Enter data below:\n";
            std::cin.ignore();
            std::getline(std::cin, w);
            std::cout << std::endl;
            exp(w);
        }
    }

    if (menuInput != "f"){
        std::cout << "Enter a key: ";
        std::cin >> key;
        std::string mkey = setKey(w, key);
        std::cout << std::endl;

        if (input == "e"){
            std::cout << "Encrypted data: " << encrpt(w, mkey) << std::endl;
            std::cout << std::endl;
        }
        else if (input == "d"){
            std::cout << "Decrypted data: " << decrpt(w, mkey) << std::endl;
            std::cout << std::endl;
        }
        std::cout << "Press any key to continue...\n";
        system("read dummy");
    }

}
