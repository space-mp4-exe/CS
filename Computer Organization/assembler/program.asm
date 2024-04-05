            ORG     10
DIVIDE,     LDA     DIVIDEND    //To use, set values for DIVIDEND and DIVISOR. After completion, quotient is in QUO and remainder is in DIVIDEND.
DIVIDEL,    STA     DIVIDEND    //store value of last loop
            LDA     QUO         //load quotient into AC
            INC                 
            STA     QUO         //QUO++
            LDA     DIVISOR     //move divisor into AC
            CMA                 //complement divisor
            INC                 //Divisor is now negative
            ADD     DIVIDEND    //Subtract Dividend from Divisor
            SNA                 //If Dividend is larger than Divisor, this number will be positive
            BUN     DIVIDEL     //internal label for looping, end of loop. while(Dividend>=Divisor){};
            LDA     QUO         //quotient is 1 more than actual value
            ADD     MIN1        //subtract 1
            STA     QUO
            HLT

DIVIDEND,   DEC     22
DIVISOR,    DEC     4
QUO,        DEC     0
MIN1,       DEC     -1
            END
