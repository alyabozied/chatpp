#include "ui.hh"

UI* UI::ui = nullptr;
UI::UI(){

}
UI* UI::initUI(){
    if(ui == nullptr){
        ui = new UI();
        initscr();
        timeout(30);
        noecho();
        cbreak();
        refresh();
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_BLUE);
    }
    return ui;

}
UI::~UI(){

}
std::string UI::readUserInput(){
    c = getch();
    if(c==10){
        currentMessage.push_back('\0');
        std::string s = std::string(currentMessage.begin(),currentMessage.begin()+currentMessage.size());

        currentMessage.clear();
        
        move(20,0);
        clrtoeol();
        currentchar=0;
        return s;
    }
    if(isalnum(c) || c == ' '){
        attron(COLOR_PAIR(2));

        mvprintw(20,currentchar++,"%c",c);
        currentMessage.push_back(c);
     
    }
    if(c == 127 && currentMessage.size()>0){        
        currentMessage.pop_back();
        currentchar--;
        mvprintw(20,currentchar," ");
        move(20,currentchar);
     
    }
    return std::string();
}
void UI::printMessages(char*buffer,int type){
    if(type ==1 ){
        attron(COLOR_PAIR(1));
        mvprintw(currentLine,0,"You: ");
    }
    else{
        attron(COLOR_PAIR(2));
        mvprintw(currentLine,0,"Friend: ");
    }
    printw("%s\n",buffer);
    currentLine++;
    refresh();
}
void UI::printMessages(std::string s,int type){
    if(type ==1 ){
        attron(COLOR_PAIR(1));
        mvprintw(currentLine,0,"You: ");
    }
    else{
        attron(COLOR_PAIR(2));
        mvprintw(currentLine,0,"Friend: ");
    }
    printw("%s\n",s.c_str());
    currentLine++;
    refresh();
}