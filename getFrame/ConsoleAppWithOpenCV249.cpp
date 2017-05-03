// ConsoleAppWithOpenCV249.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
#include <iostream>
#include <direct.h>

using namespace cv;
using namespace std;

string firstName;
int perFrame = 15;
bool needResize = false;
bool isFast = false;
bool isExist;

string getFileName(int argc, char* argv[]){
	string pathString, temp, dirString;
	char pathChar[2000], *dirPath = new char[2000];
	isExist = false;
	if (argc > 0 && argv[1] != NULL){
		strcpy_s(pathChar, argv[1]); //Pointer to Char
		cout << pathChar << endl;
		pathString.assign(pathChar); //Char to String
		strcpy_s(pathChar, argv[2]); //Pointer to Char
		dirString.assign(pathChar);
		firstName = "output/" + dirString + "/";
		strcpy(dirPath, firstName.c_str());
		if (_mkdir(dirPath) != 0){
			cout << "無法新增，或已存在" << firstName << endl;
			system("pause");
			isExist = true;
		}
		if (!isExist){
			if (argc > 3){
				for (int i = 3; i < argc; i++){
					if (argv[i] != NULL){
						strcpy_s(pathChar, argv[i]); //Pointer to Char
						if (pathChar[0] == '-'){
							if (!needResize){
								needResize = pathChar[1] == 'r' ? true : false;
								if (needResize) cout << "[need resize: true]";
							}
							if (!isFast){
								isFast = pathChar[1] == 'f' ? true : false;
								if (isFast) cout << "[skip pause: true]";
							}
						}
						else{
							int sum = atoi(pathChar);
							cout << "[get frame per " << sum << " frame]";
							perFrame = sum;
						}
					}
				}
				cout << endl;
			}
			else{
				needResize = false;
			}
		}
	}
	else{
		cout << "[Video Path][output folder name][needResize][skipPause]" << endl
			<< "-------------------------------------------------------" << endl
			<< "Video Path = 影片路徑" << endl
			<< "output folder name = 輸出資料夾名稱" << endl
			<< "needResize = -r 是否需要壓縮至272p" << endl
			<< "skipPause = -f 是否需要壓縮至272p" << endl
			<< "-------------------------------------------------------" << endl
			<< "拖曳影片檔案至視窗，或是輸入檔案路徑：" << endl;
		getline(cin, temp);
		//-- Remove the " mark in head and tail
		if (pathString.assign(temp, 0, 1) == "\""){
			pathString = pathString.assign(temp, 1, temp.length() - 2);
		}
		else{
			pathString = temp;
		}
		if (pathString == ""){
			throw std::runtime_error("path is error");
		}
		else{
			do{
				std::cout << "輸出資料夾名稱" << std::endl;
				getline(cin, dirString);
				firstName = "output/" + dirString + "/";

				strcpy(dirPath, firstName.c_str());
				if (_mkdir(dirPath) != 0){
					cout << "無法新增，或已存在" << firstName << endl;
				}
			} while (_mkdir(dirPath) == 0);
		}
	}
	return pathString;
}

int main(const int argc, char* argv[])
{
	VideoCapture capture;
	string pathString;
	try{
		pathString = getFileName(argc, argv);
	}
	catch (const std::exception &e){
		cout << e.what() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	char chars[] = { '-', '\\', '|', '/' };
	unsigned int frameCount = 0;
	Mat res;
	capture.open(pathString);
	if (!isExist){
		if (capture.isOpened())
		{
			int count = 0;
			for (;;)
			{
				res;
				capture >> res;
				if (!res.empty())
				{
					if (frameCount % perFrame == 0){
						// Process animetion.
						printf("%c\r", chars[frameCount % sizeof(chars)]);
						// Generate file name.
						char s[6];
						sprintf_s(s, "%05d", frameCount);
						string outputName, outNum(s);
						outputName = firstName + outNum + ".png";
						//cout << outputName << endl;
						//system("cls");

						if (needResize){
							// Resize the frame.
							Mat res272;
							resize(res, res272, Size(480, 272));
							// Save the frame to image.
							imwrite(outputName, res272);
						}
						else{
							imwrite(outputName, res);
						}
					}
					frameCount++;
				}
				else
				{
					printf("-- Finished --\n");
					if (!isFast)
						system("pause");
					return EXIT_SUCCESS;
				}
				int c = waitKey(1);
				if ((char)c == 'c') { waitKey(0); }
			}
		}
		else{
			cout << "Can't open the file.";
		}
		system("pause");
	}
	return EXIT_SUCCESS;
}