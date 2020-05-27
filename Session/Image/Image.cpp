#include<iostream>
#include<fstream>
#include"Image.h"



Image::Image()
{
    this->transformed = false;
    this->height = 0;
    this->width = 0;
    this->range = 0;
}
Image::Image(const std::string& path)
{
    this->path = path;
    ReadData(type, height, width, range, pixels, path);
    this->transformed = false;
}

void Image::Open(std::string path)
{
    this->path = path;
    ReadData(type,height,width,range,pixels,path);
}
void Image::Save()
{
    WriteToFile(type, height, width, range, pixels, path);
}
void Image::SaveAs(const std::string& pathTo)
{
    WriteToFile(type, height, width, range, pixels, pathTo);

}

void Image::Grayscale()
{
    std::vector<std::string> grayscaledPixels;
    int first = 0,
        second = 0,
        third = 0,
        grayscaledValue = 0;
    for (int i = 0; i < (int)pixels.size() - 2; i+=3)
    {
        first = StringToInt(pixels[i]);
        second = StringToInt(pixels[i+1]);
        third =StringToInt(pixels[i+2]);
        grayscaledValue = ((int)(first*0.23 + second*0.47 + third*0.30)) / 3;
        grayscaledPixels.push_back(std::to_string(grayscaledValue));
    }
    oldType = type;
    oldVersion = pixels;
    type = "P2";
    pixels = grayscaledPixels;

}
void Image::Monochrome()
{
    std::vector<std::string> LuminancePixels;
    int first = 0,
        second = 0,
        third = 0,
        LuminanceValue = 0;
    for (int i = 0; i < (int)pixels.size() - 2; i += 3)
    {
        first = StringToInt(pixels[i]);
        second = StringToInt(pixels[i + 1]);
        third = StringToInt(pixels[i + 2]);
        LuminanceValue = ((int)(first * 0.2125 + second * 0.7154 + third * 0.0721));
        LuminancePixels.push_back(std::to_string(LuminanceValue));
    }
    type = "P1";
    pixels = LuminancePixels;
    oldType = type;
    oldVersion = pixels;
    
}
void Image::Negative()
{
	std::vector<std::string> negativePixels;
    int pixel = 0,
       
        negativeValue = 0;
    for (int i = 0; i < (int)pixels.size() ; i ++)
    {
        pixel = StringToInt(pixels[i]);
        negativeValue = (int)(250 - pixel);
        negativePixels.push_back(std::to_string(negativeValue));
    }
    type = "P3";
    pixels = negativePixels;
    oldType = type;
    oldVersion = pixels;

}
void Image::Undo()
{
    pixels = oldVersion;
    type = oldType;

}

void Image::EvaluateOperations()
{
    for (size_t i = 0; i < transformations.size(); i++)
    {
        std::string transformation = transformations[i];
        if (transformation == "grayscale" && type =="P3")
        {
            Grayscale();
            throw std::string("Transformed");
        }
        else if (transformation == "monochrome")
        {
            Monochrome();
            throw std::string("Transformed");
        }
        else if (transformation == "negative")
        {
            Negative();
            throw std::string("Transformed");

        }
        else if (transformation == "rotateleft")
        {
            oldVersion = pixels;
            RotateLeft(height, width, pixels, oldVersion);
            throw std::string("Transformed");
        }
        else if (transformation == "rotateright")
        {
            oldVersion = pixels;
            RotateRight(height, width, pixels, oldVersion);
            throw std::string("Transformed");
        }
        transformed = true;
    }
}
void Image::AddOperation(std::string operation)
{
    transformations.push_back(operation);
}

std::string Image::GetName()
{
    return path;
}
std::string Image::GetTransformations()
{
    std::string transformatiosMessage = "";
    if (transformations.size() >= 1)
    {
        for (size_t i = 0; i < transformations.size() - 1; i++)
        {
            transformatiosMessage += transformations[i] + ", ";
        }
        transformatiosMessage += transformations[transformations.size() - 1];
    }
    return transformatiosMessage;
}

void Image::WriteToFile(std::string& type, int& height, int& width, int& range, std::vector<std::string>& tokens, std::string path)
{
    std::ofstream myfile(path, std::ios::trunc);
    if (myfile.is_open())
    {
        if (type == "P3")
        {


            myfile << type <<std::endl;
            myfile << width << "   " << height << std::endl;
            myfile << range;
            for (long i = 0; i < (long)tokens.size(); i++)
            {
               

                    if (width != 0 && i % (width * 3) == 0)
                    {
                        myfile << std::endl;
                    }
                    else if(width == 0 && i % 3 == 0)
                    {
                        myfile << std::endl;

                    }
                    myfile << "   " << tokens[i];
                
            }
            myfile.close();
        }
        else if (type == "P1" || type == "P2")
        {
            myfile << type << std::endl;
            myfile << width << "   " << height << std::endl;
            if (type != "P1")
            {
                myfile << range;
            }
            for (long i = 0; i < (long)tokens.size(); i++)
            {
                


                    if (width != 0 && i % width == 0)
                    {
                        myfile << std::endl;
                    }
                    else if (width == 0 && i % 3)
                    {
                        myfile << std::endl;

                    }
                    myfile << "   " << tokens[i];
                
            }
            myfile.close();
        }
        else
        {
            myfile.close();
            throw std::string("Cannot work with file type \"" + type + "\"");
        }
    }
    else
    {
        throw std::string("Unable to open file \"" + path + "\"");
    }

    throw std::string("Successfully wrote to file \"" + path + "\"");
}
void Image::ReadData(std::string& type, int& height, int& width, int& range, std::vector<std::string>& tokens, std::string path)
{
    std::ifstream file(path, std::ios::in | std::ios::ate);
    std::streampos size;
    char* memblock = NULL;

    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();
    }
    else
    {
        throw std::string("Cannot open file!");
    }


    std::string token = "";

    for (long i = 0; i < size; i++)
    {
        if (memblock[i] == ' ' || memblock[i] == '\n')
        {
            if (token != "")
            {
                tokens.push_back(token);
                token = "";
            }
        }
        else if (
            memblock[i] == '0' || memblock[i] == '1' || memblock[i] == '1' || memblock[i] == '2' || memblock[i] == '3' || memblock[i] == '4' ||
            memblock[i] == '5' || memblock[i] == '6' || memblock[i] == '7' || memblock[i] == '8' || memblock[i] == '9' || memblock[i] == 'P')
        {
            token += memblock[i];
        }
    }
    if (token != "" && token != " ")
    {
        tokens.push_back(token);
    }


    delete memblock;


    if (tokens.size() >= 1)
    {
        type = tokens[0];
    }
    else
    {
        throw std::string("Can't read file. Not enough information in it.");
    }

    if (type == "P1")
    {
        if (tokens.size() >= 3)
        {
            width = StringToInt(tokens[1]);
            height = StringToInt(tokens[2]);
            range = 1;
            for (long i = 0; i < (long)tokens.size() - 3; i++)
            {
                tokens[i] = tokens[i + 3];
                while (tokens[i].find("P") != std::string::npos)
                {
                    tokens[i].replace(tokens[i].find("P"), 1, " ");
                }
                
            }
            tokens.pop_back();
            tokens.pop_back();
            tokens.pop_back();
        }
        else
        {
            throw std::string("Can't read file. Not enough information in it.");
        }

    }
    else if (type == "P3" || type == "P2")
    {
        if (tokens.size() >= 4)
        {
            width = StringToInt(tokens[1]);
            height = StringToInt(tokens[2]);
            range = StringToInt(tokens[3]);
            for (long i = 0; i < (long)tokens.size() - 4; i++)
            {
                tokens[i] = tokens[i + 4];
                while (tokens[i].find("P") != std::string::npos)
                {
                    tokens[i].replace(tokens[i].find("P"), 1, " ");
                }
            }
            tokens.pop_back();
            tokens.pop_back();
            tokens.pop_back();
            tokens.pop_back();
        }
        else
        {
            throw std::string("Can't read file. Not enough information in it.");
        }
    }
    else
    {
        throw std::string("Can't read file. Type \"" + type + "\" is not supported.");
    }

    throw std::string("Successfully read file \"" + path + "\"");
}

void Image::RotateRight(int& height, int& width, std::vector<std::string>& ramzes, std::vector < std::string > & array)
{
    ramzes.clear();
    for (int i = 0; i < width; i++)
    {
        for (int j = height - 1; j >= 0; j--)
        {
            ramzes.push_back(array[j * width + i]);
        }
    }
    std::swap(height, width);
}
void Image::RotateLeft(int& height, int& width, std::vector<std::string>& ramzes, std::vector<std::string>& array)
{
    ramzes.clear();
    for (long i = width - 1; i >= 0; i--)
    {
        for (long j = 0; j < height; j++)
        {
            ramzes.push_back(array[j * width + i]);
        }
    }
    std::swap(height, width);
}

int Image::StringToInt(std::string& width)
{
    {
        int num = 0;
        for (size_t i = 0; i < width.length(); i++)
        {
            if (isdigit(width[i]))
            {
                num *= 10;
                num += (width[i] - '0');
            }
            else if (i > 0)
            {
                throw std::string("Invalid input.");
            }
        }
        if (width.length() > 0 && width[0] == '-')
        {
            num *= (-1);
        }
        return num;
    }
}
