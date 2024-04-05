            ORG     10
DIVIDE,     STA     DIVIDEND    //store value of last loop
            //NOP               Body of while loop goes here
            LDA     DIVISOR     //move divisor into AC
            CMA                 //complement divisor
            INC                 //Divisor is now negative
            ADD     DIVIDEND    //Subtract Dividend from Divisor
            STA     RES
            SNA                 //If Dividend is larger than Divisor, this number will be positive
            BUN     DIVIDE
            HLT

DIVIDEND,   DEC     22
DIVISOR,    DEC     4
RES,        DEC     0
            END
