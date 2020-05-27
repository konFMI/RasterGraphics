#pragma once

#include"User/User.h"
class Session
{
    public:
        Session();
        void InfoMessage();
        void HelpMessage();
        void Exit();
        void SaveAs(std::string path);
        void Save();
        void Close();
        void Grayscale();
        void Monochrome();
        void Negative();
        void Rotate(std::string direction);
        void Undo();
        void Add(std::string path);
        void SessionInfo();
        void Collage();
        void Load(std::string path);
        void Switch(std::string idString);
        void SwitchUser(int id);

    private:
        std::vector<User> users;
        User* currentUser;

        int StringToInt(std::string& width);
        
       
};