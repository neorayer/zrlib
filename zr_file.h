/* 
* Copyright (c) 2005，上海天奇科技有限公司 www.skymiracle.com
* All right reserved.
*
* 文件名称：zr_file.h
* 摘    要：
*     处理文件，包括读、写、改名、删除等。
*
* char *zr_file2str(char *fname)
* char *zr_file2nstr(char *fname, unsigned long nsize)
* int zr_str2file(char *s, char *fname)
* int zr_filesize(char *fname)
* void *zr_file2mem(char *fname, int *memsize)
* int zr_mem2file(void *p, size_t psize, char *fname)
* int zr_int2file(int i, char *fname)
* int zr_stdin2file(char *fname)
* int zr_stdin2file_maxsize(char *fname, size_t maxsize)
* int zr_fcopy(char *src, char *dst)
* int zr_fmove(char *src, char *dst)
* bool zr_fexist(char *fname)
* int zr_file2strbuf(char *fname, char *buf)
* 
* 描    述：
* zr_file2str()，将文件全部内容读取到一个字符串。
* zr_file2nstr()，从文件中读取指定大小的内容到一个字符串。
* zr_str2file()，将字符串存入文件。
* zr_filesize()，查文件大小。
* zr_file2mem()，将文件内容读入内存。
* zr_mem2file()，将内存中的内容存入文件。
* zr_int2file()，将整数转换成字符串存入文件。
* zr_stdin2file()，从标准输入读取数据存入文件。
* zr_stdin2file_maxsize()，从标准输入读取不超过最以大限度的数据存入文件。如果最大
*      限度是负数，则无限度。
* zr_fcopy()，拷贝文件。
* zr_fmove()，移动文件。
* zr_fexist()，文件是否存在？
* zr_file2strbuf()，将文件读入字符缓冲区。
*
* 说    明：
* 
* 当前版本：9.0
* 作者：
* 完成日期：2004.12.31
*
* 取代版本：8.2
* 原作者：
* 完成日期：2002.07.17
*/
#ifndef _ZR_FILE_H
#define _ZR_FILE_H

#include <windows.h>

#define ZR_FILE_SUCC 1
#define ZR_FILE_FAIL 0
#define ZR_FILE_FULL -1

/* 函数功能：将文件全部内容读取到一个字符串。
 * 入口参数：char *fname -> 文件名
 * 出口参数：字符指针
 * 返    回：NULL -> 打不开文件
 *			 其他 -> 指针
 */
  //notice: need be freed!!
char *zr_file2str(char *fname);


/* 函数功能：从文件中读取指定大小的内容到一个字符串。
 * 入口参数：char *fname -> 文件名
 *			 unsigned long nsize -> 大小
 * 出口参数：字符指针
 * 返    回：NULL -> 打不开文件
 *			 其他 -> 指针
 */
  //notice: need be freed!!
char *zr_file2nstr(char *fname, unsigned long nsize);


/* 函数功能：将字符串存入文件。
 * 入口参数：char *s -> 字符串
 *			 char *fname -> 文件名
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 */
int zr_str2file(char *s, char *fname);


/* 函数功能：将整数转换成字符串存入文件。
 * 入口参数：int i -> 整数
 *			 char *fname -> 文件名
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 */
int zr_int2file(int i, char *fname);


/* 函数功能：查文件大小。
 * 入口参数：char *fname -> 文件名
 * 出口参数：整数
 * 返    回：   0 -> 0
 *			 其他 -> 文件大小
 */
int zr_filesize(char *fname);


/* 函数功能：将文件内容读入内存。
 * 入口参数：char *fname -> 文件名
 *			 int *memsize -> 文件大小（被返回）
 * 出口参数：无
 * 返    回：NULL -> 失败
 *			 其他 -> 内存地址
 */
  //notice: need be freed!!
void *zr_file2mem(char *fname, int *memsize);
int zr_file2memBuf(char *fname, void * memBuf, int bufLen);


/* 函数功能：将内存中的内容存入文件。
 * 入口参数：void *p -> 内存地址
 *			 size_t psize -> 大小
 *			 char *fname -> 文件名
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 */
int zr_mem2file(void *p, size_t psize, char *fname);


/* 函数功能：从标准输入读取数据存入文件。
 * 入口参数：char *fname -> 文件名
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 */
int zr_stdin2file(char *fname);


/* 函数功能：从标准输入读取不超过最以大限度的数据存入文件。如果最大限度是负数，
 *		则无限度。
 * 入口参数：char *fname -> 文件名
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 *			 ZR_FILE_FULL -> 达到限度
 */
int zr_stdin2file_maxsize(char *fname, size_t maxsize);


/* 函数功能：拷贝文件。
 * 入口参数：char *src -> 源
 *			 char *dst -> 目标
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 */
int zr_fcopy(char *src, char *dst);


/* 函数功能：移动文件。
 * 入口参数：char *src -> 源
 *			 char *dst -> 目标
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 */
int zr_fmove(char *src, char *dst);


/* 函数功能：文件是否存在？
 * 入口参数：char *fname -> 文件名
 * 出口参数：整数
 */
bool zr_fexist(char *fname);


/* 函数功能：将文件读入字符缓冲区。
 * 入口参数：char *fname -> 文件名
 *			 char *buf -> 缓冲区指针
 * 出口参数：整数
 * 返    回：ZR_FILE_SUCC -> 成功
 *			 ZR_FILE_FAIL -> 失败
 */
int zr_file2strbuf(char *fname, char *buf);



int zr_file_get_systemtime(char * fpath, SYSTEMTIME *p_st);

void zr_file_get_timestr(char * fpath, char *str_buf);


int zr_handle2file(HANDLE h, char *fname);
int zr_file2handle(char *fname, HANDLE *ph);

int zr_fileVarStr_set(char * varName, char * varValue);
int zr_fileVarStr_get(char * varName, char * varValueBuf);


int zr_fileVarBool_set(char * varName, bool val);
bool zr_fileVarBool_get(char * varName);

int zr_fileVarInt_set(char * varName, int val);
int zr_fileVarInt_get(char * varName);

bool zr_fileGetAppVersion(char* AppName, char * verBuf);
#endif
