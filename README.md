# RedIM 

## 项目简介

RedIM是一个基于Mirai项目的QQ第三方桌面客户端。

采用Qt开发以支持跨平台。已经在Linux平台编译通过。理论macOS, Windows可用。

## 部署方法

### 服务器部署

本项目是[mirai-api-http](https://github.com/project-mirai/mirai-api-http)项目的前端。
为了使用本软件，请先在远程或者本地按照教程部署一个mirai-api-http服务器。
为了安全起见，请配置为single-session模式。具体查看教程。

### 本地配置

下载本软件或自行编译后，请按照配置向导指示。

## 设计开发

### 项目架构



| View | → | Model | → | Connection |
|:------:|:------:|:------:|:------:|:------:|
|    ↑    |    |  ↓ |
|    Controller    |  →  |    DataCollection   |    
|    ↑    |  
|    PushService   |  



### TODO

1.  UI界面、个性化
- 自定义字体
- 导入自定义qss，更换主题
- 黑夜模式
- 设置背景图像
- 设置文档下载目录
2. 功能列表
- 增加QQ空间/内置浏览器
- 增加文件、图像、语音上传功能
- 增加更新功能
- 增加代理功能
3. 修bug
- 减少内存泄露，优化内存占用
- 增大缓存内容，减少在线加载内容

## 引用项目

[**mirai:高效率 QQ机器人库**](https://github.com/mamoe/mirai)

[**Qt:跨平台应用程序开发框架**](https://www.qt.io)

[**configor:轻量级C/C++ JSON解析库**](https://github.com/Nomango/configor)
