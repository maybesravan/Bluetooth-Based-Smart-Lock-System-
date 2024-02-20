//interrupt_H
#define EINT0_LED 31
#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3
#define CFGPIN(WORD,PIN,FUNC)  WORD=((PIN<16)?((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))):((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2))));
void eint0_isr(void) __irq;
void Enable_EINT0(void);

