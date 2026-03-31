# 快速开始指南 / Quick Start Guide

## 中文 / Chinese

### 完整源码结构
项目已包含所有源码文件，无需额外配置：

```
SnakeGame/
├── CMakeLists.txt           # CMake 配置文件
├── README.md                 # 完整项目文档
├── QUICKSTART.md            # 本文件
├── include/                  # 8 个头文件
│   ├── Direction.h
│   ├── Food.h
│   ├── Game.h
│   ├── Input.h
│   ├── Point.h
│   ├── Renderer.h
│   ├── SaveSystem.h
│   └── Snake.h
└── src/                      # 7 个源文件实现
    ├── Food.cpp
    ├── Game.cpp
    ├── Input.cpp
    ├── main.cpp
    ├── Renderer.cpp
    ├── SaveSystem.cpp
    └── Snake.cpp
```

### 编译步骤

1. **打开 PowerShell**
2. **进入项目目录**
   ```powershell
   cd d:\snake\SnakeGame
   ```

3. **创建构建目录**
   ```powershell
   mkdir build
   cd build
   ```

4. **配置并编译**
   ```powershell
   cmake ..
   cmake --build .
   ```

5. **运行游戏**
   ```powershell
   .\Debug\SnakeGame.exe
   ```

### 游戏界面说明

游戏窗口左侧：
- `@` 表示蛇头
- `o` 表示蛇身
- `*` 表示食物  
- `#` 表示边界

游戏窗口右侧（信息面板）：
- 显示游戏控制说明
- 显示当前游戏状态
- 显示当前分数

### 游戏控制
- **W** / **↑** - 向上移动
- **A** / **←** - 向左移动
- **S** / **↓** - 向下移动
- **D** / **→** - 向右移动
- **P** - 暂停/继续
- **C** - 保存游戏
- **V** - 读取存档
- **X** - 退出游戏

### 常见问题解决

**Q: 编译失败？**
- 确保已安装 CMake 3.10+
- 确保已安装 Visual Studio 2022 或更新版本

**Q: 窗口显示不全？**
- 最小化其他窗口，确保有足够屏幕空间

**Q: 游戏运行缓慢？**
- 这是正常的，游戏采用双缓冲技术，每 100ms 更新一次画面

---

## English / 英文

### Complete Source Code Structure
All source files are included. No additional configuration needed:

**15 Files Total:**
- 1 CMakeLists.txt (Build configuration)
- 1 main.cpp (Entry point)
- 6 C++ source files (.cpp)
- 8 Header files (.h)

### Build Steps

1. **Open PowerShell**
2. **Navigate to project**
   ```powershell
   cd d:\snake\SnakeGame
   ```

3. **Create build directory**
   ```powershell
   mkdir build
   cd build
   ```

4. **Configure and compile**
   ```powershell
   cmake ..
   cmake --build .
   ```

5. **Run game**
   ```powershell
   .\Debug\SnakeGame.exe
   ```

### Game Interface

**Game Area (Left Side):**
- `@` = Snake head
- `o` = Snake body
- `*` = Food
- `#` = Borders

**Info Panel (Right Side):**
- Control instructions
- Game status
- Score display

### Controls
- **W/A/S/D** or **Arrow Keys** - Move snake
- **P** - Pause/Resume
- **C** - Save game
- **V** - Load game
- **X** - Exit

### Features Implemented
✓ Double buffering rendering  
✓ Modular architecture  
✓ Save/Load system  
✓ Score system  
✓ Game state management  
✓ Chinese UI on game panel