#include <bits/stdc++.h>

#ifdef _WIN32
#include "Windows.h"
#endif

/*
by farmersrice
*/
using namespace std;


const string SCP_START_STRING_SUBSTRING = "<p><strong>Item #:</strong>";
const string SCP_END_STRING = "<div class=\"footer-wikiwalk-nav\">";
const string SCP_END_STRING_2 = "<!-- wikidot_bottom_300x250 -->";


void replaceStringInPlace(string &target, string toFind, string toReplaceWith) {
	int position = 0;

	while ((position = target.find(toFind)) != string::npos) {
		target.replace(position, toFind.length(), toReplaceWith);
	}
}

set<string> viewedFiles;

void viewFile(string scpname = "INVALID") {

	if (scpname == "INVALID") {
		cout << "Which file would you like to access? (Format: SCP-XXX or SCP-XXXX)" << endl;
		cin >> scpname;
	}

	string filename = scpname + ".scp";

	viewedFiles.insert(filename);

	cout << "filename is " << filename << endl << endl;

	for (char &c : scpname) c = tolower(c);

	cout << "Retrieving file... " << "curl http://www.scp-wiki.net/" + scpname + " --output " + filename << endl;

	system(("curl http://www.scp-wiki.net/" + scpname + " --output " + filename).c_str());

	cout << endl;

	ifstream fin(filename);

	string currentLine;

	bool notUsingWindows = true;

	#ifdef _WIN32
	notUsingWindows = false;
	#endif

	bool active = false;


	set<string> currentTags;

	
	while (getline(fin, currentLine)) {
		if (currentLine.find(SCP_START_STRING_SUBSTRING) != string::npos) {
			active = true;
		}
		if (currentLine.find(SCP_END_STRING) != string::npos || currentLine.find(SCP_END_STRING_2) != string::npos) {
			active = false;
			break;
		}

		if (active) {

			//another sad hack
			//we cannot render the html characters so we have to substitute their lame equivalents
			replaceStringInPlace(currentLine, "&nbsp;", " ");
			replaceStringInPlace(currentLine, "&#160;", " ");
			replaceStringInPlace(currentLine, "&quot;", "\"");
			replaceStringInPlace(currentLine, "&lt;", "--"); //also because too lazy to parse <>
			replaceStringInPlace(currentLine, "&gt;", "--");
			replaceStringInPlace(currentLine, "&#8230;", "...");

			bool printedSomething = false;

			string currentTag = "";
			bool inTag = false;
			bool closeTag = false;


			bool printedBlockquote = false;

			//parse the line
			for (char c : currentLine) {
				if (c == '<') {
					//Starting a tag
					inTag = true;
					currentTag = "";
				} else if (c == '/' && inTag) {
					//closing a tag
					currentTag = "";
					closeTag = true;
				} else if (c == '>') {
					//ending a tag

					//Now print new string based on the tag we just got

					if (closeTag) {
						if (notUsingWindows) cout << "\e[0m";

						currentTags.erase(currentTag);
					} else {
						if (currentTag == "strong") {
							//Make bold.

							if (notUsingWindows) cout << "\e[1m";
						} else if (currentTag == "em") {
							//Make italic
							//Not supported 
						} else {
							//All other tags unsupported
						}

						currentTags.insert(currentTag);
					}

					inTag = false;
					closeTag = false;

				} else if (inTag) {
					currentTag += c;
				} else {
					if (!printedBlockquote && currentTags.find("blockquote") != currentTags.end()) {
						//cout << "WE ARE IN BLOCKQUOTE " << endl;
						cout << "    ";
						printedBlockquote = true;
					}

					printedSomething = true;
					cout << c;
				}
			}

			if (printedSomething) cout << endl << endl;
		}
	}

	fin.close();
	
	if (remove(filename.c_str()) != 0) {
		perror("uh oh spaghetti os -- please report on github, thank you");
	}

	cout << endl;
}

void fastquit() {
	#ifdef _WIN32
	system("CLS"); //works on windows
	#else
	system("clear && printf '\e[3J'"); //should work on linux/mac, tested in Windows Subsystem for Linux so far
	#endif
	exit(0);
}

void quit() {
	//This part is just to look cool -- ofc we delete files as soon as we print them to text
	cout << "Deleting local files." << endl;

	for (string filename : viewedFiles) {
		cout << "Deleting " << filename << "... ";
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "Done" << endl; 
	}

	cout << "Clearing sensitive information in 5 seconds." << endl;

	this_thread::sleep_for(chrono::milliseconds(5000));

	fastquit();
}


int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);

	ifstream logoin("logo.txt");
	string logoLine;
	while (getline(logoin, logoLine)) {
		cout << logoLine << endl;
	}

	logoin.close();

	cout << "Welcome." << endl;

	while (true) {
		cout << "> " << flush;

		string input;
		cin >> input;

		if (input == "access") {
			viewFile();
		} else if (input == "quit") {
			quit();
		} else if (input == "fastquit") {
			fastquit();
		} else if (input == "help") {
			cout << "Use \"access\" to access files (ex. \"access SCP-140\" or \"access SCP-4001\"). Type \"quit\" to quit, and \"fastquit\" to quit with haste." << endl;
		} else {
			cout << "Invalid command." << endl;
		}
	}	
}

//don't do dumb stuff with merge-sort tree like using update when everything is static...

//IF IT'S MATH THE ANSWER IS IN THE GCD, GCD THE INPUTS, OR WHATEVER USE GCD
//CAST .SIZE() TO INT!!!!

//PRO TIP: THE BEST WAY TO SOLVE THE PROBLEM IS TO HAVE THE RIGHT ANSWER!