#pragma once

#include <iostream>	// for cout
#include <string>	// for string
#include <thread>	// for milliseconds and sleepfor

// ANSI code for clearing the screen
// for example: cout << ICS_CLEAR_SCREEN;
const std::string ICS_CLEAR_SCREEN =				"\033[H\033[2J\033[3J";

// ANSI codes for setting text color
// for example: cout << ICS_BLUE_TEXT << "Blue text!" << endl;
const std::string ICS_BLACK_TEXT =					"\033[30m";
const std::string ICS_RED_TEXT =					"\033[31m";
const std::string ICS_GREEN_TEXT =					"\033[32m";
const std::string ICS_YELLOW_TEXT =					"\033[33m";
const std::string ICS_BLUE_TEXT =					"\033[34m";
const std::string ICS_MAGENTA_TEXT =				"\033[35m";
const std::string ICS_CYAN_TEXT =					"\033[36m";
const std::string ICS_WHITE_TEXT =					"\033[37m";
const std::string ICS_INTENSE_BLACK_TEXT =			"\033[90m";
const std::string ICS_INTENSE_RED_TEXT =			"\033[91m";
const std::string ICS_INTENSE_GREEN_TEXT =			"\033[92m";
const std::string ICS_INTENSE_YELLOW_TEXT =			"\033[93m";
const std::string ICS_INTENSE_BLUE_TEXT =			"\033[94m";
const std::string ICS_INTENSE_MAGENTA_TEXT =		"\033[95m";
const std::string ICS_INTENSE_CYAN_TEXT =			"\033[96m";
const std::string ICS_INTENSE_WHITE_TEXT =			"\033[97m";

// ANSI codes for setting the console window's color
// for example: cout << ICS_CYAN_BACKGROUND;
const std::string ICS_BLACK_BACKGROUND =			std::string("\033[40m") + ICS_CLEAR_SCREEN;
const std::string ICS_RED_BACKGROUND =				std::string("\033[41m") + ICS_CLEAR_SCREEN;
const std::string ICS_GREEN_BACKGROUND =			std::string("\033[42m") + ICS_CLEAR_SCREEN;
const std::string ICS_YELLOW_BACKGROUND =			std::string("\033[43m") + ICS_CLEAR_SCREEN;
const std::string ICS_BLUE_BACKGROUND =				std::string("\033[44m") + ICS_CLEAR_SCREEN;
const std::string ICS_MAGENTA_BACKGROUND =			std::string("\033[45m") + ICS_CLEAR_SCREEN;
const std::string ICS_CYAN_BACKGROUND =				std::string("\033[46m") + ICS_CLEAR_SCREEN;
const std::string ICS_WHITE_BACKGROUND =			std::string("\033[47m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_BLACK_BACKGROUND =	std::string("\033[100m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_RED_BACKGROUND =		std::string("\033[101m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_GREEN_BACKGROUND =	std::string("\033[102m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_YELLOW_BACKGROUND =	std::string("\033[103m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_BLUE_BACKGROUND =		std::string("\033[104m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_MAGENTA_BACKGROUND =	std::string("\033[105m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_CYAN_BACKGROUND =		std::string("\033[106m") + ICS_CLEAR_SCREEN;
const std::string ICS_INTENSE_WHITE_BACKGROUND =	std::string("\033[107m") + ICS_CLEAR_SCREEN;

/*
 * If value is less than min, it is set to min.
 * If value is greater than max, it is set to max.
 *
 * @param value		The value to clamp.
 * @param min		The minimum that value can be.
 * @param max		The maximum that value can be.
*/
template <typename T>
void ICS_clamp(T& value, T min, T max)
{
	// make sure value is no less than min
	if (value < min)
	{
		value = min;
	}

	// make sure value is no more than max
	if (value > max)
	{
		value = max;
	}
}

/**
 * Waits for the user to press a key before continuing with the program, similar
 * to system("cls") in Windows, but this function should be platform independent
 */
void ICS_pause()
{
#ifdef _WIN32
	// on Windows, this will be exectuted
	system("pause");
#else
	// all other operating systems will execute this
	std::cout << "Press any key to continue . . .";
	getchar();
#endif
}

/**
 * This causes the program to sleep for period of time.
 *
 * @param milliseconds	The number of milliseconds to sleep for.
 */
void ICS_sleep(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

/*
 * This generates an ANSI code to change the text color in the console window using RGB values.
 *
 *	Example:
 *
 *		cout << ICS_textColor(255, 0, 255);
 *
 * @param red		The red component of the color.  Must be between 0 and 255.
 * @param green		The green component of the color.  Must be between 0 and 255.
 * @param blue		The blue component of the color.  Must be between 0 and 255.
 *
 * @returns		An ANSI code for setting the text color in the console window.
 */
std::string ICS_textColor(int red, int green, int blue)
{
	// make sure the components are in the correct range
	ICS_clamp(red, 0, 255);
	ICS_clamp(green, 0, 255);
	ICS_clamp(blue, 0, 255);

	// create the ANSI escape code
	std::string code = "\033[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";

	// set the foreground color
	return code;
}

/**
 * This generates an ANSI code to change the background color of the console window using RGB values.
 *
 *	Example:
 *
 *		cout << ICS_backgroundColor(255, 0, 255);
 *
 * @param red		The red component of the color.  Must be between 0 and 255.
 * @param green		The green component of the color.  Must be between 0 and 255.
 * @param blue		The blue component of the color.  Must be between 0 and 255.
 *
 * @returns			An ANSI code for setting the background color of the console window.
 */
std::string ICS_backgroundColor(int red, int green, int blue)
{
	// make sure the components are in the correct range
	ICS_clamp(red, 0, 255);
	ICS_clamp(green, 0, 255);
	ICS_clamp(blue, 0, 255);

	// create the ANSI escape code
	std::string code = "\033[48;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";

	// set the background color
	return code + ICS_CLEAR_SCREEN;
}