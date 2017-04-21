
void delay_ms(int count)  // /* X1ms */	 ÑÓÊ±1ms³ÌĞò
{
    uint i,j;
 	for(i=xms;i>0;i--)
 		for(j=124;j>0;j--);
}


unsigned int step = 0;

void setStep(int s)
{
	step = s;
}