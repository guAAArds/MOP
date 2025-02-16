
#define STK_CTRL ((volatile unsigned int *)0xE000E010)
#define STK_LOAD ((volatile unsigned int *)0xE000E014)



void delay_250ns(){
    *STK_LOAD = 42; // 42 cykler = 250 ns
    *STK_CTRL = 0x5; // (binärt 101)
    while((*STK_CTRL & 0x10000) == 0) // Medans COUNTFLAG=0
    {}; // Gör ingenting
}
void delay_mikro(unsigned int us){
    for(unsigned int i = 0; i < us; i++){
        delay_250ns();
    }
}
void delay_milli(unsigned int ms){
    for(unsigned int i = 0; i < ms; i++){
        delay_250ns();
    }
}



#define PORT_BASE ((volatile unsigned int *) 0x40021000)





void ascii_write_controller(unsigned char byte){
    *PORT_BASE = 
}



void ascii_ctrl_bit_set(unsigned char x){
    *PORT_BASE = *PORT_BASE | x;
}

void ascii_ctrl_bit_clear(unsigned char x){
    *PORT_BASE = *PORT_BASE & (~x);
}


#define GPIO_E_ODR ((unsigned short *) 0x40021014)
void main(void){
     
    
}