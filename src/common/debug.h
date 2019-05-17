#ifdef DEBUG
#define DEBUG_PRINT_LN(x) Serial.println(x)
#else
#define DEBUG_PRINT_LN(x)
#endif

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINT(x)
#endif