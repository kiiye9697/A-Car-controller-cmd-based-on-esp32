#pragma warning(disable : 4996)//以有效化的取消移植性警告。
#include <iostream>
#include <string>
#include <windows.h>
#include"Car_Function.h"
#include <string>
#include <locale>
#include <codecvt>
#ifndef SERIAL_H
#define SERIAL_H
#endif
using namespace std;
unsigned char calculateBCC(const unsigned char* data, size_t length) {
    unsigned char bcc = 0x00;  // 初始化BCC值为0
    for (size_t i = 0; i < length; i++) {
        bcc ^= data[i];  // 对每个字节进行异或运算
    }
    return bcc;
}
//以下为串口初始化句柄。
bool initSerialPort(const std::wstring& portName, DWORD baudRate) {
    hSerial = CreateFile(portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,    // 不共享
        NULL, // 默认安全属性
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        return 0;
    }
    // 设置波特率、数据位、停止位等
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = baudRate;   // 使用传入的波特率
    dcbSerialParams.ByteSize = 8;          // 8个数据位
    dcbSerialParams.StopBits = ONESTOPBIT; // 1个停止位
    dcbSerialParams.Parity = NOPARITY;     // 无奇偶校验

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "设置串口参数失败!\n";
        CloseHandle(hSerial);
        return false;
    }
    return true;
}
void closeSerialPort() {
    CloseHandle(hSerial);
}
void exitexe() 
{
    exit(0);
    closeSerialPort();
};
//用这个函数将string变量改为wstring。
std::wstring stringToWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}
void forward()
{
    // 构造数据帧（不包括BCC校验字节）
    formbits[0] = 0xAA;
    formbits[1] = 0x01;
    formbits[2] = 0xFF;
    formbits[3] = 0x01;
    formbits[4] = 0xFF;
    // 计算BCC校验字节
    formbits[5] = calculateBCC(formbits, 5);
    // 发送数据帧
    WriteFile(hSerial, formbits, sizeof(formbits), &bytesWritten, NULL);
    // 关闭串口
    CloseHandle(hSerial);
}
void backward() 
{
    formbits[0] = 0xAA;
    formbits[1] = 0x00;
    formbits[2] = 0xFF;
    formbits[3] = 0x00;
    formbits[4] = 0xFF;

    formbits[5] = calculateBCC(formbits, 5);
    WriteFile(hSerial, formbits, sizeof(formbits), &bytesWritten, NULL);
    CloseHandle(hSerial);
}
void leftmove()
{
    formbits[0] = 0xAA;
    formbits[1] = 0x00;
    formbits[2] = 0x00;
    formbits[3] = 0x01;
    formbits[4] = 0xFF;

    formbits[5] = calculateBCC(formbits, 5);

    WriteFile(hSerial, formbits, sizeof(formbits), &bytesWritten, NULL);
    CloseHandle(hSerial);
}
void rightmove()
{
    formbits[0] = 0xAA;
    formbits[1] = 0x01;
    formbits[2] = 0xFF;
    formbits[3] = 0x00;
    formbits[4] = 0x00;

    formbits[5] = calculateBCC(formbits, 5);

    WriteFile(hSerial, formbits, sizeof(formbits), &bytesWritten, NULL);

    CloseHandle(hSerial);
}
void leftfast(){
    formbits[0] = 0xAA;
    formbits[1] = 0x00;
    formbits[2] = 0xFF;
    formbits[3] = 0x01;
    formbits[4] = 0xFF;

    formbits[5] = calculateBCC(formbits, 5);

    WriteFile(hSerial, formbits, sizeof(formbits), &bytesWritten, NULL);

    CloseHandle(hSerial);
}
void rightfast(){
    formbits[0] = 0xAA;
    formbits[1] = 0x01;
    formbits[2] = 0xFF;
    formbits[3] = 0x00;
    formbits[4] = 0xFF;

    formbits[5] = calculateBCC(formbits, 5);

    WriteFile(hSerial, formbits, sizeof(formbits), &bytesWritten, NULL);

    CloseHandle(hSerial);
}
void changePWM()
{
    formbits[0] = 0xAA;
    formbits[1] = 0x01;
    formbits[2] = PWM;
    formbits[3] = 0x01;
    formbits[4] = PWM;

    formbits[5] = calculateBCC(formbits, 5);

    WriteFile(hSerial,formbits, sizeof(formbits), &bytesWritten, NULL);

    CloseHandle(hSerial);
}
//以下部分来自伟大的源神，让我们感谢他:-）
/*int main()
{
    // 用户选择COM端口
    wstring comPort;
    cout << "请输入COM端口(例如: COM3): ";
    getline(wcin, comPort);

    // 用户选择波特率
    int baudRate = 9600;

    // 初始化串口
    if (!initSerialPort(comPort, baudRate)) {
        cerr << "初始化串口失败!\n";
        return 1;
    }

    while (true) {
        cout << "==============================\n";
        cout << "智能车控制菜单\n";
        cout << "选择操作:\n";
        cout << "1. 前进\n";
        cout << "2. 后退\n";
        cout << "3. 左转\n";
        cout << "4. 右转\n";
        cout << "5. 快速左转\n";
        cout << "6. 快速右转\n";
        cout << "7. PWM调速\n";
        cout << "0. 退出\n";
        cout << "==============================\n";
        cout << "请输入选项: ";

        int choice;
        cin >> choice;
        unsigned char data[6];
        DWORD bytesWritten;

        switch (choice) {
        case 1:
            // 构造数据帧（不包括BCC校验字节）
            data[0] = 0xAA;
            data[1] = 0x01;
            data[2] = 0xFF;
            data[3] = 0x01;
            data[4] = 0xFF;

            // 计算BCC校验字节
            data[5] = calculateBCC(data, 5);

            // 发送数据帧
            WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

            cout << "数据帧（包括BCC）发送成功!" << endl;

            // 关闭串口
            CloseHandle(hSerial);

            break;

        case 2:
            data[0] = 0xAA;
            data[1] = 0x00;
            data[2] = 0xFF;
            data[3] = 0x00;
            data[4] = 0xFF;

            data[5] = calculateBCC(data, 5);

            WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

            cout << "数据帧（包括BCC）发送成功!" << endl;

            CloseHandle(hSerial);

            break;

        case 3:
            data[0] = 0xAA;
            data[1] = 0x00;
            data[2] = 0x00;
            data[3] = 0x01;
            data[4] = 0xFF;

            data[5] = calculateBCC(data, 5);

            WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

            cout << "数据帧（包括BCC）发送成功!" << endl;

            CloseHandle(hSerial);

            break;

        case 4:
            data[0] = 0xAA;
            data[1] = 0x01;
            data[2] = 0xFF;
            data[3] = 0x00;
            data[4] = 0x00;

            data[5] = calculateBCC(data, 5);

            WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

            cout << "数据帧（包括BCC）发送成功!" << endl;

            CloseHandle(hSerial);

            break;

        case 5:
            data[0] = 0xAA;
            data[1] = 0x00;
            data[2] = 0xFF;
            data[3] = 0x01;
            data[4] = 0xFF;

            data[5] = calculateBCC(data, 5);

            WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

            cout << "数据帧（包括BCC）发送成功!" << endl;

            CloseHandle(hSerial);

            break;

        case 6:
            data[0] = 0xAA;
            data[1] = 0x01;
            data[2] = 0xFF;
            data[3] = 0x00;
            data[4] = 0xFF;

            data[5] = calculateBCC(data, 5);

            WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

            cout << "数据帧（包括BCC）发送成功!" << endl;

            CloseHandle(hSerial);

            break;

        case 7:
            int pwm;
            cout << "请输入速度(0-255): ";
            cin >> pwm;

            data[0] = 0xAA;
            data[1] = 0x01;
            data[2] = pwm;
            data[3] = 0x01;
            data[4] = pwm;

            data[5] = calculateBCC(data, 5);

            WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

            cout << "数据帧（包括BCC）发送成功!" << endl;

            CloseHandle(hSerial);

            break;

        case 0:
            return 0;

        default:
            cout << "无效选项，请重新选择。\n";
            break;
        }
    }
    return 0;
}
*/