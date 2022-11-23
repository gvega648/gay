void setupUART();
unsigned char UART_read();
void UART_write(unsigned char a);
#include <stdint.h>
void WriteNum(int number)
{    char outChar;
    uint32_t    d=5;
    uint32_t   q;
    uint32_t   c=10000;
    int count =0;
    if(number==0){
         UART_write('0');
         return;
    }
    while (d)
    {
        q = number/c;
        number = number - q*c;
        outChar = q +'0';
        if(outChar!='0'){
            count++;
        }
        if(count>=1){
         UART_write(outChar);
        }
    
        d--;
        c /=10;
    }

}
int main()
{
    setupUART();
    unsigned char myChar, Operator ='0';
    int FirstNum = 0, SecNum = 0;
    while(1)
    {
        myChar = UART_read();
        UART_write(myChar);
        if ((myChar=='0') || (myChar=='1') || (myChar=='2') || 
            (myChar=='3') || (myChar=='4') || (myChar=='5') || (myChar=='6') || 
            (myChar=='7') || (myChar=='8') || (myChar=='9'))
        {
            if ((Operator =='0'))
            {
                FirstNum = FirstNum*10+(myChar-'0');
            }
            else
            {
                SecNum = SecNum*10+(myChar-'0');
            }
        } else if ((myChar =='+') || (myChar =='-') || (myChar 
            =='*') || (myChar =='/'))
            {
            Operator = myChar;
            }
        else if ((myChar =='='))
        {
            switch (Operator)
            {
                case '+':
                WriteNum(FirstNum+SecNum);
                break;
                case '-':
                WriteNum(FirstNum-SecNum);
                break;
                case '*':
                WriteNum(FirstNum*SecNum);
                break;
                case '/':
                WriteNum(FirstNum/SecNum);
                break;
                default:
                break;
                }
            FirstNum =0;
            SecNum =0;
            Operator ='0';
            }
    }
return 1;
}