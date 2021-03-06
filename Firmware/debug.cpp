#include "debug.h"


/**************************************************************************/
/*!
    @brief  This function will display the number of bytes currently free
            in RAM ... useful for debugging!
*/
/**************************************************************************/
void displayFreeRam(void)
{
  extern int  __bss_end;
  extern int  *__brkval;
  int free_memory;
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
  }
  
  Serial.print(F("Free RAM: "));
  Serial.print(free_memory);
  Serial.println(F(" bytes"));
} 


void uart_putchar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    UDR0 = c;
}

void printDec(uint8_t h) {
  uart_putchar((h / 100) + '0');
  h %= 100;
  uart_putchar((h / 10) + '0');
  h %= 10;
  uart_putchar(h + '0');
}


void printHex(uint8_t h) {
  uint8_t d = h >> 4;
  if (d > 10) {
    uart_putchar(d - 10 + 'A');
  } else {
    uart_putchar(d + '0');
  }
  h &= 0xF;
  if (h > 10) {
    uart_putchar(h - 10 + 'A');
  } else {
    uart_putchar(h + '0');
  }
}

void printHex16(uint16_t h) {
  uart_putchar('0');
  uart_putchar('x');
  DEBUGPRINT_HEX(h >> 8);
  DEBUGPRINT_HEX(h);
}


void printDec16(uint16_t h) {
  uart_putchar((h / 10000) + '0');
  h %= 10000;
  uart_putchar((h / 1000) + '0');
  h %= 1000;
  uart_putchar((h / 100) + '0');
  h %= 100;
  uart_putchar((h / 10) + '0');
  h %= 10;
  uart_putchar(h + '0');
}


void DEBUGPRINT(const prog_char *fstr)
{
  char c;
  if(!fstr) return;
  while((c = pgm_read_byte(fstr++)))
    uart_putchar(c);
}
