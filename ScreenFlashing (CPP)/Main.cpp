/* Project: ScreenFlashing
*
Description: A simple console application that does some screen flashing GDI for Windows using the BitBlt function from wingdi.h, written completely in C++. This program allows the user to specify the number of times to flash the screen and the interval between flashes. It also provides an option for endless flashing until the program is terminated by the user.

Compatibilty: Windows XP and above, 32-bit or 64-bit, on all versions.

Author: Ali Diaa */

// We need to put this at the beginning of Main.cpp to run on Windows XP and above (just because it is C++, damn...).
typedef struct IUnknown IUnknown;

#include "ScreenFlashing.h"

// Variables for screen flashing
HWND hwnd;
HDC hdc;
RECT rect;
int width;
int height;
int timesFlashed;
int flashingInterval;
int clean;

int screen_flashing() {

	for (int i = 0; i < timesFlashed; i++) {

		BitBlt(hdc, null, null, width, height, hdc, null, null, NOTSRCCOPY);

		Sleep(flashingInterval);
	}

	return null;

}

int forever_flashing() {

	while (true) {

		BitBlt(hdc, null, null, width, height, hdc, null, null, NOTSRCCOPY);

		Sleep(flashingInterval);
	}

	return null;

}

int clean_screen() {

	for (clean = 0; clean < 10; clean++) {

		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, null, SPIF_SENDCHANGE);

		Sleep(10);

	}

	return null;

}

bool is_valid_integer(const std::string& str) {

	if (str.empty()) return false;
	for (char c : str) {

		if (!std::isdigit(c)) return false;
	}

	return true;

}

int main() {

	char inputBuffer[100];

	// Set the console title
	SetConsoleTitleW(TEXT("Screen Flashing Program (by Ali Diaa)"));

	// Set the console text color to light blue
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	// Get the handle to the desktop window
	hwnd = GetDesktopWindow();

	// Get the device context of the desktop window
	hdc = GetWindowDC(hwnd);

	// Get the dimensions of the screen
	GetWindowRect(hwnd, &rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	std::cout << "Enter the number of times to flash the screen. If you want it to be forever (endless unless you terminate the program yourself, enter 0 - to terminate it, press Alt + F4) (must be integer):" << std::endl;

	std::cin.getline(inputBuffer, sizeof(inputBuffer));

	std::string inputStr(inputBuffer);

	if (!is_valid_integer(inputStr)) {

		MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer for specific times of flashing or 0 for endless flashing."),
			TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);

		return 1;

	}

	timesFlashed = std::atoi(inputStr.c_str());

	if (timesFlashed == 0) {
		std::cout << "Enter the flashing interval in milliseconds (must be integer):\n";
		std::cin.getline(inputBuffer, sizeof(inputBuffer));
		inputStr = inputBuffer;

		if (!is_valid_integer(inputStr)) {
			MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer value for the interval."),
				TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
			return 1;
		}

		flashingInterval = std::atoi(inputStr.c_str());
		forever_flashing();
	}

	else if (timesFlashed < 0) {
		MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer for specific times of flashing or 0 for endless flashing."),
			TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
		return 1;
	}

	else if (timesFlashed > 0) {
		// LOL, the user can enter a value like 7598475498357984759874389675 and the program will still run the flashing that value. XD

		std::cout << "Enter the flashing interval in milliseconds (must be integer):\n";
		std::cin.getline(inputBuffer, sizeof(inputBuffer));
		inputStr = inputBuffer;

		if (!is_valid_integer(inputStr)) {

			MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer value for the interval."),
				TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
			return 1;

		}

		flashingInterval = std::atoi(inputStr.c_str());

		screen_flashing();
		clean_screen();
		MessageBoxW(null, TEXT("Flashing is done!"), TEXT("Flashing done"), MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
	}

	else {

		MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer for specific times of flashing or 0 for endless flashing."),
			TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
		return true;

	}

	return null;

}