#pragma once 
#include <ncurses.h>
#include <vector>
#include <string>
class UI {
    
    public:
        static UI* initUI();
        ~UI();
        std::string readUserInput();
        void printMessages(char*buffer,int type);
        void printMessages(std::string buffer,int type);
    private:
        char c;
        int currentLine=0;
        int x = 0;
        int currentchar=0;
        static UI* ui;    
        std::vector<char> currentMessage;
        UI();
        UI(UI const&);
        
        void operator=(UI const &);

};

