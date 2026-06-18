# FTXUI Snake Coursework

这是一个使用 C++ 和 FTXUI 开发的终端版贪吃蛇小游戏
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
