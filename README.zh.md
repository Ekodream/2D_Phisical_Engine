# 2D_Physical_Engine

这是一个用 C++ 编写的简易 2D 物理引擎并带有基于 SFML 的交互查看器。

仓库内容：质点物理核心、圆形碰撞检测与冲量响应、以及基于 SFML 的渲染与输入交互。

重要说明：当前代码要求 SFML。项目在配置时会查找并链接 SFML（可通过 vcpkg 或本地 SFML 安装）。

## 功能

- 2D 向量（Vector2）数学工具
- 质点（PointMass）：位置、速度、质量、半径、恢复系数
- 圆-圆碰撞检测与脉冲响应
- SFML 渲染 + 交互（生成、拖拽、选择、参数调整）

## 交互说明（GUI 模式）

- 左键单击：在光标位置生成一个质点（使用当前设置的半径与恢复系数）
- 拖拽（左键）：按拖拽向量生成并赋初速度
- 右键单击：选择最近的物体（约 30 像素范围）
- R / F：增加 / 减少生成半径（同时应用到被选中的物体）
- T / G：增加 / 减少恢复系数（同时应用到被选中的物体）
- 空格：暂停 / 恢复仿真
- ESC：退出程序

被选中物体会高亮并绘制碰撞半径轮廓（黄色）。

## 构建（Windows 示例）

依赖：
- CMake 3.10+
- 支持 C++17 的编译器（Windows 下推荐 MSVC）
- SFML（推荐使用 vcpkg 安装）

使用 vcpkg 的示例（请替换为你的 vcpkg 路径）：

```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine
mkdir build; cd build
cmake -DCMAKE_TOOLCHAIN_FILE=D:\Programs\vcpkg-master\scripts\buildsystems\vcpkg.cmake ..
cmake --build . --config Release
```

手动安装 SFML 的示例：

```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine\build
cmake -DSFML_DIR="C:\Path\To\SFML\lib\cmake\SFML" ..
cmake --build . --config Release
```

运行：

```powershell
.\Release\physics_app.exe
```

## 项目结构

```
2D_Physical_Engine/
├── CMakeLists.txt
├── README.md
├── README.zh.md
├── src/
│   ├── main.cpp
│   ├── core/
│   │   ├── Math/
│   │   │   ├── Vector2.h
│   │   │   └── Vector2.cpp
│   │   └── Physics/
│   │       ├── Body.h
│   │       ├── Collision.h
│   │       └── Collision.cpp
│   └── render/
│       ├── Renderer.h
│       └── Renderer.cpp
└── build/
```

## 备注

- 当前基于 SFML 3 的 API（vcpkg 提供的版本），如果需要支持 SFML 2.5，需额外兼容处理。
- 仿真使用固定时间步（1/60），若出现穿透或不稳定，可考虑子步或更稳的积分方式。
