// ii. Route Cipher.

#include <bits/stdc++.h>

using namespace std;

enum class Route
{
    SPIRAL_CLOCKWISE,
    SPIRAL_COUNTERCLOCKWISE,
    DIAGONAL
};

class RouteCipher
{
private:
    int rows, cols;
    vector<vector<char>> grid;

    void fillGrid(const string &message)
    {
        int index = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (index < message.length())
                {
                    grid[i][j] = message[index++];
                }
                else
                {
                    grid[i][j] = 'X';
                }
            }
        }
    }

    void printGrid(const string &title)
    {
        cout << "\n" << title << ":\n";
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << setw(2) << grid[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    string readRoute(Route route)
    {
        string result;
        switch (route)
        {
        case Route::SPIRAL_CLOCKWISE:
            result = readSpiralClockwise();
            break;
        case Route::SPIRAL_COUNTERCLOCKWISE:
            result = readSpiralCounterclockwise();
            break;
        case Route::DIAGONAL:
            result = readDiagonal();
            break;
        }
        return result;
    }

    void writeRoute(const string &ciphertext, Route route)
    {
        switch (route)
        {
        case Route::SPIRAL_CLOCKWISE:
            writeSpiralClockwise(ciphertext);
            break;
        case Route::SPIRAL_COUNTERCLOCKWISE:
            writeSpiralCounterclockwise(ciphertext);
            break;
        case Route::DIAGONAL:
            writeDiagonal(ciphertext);
            break;
        }
    }

    string readSpiralClockwise()
    {
        string result;
        int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
        while (top <= bottom && left <= right)
        {
            for (int i = left; i <= right; i++)
                result += grid[top][i];
            top++;
            for (int i = top; i <= bottom; i++)
                result += grid[i][right];
            right--;
            if (top <= bottom)
            {
                for (int i = right; i >= left; i--)
                    result += grid[bottom][i];
                bottom--;
            }
            if (left <= right)
            {
                for (int i = bottom; i >= top; i--)
                    result += grid[i][left];
                left++;
            }
        }
        return result;
    }

    void writeSpiralClockwise(const string &ciphertext)
    {
        int index = 0;
        int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
        while (top <= bottom && left <= right && index < ciphertext.length())
        {
            for (int i = left; i <= right && index < ciphertext.length(); i++)
                grid[top][i] = ciphertext[index++];
            top++;
            for (int i = top; i <= bottom && index < ciphertext.length(); i++)
                grid[i][right] = ciphertext[index++];
            right--;
            if (top <= bottom)
            {
                for (int i = right; i >= left && index < ciphertext.length(); i--)
                    grid[bottom][i] = ciphertext[index++];
                bottom--;
            }
            if (left <= right)
            {
                for (int i = bottom; i >= top && index < ciphertext.length(); i--)
                    grid[i][left] = ciphertext[index++];
                left++;
            }
        }
    }

    string readSpiralCounterclockwise()
    {
        string result;
        int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
        while (top <= bottom && left <= right)
        {
            for (int i = top; i <= bottom; i++)
                result += grid[i][left];
            left++;
            for (int i = left; i <= right; i++)
                result += grid[bottom][i];
            bottom--;
            if (left <= right)
            {
                for (int i = bottom; i >= top; i--)
                    result += grid[i][right];
                right--;
            }
            if (top <= bottom)
            {
                for (int i = right; i >= left; i--)
                    result += grid[top][i];
                top++;
            }
        }
        return result;
    }

    void writeSpiralCounterclockwise(const string &ciphertext)
    {
        int index = 0;
        int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
        while (top <= bottom && left <= right && index < ciphertext.length())
        {
            for (int i = top; i <= bottom && index < ciphertext.length(); i++)
                grid[i][left] = ciphertext[index++];
            left++;
            for (int i = left; i <= right && index < ciphertext.length(); i++)
                grid[bottom][i] = ciphertext[index++];
            bottom--;
            if (left <= right)
            {
                for (int i = bottom; i >= top && index < ciphertext.length(); i--)
                    grid[i][right] = ciphertext[index++];
                right--;
            }
            if (top <= bottom)
            {
                for (int i = right; i >= left && index < ciphertext.length(); i--)
                    grid[top][i] = ciphertext[index++];
                top++;
            }
        }
    }

    string readDiagonal()
    {
        string result;
        for (int sum = 0; sum < rows + cols - 1; sum++)
        {
            for (int i = 0; i < rows; i++)
            {
                int j = sum - i;
                if (j >= 0 && j < cols)
                {
                    result += grid[i][j];
                }
            }
        }
        return result;
    }

    void writeDiagonal(const string &ciphertext)
    {
        int index = 0;
        for (int sum = 0; sum < rows + cols - 1 && index < ciphertext.length(); sum++)
        {
            for (int i = 0; i < rows && index < ciphertext.length(); i++)
            {
                int j = sum - i;
                if (j >= 0 && j < cols)
                {
                    grid[i][j] = ciphertext[index++];
                }
            }
        }
    }

public:
    RouteCipher(int r, int c) : rows(r), cols(c), grid(r, vector<char>(c)) {}

    string encrypt(const string &message, Route route)
    {
        fillGrid(message);
        printGrid("Initial Grid");
        string result = readRoute(route);
        cout << "Encryption Route: " << getRouteName(route) << "\n";
        return result;
    }

    string decrypt(const string &ciphertext, Route route)
    {
        writeRoute(ciphertext, route);
        printGrid("Decryption Grid");
        string result;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (grid[i][j] != 'X')
                {
                    result += grid[i][j];
                }
            }
        }
        cout << "Decryption Route: " << getRouteName(route) << "\n";
        return result;
    }

    string getRouteName(Route route)
    {
        switch (route)
        {
        case Route::SPIRAL_CLOCKWISE:
            return "Spiral Clockwise";
        case Route::SPIRAL_COUNTERCLOCKWISE:
            return "Spiral Counterclockwise";
        case Route::DIAGONAL:
            return "Diagonal";
        default:
            return "Unknown";
        }
    }
};

Route getRouteChoice()
{
    int choice;
    cout << "\nChoose a route:\n";
    cout << "1. Spiral Clockwise\n";
    cout << "2. Spiral Counterclockwise\n";
    cout << "3. Diagonal\n";
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    cin.ignore(); 

    switch (choice)
    {
    case 1:
        return Route::SPIRAL_CLOCKWISE;
    case 2:
        return Route::SPIRAL_COUNTERCLOCKWISE;
    case 3:
        return Route::DIAGONAL;
    default:
        return Route::SPIRAL_CLOCKWISE; 
    }
}

int main()
{
    int rows, cols;
    string message;

    cout << "=== Route Cipher Encryption/Decryption ===\n\n";
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;
    cin.ignore(); 

    cout << "Enter the message: ";
    getline(cin, message);

    Route route = getRouteChoice();

    RouteCipher cipher(rows, cols);

    cout << "\n--- Encryption Process ---\n";
    string encrypted = cipher.encrypt(message, route);
    cout << "Encrypted message: " << encrypted << "\n";

    cout << "\n--- Decryption Process ---\n";
    string decrypted = cipher.decrypt(encrypted, route);
    cout << "Decrypted message: " << decrypted << "\n";

    cout << "\n=== Process Complete ===\n";

    return 0;
}