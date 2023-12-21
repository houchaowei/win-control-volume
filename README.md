# win-control-volume
windows 下控制系统音量。
others：[macOS 下控制系统音量](https://github.com/houchaowei/mac-control-volume)

done：
- [x] 获取扬声器音量：执行命令 volume.exe -o
- [x] 设置扬声器音量：执行命令 volume.exe -s 50
- [x] 获取麦克风音量：执行命令 volume.exe -mo
- [x] 设置麦克风音量：执行命令 volume.exe -ms 50
- [x] 获取静音状态：执行命令 volume.exe -mute
- [x] 设置静音状态：执行命令 volume.exe -mt [true/false]
- [x] 监听系统输出音量变化，当音量变化时，会输出当前音量
- [x] 监听系统输入音量变化，当音量变化时，会输出当前音量

Usage:
```sh
$ ./volume.exe -o
```

Releases:
https://github.com/houchaowei/win-control-volume/releases/tag/0.0.1