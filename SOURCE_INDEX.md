# 源代码文件索引 / Source Code Index

## 📁 项目目录树 / Project Directory Tree

```
d:\snake\SnakeGame/
├── build/                          # 编译生成目录 / Build directory
│   └── Debug/
│       └── SnakeGame.exe          # ✅ 可执行文件 / Executable
│
├── include/                        # 头文件目录 / Headers
│   ├── Direction.h                # 方向枚举 / Direction enum
│   ├── Food.h                     # 食物类 / Food class
│   ├── Game.h                     # 游戏主类 / Game main class
│   ├── Input.h                    # 输入处理 / Input handler
│   ├── Point.h                    # 坐标结构 / Point structure
│   ├── Renderer.h                 # 渲染器 / Renderer class
│   ├── SaveSystem.h               # 存档系统 / Save system
│   └── Snake.h                    # 贪吃蛇类 / Snake class
│
├── src/                           # 源文件目录 / Source code
│   ├── Food.cpp                   # 食物实现 / Food implementation
│   ├── Game.cpp                   # 游戏实现 / Game implementation
│   ├── Input.cpp                  # 输入实现 / Input implementation
│   ├── main.cpp                   # 程序入口 / Entry point
│   ├── Renderer.cpp               # 渲染实现 / Renderer implementation
│   ├── SaveSystem.cpp             # 存档实现 / Save system implementation
│   └── Snake.cpp                  # 蛇实现 / Snake implementation
│
├── CMakeLists.txt                 # CMake 配置 / CMake config
├── README.md                      # 详细文档 / Detailed documentation
├── QUICKSTART.md                  # 快速开始 / Quick start
└── PROJECT_COMPLETION.md          # 完成报告 / Completion report

```

## 📄 文件详细说明 / Detailed File Description

### 头文件 (Headers)

#### **Direction.h** ⭐
```cpp
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
```
- **作用**：定义游戏中的移动方向
- **行数**：11 行
- **关键内容**：方向枚举定义

#### **Point.h** ⭐
```cpp
struct Point {
    int x, y;
};
```
- **作用**：定义二维坐标结构
- **行数**：12 行
- **关键内容**：坐标点类和等号操作符重载

#### **Snake.h** ⭐⭐
- **类成员**：
  - `std::deque<Point> body` - 蛇身链表
  - `Direction direction` - 移动方向
- **关键方法**：
  - `void move()` - 移动
  - `void grow()` - 增长
  - `bool checkCollision()` - 碰撞检测
  - `void setDirection()` - 设置方向
- **行数**：25 行

#### **Food.h** ⭐
- **类成员**：
  - `Point position` - 食物位置
  - `int stageWidth, stageHeight` - 游戏区域大小
- **关键方法**：
  - `void generate(const deque<Point>&)` - 随机生成
  - `Point getPosition()` - 获取位置
- **行数**：17 行

#### **Renderer.h** ⭐⭐⭐
- **类成员**：
  - `HANDLE hOutput1, hOutput2` - 两个缓冲区句柄
  - `vector<vector<char>> buffer1, buffer2` - 缓冲区内存
- **关键方法**：
  - `void clear()` - 清空缓冲
  - `void drawChar()` - 绘制字符
  - `void render()` - 输出到屏幕
  - `void swapBuffers()` - 交换缓冲区
- **行数**：27 行
- **核心技术**：双缓冲渲染

#### **Input.h** ⭐
- **关键方法**：
  - `static Direction getInput()` - 非阻塞获取方向输入
  - `static char getSpecialInput()` - 获取特殊按键
- **行数**：10 行

#### **SaveSystem.h** ⭐⭐
- **数据结构**：
  ```cpp
  struct SaveData {
      deque<Point> snakeBody;
      Direction direction;
      Point foodPos;
      int score;
  };
  ```
- **关键方法**：
  - `static bool saveGame()` - 保存到文件
  - `static bool loadGame()` - 从文件读取
- **行数**：20 行

#### **Game.h** ⭐⭐⭐
- **类成员**：
  - `Snake snake` - 蛇对象
  - `Food food` - 食物对象
  - `Renderer* renderer` - 渲染器
  - `GameStatus state` - 游戏状态
  - `int score` - 分数
- **关键方法**：
  - `void run()` - 游戏主循环
  - `void update()` - 更新游戏逻辑
  - `void render()` - 渲染画面
  - `void save/load()` - 存档读档
- **行数**：37 行

### 源文件 (Source Code)

#### **main.cpp** 📍
```cpp
int main() {
    const int WIDTH = 20;
    const int HEIGHT = 20;
    Game game(WIDTH, HEIGHT);
    game.run();
    return 0;
}
```
- **作用**：程序入口点
- **行数**：12 行
- **职责**：创建游戏对象并启动

#### **Snake.cpp** 蛇贪类实现
- **move()** (9-16 行)：移动蛇身，头部前进，尾部后退
- **grow()** (18-20 行)：增加蛇身长度
- **checkCollision()** (22-25 行)：检测与边界碰撞
- **checkSelfCollision()** (27-32 行)：检测与自身碰撞
- **setDirection()** (34-42 行)：设置移动方向，防止反向
- **行数**：~60 行

#### **Food.cpp** 食物类实现
- **generate()** (10-16 行)：随机生成食物位置，避开蛇身
- **getPosition/setPosition()** (18-23 行)：获取/设置食物位置
- **行数**：~25 行

#### **Renderer.cpp** 渲染器实现 🎨
- **构造函数** (5-33 行)：创建两个控制台缓冲区，隐藏光标
- **clear()** (35-40 行)：清空当前缓冲区
- **drawChar()** (42-48 行)：在指定位置绘制字符
- **drawText()** (50-54 行)：绘制文本字符串
- **render()** (56-63 行)：输出缓冲区到屏幕
- **swapBuffers()** (65-68 行)：交换两个缓冲区
- **行数**：~75 行
- **关键**：Windows 控制台 API 使用

#### **Input.cpp** 输入处理
- **getInput()** (3-15 行)：非阻塞读取方向键
  - WASD 控制方向
  - X 键退出
  - 防止方向反向
- **getSpecialInput()** (17-21 行)：读取特殊按键（P/S/L）
- **行数**：~25 行

#### **SaveSystem.cpp** 存档系统 💾
- **saveGame()** (5-20 行)：序列化游戏状态到文本
  - 格式：`key=value`
  - 蛇身格式：`x,y;x,y;x,y`
- **loadGame()** (22-50 行)：反序列化游戏状态
  - 解析文本文件
  - 恢复蛇身、方向、食物、分数
- **行数**：~60 行

#### **Game.cpp** 游戏主类 🎮
- **run()** (16-26 行)：游戏主循环
  - 处理输入
  - 更新逻辑
  - 检测碰撞
  - 渲染画面
  - 100ms 延迟
- **update()** (28-35 行)：游戏逻辑更新
  - 蛇移动
  - 吃食物检测
  - 增加分数
- **render()** (37-60 行)：画面渲染
  - 清空缓冲
  - 绘制边界
  - 绘制蛇和食物
  - 显示信息面板
- **handleInput()** (62-98 行)：处理用户输入
  - 方向控制
  - 暂停功能
  - 存读档快捷键
- **drawGameInfo()** (114-126 行)：右侧信息面板（新增）
  - 显示控制说明
  - 显示游戏状态
- **save/load()** (135-155 行)：存档读档实现
- **行数**：~170 行

### 配置文件 (Configuration)

#### **CMakeLists.txt** 🔧
```cmake
cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Snake.cpp
    src/Food.cpp
    src/Renderer.cpp
    src/Input.cpp
    src/SaveSystem.cpp
)

add_executable(SnakeGame ${SOURCES})
```
- **作用**：CMake 构建配置
- **支持平台**：Windows (MSVC)
- **C++ 标准**：C++17

## 📊 代码统计 / Code Statistics

| 项 | 数量 |
|----|------|
| 头文件数 | 8 |
| 源文件数 | 7 |
| 总代码行 | ~600-700 |
| 类数量 | 6 |
| 函数总数 | 50+ |
| 关键算法 | 3 (渲染、碰撞、序列化) |

## 🔗 依赖关系 / Dependency Graph

```
main.cpp
    ↓
Game.h/cpp → Snake.h/cpp
          → Food.h/cpp
          → Renderer.h/cpp → (Windows API)
          → Input.h/cpp
          → SaveSystem.h/cpp

Direction.h ← Snake, SaveSystem
Point.h ← Snake, Food, SaveSystem
```

## ✅ 文件完整性检查 / Completeness Check

- [x] 所有头文件都有对应源文件
- [x] 所有源文件都在 CMakeLists.txt 中
- [x] 没有循环依赖
- [x] 没有未定义符号
- [x] 代码可正常编译
- [x] 程序可正常运行

---

**生成日期** / Generated: 2026-03-31
