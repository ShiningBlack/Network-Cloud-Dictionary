# 基于TCP和epoll多路复用的电子词典项目
此项目主要实现了注册和登录和查询单词的功能，服务器使用epoll多路复用实现一个服务器服务多个客户端。服务器方面的单词数据通过sqlite3数据库存储，客户端主要通过建立的TCP连接发送指令，从而实现登录、注册、查询功能。

## 服务器端介绍
![image](https://user-images.githubusercontent.com/51869117/228161716-0142e598-8457-4f6f-a424-fbc64d377b9e.png)
- myserver 是服务器端的二进制可执行文件
- read 是用来读取指定格式的数据并写入到sqlite3数据库的一个辅助程序
- word.db 是存储单词的sqlite3数据库文件
- userlist.db 用来存储已经注册的用户信息的sqlite3数据库文件
## 客户端介绍
![image](https://user-images.githubusercontent.com/51869117/228162647-7bdeca61-751f-415f-8060-582212173f64.png)
- 客户端主要由核心控制文件和ui界面文件组成
## 展示
![Snipaste_2023-03-28_09-20-38](https://user-images.githubusercontent.com/51869117/228163356-b2acf3c9-a9c3-44ad-af99-290e4595d79a.png)
![Snipaste_2023-03-28_09-21-37](https://user-images.githubusercontent.com/51869117/228163391-10b36274-6d83-4d20-9ed6-b22d06238024.png)
![Snipaste_2023-03-28_09-21-55](https://user-images.githubusercontent.com/51869117/228163404-50fd884a-028d-4532-9f88-e88c0ac52fb9.png)
![Snipaste_2023-03-28_09-22-02](https://user-images.githubusercontent.com/51869117/228163462-10a6e7cd-5731-405f-aff8-c8e365ead6bf.png)
![Snipaste_2023-03-28_09-22-24](https://user-images.githubusercontent.com/51869117/228163493-8cbe2a19-ed44-4581-b72a-e32137b1504d.png)
![Snipaste_2023-03-28_09-22-35](https://user-images.githubusercontent.com/51869117/228163528-baf170fc-aaae-4539-b8dd-c8bd9f52729d.png)
![Snipaste_2023-03-28_09-23-16](https://user-images.githubusercontent.com/51869117/228163535-c85ce53e-1192-49ab-95da-67e59b4e6a30.png)

# 前置条件
```bash
# 更新软件包
sudo apt-get update
# 安装gcc
sudo apt install gcc
# 安装make
sudo apt install make
# 安装sqlite3以及开发工具包
sudo apt-get install sqlite3
sudo apt-get install libsqlite3-dev
```