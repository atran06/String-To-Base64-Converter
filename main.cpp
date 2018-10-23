#include <string>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

const string base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012456789+/";
const int base64BinaryLength = 6;
const int regularBinaryLength = 8;

int getLargestPossbleNumber(int binaryPlaces) {
     int sum = 0;
     for(int i = pow(2, binaryPlaces - 1); i >= 1; i /= 2) {
          sum += i;
     }
     return sum;
}


string numberToBinary(int number, int binaryPlaces) {
     int currentPlace = pow(2, binaryPlaces - 1);
     int currentNum = 0;
     string bin = "";

     if(number <= getLargestPossbleNumber(binaryPlaces)) {
          while(binaryPlaces > 0) {
               if(currentNum + currentPlace == number) {
                    currentNum += currentPlace;
                    bin += "1";
               } else if(currentNum + currentPlace < number) {
                    currentNum += currentPlace;
                    bin += "1";
               } else {
                    bin += "0";
               }
               currentPlace /= 2;
               binaryPlaces -= 1;
          }
     }
     return bin;
}

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

int main() {
     string stringToChange = "Arthur";
     cout << stringToChange << " in binary is " << stringToBinary(stringToChange, regularBinaryLength) << endl;
     cout << stringToChange << " in base64 is " << stringToBase64(stringToChange) << endl;

     return 0;
}
