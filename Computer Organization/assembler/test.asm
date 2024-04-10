                ORG     10
                LDA     DECIMAL
                STA     DIVIDEND
                LDA     THREE
                STA     DIVISOR
                BSA     DIVIDE
                CLA
                LDA     DIVIDEND
                STA     MOD3            //mod3 = decimal % 3
                HLT

                //DIVIDE subroutine
DIVIDE,	        LDA 	DIVIDEND	//To use, set values for DIVIDEND and DIVISOR. After completion, quotient is in QUO and remainder is in DIVIDEND.
DIVIDEL,        STA 	DIVIDEND	//store value of last loop
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
                STA 	QUO		//QUO--
                BSA	DIVIDE  I

ORG     100             
INPUT1,	        DEC 	0               //first digit of input
INPUT2,	        DEC	0               //second digit of input
OUTPUT1,        DEC     0               //first digit of OUTPUT
OUTPUT2,        DEC     0               //second digit of OUTPUT
NEG30,	        HEX	-30             //for converting into octal
DECIMAL,        DEC	    63               //input in decimal form
NEG10,          DEC     -10             //for checking if output digits have a max value of 9
MOD3,           DEC     0               //decimal % 3
MOD5,           DEC     0               //decimal % 5
THREE,          DEC     3               //for MOD3
FIVE,           DEC     5               //for MOD5
SIX,            DEC     6               //for converting hex into dec
SIXTEEN,        DEC     16              //for MOD16
DIVIDEND,   	DEC	0 		//the number that is being divided. Stores remainder after running.
DIVISOR,	DEC 	0		//the number you are dividing by
QUO,    	DEC 	0		//result of division
MIN1,   	DEC 	-1		//for decrementing
ZERO,           HEX     30              //0 in ascii
COUNT,          DEC     0               //for counting in SPLITDEC
1PLACE,         HEX     000F            //used for isolating the first digit
                END