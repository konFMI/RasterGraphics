#include"Session.h"

Session::Session()
{
	users.clear();
	currentUser = NULL;
}
void Session::InfoMessage()
{
	std::string infoUserId = "Session ID: " + std::to_string(currentUser->GetId());
	std::string infoMessageImages = "Name of images in the session : ";
	std::string infoMessagesTransformations = "Pending transformations : ";

	infoMessageImages += currentUser->GetOpenFileNames();
	infoMessagesTransformations += currentUser->GerPendingTransformations();
	throw std::string(infoUserId + '\n' + infoMessageImages + '\n' + infoMessagesTransformations);
}
void Session::HelpMessage()
{
	std::cout << "The following commands are supported :\n\n";
	std::cout << "close........................................................closes currently opened file\n";
	std::cout << "save.........................................................saves the currently opened files\n";
	std::cout << "saveas <file>................................................saves the first open file in <file>\n";
	std::cout << "help.........................................................prints this information\n";
	std::cout << "exit.........................................................exists the program\n";
	std::cout << "grayscale....................................................grayscales the images in the current session\n";
	std::cout << "monochrome...................................................monochromes the images in the current session\n";
	std::cout << "negative.....................................................negatives the images in the current session\n";
	std::cout << "rotate <direction>...........................................rotates the images in a given direction, left or right\n";
	std::cout << "undo.........................................................not implemented\n";
	std::cout << "add <image>..................................................add an image to the current session\n";
	std::cout << "session info.................................................print information about the current session\n";
	std::cout << "switch <session>.............................................switches between sessions\n";
	std::cout << "IMPORTANT: the \"rotate\" works for small sized pictures. For bigger it goes crazy.\n";
	//std::cout << "collage <direction> <image1> <image2> <outimage>.............not implemented\n";
}
void Session::Exit()
{
	throw std::string("Exiting the program...\n");
}
void Session::SaveAs(std::string path)
{
	if (users.size() >= 1)
	{
		currentUser->SaveFirstImageAs(path);
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Save()
{
	if (currentUser != NULL)
	{
		currentUser->Save();
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Close()
{
	if (currentUser != NULL)
	{
		currentUser->CloseLastOpenedFile();
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Grayscale()
{
	if (currentUser != NULL)
	{
		currentUser->AddOperation("grayscale");
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Monochrome()
{
	if (currentUser != NULL)
	{
		currentUser->AddOperation("monochrome");
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Negative()
{
	if (currentUser != NULL)
	{
		currentUser->AddOperation("negative");
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Rotate(std::string direction)
{
	if (currentUser != NULL)
	{
		currentUser->AddOperation(std::string("rotate" + direction));
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Undo()
{
	if (currentUser != NULL)
	{
		currentUser->Undo();
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Add(std::string path)
{
	if (currentUser != NULL)
	{
		
		std::string message = "";
		Image image;
		try {
			image.Open(path);
		}
		catch (std::string ms) {
			if (ms == "Successfully read file \"" + path + "\"")
			{
				currentUser->AddImage(image);
			}
			throw ms;
		}
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::SessionInfo()
{
	if (users.empty())
	{
		throw std::string("No active sessions.");
	}
	else {
		InfoMessage();
	}
}
void Session::Collage()
{
	if (currentUser != NULL)
	{
		//TODO:
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::Load(std::string path)
{
	std::string message = "";
	Image image;
	try
	{
		 image.Open(path);
	}
	catch (std::string ms)
	{
		if (ms == "Successfully read file \"" + path + "\"")
		{
			User user(users.size());
			user.AddImage(image);
			users.push_back(user);
			SwitchUser(user.GetId());
			throw std::string("User with ID: " + std::to_string(user.GetId()) + " has been created.\n" + ms);
		}
		else
		{
			throw std::string(ms);
		}
	}
	
	
}
void Session::Switch(std::string idString)
{
	if (currentUser != NULL)
	{
		
		int id = -1;
		id = StringToInt(idString);
		SwitchUser(id);
		InfoMessage();
	}
	else
	{
		throw std::string("There are no open sessions.");
	}
}
void Session::SwitchUser(int id )
{
	if (id >= 0 && id < (int)users.size())
	{
		currentUser = &users[id];
	}
}
int Session::StringToInt(std::string& width)
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
