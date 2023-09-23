#include <Windows.h>
#include <thread>
#include "../util/xorstr.h"
#include "logger.h"
#include "../../main.hh"
#include "termcolor.h"

FILE* out;
FILE* err;

static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool check_license(const char* user, const char* users_license)
{
	std::string license;
	size_t ll = strlen(users_license);
	size_t l = strlen(user), lic_ctr = 0;
	int add = 0;

	for (size_t i = 0; i < ll; i++)
		if (users_license[i] != '-')
			license += users_license[i];

	while (lic_ctr < license.length()) {
		size_t i = lic_ctr;
		i %= l;
		int current = 0;
		while (i < l) current += user[i++];
		current += add;
		add++;
		if (license[lic_ctr] != letters[current % sizeof letters])
			return false;
		lic_ctr++;
	}
	return true;
}

void msg(std::string msg) {
	std::string msg1 = ' ' + msg;
	std::cout << termcolor::white << "[" << termcolor::green << "#" << termcolor::white << "]" << msg1 + "\n";
}

void ASCII(std::string msg) {
	std::cout << termcolor::yellow << msg;
}

void Logger::infoMsg(std::string msg) {
	std::string msg1 = ' ' + msg;
	std::cout << termcolor::white << "[" << termcolor::yellow << "?" << termcolor::white << "]" + msg1 + "\n";
}

void Logger::Init()
{
	AllocConsole();
	freopen_s(&out, "CONOUT$", "w", stdout);
	freopen_s(&err, "CONOUT$", "w", stderr);

	std::cout << "  ___________   .__    .___                               \n";
	std::cout << " /   _____/  | _|__| __| _/_  _  _______ _______   ____   \n";\
	std::cout << " \\_____  \\|  |/ /  |/ __ |\\ \\/ \\/ /\\__  \\\\_  __\\_/ __ \\  \n";
	std::cout << " /        \\    <|  / /_/ | \\     /  / __ \\|  | \\/\\  ___/  \n";
	std::cout << "/_______  /__|_ \\__\\____ |  \\/\\_/  (____  /__|	\\___  > \n";
	std::cout << "        \\/     \\/       \\/              \\/          \\/  \n";
	std::cout << ("Best Client \n");
	std::cout << ("https://discord.gg/qhq28Sz2GP \n");

	std::cout << "Loading Skidware...\n";

	//std::cout << "Started Initialization \n";
	//fclose(out);
	//fclose(err);
	//FreeConsole();

	Logger::Initialized = true;
}

void Logger::Kill()
{
	if (Logger::Initialized)
	{
		fclose(out);
		fclose(err);
		FreeConsole();
	}
}

void Logger::Log(std::string message)
{
	if (!Logger::Initialized) Logger::Init();
	std::string msg1 = ' ' + message;
	std::cout << termcolor::white << "[" << termcolor::yellow << "LOG" << termcolor::white << "]" + msg1 + "\n";
	//std::cout << "[ LOG ] :: " + message << "\n";
	Sleep(1000);
}

void Logger::Log(double message)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << message << "\n";
	Sleep(1000);
}


void Logger::LogPosition(Vector3 position)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG POS ] :: X -> " << position.x << " Y -> " << position.y << " Z ->" << position.z << std::endl;
	Sleep(1000);
}

void Logger::Err(std::string message)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ ERR ] :: " + message << std::endl;
	Sleep(1000);
}

void Logger::LogWait(std::string message, int seconds)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG ] :: " + message << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	//Sleep(1000);
}

void Logger::ErrWait(std::string message, int seconds)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ ERR ] :: " + message << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	//Sleep(1000);
}
