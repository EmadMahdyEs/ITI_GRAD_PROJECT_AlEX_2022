#ifndef BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(reg,bit_no) 	(reg|=(1<<bit_no) )
#define CLEAR_BIT(reg,bit_no) 	(reg&=~(1<<bit_no) )
#define TOGGLE_BIT(reg,bit_no) 	(reg^=(1<<bit_no) )

/*this is the best way to make the function as macro to make the return true or 
false, it's not changing the value of the register and doesn't resturn the binary 
value of the register in contrast to (register&(1<<bit_no)) or (register&=(1<<bit_no))
*/
#define GET_BIT(reg,bit_no)	((reg>>bit_no)&0x00000001)

#define CAT_BITS(b7,b6,b5,b4,b3,b2,b1,b0) CAT_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CAT_HELP(b7,b6,b5,b4,b3,b2,b1,b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0

#endif
