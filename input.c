#define GPIO_BASE 0x04000060 // check GPIO_BASE in system.h file 
#define LED_BASE 0x04000000




volatile int *gpio_pins = (volatile int*) GPIO_BASE; //tells the compiler to not optimise reads 
                                                    //or writes to this pointer

                                                   

