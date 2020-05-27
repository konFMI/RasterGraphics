#pragma once
#include<iostream>
#include<string>
#include<vector>

class Image
{
    public:
        Image(const std::string& path);
        Image();

        void Open(std::string path);
        void Save();
        void SaveAs(const std::string& path);

        void Grayscale();
        void Monochrome();
        void Negative();
        void Undo();

        void EvaluateOperations();
        void AddOperation(std::string operation);

        std::string GetName();
        std::string GetTransformations();
private:
        std::string type;
        std::string path;
        int height;
        int width;
        int range;

        std::vector<std::string> pixels;

        std::vector<std::string> transformations;
        std::vector<std::string> oldVersion;
        std::string oldType;
        bool transformed;

        void ReadData(std::string& type, int& height, int& width, int& range, std::vector<std::string>& tokens, std::string path);
        void WriteToFile(std::string& type, int& height, int& width, int& range, std::vector<std::string>& tokens, std::string path);
        
        void RotateRight(int& width, int& height, std::vector<std::string>& ramzes, std::vector<std::string>& array);
        void RotateLeft(int& width, int& height, std::vector<std::string>& ramzes, std::vector<std::string>& array);
        
       int StringToInt(std::string& width);
        /**/
};