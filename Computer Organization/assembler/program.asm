        ORG 10
        //get input of 2 digit octal number
FSA,    SKI 		//look for input
	    BUN	FSA		//No input
	    CLA			//Clear AC
	    INP			//input character to AC
	    ADD	NEG30	//convert to octal
	    STA	INPUT1	//Store first character in INPUT1
        CLA
FSB,    SKI 		//look for input
	    BUN	FSB		//No input
	    CLA			//Clear AC
	    INP 		//Second INP for second character
	    ADD	NEG30	//convert to octal
	    STA	INPUT2 	//store input in INPUT2
        
        //convert input to decimal
        LDA	INPUT1  //dont have to do a loop becuase input will always be 2 digits
        CIL
        ADD MIN1
        CIL
        ADD MIN1
        CIL                 
        ADD MIN1     //INPUT1 * pow(8,1)
        ADD	INPUT2
        STA	DECIMAL //DECIMAL = INPUT1 * pow(8,0) + INPUT2 * pow(8,1)

        //find if divisible by 3 or 5
        STA DIVIDEND
        CLA
        LDA THREE
        STA DIVISOR
        BSA DIVIDE
        CLA
        LDA DIVIDEND
        STA MOD3    //mod3 = decimal % 3

        CLA
        LDA DECIMAL
        STA DIVIDEND
        LDA FIVE
        STA DIVISOR
        BSA DIVIDE
        LDA DIVIDEND
        STA MOD5    //mod5 = decimal % 5
        HLT

DIVIDE,	LDA 	DIVIDEND	//To use, set values for DIVIDEND and DIVISOR. After completion, quotient is in QUO and remainder is in DIVIDEND.
DIVIDEL,STA 	DIVIDEND	//store value of last loop
        LDA 	QUO     	//load quotient into AC
        INC            	 
       	STA 	QUO     	//QUO++
        LDA 	DIVISOR 	//move divisor into AC
        CMA             	//complement divisor
        INC             	//Divisor is now negative
        ADD 	DIVIDEND	//Subtract Dividend from Divisor
        SNA             	//If Dividend is larger than Divisor, this number will be positive
        BUN 	DIVIDEL 	//internal label for looping, end of loop. while(Dividend>=Divisor){Dividend-=Divisor; QUO++;};
        LDA 	QUO     	//quotient is 1 more than actual value
        ADD 	MIN1    	//subtract1
        STA 	QUO		    //QUO--
        BSA	    DIVIDE  I
        

INPUT1,	DEC 	0
INPUT2,	DEC	    0
NEG30,	HEX	    -30
DECIMAL,DEC	0
MOD3,   DEC     0
MOD5,   DEC     0
THREE,  DEC     3
FIVE,   DEC     5
DIVIDEND,   	DEC	0 		//the number that is being divided. Stores remainder after running.
DIVISOR,	DEC 	0		//the number you are dividing by
QUO,    	DEC 	0		//result of division
MIN1,   	DEC 	-1		//for decrementing
        END