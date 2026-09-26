# dedit

dedit 是一个基于 C 语言和 ncurses 库实现的终端文本编辑器。

本项目实现了基本文本编辑、文件读写、窗口显示以及自动化测试功能。

---

## Features

### 文本编辑

- 字符插入
- Backspace 删除字符
- Delete 删除字符
- Enter 插入新行
- 光标移动：
  - ↑ ↓ ← →
- 长文本窗口滚动

### 文件操作

- 打开文本文件
- 保存文本文件
- 未保存修改退出保护

### 用户界面

- 基于 ncurses 实现终端界面
- 状态栏显示：
  - 文件名
  - 当前行号
  - 当前列号
  - 状态信息

### 自动化测试

包含 Editor 模块自动化测试：

- editor 初始化测试
- 字符插入测试
- 字符删除测试
- Delete 删除测试
- 换行测试
- 文件保存与读取测试

---

## Build

### Requirements

- gcc
- ncurses

Ubuntu 安装：

```bash
sudo apt install gcc libncurses-dev
```

---

### Compile

在项目根目录执行：

```bash
make
```

生成：

```
dedit
```

---

## Run

运行：

```bash
./dedit filename
```

例如：

```bash
./dedit test.txt
```

---

## Controls

| 按键 | 功能 |
|---|---|
| ↑ ↓ ← → | 移动光标 |
| Backspace | 删除光标前字符 |
| Delete | 删除光标所在字符 |
| Enter | 插入新行 |
| Ctrl + S | 保存文件 |
| Ctrl + Q | 退出编辑器 |

---

## Automated Test

运行：

```bash
make test
```

测试程序会自动执行所有测试并输出结果。

示例：

```text
=== dedit test ===

[PASS] editor_init
[PASS] insert_char
[PASS] delete_char
[PASS] delete_forward_char
[PASS] insert_newline
[PASS] save_load

6 passed, 0 failed
```

---

## Test Design

测试数据主要覆盖文本编辑器中的基本操作场景。

设计原则：

1. 每个测试独立初始化 Editor，避免测试之间互相影响。
2. 使用固定字符串作为输入数据，方便验证结果。
3. 通过比较实际结果与预期结果判断功能是否正确。

测试示例：

| 功能 | 输入 | 预期结果 |
|---|---|---|
| 字符插入 | `abc` 中插入 `X` | `aXbc` |
| 字符删除 | 删除 `b` | `ac` |
| 换行 | `hello world` 分割 | 两行文本 |
| 保存读取 | 保存后重新加载 | 内容一致 |

---

## Project Structure

```
dedit/
├── main.c
├── editor.c
├── editor.h
├── ui.c
├── ui.h
├── Makefile
└── tests/
    ├── test_runner.c
    └── test_editor.c
```

---

## Development Notes

项目采用模块化设计：

- editor 模块：
  - 文本数据管理
  - 插入、删除、换行
  - 文件保存和读取

- ui 模块：
  - ncurses 界面显示
  - 状态栏
  - 光标和窗口管理

- tests 模块：
  - 自动化测试

模块之间通过头文件声明接口，提高代码可维护性。