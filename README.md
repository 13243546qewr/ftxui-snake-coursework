# FTXUI Snake Coursework

这是一个使用 C++ 和 FTXUI 开发的终端版贪吃蛇小游戏，作为 C++ 大作业项目示例。项目只参考了开源仓库 `taylorconor/tinytetris` 使用终端界面实现小游戏的思路，但玩法、代码结构、界面实现和游戏逻辑均重新编写，没有直接复制原项目代码。

## 项目特点

- 使用 C++17 开发。
- 使用 FTXUI 实现彩色终端界面。
- 使用 CMake 构建项目。
- 采用头文件和源文件分离的项目结构。
- 支持方向控制、暂停、重新开始和退出。
- 包含分数、蛇身长度和速度显示。
- 食物随机生成，蛇吃到食物后增长并加分。
- 撞墙或撞到自己后游戏结束。

## 操作方式

| 按键 | 功能 |
| --- | --- |
| A / 左方向键 | 左移 |
| D / 右方向键 | 右移 |
| W / 上方向键 | 上移 |
| S / 下方向键 | 下移 |
| P | 暂停 / 继续 |
| R | 重新开始 |
| Q / Esc | 退出 |

## 构建方法

请先安装 CMake 和支持 C++17 的编译器。FTXUI 会由 CMake 自动下载。

```bash
cmake -S . -B build
cmake --build build
```

运行程序：

```bash
./build/ftxui_snake
```

在 Windows 下，如果使用 Visual Studio 生成器，程序可能位于：

```powershell
.\build\Debug\ftxui_snake.exe
```

如果使用 MinGW，程序通常位于：

```powershell
.\build\ftxui_snake.exe
```

## 项目结构

```text
ftxui-snake-coursework/
├── CMakeLists.txt
├── README.md
├── include/
│   └── SnakeGame.hpp
└── src/
    ├── main.cpp
    └── SnakeGame.cpp
```

## 贡献指南

欢迎在个人仓库中继续改进本项目，可以从以下方向扩展：

- 增加最高分保存功能。
- 增加开始菜单和难度选择。
- 增加音效或更丰富的界面配色。
- 增加穿墙模式、障碍物模式或关卡系统。
- 添加单元测试，验证移动、吃食物、碰撞和计分逻辑。

提交改动前建议先确认项目可以正常构建并运行。

## 说明

本项目适合提交到个人 GitHub 仓库中作为大作业实现。根据作业要求，最终提交时应提交个人账号下的仓库链接，而不是直接在参考仓库中提交代码。
