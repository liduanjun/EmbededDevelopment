git 基本功能 
===========
### gitlab 本地 git 服务仓库
ip		 : 192.168.1.106
url 	 : mabot.win
hostname : mabot

### git 安装
sudo apt-get install git

### git 配置
git config --global user.name "liduanjun"
git config --global user.email "liduanjun@126.com"
git config --global core.editor vim

### ssh-key 生成
ssh-keygen -t rsa -C "GitLab" -b 4096
ssh-key路径 ~/.ssh/id_rsa.pub

### 从仓库 clone (下载，仅一次)代码到本地
git clone git@mabot.win:liduanjun/note.git

### 从本地 push 到仓库
git add client.c 或者 git add *
git commit 或者 git commit -m "add file"
git push origin master

### 从仓库 fetch 代码到本地
git fetch origin master:new_branch
new_branch是远程下载到本地的新版本号名称

### 合并分支 new_branch 到当前分支上
git merge new_branch

### 从仓库 pull 代码到本地
git pull master origin 
new_branch 是远程下载到本地的新版本号名称

fetch 和 pull 的区别是：
pull == fetch + merge

## 基本概念
### 本地
工作目录
暂存
本地仓库(快照)

### 远程
远程仓库