#ifndef __ZR_LOGGER_H__
#define __ZR_LOGGER_H__

	
#define ZR_LOG_LV_NO 			0
#define ZR_LOG_LV_FERROR 	1
#define ZR_LOG_LV_ERROR 		2
#define ZR_LOG_LV_WARN 		3
#define ZR_LOG_LV_INFO 		4
#define ZR_LOG_LV_DEBUG 		5
#define ZR_LOG_LV_DETAIL 		6

#define ZR_LOG_TG_STDOUT		0
#define ZR_LOG_TG_FILE			1

void zr_log_set_level(int l);
void zr_log_set_target(int t);
void zr_log_set_filepath(char * s);

void zr_log_msg(int errorcode, char * head, char *format, ...);

void zr_log_detail_ec(int errorcode, char * format, ...);
void zr_log_debug_ec(int errorcode, char * format, ...);
void zr_log_info_ec(int errorcode, char * format, ...);
void zr_log_warn_ec(int errorcode, char * format, ...);
void zr_log_error_ec(int errorcode, char * format, ...);
void zr_log_ferror_ec(int errorcode, char * format, ...);

#define zr_log_detail(s)		zr_log_detail_ec(0, s)
#define zr_log_debug(s)		zr_log_debug_ec(0, s)
#define zr_log_info(s)			zr_log_info_ec(0, s)
#define zr_log_warn(s)			zr_log_warn_ec(0, s)
#define zr_log_error(s)		zr_log_error_ec(0, s)
#define zr_log_ferror(s)		zr_log_ferror_ec(0, s)


#endif //__ZR_LOGGER_H__
