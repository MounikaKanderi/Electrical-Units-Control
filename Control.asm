#include "p18f452.inc"
    
    ORG 00H
    GOTO MAIN
    
    ORG 0008H
CHECK    BTFSC INTCON , INT0IF
    GOTO LIGHT1
    BCF PORTA,0
    BTFSC INTCON3 , INT1IF
    GOTO LIGHT2
    BCF PORTA,1
    BTFSC INTCON3 , INT2IF
    GOTO FAN
    BCF PORTA,2
    RETFIE
    
    ORG 100H
    ;Connecting PORTA 0 to 3 to electrical devices 
MAIN    BCF TRISA , 0 ; PORTA,0 to light1 
    BCF TRISA , 1 ; PORTA,1 to light2 
    BCF TRISA , 2 ; PORTA,2 to fan 
    
    BSF TRISB , 0 ; PORTB,0 to light1 control to a switch/button on mobile 
    BSF TRISB , 1 ; PORTB,1 to light2 control to a switch/button on mobile 
    BSF TRISB , 2 ; PORTB,2 to fan control to a switch/button on mobile 
    
    BSF INTCON , INT0IE
    BSF INTCON3 , INT1IE
    BSF INTCON3 , INT2IE
    BCF INTCON , INT0IF
    BCF INTCON3 , INT1IF
    BCF INTCON3 , INT2IF

    
    ;Basic Switch control
    BTFSC PORTB , 0
    BSF PORTA , 0
    BTFSC PORTB , 1
    BSF PORTA , 1
    BTFSC PORTB , 2
    BSF PORTA , 2
    

    ORG 200H
LIGHT1 BTG PORTA,0
    BCF INTCON , INT0IF
    GOTO CHECK
    
    ORG 300H
LIGHT2 BTG PORTA,1
    BCF INTCON3 , INT1IF
    GOTO CHECK
    
    ORG 400H
FAN BTG PORTA,2
    BCF INTCON3 , INT2IF
    GOTO CHECK
    
    END