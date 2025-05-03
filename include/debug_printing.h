#include <Arduino.h>
#ifndef DEBUG_PRINTING_H
    #define DEBUG_PRINTING_H
    #ifdef DEBUG
        #define DPRINT(msg)   Serial.print(msg);
        #define DPRINTLN(msg) Serial.println(msg);
        #define OK_PRINT(msg) Serial.printf("[OKAY] %s", msg);
        #define OK_PRINTLN(msg) Serial.printf("[OKAY] %s\n", msg);
        #define ERR_PRINT(msg) Serial.printf("[ERROR] %s", msg);
        #define ERR_PRINTLN(msg) Serial.printf("[ERROR] %s\n", msg);
        #define DBG_PRINT(msg) Serial.printf("[DEBUG] %s", msg);
        #define DBG_PRINTLN(msg) Serial.printf("[DEBUG] %s\n", msg);
        #define WARN_PRINT(msg) Serial.printf("[WARN] %s", msg);
        #define WARN_PRINTLN(msg) Serial.printf("[WARN] %s\n", msg);
    #else
        #define DPRINT(msg)
        #define DPRINTLN(msg)
        #define OK_PRINT(msg)
        #define OK_PRINTLN(msg)
        #define ERR_PRINT(msg)
        #define ERR_PRINTLN(msg)
        #define DBG_PRINT(msg)
        #define DBG_PRINTLN(msg)
        #define WARN_PRINT(msg)
        #define WARN_PRINTLN(msg)
    #endif
#endif
