#include <windows.h>
#include <iostream>
#include "volume.h"

using namespace std;

// 每隔 1 秒输出一次音量
static void printVolume() {
    while (true) {
        cout << getVolume() << endl;
        Sleep(1000);
    }
}

// 只输出一次音量
static void printVolumeOnce() {
    cout << getVolume() << endl;
}

int main(int argc, char* argv[]) {
    // 根据命令行参数，判断是否需要循环输出音量
    if (argc > 1 && strcmp(argv[1], "-m") == 0)
    {
        // 在控制台的执行命令：volume.exe -m
        printVolume();
    }
    // 当输入的参数为-o时，只输出一次音量
    else if (argc > 1 && strcmp(argv[1], "-o") == 0)
    {
        printVolumeOnce();
    }
    // 当输入的参数为 -s 时，设置音量
    else if (argc > 2 && strcmp(argv[1], "-s") == 0)
    {
        // 输出要设置的音量大小
        // cout << "set volume: " << argv[2] << endl;
        int res = setVolume(atoi(argv[2]));
        if (res == 0) {
            cout << "success" << endl;
        }
        else {
            cout << "error" << endl;
        }
    }
    // 当输入的参数为 -mo 时，输出麦克风音量
    else if (argc > 1 && strcmp(argv[1], "-mo") == 0)
    {
        cout << getVolumeMicrophone() << endl;
    }
    // 当输入参数为 -ms 时，设置麦克风音量
    else if (argc > 2 && strcmp(argv[1], "-ms") == 0)
    {
        // 输出要设置的音量大小
        // cout << "set volume: " << argv[2] << endl;
        // setVolumeMicrophone(atoi(argv[2]));
        int res = setVolumeMicrophone(atoi(argv[2]));
        if (res == 0) {
            cout << "success" << endl;
        }
        else {
            cout << "error" << endl;
        }
    }
    // 当输入的参数为 -mute 时，输出是否静音
    else if (argc > 1 && strcmp(argv[1], "-mute") == 0)
    {
        const char* mute = getMute() ? "true" : "false";
        cout << mute << endl;
    }
    // 当输入的参数为 -mute true 时，设置是否静音
    else if (argc > 2 && strcmp(argv[1], "-mt") == 0)
    {
        if (strcmp(argv[2], "true") == 0)
        {
            int res = setMute(true);
            if (res == 0) {
                cout << "success" << endl;
            }
            else {
                cout << "error" << endl;
            }
        }
        else if (strcmp(argv[2], "false") == 0)
        {
            int res = setMute(false);
            if (res == 0) {
                cout << "success" << endl;
            }
            else {
                cout << "error" << endl;
            }
        }
    }
    // 监听系统输出音量变化, 当音量变化时，触发 OnNotify 方法
    else if (argc > 1 && strcmp(argv[1], "-w") == 0)
    {
        listenVolume();
    }
    // 监听系统麦克风音量变化, 当音量变化时，触发 OnNotify 方法
    else if (argc > 1 && strcmp(argv[1], "-wm") == 0)
    {
        listenVolumeMicrophone();
    }
    else
    {
        cout << "usage: volume [-m] [-o] [-s volume] [-mo] [-ms volume] [-mute] [-mute true|false] [-w] [-m]" << endl;
    }
}

// 编译命令：g++ -o volume volume.cpp -lpsapi -lole32 -luuid -lwinmm