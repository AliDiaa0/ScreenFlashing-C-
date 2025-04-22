#pragma once

// ScreenFlashing.h : Header file for screen flashing functionality

// Necessary header files for the program
#include <iostream>
#include <Windows.h>
#include <cctype>

// Define constants for flashing intervals
#define null 0

// Function to flash the screen a specific number of times
int screen_flashing();

// Function to flash the screen forever
int forever_flashing();

// Function to clean the screen from the GDI mess
int clean_screen();

// Function to check if the input is a valid integer
bool is_valid_integer(const std::string& str);

// Global variables for screen flashing
extern HWND hwnd;
extern HDC hdc;
extern RECT rect;
extern int width;
extern int height;
extern int timesFlashed;
extern int flashingInterval;
extern int clean;