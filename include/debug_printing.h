#ifndef DEBUG_PRINTING_H
#define DEBUG_PRINTING_H
#ifdef DEBUG
    #define DPRINT(str)           Serial.print(str);
    #define DPRINTF(fmt, ...)     Serial.printf(fmt, __VA_ARGS__);
    #define DPRINTLN()            Serial.println();
    #define DBG_PRINT(str)        Serial.print("[DEBUG] " str);
    #define OK_PRINT(str)         Serial.print("[OKAY] " str);
    #define WARN_PRINT(str)       Serial.print("[WARN] " str);
    #define ERR_PRINT(str)        Serial.print("[ERROR] " str);
    #define DBG_PRINTF(fmt, ...)  DPRINTF("[DEBUG] " fmt, __VA_ARGS__);
    #define OK_PRINTF(fmt, ...)   DPRINTF("[OKAY] " fmt, __VA_ARGS__);
    #define WARN_PRINTF(fmt, ...) DPRINTF("[WARN] " fmt, __VA_ARGS__);
    #define ERR_PRINTF(fmt, ...)  DPRINTF("[ERROR] " fmt, __VA_ARGS__);
#else
    #define DPRINT(str)
    #define DPRINTF(fmt, ...)
    #define DPRINTLN()
    #define DBG_PRINT(str)
    #define OK_PRINT(str)
    #define WARN_PRINT(str)
    #define ERR_PRINT(str)
    #define DBG_PRINTF(fmt, ...)
    #define OK_PRINTF(fmt, ...)
    #define WARN_PRINTF(fmt, ...)
    #define ERR_PRINTF(fmt, ...)
#endif
#endif
