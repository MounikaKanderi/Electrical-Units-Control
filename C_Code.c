#include <p18f452.h>

// Define constants for bit positions
#define LIGHT1_PIN PORTAbits.RA0
#define LIGHT2_PIN PORTAbits.RA1
#define FAN_PIN PORTAbits.RA2
#pragma code
// Interrupt Service Routine for INT0 (connected to PORTB, bit 0)
void __interrupt() ISR(void)
{
    if (INTCONbits.INT0IF) // Check if INT0 interrupt flag is set
    {
        LIGHT1_PIN ^= 1;    // Toggle LIGHT1
        INTCONbits.INT0IF = 0; // Clear INT0 interrupt flag
    }
    
    if (INTCON3bits.INT1IF) // Check if INT1 interrupt flag is set
    {
        LIGHT2_PIN ^= 1;    // Toggle LIGHT2
        INTCON3bits.INT1IF = 0; // Clear INT1 interrupt flag
    }
    
    if (INTCON3bits.INT2IF) // Check if INT2 interrupt flag is set
    {
        FAN_PIN ^= 1;       // Toggle FAN
        INTCON3bits.INT2IF = 0; // Clear INT2 interrupt flag
    }
}

void main(void)
{
    // Initialize PORTA as output for controlling devices
    TRISAbits.TRISA0 = 0; // LIGHT1 control
    TRISAbits.TRISA1 = 0; // LIGHT2 control
    TRISAbits.TRISA2 = 0; // FAN control

    // Initialize PORTB as input for switch/button control
    TRISBbits.TRISB0 = 1; // Switch for LIGHT1
    TRISBbits.TRISB1 = 1; // Switch for LIGHT2
    TRISBbits.TRISB2 = 1; // Switch for FAN

    // Enable external interrupts
    INTCONbits.INT0IE = 1; // Enable INT0 (connected to PORTB, bit 0)
    INTCON3bits.INT1IE = 1; // Enable INT1 (connected to PORTB, bit 1)
    INTCON3bits.INT2IE = 1; // Enable INT2 (connected to PORTB, bit 2)

    // Clear interrupt flags
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;

    // Basic switch control
    if (PORTBbits.RB0) // Check if switch for LIGHT1 is pressed
    {
        LIGHT1_PIN = 1; // Turn on LIGHT1
    }
    if (PORTBbits.RB1) // Check if switch for LIGHT2 is pressed
    {
        LIGHT2_PIN = 1; // Turn on LIGHT2
    }
    if (PORTBbits.RB2) // Check if switch for FAN is pressed
    {
        FAN_PIN = 1;    // Turn on FAN
    }
    
    for(;;);
    
}
