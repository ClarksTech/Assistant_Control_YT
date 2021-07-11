//Include all required libraries
#include	<fstream>
#include	<iostream>
#include	<string>	
#include	<windows.h>

//set namespace
using namespace std;

//initalise functions we want the program to perform
int lock_command();
int shutdown_command();
int restart_command();
int keystroke_command(int KEY); //allows windows keybord shortcuts to be used

int main()
{
	//Program loop to run continuously
	while (1)
	{
		//locate the command file and set as an input stream to be stored in variable
		ifstream commandFile("C:\\Users\\crutt\\Dropbox\\Assistant_Control\\Command.txt");
		string command;

		//check if there is a new command by attempting to open file
		if (commandFile.is_open())
		{
			//read in the command and store as string
			getline(commandFile, command);

			//Check for a match with command and functions this program can perform - if match found, execute function
			if (command == "lock")
			{
				lock_command();	
			}
			else if (command == "shut down")
			{
				shutdown_command();
			}
			else if (command == "restart")
			{
				restart_command();
			}
			else if (command == "play" || command == "pause")
			{
				keystroke_command(0xB3);
			}
			else if (command == "play the next track" || command == "skip")
			{
				keystroke_command(0xB0);
			}
			else if (command == "play the previous track" || command == "go back")
			{
				keystroke_command(0xB1);
				keystroke_command(0xB1);	//needed twice as single key press will only restart the track
			}
			else if (command == "restart track" || command == "replay the song")
			{
				keystroke_command(0xB1);
			}
			else if (command == "turn the volume up" || command == "turn up the volume")
			{
				keystroke_command(0xAF);	//this is an increment of 2% therefore 5x for 10%
				keystroke_command(0xAF);
				keystroke_command(0xAF);
				keystroke_command(0xAF);
				keystroke_command(0xAF);
			}
			else if (command == "turn the volume down" || command == "turn down the volume")
			{
				keystroke_command(0xAE);	//this is an increment of 2% therefore 5x for 10%
				keystroke_command(0xAE);
				keystroke_command(0xAE);
				keystroke_command(0xAE);
				keystroke_command(0xAE);
			}

			//now all matches explored close the file and delete it so command is not run multiple times
			commandFile.close();
			remove("C:\\Users\\crutt\\Dropbox\\Assistant_Control\\Command.txt");
		}
		//sleep program for 5 seconds so that it does not hog resources
		Sleep(5000);
	}
}

//Lock function
int lock_command()
{
	system("rundll32.exe user32.dll, LockWorkStation");
	return 1;
}

//shutdown function
int shutdown_command()
{
	system("shutdown /s");
	return 1;
}

//restart function
int restart_command()
{
	system("shutdown /r");
	return 1;
}

//Keystroke Function - take any keystroke input and execute it as a keyboard emulation
int keystroke_command(int KEY)
{
	//setup virtual keyboard
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	//press key signal
	ip.ki.wVk = KEY;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	//release key signal
	ip.ki.wVk = KEY;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	return 1;
}