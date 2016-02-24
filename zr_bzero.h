/* 
* Copyright (c) 2005，上海天奇科技有限公司 www.skymiracle.com
* All right reserved.
*
* 文件名称：zr_bzero.h
* 摘    要：
*     置零操作。
* 
* 当前版本：9.0
* 作者：
* 完成日期：2004.12.28
*
* 取代版本：8.2
* 原作者：
* 完成日期：2002.07.17
*/

#ifndef _ZR_BZERO_H
#define _ZR_BZERO_H

/* 函数功能：从指针p开始处置数量n个零
 * 入口参数：void *p ->	源指针地址
 *			 int n	 -> 数量
 * 出口参数：void
 * 函数返回：NULL -> 源指针地址为空
 *			 其他 -> 源指针地址
 */
void *zr_bzero(void *p, int n);

#endif
