/* 
* Copyright (c) 2005���Ϻ�����Ƽ����޹�˾ www.skymiracle.com
* All right reserved.
*
* �ļ����ƣ�zr_file.h
* ժ    Ҫ��
*     �����ļ�����������д��������ɾ���ȡ�
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
* ��    ����
* zr_file2str()�����ļ�ȫ�����ݶ�ȡ��һ���ַ�����
* zr_file2nstr()�����ļ��ж�ȡָ����С�����ݵ�һ���ַ�����
* zr_str2file()�����ַ��������ļ���
* zr_filesize()�����ļ���С��
* zr_file2mem()�����ļ����ݶ����ڴ档
* zr_mem2file()�����ڴ��е����ݴ����ļ���
* zr_int2file()��������ת�����ַ��������ļ���
* zr_stdin2file()���ӱ�׼�����ȡ���ݴ����ļ���
* zr_stdin2file_maxsize()���ӱ�׼�����ȡ���������Դ��޶ȵ����ݴ����ļ���������
*      �޶��Ǹ����������޶ȡ�
* zr_fcopy()�������ļ���
* zr_fmove()���ƶ��ļ���
* zr_fexist()���ļ��Ƿ���ڣ�
* zr_file2strbuf()�����ļ������ַ���������
*
* ˵    ����
* 
* ��ǰ�汾��9.0
* ���ߣ�
* ������ڣ�2004.12.31
*
* ȡ���汾��8.2
* ԭ���ߣ�
* ������ڣ�2002.07.17
*/
#ifndef _ZR_FILE_H
#define _ZR_FILE_H

#include <windows.h>

#define ZR_FILE_SUCC 1
#define ZR_FILE_FAIL 0
#define ZR_FILE_FULL -1

/* �������ܣ����ļ�ȫ�����ݶ�ȡ��һ���ַ�����
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ������ַ�ָ��
 * ��    �أ�NULL -> �򲻿��ļ�
 *			 ���� -> ָ��
 */
  //notice: need be freed!!
char *zr_file2str(char *fname);


/* �������ܣ����ļ��ж�ȡָ����С�����ݵ�һ���ַ�����
 * ��ڲ�����char *fname -> �ļ���
 *			 unsigned long nsize -> ��С
 * ���ڲ������ַ�ָ��
 * ��    �أ�NULL -> �򲻿��ļ�
 *			 ���� -> ָ��
 */
  //notice: need be freed!!
char *zr_file2nstr(char *fname, unsigned long nsize);


/* �������ܣ����ַ��������ļ���
 * ��ڲ�����char *s -> �ַ���
 *			 char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_str2file(char *s, char *fname);


/* �������ܣ�������ת�����ַ��������ļ���
 * ��ڲ�����int i -> ����
 *			 char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_int2file(int i, char *fname);


/* �������ܣ����ļ���С��
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�   0 -> 0
 *			 ���� -> �ļ���С
 */
int zr_filesize(char *fname);


/* �������ܣ����ļ����ݶ����ڴ档
 * ��ڲ�����char *fname -> �ļ���
 *			 int *memsize -> �ļ���С�������أ�
 * ���ڲ�������
 * ��    �أ�NULL -> ʧ��
 *			 ���� -> �ڴ��ַ
 */
  //notice: need be freed!!
void *zr_file2mem(char *fname, int *memsize);
int zr_file2memBuf(char *fname, void * memBuf, int bufLen);


/* �������ܣ����ڴ��е����ݴ����ļ���
 * ��ڲ�����void *p -> �ڴ��ַ
 *			 size_t psize -> ��С
 *			 char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_mem2file(void *p, size_t psize, char *fname);


/* �������ܣ��ӱ�׼�����ȡ���ݴ����ļ���
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_stdin2file(char *fname);


/* �������ܣ��ӱ�׼�����ȡ���������Դ��޶ȵ����ݴ����ļ����������޶��Ǹ�����
 *		�����޶ȡ�
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 *			 ZR_FILE_FULL -> �ﵽ�޶�
 */
int zr_stdin2file_maxsize(char *fname, size_t maxsize);


/* �������ܣ������ļ���
 * ��ڲ�����char *src -> Դ
 *			 char *dst -> Ŀ��
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_fcopy(char *src, char *dst);


/* �������ܣ��ƶ��ļ���
 * ��ڲ�����char *src -> Դ
 *			 char *dst -> Ŀ��
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_fmove(char *src, char *dst);


/* �������ܣ��ļ��Ƿ���ڣ�
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 */
bool zr_fexist(char *fname);


/* �������ܣ����ļ������ַ���������
 * ��ڲ�����char *fname -> �ļ���
 *			 char *buf -> ������ָ��
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
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
