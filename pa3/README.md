# Docker虚拟环境运行流程

## 启动及进入容器

```bash
docker-compose up -d
docker exec -it pa3 bash
```

切换到pa3目录：

```bash
cd root/pa3
```

## 后续操作：

- 停止容器：`docker-compose down`
- 重启容器：`docker-compose up -d`（依赖已安装，重启后无需重新安装）
- 本地修改代码后，容器内 `/root/pa3` 会实时同步，直接编译即可。