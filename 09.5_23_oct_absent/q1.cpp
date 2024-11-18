// IMPLEMENT THE ENCRYPTION AND DECRYPTION PROCEDURE FOR THE DES ALGORITHM

#include <bits/stdc++.h>
using namespace std;

// DES Tables
const int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
                  60, 52, 44, 36, 28, 20, 12, 4,
                  62, 54, 46, 38, 30, 22, 14, 6,
                  64, 56, 48, 40, 32, 24, 16, 8,
                  57, 49, 41, 33, 25, 17, 9, 1,
                  59, 51, 43, 35, 27, 19, 11, 3,
                  61, 53, 45, 37, 29, 21, 13, 5,
                  63, 55, 47, 39, 31, 23, 15, 7};

const int IP_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41, 9, 49, 17, 57, 25};

const int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
                    1, 58, 50, 42, 34, 26, 18,
                    10, 2, 59, 51, 43, 35, 27,
                    19, 11, 3, 60, 52, 44, 36,
                    63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                    14, 6, 61, 53, 45, 37, 29,
                    21, 13, 5, 28, 20, 12, 4};

const int PC_2[] = {14, 17, 11, 24, 1, 5,
                    3, 28, 15, 6, 21, 10,
                    23, 19, 12, 4, 26, 8,
                    16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32};

const int E[] = {32, 1, 2, 3, 4, 5,
                4, 5, 6, 7, 8, 9,
                8, 9, 10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32, 1};

const int S_BOX[8][4][16] = {
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
};

const int P[] = {16, 7, 20, 21, 29, 12, 28, 17,
                 1, 15, 23, 26, 5, 18, 31, 10,
                 2, 8, 24, 14, 32, 27, 3, 9,
                 19, 13, 30, 6, 22, 11, 4, 25};

// Function to perform initial permutation
bitset<64> initial_permutation(const bitset<64>& plain_text) {
    bitset<64> permuted;
    for(int i = 0; i < 64; i++)
        permuted[63-i] = plain_text[64-IP[i]];
    cout << "After initial permutation: " << permuted.to_string() << endl;
    return permuted;
}

// Function to generate 16 subkeys
vector<bitset<48>> generate_subkeys(const bitset<64>& key) {
    cout << "\nGenerating subkeys..." << endl;
    vector<bitset<48>> subkeys;
    bitset<56> permuted_choice_1;
    
    // PC-1
    for(int i = 0; i < 56; i++)
        permuted_choice_1[55-i] = key[64-PC_1[i]];
    
    bitset<28> C = bitset<28>((permuted_choice_1 >> 28).to_ulong());
    bitset<28> D = bitset<28>((permuted_choice_1 & bitset<56>((1LL << 28) - 1)).to_ulong());
    
    cout << "Initial C0: " << C.to_string() << endl;
    cout << "Initial D0: " << D.to_string() << endl;

    // Generate 16 subkeys
    for(int round = 0; round < 16; round++) {
        // Left circular shift
        int shift = (round < 2 || round == 8 || round == 15) ? 1 : 2;
        C = (C << shift) | (C >> (28-shift));
        D = (D << shift) | (D >> (28-shift));
        
        // Combine C and D
        bitset<56> combined;
        for(int i = 0; i < 28; i++) {
            combined[i] = D[i];
            combined[i+28] = C[i];
        }
        
        // PC-2
        bitset<48> subkey;
        for(int i = 0; i < 48; i++)
            subkey[47-i] = combined[56-PC_2[i]];
        
        subkeys.push_back(subkey);
        cout << "Subkey " << round+1 << ": " << subkey.to_string() << endl;
    }
    return subkeys;
}

// Function to expand 32 bits to 48 bits
bitset<48> expansion(const bitset<32>& input) {
    bitset<48> output;
    for(int i = 0; i < 48; i++)
        output[47-i] = input[32-E[i]];
    return output;
}

bitset<32> s_box_substitution(const bitset<48>& input) {
    bitset<32> output;
    int pos = 0;
    
    for(int i = 0; i < 8; i++) {
        int row = input[47-6*i]*2 + input[47-6*i-5];
        int col = (input[47-6*i-1]*8) + (input[47-6*i-2]*4) + 
                 (input[47-6*i-3]*2) + input[47-6*i-4];
        
        int val = S_BOX[i][row][col];
        bitset<4> bits(val);
        
        for(int j = 0; j < 4; j++)
            output[31-pos-j] = bits[3-j];
        pos += 4;
    }
    return output;
}

// Function to perform permutation
bitset<32> permutation(const bitset<32>& input) {
    bitset<32> output;
    for(int i = 0; i < 32; i++)
        output[31-i] = input[32-P[i]];
    return output;
}

// Feistel function
bitset<32> f_function(const bitset<32>& R, const bitset<48>& subkey) {
    cout << "\nFeistel function:" << endl;
    cout << "Input R: " << R.to_string() << endl;
    
    bitset<48> expanded = expansion(R);
    cout << "After expansion: " << expanded.to_string() << endl;
    
    bitset<48> xored = expanded ^ subkey;
    cout << "After XOR with subkey: " << xored.to_string() << endl;
    
    bitset<32> substituted = s_box_substitution(xored);
    cout << "After S-box substitution: " << substituted.to_string() << endl;
    
    bitset<32> permuted = permutation(substituted);
    cout << "After permutation: " << permuted.to_string() << endl;
    
    return permuted;
}

bitset<64> des_process(bitset<64>& input_text, const bitset<64>& key, bool encrypt = true) {
    cout << "\nStarting DES " << (encrypt ? "encryption" : "decryption") << "..." << endl;
    cout << (encrypt ? "Plain" : "Cipher") << " text: " << input_text.to_string() << endl;
    cout << "Key: " << key.to_string() << endl;
    
    // Generate subkeys
    vector<bitset<48>> subkeys = generate_subkeys(key);
    
    // For decryption, reverse the subkey order
    if (!encrypt) {
        cout << "\nReversing subkey order for decryption..." << endl;
        reverse(subkeys.begin(), subkeys.end());
    }
    
    // Initial permutation
    bitset<64> current_bits = initial_permutation(input_text);
    
    // Split into left and right halves
    bitset<32> left = bitset<32>((current_bits >> 32).to_ulong());
    bitset<32> right = bitset<32>((current_bits & bitset<64>((1LL << 32) - 1)).to_ulong());
    
    // 16 rounds
    for(int round = 0; round < 16; round++) {
        cout << "\nRound " << round+1 << ":" << endl;
        cout << "L: " << left.to_string() << endl;
        cout << "R: " << right.to_string() << endl;
        
        bitset<32> temp = right;
        right = left ^ f_function(right, subkeys[round]);
        left = temp;
    }
    
    // Combine right and left (reversed)
    bitset<64> pre_output(((unsigned long long)right.to_ulong() << 32) | left.to_ulong());
    
    // Final permutation
    bitset<64> output;
    for(int i = 0; i < 64; i++)
        output[63-i] = pre_output[64-IP_1[i]];
    
    cout << "\nFinal " << (encrypt ? "cipher" : "plain") << " text: " << output.to_string() << endl;
    return output;
}

bitset<64> des_encrypt(bitset<64>& plain_text, const bitset<64>& key) {
    return des_process(plain_text, key, true);
}

bitset<64> des_decrypt(bitset<64>& cipher_text, const bitset<64>& key) {
    return des_process(cipher_text, key, false);
}

int main() {
    string input_text, input_key;
    unsigned long long hex_text, hex_key;

    cout << "Enter plain text in hexadecimal: ";
    cin >> input_text;
    
    cout << "Enter key in hexadecimal: ";
    cin >> input_key;
    
    // Convert hex string to integer
    hex_text = stoull(input_text, nullptr, 16);
    hex_key = stoull(input_key, nullptr, 16);
    
    // Create bitsets from the hex values
    bitset<64> plain_text(hex_text);
    bitset<64> key(hex_key);
    
    cout << "\n=== ENCRYPTION ===" << endl;
    bitset<64> cipher_text = des_encrypt(plain_text, key);
    
    cout << "\n=== DECRYPTION ===" << endl;
    bitset<64> decrypted_text = des_decrypt(cipher_text, key);
    
    cout << "\nResults in hexadecimal:" << endl;
    cout << "Original plain text: " << uppercase << input_text << endl;
    cout << "Key: " << uppercase << input_key << endl;
    
    cout << "Cipher text: ";
    for(int i = 60; i >= 0; i -= 4) {
        bitset<4> bits;
        for(int j = 0; j < 4; j++)
            bits[j] = cipher_text[i+j];
        cout << hex << uppercase << bits.to_ulong();
    }
    cout << endl;
    
    cout << "Decrypted text: ";
    for(int i = 60; i >= 0; i -= 4) {
        bitset<4> bits;
        for(int j = 0; j < 4; j++)
            bits[j] = decrypted_text[i+j];
        cout << hex << uppercase << bits.to_ulong();
    }
    cout << endl;
    
    return 0;
}