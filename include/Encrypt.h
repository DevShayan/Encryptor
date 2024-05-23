#include <iostream>
#ifndef ENCRYPT_H
#define ENCRYPT_H


class Encrypt
{
    private:
        const static int a = 27;
        const static int b = 28;
        char arry[a][b];

    public:
        Encrypt();
        std::string encrpt(std::string& epText, std::string& ekey);
        std::string decrpt(std::string& dpText, std::string& dkey);
        void printCipher();
        void exp(std::string& edata);
        void imp();
        void start();
        std::string setKey(std::string& pText, std::string& key);

};

#endif
