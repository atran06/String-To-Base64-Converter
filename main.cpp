/*********************************************************************************************
 * String to Binary and Base64 Converter
 *
 * File: main.cpp
 * Desc: Converts a given string to either Binary or Base64.
 * Date: 10-23-18
 * Author: Arthur Tran
 * Website: https://arthurtran.com/
 *********************************************************************************************/

#include <string>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

const string base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012456789+/";
const int base64BinaryLength = 6; //base64 takes binary numbers in groups of 6
const int regularBinaryLength = 8; //normal binary representation of a number is in groups of 8

/*
 * Function: getLargestPossbleNumber()
 * Desc: Given the number of places, function returns the largest possible number
 *       that can be obtained. (Ex. 6, 111111 = 63)
 * Params:
 *   binaryPlaces - How many places the binary number is. Ex. 6 = 000000
 * Returns: Returns the largest possible number that can be had with the number of
 *          places.
 */
int getLargestPossbleNumber(int binaryPlaces) {
     int sum = 0;
     for(int i = pow(2, binaryPlaces - 1); i >= 1; i /= 2) {
          sum += i;
     }
     return sum;
}

/*
 * Function: numberToBinary()
 * Desc: Converts a given base 10 number to binary
 * Params:
 *   number - Base 10 number to convert
 *   binaryPlaces - How many places the binary number is. Ex. 6 = 000000
 * Returns: Returns the given number in binary.
 */
string numberToBinary(int number, int binaryPlaces) {
     int currentPlace = pow(2, binaryPlaces - 1);
     int currentNum = 0;
     string binary = "";

     if(number <= getLargestPossbleNumber(binaryPlaces)) {
          while(binaryPlaces > 0) {
               if(currentNum + currentPlace == number) {
                    currentNum += currentPlace;
                    binary += "1";
               } else if(currentNum + currentPlace < number) {
                    currentNum += currentPlace;
                    binary += "1";
               } else {
                    binary += "0";
               }
               currentPlace /= 2;
               binaryPlaces -= 1;
          }
     }
     return binary;
}

/*
 * Function: binaryToNumber()
 * Desc: Given a binary string, converts it a base 10 number.
 * Params:
 *   binary - The binary string to convert
 *   binaryPlaces - How many places the binary number is. Ex. 6 = 000000
 * Returns: Returns the given binary string in base 10
 */
int binaryToNumber(string binary, int binaryPlaces) {
     int originalPlaces = binaryPlaces;
     int currentPlace = pow(2, binaryPlaces - 1);
     int num = 0;

     while(binaryPlaces > 0) {
          if(binary.substr(abs(binaryPlaces - originalPlaces), 1) == "1") num += currentPlace;
          currentPlace /= 2;
          binaryPlaces--;
     }
     return num;
}

string stringToBinary(string str, int binaryPlaces) {
     string binary = "";
     for(int i = 0; i < str.size(); i++) {
          binary += numberToBinary(int(str[i]), binaryPlaces);
     }
     return binary;
}

string binaryToString(string binary, int binaryPlaces) {
     string str = "";
     for(int i = 0; i <= binary.size() - binaryPlaces; i += binaryPlaces) {
          str += char(binaryToNumber(binary.substr(i, binaryPlaces), binaryPlaces));
     }

     return str;
}

string stringToBase64(string str) {
     string stringInBinary = stringToBinary(str, regularBinaryLength);

     int padding = 0;
     if(stringInBinary.size() % base64BinaryLength != 0) {
          padding = (base64BinaryLength * ((stringInBinary.size() / base64BinaryLength) + 1)) - stringInBinary.size();
     }

     //makes the binary number's length a multiple of 6 for base64 to work
     for(int x = 0; x < padding; x++) {
          stringInBinary += "0";
     }

     string messageBase64 = "";
     for(int i = 0; i < stringInBinary.size(); i += base64BinaryLength) {
          messageBase64 += base64Table[binaryToNumber(stringInBinary.substr(i, base64BinaryLength), base64BinaryLength)];
     }

     for(int y = 0; y < padding / 2; y++) {
          messageBase64 += "=";
     }
     return messageBase64;
}

string base64ToBinary(string base64) {
     int paddingCount = 0;

     string base64InBinary = "";
     for(int i = 0; i < base64.size(); i++) {
          if(base64.substr(i, 1) == "=") paddingCount++;
          else {
               for(int x = 0; x < base64Table.size(); x++) {
                    if(base64Table.substr(x, 1) == base64.substr(i, 1)) {
                         base64InBinary += numberToBinary(x, base64BinaryLength);
                         continue;
                    }
               }
          }
     }

     return base64InBinary.substr(0, base64InBinary.size() - (paddingCount * 2));
}

string base64ToString(string base64) {
     return binaryToString(base64ToBinary(base64), regularBinaryLength);
}

string numberToBase64(int number) {
     int power = 0;
     while(pow(64, power) <= number) {
          power++;
     }
     cout << power << endl;
     return "";
}

int main() {
     string stringToChange = "Ian";
     cout << stringToChange << " in binary is " << stringToBinary(stringToChange, regularBinaryLength) << endl;
     cout << stringToChange << " in base64 is " << stringToBase64(stringToChange) << endl;

     numberToBase64(3);

     return 0;
}
