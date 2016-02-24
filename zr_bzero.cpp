/* 
* Copyright (c) 2005，上海天奇科技有限公司 www.skymiracle.com
* All right reserved.
*
* 文件名称：zr_bzero.c
* 摘    要：
*     从指针开始按字符方式置n个零。
* 
* 当前版本：9.0
* 作者：
* 完成日期：2004.12.28
*
* 取代版本：8.2
* 原作者：
* 完成日期：2002.07.17
*/

#include <string.h>
#include "zr_bzero.h"

/* 函数功能：从指针p开始处置数量n个零
 * 入口参数：void *p ->	源指针地址
 *			 int n	 -> 数量
 * 出口参数：void
 * 函数返回：NULL -> 源指针地址为空
 *			 其他 -> 源指针地址
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
