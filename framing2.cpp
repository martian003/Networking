#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Character Count Stuffing
void characterCountStuffing(string& data) {
    int count = data.length();  // Count the number of characters
    stringstream stuffedData;
    stuffedData << count;  // Add the character count at the start
    stuffedData << data;  // Append the actual data
    data = stuffedData.str();
    cout << "Character Count Stuffing: " << data << endl;
}

// Bit Stuffing
void bitStuffing(string& data) {
    string stuffedData = "";
    int consecutiveOnes = 0;

    // Iterate over the input data to check for bit stuffing pattern
    for (char c : data) {
        stuffedData += c;
        
        if (c == '1') {
            consecutiveOnes++;
            // After five consecutive '1's, insert a '0'
            if (consecutiveOnes == 5) {
                stuffedData += '0';
                consecutiveOnes = 0;
            }
        } else {
            consecutiveOnes = 0;
        }
    }
    
    data = stuffedData;
    cout << "Bit Stuffing: " << data << endl;
}

// Byte Stuffing
void byteStuffing(string& data) {
    string stuffedData = "";
    for (char c : data) {
        if (c == 0x7D || c == 0x7E) {  // Escape characters
            stuffedData += 0x7D;  // Insert escape character
            stuffedData += c ^ 0x20;  // XOR the byte with 0x20
        } else {
            stuffedData += c;  // Append the character without modification
        }
    }
    
    data = stuffedData;
    cout << "Byte Stuffing: " << data << endl;
}

int main() {
    string data;

    // Taking input from the user
    cout << "Enter the data for stuffing operations: ";
    getline(cin, data);  // Read input with spaces, if any

    // Character Count Stuffing
    characterCountStuffing(data);
    
    // Perform Bit Stuffing
    string bitStuffedData = data;  // Using the original data again for bit stuffing
    bitStuffing(bitStuffedData);

    // Perform Byte Stuffing
    string byteStuffedData = data;  // Using the original data for byte stuffing
    byteStuffing(byteStuffedData);

    return 0;
}
