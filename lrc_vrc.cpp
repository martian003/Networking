#include <iostream>
#include <vector>

using namespace std;

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Function to calculate Longitudinal Redundancy Check (LRC)
void longitudinalRedundancyCheck(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Calculate the LRC for each column and store the result in the last row
    for (int col = 0; col < cols; ++col) {
        int parity = 0;
        for (int row = 0; row < rows - 1; ++row) {  // Exclude the last row where parity will be stored
            parity ^= matrix[row][col];  // XOR for parity
        }
        matrix[rows - 1][col] = parity;  // Store the parity in the last row
    }
}

// Function to calculate Vertical Redundancy Check (VRC)
void verticalRedundancyCheck(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Calculate the VRC for each row and store the result in the last column
    for (int row = 0; row < rows; ++row) {
        int parity = 0;
        for (int col = 0; col < cols - 1; ++col) {  // Exclude the last column where parity will be stored
            parity ^= matrix[row][col];  // XOR for parity
        }
        matrix[row][cols - 1] = parity;  // Store the parity in the last column
    }
}

// Function to check the Longitudinal Redundancy Check (LRC) for errors
bool checkLRC(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Check if the last row matches the calculated parity for each column
    for (int col = 0; col < cols - 1; ++col) {  // Exclude the last column, which contains VRC
        int parity = 0;
        for (int row = 0; row < rows - 1; ++row) {  // Exclude the last row, which contains LRC
            parity ^= matrix[row][col];  // XOR for parity
        }
        if (parity != matrix[rows - 1][col]) {  // Error detected
            return false;
        }
    }
    return true;
}

// Function to check the Vertical Redundancy Check (VRC) for errors
bool checkVRC(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Check if the last column matches the calculated parity for each row
    for (int row = 0; row < rows; ++row) {
        int parity = 0;
        for (int col = 0; col < cols - 1; ++col) {  // Exclude the last column
            parity ^= matrix[row][col];  // XOR for parity
        }
        if (parity != matrix[row][cols - 1]) {  // Error detected
            return false;
        }
    }
    return true;
}

int main() {
    int rows, cols;

    // Get the size of the matrix from the user
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    // Initialize the matrix based on user input
    vector<vector<int>> matrix(rows, vector<int>(cols));

    cout << "Enter the elements of the matrix (0 or 1):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }

    // Add the extra row for LRC (Longitudinal Redundancy Check)
    matrix.push_back(vector<int>(cols, 0));  // New row for parity bits

    // Apply Longitudinal Redundancy Check
    longitudinalRedundancyCheck(matrix);

    cout << "\nMatrix with LRC (Longitudinal Redundancy Check):" << endl;
    printMatrix(matrix);

    // Add the extra column for VRC (Vertical Redundancy Check)
    for (auto& row : matrix) {
        row.push_back(0);  // New column for parity bits
    }

    // Apply Vertical Redundancy Check
    verticalRedundancyCheck(matrix);

    cout << "\nMatrix with VRC (Vertical Redundancy Check):" << endl;
    printMatrix(matrix);

    // Check if the matrix is correct (without errors)
    if (checkLRC(matrix)) {
        cout << "\nLRC Check passed!" << endl;
    } else {
        cout << "\nLRC Check failed!" << endl;
    }

    if (checkVRC(matrix)) {
        cout << "VRC Check passed!" << endl;
    } else {
        cout << "VRC Check failed!" << endl;
    }

    return 0;
}
