                ORG 10
                BSA     SPLITDEC        //splits DECIMAL into OUTPUT1 and OUTPUT2
                CLA
                LDA     OUTPUT1
                ADD     ZERO
                OUT
                LDA     OUTPUT2
                ADD     ZERO
                OUT
                HLT

                //SPLITDEC subroutine
                //split hex variable into two decmial variables. ex: if demcimal = 3F then OUTPUT1 = 6, OUTPUT2 = 3.
SPLITDEC,       CLA 
                LDA     DECIMAL         //input1 - input1 % 16. removes lowest digit. in hex.
                CIR
                CIR
                CIR
                CIR                     //shift over 4 digits to the left
                AND     1PLACE          //changes 00x0 to 000x. moves 16s place into 1s place  
                CMA                     
                INC                     //complement of 16s place
                INC
                STA     COUNT           //counts how many times to add 16 to output2
                LDA     DECIMAL
                AND     1PLACE
                STA     OUTPUT2         //converts digit into decimal. ex: if, dividend = F. then, OUTPUT1 = 1, OUTPUT2 = 5.
                ADD     NEG10           
                SPA                     //checks if first digit is greater than A
                BUN     LESSTHANA
                STA     OUTPUT2
                LDA     OUTPUT1
                INC          
                STA     OUTPUT1
                LDA     COUNT
                ADD     MIN1
                SNA
                BSA     SPLITDEC I
LESSTHANA,      CLA                      //OUTPUT2 is less than A, so it fits in one variable.
                LDA     OUTPUT1
                INC     
                STA     OUTPUT1
                LDA     OUTPUT2
                ADD     SIX
                STA     OUTPUT2
                ADD     NEG10           //number is positive if digit is greater than A
                SPA     
                BUN     LESSTHANA
                STA     OUTPUT2
                LDA     OUTPUT1
                INC 
                STA     OUTPUT1
                LDA     COUNT           //counts from negative number to 0. break when 0
                INC
                SPA
                BUN     LESSTHANA 
                BSA     SPLITDEC I

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
DIVIDEND,   	DEC	    15 		//the number that is being divided. Stores remainder after running.
DIVISOR,	    DEC 	0		//the number you are dividing by
QUO,    	    DEC 	0		//result of division
MIN1,   	    DEC 	-1		//for decrementing
ZERO,           HEX     30              //0 in ascii
COUNT,          DEC     0               //for counting in SPLITDEC
1PLACE,         HEX     000F            //used for isolating the first digit
                END