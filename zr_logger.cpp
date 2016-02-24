#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>


#include "zr_const.h"
#include "zr_logger.h"

char zr_log_filepath[MAX_PATH];
int zr_log_level = ZR_LOG_LV_DETAIL;
int zr_log_target = ZR_LOG_TG_STDOUT;

void zr_log_set_level(int l) {
	zr_log_level = l;
}

void zr_log_set_target(int t) {
	zr_log_target = t;
}

void zr_log_set_filepath(char * s) {
	strcpy(zr_log_filepath, s);
}

void _zr_log_vmsg(int errorcode, char * head, char *format, va_list ap) {
	switch (zr_log_target) {
	case ZR_LOG_TG_STDOUT:
		printf("%d: ", time(NULL));
		printf("%s", head);
		printf(" [%d]: ", errorcode);
		vprintf(format, ap);
		printf("\r\n");
		break;
	case ZR_LOG_TG_FILE:
		FILE *fd;
		if (!(fd = fopen(zr_log_filepath, "a+t"))) {
			printf("%s\n", "zr_log_filepath is NULL");
			return;
		}
		fprintf(fd, "%d: ", time(NULL));
		fprintf(fd, "%s", head);
		fprintf(fd, " [%d]: ", errorcode);
		vfprintf(fd, format, ap);
		fprintf(fd, "\n");
		fclose(fd);
		break;
	}
	return;
}


void zr_log_msg(int errorcode, char * head, char *format, ...) {
	va_list ap;
	va_start(ap, format);
	_zr_log_vmsg(errorcode, head, format, ap);
	va_end(ap);
}

void zr_log_detail_ec(int errorcode, char * format, ...) {
	if (zr_log_level < ZR_LOG_LV_DETAIL)
		return;
	va_list ap;
	va_start(ap, format);
	_zr_log_vmsg(errorcode, "DETAIL", format, ap);
	va_end(ap);
}

void zr_log_debug_ec(int errorcode, char * format, ...) {
	if (zr_log_level < ZR_LOG_LV_DEBUG)
		return;
	va_list ap;
	va_start(ap, format);
	_zr_log_vmsg(errorcode, "DEBUG ", format, ap);
	va_end(ap);
}

void zr_log_info_ec(int errorcode, char * format, ...) {
	if (zr_log_level < ZR_LOG_LV_INFO)
		return;
	va_list ap;
	va_start(ap, format);
	_zr_log_vmsg(errorcode, "INFO  ", format, ap);
	va_end(ap);
}

void zr_log_warn_ec(int errorcode, char * format, ...) {
	if (zr_log_level < ZR_LOG_LV_WARN)
		return;
	va_list ap;
	va_start(ap, format);
	_zr_log_vmsg(errorcode, "WARN  ", format, ap);
	va_end(ap);
}

void zr_log_error_ec(int errorcode, char * format, ...) {
	if (zr_log_level < ZR_LOG_LV_ERROR)
		return;
	va_list ap;
	va_start(ap, format);
	_zr_log_vmsg(errorcode, "ERROR ", format, ap);
	va_end(ap);
}

void zr_log_ferror_ec(int errorcode, char * format, ...) {
	if (zr_log_level < ZR_LOG_LV_FERROR)
		return;
	va_list ap;
	va_start(ap, format);
	_zr_log_vmsg(errorcode, "FERROR", format, ap);
	va_end(ap);
}