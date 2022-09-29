//***************************************************************************
//
//  Dev Patel
//  z1912837
//  CSCI 463 
//
//  Bitwise Operators & IEEE-754 Floating Point Number Decoding
//
//***************************************************************************

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <ostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
/****************************************************************************
* Function printBinFloat uses bitwise operators to extract and shift the *
* fields of the IEEE numbers as needed to render the output.        *
*                                    *
* @param x is an unsigned int that is read in as a 32-bit hexadecimal value *
*                                   *
* @return x which contains the input from user               *
****************************************************************************/
uint32_t printBinFloat(uint32_t x)
{
   

   uint32_t sig; // sig is a unsigned int that represents the significand.
   int32_t ex; // ex is a signed int that represents the exponent.

    ex = ((x & 0x7f800000) >> 23) -0x7F; //exponent is found from bits 30-23 minus 127 (0x7F)
    sig = ( x & 0x007fffff); //sig is 32bit unsigned hex value. bits 22-0

    cout << std::hex << "0x" << setw(8) << setfill('0') << x; //prints hex value first
    cout << " = "; // printing = between hex and binary 
    for(int i = 31; i > -1; i--) //loop backwards to get the right bits from hex number for binary number
    {
        cout << (i<31 && (i%4)==3 ? " " : "") << (x & 1 << i ? '1' : '0'); //print hex number in binary and a space after every 4 bits
    }
    cout << endl;

    //print second line: sign bit
    cout << "sign: " << (x &0x80000000 ? '1' : '0') << endl; //if LSB is 1 floating point positive. 0 negative. 0x80 is 31st bit

    //print third line: exponent as 32 bit signed int
    cout << " exp: 0x" << setw(8) << ex; //prints exponent
    //print the decimal value of exponent
    cout << " (" << std::dec << ex << ")" << std::hex << endl; //converts hex to dec and prints

    //print fourth line: significand as 32 bit unsigned hex value
    cout << " sig: 0x" << std::setw(8) << setfill('0') << sig << endl; //sig is bits 22-0

    //print the fifth line: the full value of the number in binary
    std::cout << (x &0x80000000 ? '-' : '+'); //prints '-' if sign is negative and '+' if sign is positive
    //special case: inf
    if (ex == 128 && sig == 00000000) //if exponent is all ones AND significand is all zeros
    {
        cout << "inf" << endl;
    }
    //special case: 0
    else if (ex == -127 && sig == 00000000) //0 when exponent is -127 and sig is all zeros
    {
        cout << "0" << endl;
    }
    //print binary float when exponent is positive
    else if (ex >= 0) //loop what exponent is positive which includes 0
    {

    
    cout << '1' ; //one always leads sig
    sig = sig << 9; // shift to the 9 bits left

    for (int i = 0; i < (ex + 23); i++) //loop until amount of digits to print is reached
    {
    if (i == ex) //once i = exponent
    {
        cout << '.'; //insert a '.'
    }


        cout << ((sig & 0x80000000) ? '1' : '0');//check if bit of sig is 1 and print accordingly
        sig = sig << 1; //shift to the left and let loop repeat till all numbers printed

    if(i >= ex && i > 23) //if value of i is greater 
    {
        break; //break to avoid printing insignificant zeros beyond decimal
    }

    }
        cout << endl;
    }
    //print binary float when exponent is negative
    else if (ex < 0)
    {
        cout << "0."; //start with zero

        sig = sig << 9; //shift so bits that make up sig are the first bits in sig

        //store the zeros that come before the significand
        int zeros = abs(ex) - 1 ; //absolute value of exponent - 1

        for(int i = 0; i < zeros; i++) //loop to print correct amount of leading zeros
        {
            cout << '0'; //print out leading zeros
        }
        cout << '1'; //print the leading 1
        for(int i = 0; i < 23; i++) //loop through size of the significand
        {

            if (sig & 0x80000000) //if ith bit of sig is set
                cout << '1';
            else
                cout << '0';

            sig = sig << 1; //iterate through significand
        }
        cout << endl;
    }
    return x;
}


int main()
{
    uint32_t x; // x is a 32-bit hexadecimal value to be read in.
    while(cin >> std::hex >> x) //read loop
    {
        printBinFloat(x); //call printbinfloat to do the decoding and printing

    }
}