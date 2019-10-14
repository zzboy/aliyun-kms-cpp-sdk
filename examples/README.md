# 如何运行例程

## 1. 根据 [README](https://github.com/aliyun/aliyun-openapi-cpp-sdk/blob/master/README-CN.md) 安装 SDK

## 2. 构建例程

### Linux

```bash
cd examples
mkdir build
cd build
cmake ..
make -j
```

### Windows

- 通过 CMake 构建 Visual Studio 解决方案

  - 运行 cmake-ui

  - 选在源代码目录(examples 目录)和构建目录(在 examples 创建 build 目录)。

  - 配置 (configure)

  - 生成 (generate)

- 用 Visual Studio 从 build 目录打开 `alibabacloud-sdk-examples.sln`

- 编译： 生成 -> 生成解决方案


## 3. 运行例程
注意，将libalibabacloud-sdk-core.so的安装目录设置到LD_LIBRARY_PATH
