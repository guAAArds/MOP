
#define STK_CTRL ((volatile unsigned int *)0xE000E010)
#define STK_LOAD ((volatile unsigned int *)0xE000E014)




void delay_250ns(){
    *STK_LOAD = 42; // 42 cykler = 250 ns
    *STK_CTRL = 0x5; // (binärt 101)
    while(*STK_CTRL & 0x10000 == 0) // Medans COUNTFLAG=0
    {}; // Gör ingenting
}

void delay_mikro(unsigned int us){
    for(int i = 0; i < us; i++){
        delay_250ns();
    }
}

void delay_milli(unsigned int ms){
    for(int i = 0; i < ms; i++){
        delay_250ns();
    }
}

#define GPIO_E_MODER ((unsigned int *) 0x40021000)
void init_app(){
    *GPIO_E_MODER = 0x5555;
}

#define GPIO_E_ODR ((unsigned short *) 0x40021014)
void main(void){
    init_app();
    while(1){
        *GPIO_E_ODR = 0x00;
        delay_mikro(5000);
        *GPIO_E_ODR = 0xFF;
        delay_mikro(5000);
    }
    
}