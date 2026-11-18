#ifndef HOLY_CANDLES_H
#define HOLY_CANDLES_H

#define CANDLE_TYPE_GPR   double
#define CANDLE_TYPE_FLOAT float

/**
 * Try placing this above a haunted function.
 * 
 * Example:
 * 
 * ```c
 * CANDLE(Object_Draw, CANDLE_TYPE_FLOAT, *);
 * ```
 */
#define CANDLE(_name, _type, _op) static _type candle_##_name(_type argument) { return argument _op argument; }

#endif // HOLY_CANDLES_H
