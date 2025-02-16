
void startup();

int GPIOD = 0x40020C00;

#define GPIO_D_BASE ((unsigned int *) 0x40020C00)
#define GPIO_D_OTYPER (unsigned short *) (GPIO_D_BASE + 0x4)
#define GPIO_D_PUPDR (unsigned int *) (GPIO_D_BASE + 0xC)
//#define GPIO_D_ODR (unsigned int *) (GPIO_D_BASE + 0x12)


void startup();

void app_init(){
    *GPIO_D_BASE = 0x55005500;   // 010101010000....
    *GPIO_D_OTYPER = 0x0F00;     // 000111100000000
    *GPIO_D_PUPDR = 0x00AA0000;  // 0000000010101010000....
}


//Eventuella hjälprutiner
#define GPIO_D_ODR_HIGH ((volatile unsigned char *) 0x40020C15)
void activateRow(int row){
    switch (row)
    {
    case 1: *GPIO_D_ODR_HIGH = 0x10; break;
    case 2: *GPIO_D_ODR_HIGH = 0x20; break;
    case 3: *GPIO_D_ODR_HIGH = 0x40; break;
    case 4: *GPIO_D_ODR_HIGH = 0x80; break;
    
    default: *GPIO_D_ODR_HIGH = 0; break;
    }
}


#define GPIO_D_IDR_HIGH ((volatile unsigned char *) 0x40020C11)
unsigned char readColumn(){
    unsigned char c;

    c = *GPIO_D_IDR_HIGH;
    if(c & 8) return 4;
    if(c & 4) return 3;
    if(c & 2) return 2;
    if(c & 1) return 4;
    
    return 0;
}
//---------------------------------------


unsigned char keyb( void ){

    char keyValue[4][4] = {{1,2,3,0xA}, {4,5,6,0xB},{7,8,9,0xC}, {0xE,0,0xF,0xD}};
    int row, col;
    
    for(row = 0; row <= 3; row++){
        activateRow(row + 1);
        if(col = readColumn() != 0){
            activateRow(0);
            return keyValue[row][col - 1];
        }
    }
    activateRow(0);
    return 0xFF;
}

#define GPIO_D_ODR_LOW ((volatile unsigned char *) 0x40020C14)
void out7seg(unsigned char c){
    //*GPIO_D_ODR_LOW = (unsigned short) c;
    
    short t = 0b0;

    for(int i = 0; i < 256; i++){
        *GPIO_D_ODR_LOW = t;
        t = t + 0b10;
    }


    *GPIO_D_ODR_LOW = 0b00001001;
    *GPIO_D_ODR_LOW = 0b00001000;
    *GPIO_D_ODR_LOW = 0b00001111;
    *GPIO_D_ODR_LOW = 0b00001000;
    *GPIO_D_ODR_LOW = 0b00010000;
    *GPIO_D_ODR_LOW = 0b00000010;
    *GPIO_D_ODR_LOW = 0b00000010;
    *GPIO_D_ODR_LOW = 0b10000000;
}


void main(void){
    app_init();
    while (1)
    {
        unsigned char test = keyb();
        out7seg(test);
        //out7seg(keyb());
    }
    
}