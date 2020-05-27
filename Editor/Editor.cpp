#include"Editor.h"
#include"../DrawRectangle.h"

Editor::Editor()
{
    
}
void Editor::Run()
{
    std::cin.clear();
    std::cout.clear();
    PrintWelcomeMessage();
    std::string line;
	while (true)
	{
		

		
		
		try
		{
			std::cout << "@>";
			std::getline(std::cin, line);
			std::vector<std::string> parts;

			SplitInput(line, parts);

			if (!parts.empty())
			{
				std::string command = parts[0];
				std::size_t lenght = parts.size();

				if (command == "help" && lenght == 1)
				{
					session.HelpMessage();
				}
				else if (command == "exit")
				{
					session.Exit();
				}
				else if (command == "saveas" && lenght == 2)
				{
					std::string path = parts[1];
					session.SaveAs(path);
				}
				else if (command == "save")
				{
					session.Save();
				}
				else if (command == "close" && lenght == 1)
				{
					session.Close();
				}
				else if (command == "load" && parts.size() > 1)
				{
					std::string path = parts[1];
					session.Load(path);
				}
				else if (command == "grayscale" && lenght == 1)
				{
					session.Grayscale();
				}
				else if (command == "monochrome" && lenght == 1)
				{
					session.Monochrome();
				}
				else if (command == "negative" && lenght == 1)
				{
					session.Negative();
				}
				else if (command == "rotate" && lenght == 2 && (parts[1] == "left" || parts[1] == "right"))
				{
					std::string direction = parts[1];
					session.Rotate(direction);
				}
				else if (command == "undo" && lenght == 1)
				{
					session.Undo();
				}
				else if (command == "add" && lenght == 2)
				{
					std::string path = parts[1];
					session.Add(path);
				}
				else if (command == "sessioninfo" || (command == "session" && lenght > 1 && parts[1] == "info"))
				{
					session.SessionInfo();
				}
				else if (command == "collage")
				{
					session.Collage();
				}
				else if ((command == "reset" || command == "clear" || command == "4ista4kata") && lenght == 1)
				{
					system("CLS");
				}
				else if (command == "switch" && lenght == 2)
				{
					std::string idString = parts[1];
					session.Switch(idString);
				}
				else
				{
					throw std::string("Invalid command!");
				}
			}
		}

		
		catch (std::string ms)
		{
			std::cout << ms << std::endl;
			if (ms == "Exiting the program...\n")
			{
				break;
			}

		}
		

		
	}
	std::cin.get();
}

/*
*   The welcome message.
*/
void Editor::PrintWelcomeMessage()
{
    int x = 42, y = 0;
    DrawRect(0+x, 0+y, 11+x, 5, 9+x, 1+y);
    std::cout<<"Welcome to the Basic Image Editor!";
    setxy(9+x, 2+y);
    std::cout<<"For more information type help.";
    setxy(0, 7);
}
void Editor::SplitInput(std::string& input, std::vector<std::string>& tokens)
{
	if (!input.empty())
	{


		char* memblock = &*input.begin();
		std::string temp = "";

		for (size_t i = 0; i < input.length(); i++)
		{
			if (memblock[i] == '\t' || memblock[i] == ' ' || memblock[i] == '\n')
			{
				if (temp != "")
				{
					tokens.push_back(temp);
					temp = "";
				}
			}
			else
			{
				temp += memblock[i];
			}
		}
		if (temp != "")
		{
			tokens.push_back(temp);
		}
	}
}
