/**
 * @file lu_log.c
 * @author <Lucifer gj3372819612@163.com>
 * @date 2025-12-13
 * @brief Log an event to the event log.
*/
#include <stdio.h>
#include <stdarg.h>
#include "lu_log-internal.h"
#include "lu_util.h"
#include "lu_erron.h"
//#include "lu_mm-internal.h"

/**
 * @brief Log an event to the event log.
 * @param severity The severity of the event.
 * @param msg The message to log.
*/
static void lu_event_log_(int severity, const char *msg);



#ifdef LU_EVENT_DEBUG_LOGGING_ENABLED
#ifdef LU_USE_DEBUG
#define DEFAULT_MASK LU_EVENT_DBG_ALL
#else
#define DEFAULT_MASK 0
#endif
LU_EVENT_EXPORT_SYMBOL lu_uint32_t lu_event_debug_logging_mask_ = DEFAULT_MASK;
#endif /* LU_EVENT_DEBUG_LOGGING_ENABLED */


static void lu_event_log_(int severity, const char *msg) { 
        
    if(lu_event_log_global_cb)
        lu_event_log_global_cb(severity, msg);
    else{
        const char * severity_str;
        switch(severity){
            case LU_EVENT_LOG_DEBUG:
                severity_str = "debug";
                break;
            case LU_EVENT_LOG_MSG:
                severity_str = "msg";
                break;
            case LU_EVENT_LOG_WARN:
                severity_str = "warn";
                break;
            case LU_EVENT_LOG_ERROR:
                severity_str = "error";
                break;
            default:
                severity_str = "unknown_severity";
                break;
        }
        //void to avoid unused variable warning
        (void)fprintf(stderr, "[%s] %s\n", severity_str, msg);
    }

}

void lu_event_set_log_callback(lu_event_log_cb log_cb){
    lu_event_log_global_cb = log_cb;    
}

void lu_event_enable_debug_logging(lu_uint32_t which_mask)
{
    #ifdef LU_EVENT_DEBUG_LOGGING_ENABLED
    lu_event_debug_logging_mask_ = which_mask;
    #endif /* LU_EVENT_DEBUG_LOGGING_ENABLED */
}

