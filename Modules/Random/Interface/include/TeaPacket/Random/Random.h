
#ifndef TEAPACKET_RANDOM_H
#define TEAPACKET_RANDOM_H
#ifdef __cplusplus
extern "C" {
#endif

float TP_Random_F(void);
int TP_Random_IRangeInclusive(int min, int max);
unsigned int TP_Random_UIRangeInclusive(unsigned int min, unsigned max);


#ifdef __cplusplus
}
#endif
#endif
