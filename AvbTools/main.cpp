#include <iostream>

#include "TSharkManager.h"

int main()
{
	TShark::TSharkManager::GetInstance()->QueueJob("blabla", [](const std::string result, TShark::JobError error) {
		std::cout << "ceva";
	});

	return 0;
}