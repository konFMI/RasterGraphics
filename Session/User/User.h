#pragma once
#include"../Image/Image.h"

class User
{
    public:
        User();
        User(int id);
        int GetId();
        std::string GetOpenFileNames();
        std::string GerPendingTransformations();

        void SaveFirstImageAs(std::string);
        void CloseLastOpenedFile();
        void AddImage(Image&);
        void AddOperation(std::string);
        void Save();
        void Undo();
    private:
        int ID;
        std::vector<Image> images;
        std::vector<std::string> pendingTransformations;
       
};