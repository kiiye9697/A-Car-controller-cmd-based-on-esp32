#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#ifndef SERIAL_H
#define SERIAL_H
#endif
//�õ���ȫ�ֱ���
static HANDLE hSerial;
static std::wstring comPort;
static int Baudrate;
static unsigned char formbits[6];
static DWORD bytesWritten;
static int PWM;

//ʹ�õĹ��ܺ���
unsigned char calculateBCC(const unsigned char* data, size_t length);
bool initSerialPort(const std::wstring& portName, DWORD baudRate);
void closeSerialPort();//�رն˿�
std::wstring stringToWstring(const std::string& str);

//��Ӧ�Ĳۺ���
void exitexe();
void forward();
void backward();
void leftmove();
void rightmove();
void leftfast();
void rightfast();
void changePWM();