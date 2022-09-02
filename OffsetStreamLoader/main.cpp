#include "utils.h"

namespace Globals {
	uintptr_t ImageBase;

	namespace StreamedVariables {
		uintptr_t GWorld; // https://github.com/kenn-notation/OffsetStreaming/raw/master/ExampleOffset -> 0xDEADBEEF for example
	}
}

void LoopExample() {

	for (int i = 0; i < 10; i++)
	{
		auto ImportantUWorld = Utils::Read<uintptr_t>(Globals::ImageBase + Globals::StreamedVariables::GWorld);
		printf("ImportantUWorld: %p\n", ImportantUWorld);
		Sleep(1000);
	}
}


void GetVarFromServer() {
	while (true)
	{
		std::string Offset = Utils::GetString("https://github.com/kenn-notation/OffsetStreaming/raw/master/ExampleOffset");
		Globals::StreamedVariables::GWorld = std::strtoul(Offset.c_str(), NULL, 16);
		if (Globals::StreamedVariables::GWorld == 0) // -> Simple check to see if the variable has been killed from the server / link
			exit(0); // -> Exits if the stream isnt valid or killed

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main()
{
	printf("At entry!\n");

	std::thread(GetVarFromServer).detach(); // -> Starting the get offset thread

	LoopExample(); // -> Game hack loop example

	getchar();

	return 0;
}
