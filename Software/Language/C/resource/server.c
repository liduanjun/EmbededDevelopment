/**************************************************************************
 * @file     Client.c
 * @brief    人员管理系统客户端
 * @version  V1.00
 * @date     19. January 2017
 * @note
 * Copyright (C) 2017 Farsight Limited. All rights reserved.
 **************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

#define SERVER
#include "../include/common.h"

struct flag{
	int fd;
	int flag;
};

/**************************************************************************
 * @brief       人员管理系统客户端
 * @date        19. January 2017
 * @auther      刘超 liuchao@126.com
 * @name        InitSQL3 , init_sql3
 * @parameter   none
 * @return      sqlite3 *     返回值的作用 
 **************************************************************************/
sqlite3 *InitSQL3(){
	sqlite3 *staffdb;
	if(sqlite3_open(DB_NAME, &staffdb) != SQLITE_OK){
		fprintf(stderr, "%s:%d: %s!\n", __func__, __LINE__,\
						sqlite3_errmsg(staffdb));
		return NULL;
	}
	char *errmsg;
	if(sqlite3_exec(staffdb, "create table user(type integer,name text,password text,mpassword text)", NULL, NULL, &errmsg\
				) != SQLITE_OK){
		if(0 != strncmp(errmsg, "table user already exists", 25)){
			fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
			return NULL;
		}
	}
	if(sqlite3_exec(staffdb, "create table information(name text,age text,phone text,addr text,salary text,number integer,level integer)", NULL, NULL, &errmsg\
				) != SQLITE_OK){
		if(0 != strncmp(errmsg, "table information already exists", 32)){
			fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
			return NULL;
		}
	}
	return staffdb;
}

/**************************************************************************
 * @brief       人员管理系统客户端
 * @date        19. January 2017
 * @auther      刘超 liuchao@126.com
 * @name        CreateListenFd
 * @parameter   const char *ip : ip address
 * @return      int : sucess=0
 *                    failuse=-1 ~ -127
 **************************************************************************/
int CreateListenFd(const char *ip){
	if(!ip){
		fprintf(stderr, "%s:%d : ip is NULL!\n", __func__, __LINE__);
		return -1;
	}
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0){
		fprintf(stderr, "%s:%d : socket error!\n", __func__, __LINE__);
		return -1;
	}
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port   = htons(5678);
	serveraddr.sin_addr.s_addr = inet_addr(ip);
	if(bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0){
		fprintf(stderr, "%s:%d : bind error!\n", __func__, __LINE__);
		return -1;
	}
	if(listen(listenfd, SIZE_LSNMAX) < 0){
		fprintf(stderr, "%s:%d : listen error!\n", __func__, __LINE__);
	}
	return listenfd;
}//createlistenfd end

void Quit(const int fd, sqlite3 *staffdb){
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", \
				__func__, __LINE__);
		return;
	}
	printf("-----------------------------------\n");
	printf("system exited!\n");
	exit(0);
}//quit end

int Sqlite3Callback(void *para, int f_num, char **f_value, char **f_name ){
	if(para){
		int *flag = (int *)para;
		(*flag)++;
	}
	return 0;
}

int LogIn(const int fd, User *user, sqlite3 *staffdb){
	if(!user){
		fprintf(stderr, "%s:%d: user is NULL\n", \
				__func__, __LINE__);
		return -1;
	}
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", \
				__func__, __LINE__);
		return -1;
	}
	User rcvuser;
	memset(&rcvuser, 0, sizeof(rcvuser));
	int size_read = read(fd, &rcvuser, sizeof(rcvuser));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}
	rcvuser.type = ntohl(rcvuser.type);
	*user = rcvuser;
	char buf[512] = "";
	Statu LogInStatu;
	char *errmsg;
	sprintf(buf, "select * from user where type=%d and name=\"%s\" and password=\"%s\";", user->type,\
			user->name, user->password);
	int Log_flag1 = 0;
	int Log_flag0 = sqlite3_exec(staffdb, buf, Sqlite3Callback, &Log_flag1, &errmsg); 
	if((Log_flag0 != SQLITE_OK) || (!Log_flag1)){
		fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "N");
	}else{
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "Y");
		int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
		if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
		}
		return 1;
	}
	int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
	if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
	}
	return 0;
}//login end

int QueryInfoCallback(void *para, int f_num, char **f_value, char **f_name){
	if(para){
		struct flag *flag = (struct flag *)para;
		(flag->flag)++;
	printf("%s:%d...fd %d flag %d\n", __func__, __LINE__, flag->fd, flag->flag);
	StaffInfo uinfo;
	memset(&uinfo, 0, sizeof(uinfo));
	int i = 0;
	
	printf("f_num %d i %d\n", f_num, i);
	strcpy(uinfo.name, f_value[i]);
	uinfo.age = htonl(atoi(f_value[++i]));
	strcpy(uinfo.phone, f_value[++i]);
	strcpy(uinfo.addr, f_value[++i]);
	strcpy(uinfo.salary, f_value[++i]);
	uinfo.no = htonl(atoi(f_value[++i]));
	uinfo.level = htonl(atoi(f_value[++i]));
	printf("f_num %d i %d\n", f_num, i);
	
	int size_write = write(flag->fd, &uinfo, sizeof(uinfo));
	if(size_write != sizeof(uinfo)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
	}
	}
	return 0;
}

int InfoQuery(const int fd, sqlite3 *staffdb){
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", __func__, __LINE__);
		return -1;
	}
	printf("%s....\n", __func__);
	User user;
	memset(&user, 0, sizeof(user));
	int size_read = read(fd, &user, sizeof(user));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}
	user.type = ntohl(user.type);
	
	char buf[512] = "";
	Statu LogInStatu;
	char *errmsg;
	StaffInfo uinfo;
	memset(&uinfo, 0, sizeof(uinfo));
	sprintf(buf, "select * from information where name=\"%s\";", user.name);
	struct flag flag;
	flag.flag = 0;
	flag.fd   = fd;
	int Log_flag0 = sqlite3_exec(staffdb, buf, QueryInfoCallback, &flag, &errmsg); 
	if((Log_flag0 != SQLITE_OK) || (!flag.flag)){
		fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
		strcpy(uinfo.name,  "NO");
		strcpy(uinfo.addr,  "NO");
		strcpy(uinfo.phone, "NO");
		int size_write = write(fd, &uinfo, sizeof(uinfo));
		if(size_write != sizeof(uinfo)){
			fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
			return -1;
		}
	}
	return 0;
}//InfoQuery end

int UpdateInfo(int fd, sqlite3 *staffdb, const char *name, const ModifyMsg new){
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", __func__, __LINE__);
		return -1;
	}
	if(!name){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", __func__, __LINE__);
		return -1;
	}
	int Log_flag0 = 1;
	char buf[512] = "";
	Statu LogInStatu;
	char *errmsg;
	//information(name text,age text,phone text,addr text,salary text,number integer,level integer)"
	if((!strncmp(new.option, "password", 8)) || (!strncmp(new.option, "mpassword", 9))){
		Log_flag0 = 0;
		sprintf(buf, "update user set %s=\"%s\" where name=\"%s\";", new.option, \
				new.Svalue,name);
	}else if((!strncmp(new.option, "number", 6)) || (!strncmp(new.option, "level", 6))){
		Log_flag0 = 0;
		sprintf(buf, "update information set %s=%d where name=\"%s\";", new.option,\
				new.Ivalue, name);
	}else if(!strncmp(new.option, "age", 3)){
		Log_flag0 = 0;
		sprintf(buf, "update information set %s=\"%d\" where name=\"%s\";", new.option,\
				new.Ivalue, name);	
	}else if(!strncmp(new.option, "name", 4)){
		sprintf(buf, "update information set %s=\"%s\" where name=\"%s\";", new.option, \
				new.Svalue,name);
	   Log_flag0 = sqlite3_exec(staffdb, buf, NULL, NULL, &errmsg); 
		sprintf(buf, "update user set %s=\"%s\" where name=\"%s\";", new.option, \
				new.Svalue,name);
	}else{
		Log_flag0 = 0;
		sprintf(buf, "update information set %s=\"%s\" where name=\"%s\";", new.option, \
				new.Svalue,name);
	}
	int Log_flag = sqlite3_exec(staffdb, buf, NULL, NULL, &errmsg); 
	
	if((Log_flag != SQLITE_OK) || (Log_flag0 != SQLITE_OK)){
		fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "N");
	}else{
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "Y");
	}
	int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
	if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
	}
	return 0;
}

int QueryUser(const int fd, sqlite3 *staffdb){
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", __func__, __LINE__);
		return -1;
	}
	char buf[512] = "";
	User user;
	Statu LogInStatu;
	char *errmsg;
	int Query_flag = 0;
	memset(&user, 0, sizeof(user));
	int size_read = read(fd, &user, sizeof(user));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}
	sprintf(buf, "select * from user where name=\"%s\" and password=\"%s\" \
			and mpassword=\"%s\";", user.name, user.password, user.modify_password);
	int Exec_flag = sqlite3_exec(staffdb, buf, Sqlite3Callback, &Query_flag, &errmsg); 
	if((Exec_flag != SQLITE_OK) || (!Query_flag)){
		fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "N");
		int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
		if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
		}
		return 0;
	}else{
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "Y");
		int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
		if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
		}
		return 1;
	}
}//Query User

int InfoModify(const int fd, sqlite3 *staffdb){
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", __func__, __LINE__);
		return -1;
	}
	printf("%s....\n", __func__);
	User user;
	ModifyMsg new;
	memset(&user, 0, sizeof(user));
	memset(&new, 0, sizeof(new));
	int size_read = read(fd, &user, sizeof(user));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}

	size_read = read(fd, &new, sizeof(new));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}
	new.Ivalue = ntohl(new.Ivalue);
	if((!strncmp(new.option, "password", 8))&& (user.type == USER)){
		if(1 != QueryUser(fd, staffdb)){
			fprintf(stderr, "user name or password or mpassword error!\n");
			Statu LogInStatu;
			memset(&LogInStatu, 0, sizeof(LogInStatu));
			strcpy(LogInStatu.rcv, "N");
			int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
			if(size_write != sizeof(LogInStatu.rcv)){
			fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
			return -1;
			}
			return -1;
		}
	}
	UpdateInfo(fd, staffdb, user.name, new);
	return 0;
}//InfoModify end


int AddUser(const int fd , sqlite3 *staffdb){
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", \
				__func__, __LINE__);
		return -1;
	}
	printf("%s....\n", __func__);
//Add info to table information
	StaffInfo userinfo;
	memset(&userinfo, 0, sizeof(userinfo));	
	int size_read = read(fd, &userinfo, sizeof(userinfo));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}
	userinfo.age = ntohl(userinfo.age);
	userinfo.no = ntohl(userinfo.no);
	userinfo.level = ntohl(userinfo.level);

	char buf[512] = "";
	Statu LogInStatu;
	char *errmsg;
	//information(name text,age text,phone text,addr text,salary text,number integer,level integer)"
	sprintf(buf, "insert into information values(\"%s\",\"%d\",\"%s\",\"%s\",\"%s\",%d,%d)",\
			userinfo.name, userinfo.age, userinfo.phone, userinfo.addr, userinfo.salary,\
			userinfo.no, userinfo.level);
	int Log_flag = sqlite3_exec(staffdb, buf, NULL, NULL, &errmsg); 
	
		if(Log_flag != SQLITE_OK){
		fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
	memset(&LogInStatu, 0, sizeof(LogInStatu));
	strcpy(LogInStatu.rcv, "N");
	}else{
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "Y");
	}
	int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
	if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
	}
//Add info to table user
	User user;
	memset(&user, 0, sizeof(user));
    size_read = read(fd, &user, sizeof(user));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}
	user.type = htonl(user.type);
	//table user(type integer,name text,password text,mpassword text)
	sprintf(buf, "insert into user values(%d,\"%s\",\"%s\",\"%s\")",\
			user.type, user.name, user.password, user.modify_password);
		 Log_flag = sqlite3_exec(staffdb, buf, NULL, NULL, &errmsg); 
	
		if(Log_flag != SQLITE_OK){
		fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
	memset(&LogInStatu, 0, sizeof(LogInStatu));
	strcpy(LogInStatu.rcv, "N");
	}else{
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "Y");
	}
	 size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
	if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
	}
	return 0;
}//AddUser end


int DelUser(const int fd , sqlite3 *staffdb){
	if(!staffdb){
		fprintf(stderr, "%s:%d: staffdb is NULL\n", \
				__func__, __LINE__);
		return -1;
	}
	printf("%s....\n", __func__);
	
	User user;
	memset(&user, 0, sizeof(user));
	int size_read = read(fd, &user, sizeof(user));
	if(size_read < 0){
		fprintf(stderr, "%s:%d: read error!\n", __func__,\
				__LINE__);
		return -1;
	}else if(size_read == 0){
		fprintf(stderr, "%s:%d: client closed!\n", __func__, \
				__LINE__);
		return -1;
	}
	user.type = ntohl(user.type);
	
	char buf[512] = "";
	Statu LogInStatu;
	char *errmsg;
	int Log_flag1 = 1, Log_flag2 = 1, Log_flag3 = 1;
	sprintf(buf, "delete from user where type=%d and name=\"%s\";", user.type,\
			user.name);
	int Log_flag0 = sqlite3_exec(staffdb, buf, Sqlite3Callback, &Log_flag1, &errmsg); 
	
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "delete from information where name=\"%s\";", user.name);
	Log_flag3 = sqlite3_exec(staffdb, buf, Sqlite3Callback, &Log_flag2, &errmsg); 
	printf("flag0 %d, flag1 %d, flag2 %d, flag3 %d\n", Log_flag0, Log_flag1, \
			Log_flag2, Log_flag3);
	if((Log_flag0 != SQLITE_OK) || (Log_flag3 != SQLITE_OK)||\
			(!Log_flag1) || (!Log_flag2)){
		fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, errmsg);
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "N");
	}else{
		memset(&LogInStatu, 0, sizeof(LogInStatu));
		strcpy(LogInStatu.rcv, "Y");
		int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
		if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
		}
		return 1;
	}
	int size_write = write(fd, LogInStatu.rcv, sizeof(LogInStatu.rcv));
	if(size_write != sizeof(LogInStatu.rcv)){
		fprintf(stderr, "%s:%d: wirte error!\n", __func__, __LINE__);
		return -1;
	}
	return 0;
}//DelUser


