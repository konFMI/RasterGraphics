#pragma once
#include"../Session/Session.h"

/*
*   This class is the main one for running the application.
*   It deals with reading the user input and passing it to the Session class.
*   It also catches the exception messages and prints them.
*/
class Editor
{
    public:

        Editor();
        void Run();
        void PrintWelcomeMessage();

    private:
        Session session;
        
        void SplitInput(std::string& input, std::vector<std::string>& tokens);
        

};

