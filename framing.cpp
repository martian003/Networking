#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -------------------- CHARACTER COUNT --------------------
string characterCount(const string &data) {
    int length = data.size();
    string header = to_string(length);
    return header + data;  // Concatenate length followed by the data
}

// -------------------- BIT STUFFING --------------------
string bitStuffing(const string &data) {
    string stuffedData = "";
    int consecutiveOnes = 0;
    
    for (char bit : data) {
        stuffedData += bit;
        
        if (bit == '1') {
            consecutiveOnes++;
        } else {
            consecutiveOnes = 0;
        }
        
        // If we have 5 consecutive 1's, insert a 0 to avoid flag sequence
        if (consecutiveOnes == 5) {
            stuffedData += '0';
            consecutiveOnes = 0; // Reset after stuffing
        }
    }
    return stuffedData;
}

// -------------------- BYTE STUFFING --------------------
string byteStuffing(const string &data) {
    string stuffedData = "";
    string escapeByte = "0x7D"; // Escape byte in hexadecimal (could be any byte you choose)
    string flagByte = "0x7E"; // Frame flag byte (the special character to be escaped)

    for (char byte : data) {
        // If the data contains the flag byte or escape byte, we need to stuff it
        if (byte == 0x7E || byte == 0x7D) {
            stuffedData += "0x7D";  // Escape byte
            stuffedData += (byte ^ 0x20); // XOR to transform the byte
        } else {
            stuffedData += string(1, byte); // No need to stuff
        }
    }
    return stuffedData;
}

int main() {
    string data;
    cout << "Enter the data: ";
    cin >> data;

    // Character count method
    string charCountData = characterCount(data);
    cout << "\nData after Character Count: " << charCountData << endl;

    // Bit stuffing method
    string bitStuffedData = bitStuffing(data);
    cout << "\nData after Bit Stuffing: " << bitStuffedData << endl;

    // Byte stuffing method
    string byteStuffedData = byteStuffing(data);
    cout << "\nData after Byte Stuffing: " << byteStuffedData << endl;

    return 0;
}
