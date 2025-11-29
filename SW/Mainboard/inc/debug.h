#ifndef _DEBUG_H_GUARD
#define _DEBUG_H_GUARD

#define LOG_INFO (log_info(__LINE__,__FILE__))
#define LOG_WARNING (log_info(__LINE__,__FILE__))
#define LOG_FATAL (log_fatal(__LINE__,__FILE__))

void log_info(uint32_t line, char *file);

void log_fatal(uint32_t line, char *file);

#endif /* _DEBUG_H_GUARD */