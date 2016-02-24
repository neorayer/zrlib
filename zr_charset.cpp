#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#include "zr_charset.h"

void UTF_8ToUnicode(WCHAR* pOut, char *pText) {
	char* uchar = (char *)pOut;

	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);

	return;
}

void UnicodeToUTF_8(char* pOut, WCHAR* pText) {
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char *)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));

	return;
}

void UnicodeToGB2312(char* pOut, unsigned short uData) {
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(WCHAR),NULL,NULL);
	return;
}

void Gb2312ToUnicode(WCHAR* pOut, char *gbBuffer) {
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	return;
}

char * GB2312ToUTF_8( char *pText, int pLen) {
	char buf[4];
	char* rst = new char[pLen + (pLen >> 2) + 2];

	memset(buf, 0, 4);
	memset(rst, 0, pLen + (pLen >> 2) + 2);

	int i = 0;
	int j = 0;
	while (i < pLen) {
		//如果是英文直接复制就可以
		if ( *(pText + i) >= 0) {
			rst[j++] = pText[i++];
		} else {
			WCHAR pbuffer;
			Gb2312ToUnicode(&pbuffer, pText+i);

			UnicodeToUTF_8(buf, &pbuffer);

			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];

			j += 3;
			i += 2;
		}
	}
	rst[j] = '\0';

	return rst;
}
