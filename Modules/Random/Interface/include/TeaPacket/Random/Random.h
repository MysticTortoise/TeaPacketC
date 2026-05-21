/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_RANDOM_H
#define TEAPACKET_RANDOM_H
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *  Generates a random float value.
 * @return A random float value between 0 (inclusive) and 1 (exclusive)
 */
float TP_Random_F(void);
/**
 * Generates a random signed integer between two values.
 * @param min The minimum possible number to generate (inclusive)
 * @param max The maximum possible number to generate (inclusive)
 * @return A random signed integer between the given range.
 */
int TP_Random_IRangeInclusive(int min, int max);
/**
 * Generates a random unsigned integer between two values.
 * @param min The minimum possible number to generate (inclusive)
 * @param max The maximum possible number to generate (inclusive)
 * @return A random unsigned integer between the given range.
 */
unsigned int TP_Random_UIRangeInclusive(unsigned int min, unsigned max);


#ifdef __cplusplus
}
#endif
#endif
