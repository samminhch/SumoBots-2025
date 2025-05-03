#include <Arduino.h>
#ifndef DEBUG_PRINTING_H
    #define DEBUG_PRINTING_H
    #ifdef DEBUG
        #define DPRINT(msg)   Serial.print(msg);
        #define DPRINTLN(msg) Serial.println(msg);
        #define OK_PRINT(msg)           \
            Serial.print(F("[OKAY] ")); \
            Serial.print(F(msg));
        #define OK_PRINTLN(msg)         \
            Serial.print(F("[OKAY] ")); \
            Serial.println(F((msg)));
        #define ERR_PRINT(msg)           \
            Serial.print(F("[ERROR] ")); \
            Serial.print(F((msg)));
        #define ERR_PRINTLN(msg)         \
            Serial.print(F("[ERROR] ")); \
            Serial.println(F((msg)));
        #define DBG_PRINT(msg)           \
            Serial.print(F("[DEBUG] ")); \
            Serial.print(F((msg)));
        #define DBG_PRINTLN(msg)         \
            Serial.print(F("[DEBUG] ")); \
            Serial.println(F((msg)));
        #define WARN_PRINT(msg)         \
            Serial.print(F("[WARN] ")); \
            Serial.print(F((msg)));
        #define WARN_PRINTLN(msg)       \
            Serial.print(F("[WARN] ")); \
            Serial.println(F((msg)));
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
