/* 
* Copyright (c) 2005���Ϻ�����Ƽ����޹�˾ www.skymiracle.com
* All right reserved.
*
* �ļ����ƣ�zr_bzero.h
* ժ    Ҫ��
*     ���������
* 
* ��ǰ�汾��9.0
* ���ߣ�
* ������ڣ�2004.12.28
*
* ȡ���汾��8.2
* ԭ���ߣ�
* ������ڣ�2002.07.17
*/

#ifndef _ZR_BZERO_H
#define _ZR_BZERO_H

/* �������ܣ���ָ��p��ʼ��������n����
 * ��ڲ�����void *p ->	Դָ���ַ
 *			 int n	 -> ����
 * ���ڲ�����void
 * �������أ�NULL -> Դָ���ַΪ��
 *			 ���� -> Դָ���ַ
 */
void *zr_bzero(void *p, int n);

#endif
