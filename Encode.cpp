#include <iostream>
#include <cmath>

using std::pair;
using std::string;
using std::cin;
using std::cout;

class B64Encoder {

    char encode_table[64] = { 
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', '+', '/'};

    pair <int,int> bitmaskSet1 = {0b11111100, 0b00000011};
    pair <int,int> bitmaskSet2 = {0b11110000, 0b00001111};
    pair <int,int> bitmaskSet3 = {0b11000000, 0b00111111};

    float encoded_SIZE_FACTOR = 4/3;
    float decoded_SIZE_FACTOR = 3/4;

    public:
    string Encode(string toEncode){

        int remainder;

        string encoded;

        // cout << ceil(toEncode.length()*encoded_SIZE_FACTOR+1) << "\n";

        for(int charIndex = 1; charIndex <= ceil(toEncode.length()*encoded_SIZE_FACTOR+1); charIndex++){
            switch (charIndex%3) {
                case 1:
                    encoded += encode_table[( toEncode[charIndex-1] & bitmaskSet1.first ) >> 2];
                    remainder = ( toEncode[charIndex-1] & bitmaskSet1.second ) << 4;
                    break;
                case 2:
                    encoded += encode_table[(( toEncode[charIndex-1] & bitmaskSet2.first ) >> 4) + remainder];
                    remainder = ( toEncode[charIndex-1] & bitmaskSet2.second ) << 2;
                    break;
                case 0:
                    encoded += encode_table[(( toEncode[charIndex-1] & bitmaskSet3.first ) >> 6) + remainder];
                    remainder = ( toEncode[charIndex-1] & bitmaskSet3.second );
                    encoded += encode_table[remainder];
                    remainder = 0;
                    break;
            }
        }

        for (int i=0; i < toEncode.length(); i++) {
            int num = toEncode[i];
            cout << num << ", ";
        }

        cout << "\n";

        for (int i = 0; i < encoded.length()%4; i++){
            encoded += "=";
        }

        return encoded;
    }

    string Decode(string toDecode){

        string temp;
        int remainder;
        string decoded;

        int table_pos[toDecode.length()];

        for (int i = 0; i < toDecode.length(); i++){
            if (toDecode[i] == '='){
                toDecode[i] = '\0';
            }
            else {
                temp += toDecode[i];
            }
        }
        
        for (int i=0; i < temp.length(); i++) {
            for (int k=0; k < sizeof(encode_table); k++) {
                if (encode_table[k] == temp[i]) {
                    table_pos[i] = k;
                }
            }
        }

        for(int charIndex = 1; charIndex < floor(toDecode.length()/2+1); charIndex++){
            
            switch (charIndex%3)
            {
                case 1:
                    decoded += ((table_pos[charIndex-1] << 2) + (table_pos[charIndex] >> 6));
                    break;
                case 2:
                    decoded += ((table_pos[charIndex-1] << 4) + (table_pos[charIndex] >> 4));
                    break;
                case 0:
                    decoded += ((table_pos[charIndex-1] << 6) + (table_pos[charIndex] >> 2));
                    break;
            }
        }

        // for(int charIndex = 1; charIndex <= floor(toDecode.length()*decoded_SIZE_FACTOR+1); charIndex++){
        //     switch (charIndex%3) {
        //         case 1:
        //             decoded += encode_table[(( toDecode[charIndex-1] & bitmaskSet3.first ) >> 6) + remainder];
        //             remainder = ( toDecode[charIndex-1] & bitmaskSet3.second );
        //             break;
        //         case 2:
        //             decoded += encode_table[remainder];
        //             remainder = 0;
        //             break;
        //         case 0:
        //             decoded += encode_table[(( toEncode[charIndex-1] & bitmaskSet2.first ) >> 4) + remainder];
        //             remainder = ( toEncode[charIndex-1] & bitmaskSet2.second ) << 2;
        //             decoded += encode_table[( toEncode[charIndex-1] & bitmaskSet1.first ) >> 2];
        //             remainder = ( toEncode[charIndex-1] & bitmaskSet1.second ) << 4;
        //             break;
        //     }
        // }
        return decoded;
    }
};



int main(){

    string usersTextInput;
    B64Encoder Encoder;

    string encoded;

    cout << "please enter a value to encode:\n";
    cin >> usersTextInput;

    encoded = Encoder.Encode(usersTextInput);

    cout << "Encoded: " << encoded;

    cout << "\nNum Chars Encoded: " << encoded.length();

    cout << "\nDecoded: " << Encoder.Decode(encoded) << "\n";

    
}