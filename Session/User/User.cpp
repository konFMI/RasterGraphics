#include"User.h"

User::User()
{
	ID= -1;
}
User::User(int id)
{
	ID = id;
}

void User::AddImage(Image& image)
{
	images.push_back(image);
}

void User::AddOperation(std::string operation)
{
	if (images.size() > 0)
	{
		pendingTransformations.push_back(operation);
		for (size_t i = 0; i < images.size(); i++)
		{
			images[i].AddOperation(operation);
		}
	}
}


int User::GetId()
{
	return ID;
}

std::string User::GetOpenFileNames()
{
	std::string message = "";
	for (size_t i = 0; i < images.size(); i++)
	{
		message += images[i].GetName() + " ";
	}

	return message;
}


std::string User::GerPendingTransformations()
{
	std::string transformatiosMessage = "";
	if (pendingTransformations.size() >= 1)
	{
		for (size_t i = 0; i < pendingTransformations.size() - 1; i++)
		{
			transformatiosMessage += pendingTransformations[i] + ", ";
		}
		transformatiosMessage += pendingTransformations[pendingTransformations.size() - 1];
	}
	return transformatiosMessage;
}

void User::SaveFirstImageAs(std::string path)
{
	if (images.size() >= 1)
	{
		try {
			images[0].EvaluateOperations();
		}
		catch (std::string ms)
		{
			if (ms == "Transformed")
			{
				images[0].SaveAs(path);
			}
			else {
				throw ms;
			}
		}
	}
	if (images.size() == 1)
	{
		pendingTransformations.clear();
	}
}

void User::CloseLastOpenedFile()
{
	if (!images.empty())
	{
		std::string imageName = images[images.size() - 1].GetName();
		images.pop_back();
		throw std::string("Closed file \"" + imageName + "\"");
	}
	else
	{
		throw std::string("There are no open files.");
	}
}

void User::Save()
{
	//TODO: Not sure if it is the best.
	std::string savedFiles = "";
	if (images.size() > 0)
	{
		pendingTransformations.clear();
		for (size_t i = 0; i < images.size(); i++)
		{
			try
			{
				images[i].EvaluateOperations();
			}
			catch (std::string ms)
			{
				if (ms == "Transformed")
				{
					try {
						images[i].Save();
					}
					catch (std::string ms)
					{
						if (ms == "Successfully wrote to file \"" + images[i].GetName() + "\"")
						{
							savedFiles += (ms + "\n");
						}
					}
				}
			}
			
		}
	}
	throw savedFiles;

}

void User::Undo()
{
	for (size_t i = 0; i < images.size(); i++)
	{
		images[i].Undo();
	}
}