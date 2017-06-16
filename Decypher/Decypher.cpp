#include "stdafx.h"
#include "Actions.h"
#include "Console.h"
#include "FileC.h"
#include "VBMathsR.h"
#include <ctime>
#include <fstream>
#include <future>
#include <string>
#include <thread>
#define Code 31517
#define NumToAdd 23619

using namespace std;
VBMathsR r,r1;
volatile bool publishProggress = false;
volatile unsigned int kCounter = 0;
volatile unsigned int k = 0;
volatile long long lengthOfFile = 0;

void Help();
void PublishProccess();
void Wrong_Args();
long GetSeed(string password);
void NoPass(const string FileName);
void WithPass(const string FileName, const string Password);
void WriteRes(string Header, string IP);

int main(int argc, char* argv[])
{
	try {
		if (argc <= 1) Help();
		else if (argc > 3) Wrong_Args();
		else if (argc == 2) NoPass(argv[1]);
		else if (argc == 3) WithPass(argv[1], argv[2]);
		else Wrong_Args();
	}
	catch (exception& ex) {
		WORD s = Console::GetColor();
		cout << "\n";
		Console::SetColor(12);
		cout << ex.what();
		cout << "\n";
		Console::SetColor(s);
	}
	system("pause");
	return 0;
}
void NoPass(const string FileName) {
	//Values
	int RandomNumber;
	unsigned long NumberToWrite = 0;
	string HeaderF = "";
	string ipF = "";
	string MainFileNameF = "";
	string Head;
	vector<string> HeadS;
	vector<string> tempSplit;
	ofstream fout;
	ifstream infile;
	system(("title Decrypting " + FileName).c_str()); //Title
	cout << "Validating File";
	if (!File::Exists(FileName)) throw exception("The file does not exist.");
	if (!Actions::DECFormat(FileName)) throw exception("File must have dec format.");
	this_thread::sleep_for(0.5s);
	cout << ".";
	if (File::FileSize(FileName) == 0) throw exception("File is empty.");
	if (!Actions::FileValidDEC_ENG(FileName)) throw exception("File is not valid.");
	this_thread::sleep_for(0.5s);
	cout << ".";
	if (!Actions::FileSpiltsCheck(FileName)) throw exception("File is not valid.");
	this_thread::sleep_for(0.3s);
	cout << "." << endl;
	this_thread::sleep_for(0.3s);
	//Read
	system("cls");
	system("title Reading and Decrypting...");
	cout << "Reading File";
	try {
		clock_t start = clock();
		{
			ifstream infile1;
			infile1.open(FileName, ios::binary | ios::ate);
			lengthOfFile = infile1.tellg();
			infile1.close();
		}
		infile.open(FileName);
		getline(infile, Head);//Reading Header
		lengthOfFile -= Head.size();
		HeadS = StringF::split(Head, ':');
		//Mian encryption
		system("cls");
		//Decrypt Header
		tempSplit = StringF::split(HeadS[2], ' ');
		for (unsigned int i = 0; i < tempSplit.size(); i++) {
			RandomNumber = ToInt32(r.Rnd() * 50000);
			NumberToWrite = (stoi(tempSplit[i]) - NumToAdd - RandomNumber) ^ Code;
			HeaderF += (char)NumberToWrite;
		}
		//Decrypt IP
		tempSplit = StringF::split(HeadS[4], ' ');
		for (unsigned int i = 0; i < tempSplit.size(); i++) {
			RandomNumber = ToInt32(r.Rnd() * 50000);
			NumberToWrite = (stoi(tempSplit[i]) - NumToAdd - RandomNumber) ^ Code;
			ipF += (char)NumberToWrite;
		}
		//Decrypt Main File
		tempSplit = StringF::split(HeadS[6], ' ');
		for (unsigned int i = 0; i < tempSplit.size(); i++) {
			RandomNumber = ToInt32(r.Rnd() * 50000);
			NumberToWrite = (stoi(tempSplit[i]) - NumToAdd - RandomNumber) ^ Code;
			MainFileNameF += (char)NumberToWrite;
		}
		//Free memory
		Head.~basic_string();
		HeadS.~vector();
		tempSplit.~vector();
		//Setup async publishing
		fout.open(MainFileNameF, ios::out | ios::binary);
		publishProggress = true;
		future<void> fut1 = async(PublishProccess);
		//Decrypt Main
		//Decrypt every 500,000,000 chars
		unsigned int countOfTimes = ((unsigned int)(lengthOfFile / 500000000)) + 1;
		for (kCounter = 0; kCounter < countOfTimes;) {
			unsigned int TEMP = 500000000;
			vector<char> CHARS;
			vector<char> b;
			char c;
			if (countOfTimes - 1 == kCounter) {
				TEMP = lengthOfFile % 500000000;
				CHARS.resize(TEMP);
				CHARS.shrink_to_fit();
				infile.read(&CHARS[0], TEMP);
			}
			else {
				CHARS.resize(500000000);
				infile.read(&CHARS[0], 500000000);
				while (1) {
					infile.get(c);
					CHARS.push_back(c);
					if (c == ' ')
						break;
				}
				CHARS.shrink_to_fit();
			}
			unsigned long Number = 0;
			int RN;
			for (k = 0; k < CHARS.size(); k++) {
				c = CHARS[k];
				if (c == ' ') {
					RN = ToInt32(r.Rnd() * 50000);
					Number -= NumToAdd;
					Number -= RN;
					Number ^= Code;
					b.push_back((char)Number);
					Number = 0;
				}
				else {
					Number *= 10;
					switch (c)
					{
					case '1':
						Number += 1;
						break;
					case '2':
						Number += 2;
						break;
					case '3':
						Number += 3;
						break;
					case '4':
						Number += 4;
						break;
					case '5':
						Number += 5;
						break;
					case '6':
						Number += 6;
						break;
					case '7':
						Number += 7;
						break;
					case '8':
						Number += 8;
						break;
					case '9':
						Number += 9;
						break;
					default:
						break;
					}
				}
			}
			CHARS.clear();
			CHARS.shrink_to_fit();
			fout.write(reinterpret_cast<const char*>(&b[0]), b.size() * sizeof(char));
			k = 0;
			kCounter++;
		}
		infile.close();
		publishProggress = false;
		system("cls");
		cout << "100% Done";
		//Write
		system("title Writing To File...");
		fout.close();
		system("title Done");
		double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
		//Publish
		system("cls");
		cout << "Decryption Complete!" << endl;
		cout << endl;
		cout << endl;
		this_thread::sleep_for(0.2s);
		cout << "Done in " << elapsedTime << " Seconds" << "\n";
		this_thread::sleep_for(0.2s);
		WORD s = Console::GetColor();
		Console::SetColor(14);
		WriteRes(HeaderF, ipF);
		Console::SetColor(s);
		cout << endl;
		cout << "By Hirbod Behnam And Hacknet" << endl;
		cout << endl;
		this_thread::sleep_for(0.5s);
		cout << endl;
		cout << endl;
		cout << endl;
	}
	catch (exception e) {
		throw e.what();
	}
	catch (...) {
		throw exception("An error happened.");
	}

}
void WithPass(const string FileName, const string Password) {
	//Values
	int RandomNumber;
	char c;
	unsigned long NumberToWrite = 0;
	string HeaderF = "";
	string ipF = "";
	string MainFileNameF = "";
	string Head;
	vector<string> HeadS;
	vector<string> tempSplit;
	ofstream fout;
	ifstream infile;
	system(("title Decrypting " + FileName).c_str()); //Title
	cout << "Validating File";
	if (!File::Exists(FileName)) throw exception("The file does not exist.");
	if (!Actions::DECFormat(FileName)) throw exception("File must have dec format.");
	this_thread::sleep_for(0.5s);
	cout << ".";
	if (File::FileSize(FileName) == 0) throw exception("File is empty.");
	if (!Actions::FileValidDEC_ENG(FileName)) throw exception("File is not valid.");
	this_thread::sleep_for(0.5s);
	cout << ".";
	if (!Actions::FileSpiltsCheck(FileName)) throw exception("File is not valid.");
	this_thread::sleep_for(0.3s);
	cout << "." << endl;
	this_thread::sleep_for(0.3s);
	//Read
	system("cls");
	system("title Reading and Decrypting...");
	cout << "Reading File";
	try {
		lengthOfFile = File::FileSize(FileName);
		clock_t start = clock();
		{
			ifstream infile1;
			infile1.open(FileName, ios::binary | ios::ate);
			lengthOfFile = infile1.tellg();
			infile1.close();
		}
		infile.open(FileName);
		getline(infile, Head);//Reading Header
		lengthOfFile -= Head.size();
		HeadS = StringF::split(Head, ':');
		//Mian encryption
		system("cls");
		//Decrypt Header
		tempSplit = StringF::split(HeadS[2], ' ');
		for (unsigned int i = 0; i < tempSplit.size(); i++) {
			RandomNumber = ToInt32(r.Rnd() * 50000);
			NumberToWrite = (stoi(tempSplit[i]) - NumToAdd - RandomNumber) ^ Code;
			HeaderF += (char)NumberToWrite;
		}
		//Decrypt IP
		tempSplit = StringF::split(HeadS[4], ' ');
		for (unsigned int i = 0; i < tempSplit.size(); i++) {
			RandomNumber = ToInt32(r.Rnd() * 50000);
			NumberToWrite = (stoi(tempSplit[i]) - NumToAdd - RandomNumber) ^ Code;
			ipF += (char)NumberToWrite;
		}
		//Decrypt Main File
		tempSplit = StringF::split(HeadS[6], ' ');
		for (unsigned int i = 0; i < tempSplit.size(); i++) {
			RandomNumber = ToInt32(r.Rnd() * 50000);
			NumberToWrite = (stoi(tempSplit[i]) - NumToAdd - RandomNumber) ^ Code;
			MainFileNameF += (char)NumberToWrite;
		}
		vector<char> b;
		fout.open(MainFileNameF, ios::out | ios::binary);
		//Decrypt Main
		long codeForPass = 0;
		for (unsigned int i = 0; i < Password.length(); i++) {
			c = Password.at(i);
			NumberToWrite = (int)c ^ 42;
			codeForPass += NumberToWrite;
		}
		r.Rnd(-1);
		r.Randomize(GetSeed(Password));
		r1.Rnd(-1);
		r1.Randomize(GetSeed(Password));
		publishProggress = true;
		future<void> fut1 = async(PublishProccess);
		//Decrypt every 500,000,000 chars
		int Number_Read = 0;
		unsigned int countOfTimes = ((unsigned int)(lengthOfFile / 500000000)) + 1;
		for (kCounter = 0; kCounter < countOfTimes;) {
			unsigned int TEMP = 500000000;
			vector<char> CHARS;
			vector<char> b;
			char c;
			if (countOfTimes - 1 == kCounter) {
				TEMP = lengthOfFile % 500000000;
				CHARS.resize(TEMP);
				CHARS.shrink_to_fit();
				infile.read(&CHARS[0], TEMP);
			}
			else {
				CHARS.resize(500000000);
				infile.read(&CHARS[0], 500000000);
				while (1) {
					infile.get(c);
					if (c == ' ')
						break;
					else {
						CHARS.push_back(c);
					}
				}
				CHARS.shrink_to_fit();
			}
			for (k = 0; k < CHARS.size(); k++) {
				char c = CHARS[k];
				if (c == ' ') {
					RandomNumber = ToInt32(r.Rnd() * 50000);
					NumberToWrite = (Number_Read - NumToAdd - RandomNumber) ^ Code ^ codeForPass;
					if (NumberToWrite > 127) b.push_back((char)(NumberToWrite - 256));
					else b.push_back((char)NumberToWrite);
					Number_Read = 0;
				}
				else {
					Number_Read *= 10;
					switch (c)
					{
					case '1':
						Number_Read += 1;
						break;
					case '2':
						Number_Read += 2;
						break;
					case '3':
						Number_Read += 3;
						break;
					case '4':
						Number_Read += 4;
						break;
					case '5':
						Number_Read += 5;
						break;
					case '6':
						Number_Read += 6;
						break;
					case '7':
						Number_Read += 7;
						break;
					case '8':
						Number_Read += 8;
						break;
					case '9':
						Number_Read += 9;
						break;
					default:
						break;
					}
				}
			}
			fout.write(reinterpret_cast<const char*>(&b[0]), b.size() * sizeof(char));
			k = 0;
			kCounter++;
		}
		infile.close();
		publishProggress = false;
		system("cls");
		cout << "100% Done";
		//Write
		system("title Writing To File...");
		fout.close();
		system("title Done");
		double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
		//Publish
		system("cls");
		cout << "Decryption Complete!";
		cout << endl;
		cout << endl;
		this_thread::sleep_for(0.2s);
		cout << "Done in " << elapsedTime << " Seconds" << "\n";
		this_thread::sleep_for(0.2s);
		WORD s = Console::GetColor();
		Console::SetColor(14);
		WriteRes(HeaderF, ipF);
		Console::SetColor(s);
		cout << endl;
		cout << "By Hirbod Behnam And Hacknet" << endl;
		cout << endl;
		this_thread::sleep_for(0.5s);
		cout << endl;
		cout << endl;
		cout << endl;
	}
	catch (exception e) {
		throw e.what();
	}
	catch (...) {
		throw exception("An error happened.");
	}
}
void Help() {
	cout << "Decypher.exe FileName [Password]" << endl;
	cout << "  FileName: The file name with the format and it must be in current directory." << endl;
	cout << "  Password: The password for decryption." << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}
void Wrong_Args() {
	WORD s = Console::GetColor();
	Console::SetColor(12);
	cout << "Please enter right args to use the app. Example:" << endl;
	Console::SetColor(s);
	Help();
}
void PublishProccess() {
	while (1) {
		system("cls");
		cout << int((kCounter * 500000000 + k) * 100.0 / lengthOfFile) << "% Done";
		this_thread::sleep_for(0.2s);
		if (!publishProggress)
			return;
	}
}
long GetSeed(const string password) {
	unsigned char change = 0; //0:XOR 1:Sum 2:Different 3:Bitshift and Or
	long i = 0;
	for (unsigned int j = 0; j < password.length(); j++) {
		switch (change) {
		case 1:
			i += (int)password.at(j);
			break;
		case 2:
			i -= (int)password.at(j);
			break;
		case 3:
			i = i >> (int)password.at(j) | (int)password.at(j);
			break;
		case 4:
			i ^= (int)password.at(j);
			change = 1;
			break;
		case 0:
			i ^= (int)password.at(j);
			break;
		}
		change++;
	}
	return abs(i);
}
void WriteRes(string Header, string IP) {
	Header = " " + Header;
	IP = " " + IP;
	string SourceIP = "| Source IP:";
	string HeaderStr = "| Header:";
	string TopEnd = "+";
	int ipLength = IP.length();
	int HeaderLength = Header.length();
	int HeaderStrLength = HeaderStr.length();
	int SourceIPLength = SourceIP.length();
	int MostChar = Actions::Max(SourceIPLength, Actions::Max(ipLength, HeaderLength));
	for (int i = 1; i <= MostChar; i++) {
		TopEnd += "-";
		SourceIPLength--;
		if (SourceIPLength <= 1) SourceIP += " ";
		ipLength--;
		if (ipLength <= 1) IP += " ";
		HeaderStrLength--;
		if (HeaderStrLength <= 1) HeaderStr += " ";
		HeaderLength--;
		if (HeaderLength <= 1) Header += " ";
	}
	TopEnd += "--+";
	SourceIP += " |";
	HeaderStr += " |";
	cout << TopEnd << endl;
	this_thread::sleep_for(0.2s);
	cout << SourceIP <<endl;
	this_thread::sleep_for(0.2s);
	cout << "|" + IP + "|" << endl;
	this_thread::sleep_for(0.2s);
	cout << HeaderStr << endl;
	this_thread::sleep_for(0.2s);
	cout << "|" + Header + "|" << endl;
	this_thread::sleep_for(0.2s);
	cout << TopEnd << endl;
}