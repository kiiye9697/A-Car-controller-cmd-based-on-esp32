#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#ifndef SERIAL_H
#define SERIAL_H
#endif
//用到的全局变量
static HANDLE hSerial;
static std::wstring comPort;
static int Baudrate;
static unsigned char formbits[6];
static DWORD bytesWritten;
static int PWM;

//使用的功能函数
unsigned char calculateBCC(const unsigned char* data, size_t length);
bool initSerialPort(const std::wstring& portName, DWORD baudRate);
void closeSerialPort();//关闭端口
std::wstring stringToWstring(const std::string& str);

//对应的槽函数
void exitexe();
void forward();
void backward();
void leftmove();
void rightmove();
void leftfast();
void rightfast();
void changePWM();