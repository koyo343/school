#include <xc.h>


void wait(int n) {
    long wait_loops = 10000 * n;    
    for (long i = 0; i < wait_loops; ++i) {
        asm volatile ("nop");
    }
}

void on_off_on(void){
    int a, b, c;
    a = 11;
    b = 7;
    c = a + b;
    
    // LED test
    TRISBCLR = 15;  // set RBxs to output
    PORTB = 0b1110;  // blue in binary number
    wait(2);
    PORTB = 0b1101;
    wait(2);
    PORTB = 0b1110;

}


int main(void)
{
        
    on_off_on();    
    return 0;
}