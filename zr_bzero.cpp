/* 
* Copyright (c) 2005���Ϻ�����Ƽ����޹�˾ www.skymiracle.com
* All right reserved.
*
* �ļ����ƣ�zr_bzero.c
* ժ    Ҫ��
*     ��ָ�뿪ʼ���ַ���ʽ��n���㡣
* 
* ��ǰ�汾��9.0
* ���ߣ�
* ������ڣ�2004.12.28
*
* ȡ���汾��8.2
* ԭ���ߣ�
* ������ڣ�2002.07.17
*/

#include <string.h>
#include "zr_bzero.h"

/* �������ܣ���ָ��p��ʼ��������n����
 * ��ڲ�����void *p ->	Դָ���ַ
 *			 int n	 -> ����
 * ���ڲ�����void
 * �������أ�NULL -> Դָ���ַΪ��
 *			 ���� -> Դָ���ַ
 */
void *zr_bzero(void *p, int n)
{
	char *s;
	register int i;

	if (!p)
		return NULL;
	s = (char *)p;

	for (i=0; i < n; i++)
		s[i] = 0x0;

	return p;
}
