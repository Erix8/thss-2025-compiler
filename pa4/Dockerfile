# Dockerfile
FROM ubuntu:22.04

# 禁用交互式配置
ENV DEBIAN_FRONTEND=noninteractive

# 安装依赖
RUN apt update && \
    apt install -y build-essential cmake git pkg-config python3 openjdk-11-jdk curl && \
    rm -rf /var/lib/apt/lists/*

# 设置工作目录
WORKDIR /root/pa4

# 启动时进入 bash
CMD ["bash"]