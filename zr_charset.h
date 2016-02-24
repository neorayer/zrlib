#ifndef ZR_CHARSET_H_
#define ZR_CHARSET_H_


void UTF_8ToUnicode(WCHAR* pOut, char *pText) ;

void UnicodeToUTF_8(char* pOut, WCHAR* pText) ;

void UnicodeToGB2312(char* pOut, unsigned short uData) ;

void Gb2312ToUnicode(WCHAR* pOut, char *gbBuffer) ;

char * GB2312ToUTF_8(char *pText, int pLen);

#endif