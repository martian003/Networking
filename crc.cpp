#include <iostream>
#include <vector>
#include <string>
#include <bitset>
using namespace std;

// Function to perform XOR operation in CRC calculation
void xorOperation(vector<int>& dividend, const vector<int>& divisor) {
    for (int i = 0; i < divisor.size(); i++) {
        dividend[i] = dividend[i] ^ divisor[i];
    }
}

// Function to perform CRC encoding
vector<int> computeCRC(vector<int>& data, const vector<int>& divisor) {
    int m = divisor.size();
    int n = data.size();
    
    // Append zeros to the data (size of divisor - 1)
    vector<int> augmentedData = data;
    augmentedData.resize(n + m - 1, 0);

    // Perform division of augmented data by divisor
    for (int i = 0; i < n; i++) {
        if (augmentedData[i] == 1) {
            xorOperation(augmentedData, divisor);
        }
    }

    // The CRC will be the remainder of the division
    vector<int> crc(augmentedData.begin() + n, augmentedData.end());
    return crc;
}

// Function to check the CRC and verify data integrity
bool checkCRC(vector<int>& data, const vector<int>& divisor, vector<int>& crc) {
    // Combine data and CRC to form the complete bitstream
    vector<int> combinedData = data;
    combinedData.insert(combinedData.end(), crc.begin(), crc.end());

    // Perform division to check if remainder is zero
    int m = divisor.size();
    int n = combinedData.size();
    
    for (int i = 0; i < n - m + 1; i++) {
        if (combinedData[i] == 1) {
            xorOperation(combinedData, divisor);
        }
    }

    // If the remainder is zero, data is correct
    for (int i = n - m + 1; i < n; i++) {
        if (combinedData[i] != 0) {
            return false;
        }
    }
    return true;
}

// Helper function to convert binary string to a vector of integers
vector<int> stringToBinaryVector(const string& str) {
    vector<int> binary;
    for (char c : str) {
        if (c == '1') {
            binary.push_back(1);
        } else if (c == '0') {
            binary.push_back(0);
        }
    }
    return binary;
}

// Helper function to print a vector of binary digits
void printBinaryVector(const vector<int>& binary) {
    for (int bit : binary) {
        cout << bit;
    }
    cout << endl;
}

int main() {
    string inputData, inputDivisor;

    // Get data input (binary string)
    cout << "Enter the data (binary string): ";
    cin >> inputData;

    // Get divisor input (binary string)
    cout << "Enter the divisor (binary string): ";
    cin >> inputDivisor;

    // Convert input data and divisor to binary vectors
    vector<int> data = stringToBinaryVector(inputData);
    vector<int> divisor = stringToBinaryVector(inputDivisor);

    // Compute the CRC for the given data
    vector<int> crc = computeCRC(data, divisor);
    
    // Output the data and CRC
    cout << "CRC (remainder): ";
    printBinaryVector(crc);

    // Append the CRC to the original data (encoded data)
    vector<int> encodedData = data;
    encodedData.insert(encodedData.end(), crc.begin(), crc.end());

    cout << "Data after appending CRC: ";
    printBinaryVector(encodedData);

    // Now, check if the received data with CRC is valid
    bool isValid = checkCRC(data, divisor, crc);
    if (isValid) {
        cout << "Data is valid (no errors detected)." << endl;
    } else {
        cout << "Data is invalid (errors detected)." << endl;
    }

    return 0;
}
