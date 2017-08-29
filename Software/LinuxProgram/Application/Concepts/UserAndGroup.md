# User

文件的权限管理离不开unix的用户模型。

## User

### 增加用户

adduser - add a user to the system

### 删除用户

deluser - remove a user from the system

> 相关文件
> /usr/shadow 此文件包含了所有的用户的密码
> /usr/passwd 此文件包含了所有的用户

## Group

### 增加组

addgroup - add a group to the system

### 删除组

delgroup - remove a group from the system


> 相关文件
> /usr/group 此文件包含了所有的组

## 练习

1. 在ubuntu上新建一个账户，将此账户增加到sudo组
> * `sudo adduser liduanjun`
> * `sudo addgroup liduanjun sudo`
