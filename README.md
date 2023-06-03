# Decaf Compiler

Decaf 编程语言编译器的实现，用于Visual Decaf项目的后端，提供编译流程中的相关数据。

## 项目开发环境

### 主要运行依赖

- Linux操作系统
- GCC 12.3
- CMake 3.25

### Docker镜像

本项目的编译运行环境已经作为docker镜像打包，托管于Docker Hub中的`distinctwind/visual-decaf:latest`，可以通过以下命令获取：

```bash
docker pull distinctwind/visual-decaf:latest
```

`DockerFile`文件及其构建上下文位于本仓库的`docker`分支中，每次提交到该分支都会出发镜像重新打包上传到Docker Hub。

#### Docker镜像版本号

该Docker镜像自带了一个版本文件，可以查看当前镜像的版本号：

```bash
docker run --rm distinctwind/visual-decaf:latest cat /var/version
```