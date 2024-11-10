#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to encode a binary stream to AMI (Alternate Mark Inversion)
vector<int> ami_encode(const vector<int>& input) {
    vector<int> encoded_signal;
    bool last_one_positive = true; // To track the alternating polarity for 1s

    for (int bit : input) {
        if (bit == 0) {
            // For 0, no transition, just add a 0
            encoded_signal.push_back(0);
        } else {
            // For 1, alternate the polarity
            encoded_signal.push_back(last_one_positive ? 1 : -1);
            last_one_positive = !last_one_positive; // Toggle polarity after each 1
        }
    }
    return encoded_signal;
}

// Function to encode a binary stream to Manchester Encoding
vector<int> manchester_encode(const vector<int>& input) {
    vector<int> encoded_signal;
    
    for (int bit : input) {
        if (bit == 0) {
            // A 0 bit: Transition from high to low in the middle of the bit period
            encoded_signal.push_back(1); // High (first half)
            encoded_signal.push_back(0); // Low (second half)
        } else {
            // A 1 bit: Transition from low to high in the middle of the bit period
            encoded_signal.push_back(0); // Low (first half)
            encoded_signal.push_back(1); // High (second half)
        }
    }
    return encoded_signal;
}

// Function to encode a binary stream to Differential Manchester Encoding
vector<int> differential_manchester_encode(const vector<int>& input) {
    vector<int> encoded_signal;
    bool previous_level = false; // Assume the previous level is low

    for (int bit : input) {
        if (bit == 0) {
            // A 0 bit: Transition at the beginning of the bit period
            encoded_signal.push_back(previous_level ? 1 : 0); // Transition
            encoded_signal.push_back(previous_level ? 0 : 1); // Next level
            previous_level = !previous_level;  // Toggle the level after the transition
        } else {
            // A 1 bit: No transition at the beginning of the bit period, transition in the middle
            encoded_signal.push_back(previous_level ? 0 : 1); // No transition at the beginning
            encoded_signal.push_back(previous_level ? 1 : 0); // Transition at the middle
            previous_level = !previous_level; // Toggle the level after the middle transition
        }
    }
    return encoded_signal;
}

// Function to display the encoded signal
void display_encoded_signal(const vector<int>& encoded_signal, const string& encoding_type) {
    cout << encoding_type << ": ";
    for (int bit : encoded_signal) {
        cout << bit << " ";
    }
    cout << endl;
}

// Function to take user input and convert it to a vector of integers
vector<int> get_user_input() {
    string input;
    vector<int> binary_input;
    
    cout << "Enter a binary sequence (only 0s and 1s): ";
    cin >> input;
    
    // Validate the input and convert to a vector of integers
    for (char c : input) {
        if (c == '0' || c == '1') {
            binary_input.push_back(c - '0');  // Convert char '0' or '1' to integer 0 or 1
        } else {
            cout << "Invalid input! Please enter a binary sequence with only 0s and 1s." << endl;
            return get_user_input(); // Recursive call to retry input
        }
    }
    return binary_input;
}

int main() {
    // Get binary input from the user
    vector<int> input = get_user_input();
    
    // Perform AMI encoding
    vector<int> ami_signal = ami_encode(input);
    display_encoded_signal(ami_signal, "AMI Encoding");

    // Perform Manchester encoding
    vector<int> manchester_signal = manchester_encode(input);
    display_encoded_signal(manchester_signal, "Manchester Encoding");

    // Perform Differential Manchester encoding
    vector<int> diff_manchester_signal = differential_manchester_encode(input);
    display_encoded_signal(diff_manchester_signal, "Differential Manchester Encoding");

    return 0;
}
