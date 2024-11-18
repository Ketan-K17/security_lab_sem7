// Q1. Write the encryption and decryption program for the following
// i. Column Transposition Cipher.

#include <bits/stdc++.h>
using namespace std;

string Encryption(int no_rows, int len_key, int len_msg,
                  string msg, int col_val[])
{
    cout << "Encryption function called with:\n";
    cout << "no_rows: " << no_rows << ", len_key: " << len_key << ", len_msg: " << len_msg << "\n";
    cout << "msg: " << msg << "\n";
    cout << "col_val: ";
    for (int i = 0; i < len_key; i++)
    {
        cout << col_val[i] << " ";
    }
    cout << "\n";

    int x = 0;
    char enc_mat[no_rows + 1][len_key];
    char fill_chars[] = {'X', 'Y', 'Z', 'W', 'P', 'Q'};
    int fill_index = 0;
    for (int i = 0; i < no_rows + 1; i++)
    {
        for (int j = 0; j < len_key; j++)
        {
            if (x >= len_msg)
            {
                enc_mat[i][j] = fill_chars[fill_index % 6];
                fill_index++;
            }
            else
            {
                enc_mat[i][j] = msg[x];
            }
            x++;
        }
    }

    cout << "Encryption matrix:\n";
    for (int i = 0; i < no_rows + 1; i++)
    {
        for (int j = 0; j < len_key; j++)
        {
            cout << enc_mat[i][j] << " ";
        }
        cout << "\n";
    }

    int t = 1;
    string cipher = "";
    while (t <= len_key)
    {
        for (int i = 0; i < len_key; i++)
        {
            int k = col_val[i];
            if (k == t)
            {
                for (int j = 0; j < no_rows + 1; j++)
                {
                    cipher += enc_mat[j][i];
                }
                t++;
            }
        }
    }

    cout << "Encrypted cipher: " << cipher << "\n";
    return cipher;
}

string Decryption(int no_rows, int len_key, string cipher,
                  int col_val[])
{
    cout << "Decryption function called with:\n";
    cout << "no_rows: " << no_rows << ", len_key: " << len_key << "\n";
    cout << "cipher: " << cipher << "\n";
    cout << "col_val: ";
    for (int i = 0; i < len_key; i++)
    {
        cout << col_val[i] << " ";
    }
    cout << "\n";

    char dec_mat[no_rows + 1][len_key];
    int x = 0, t = 1;
    while (t <= len_key)
    {
        for (int i = 0; i < len_key; i++)
        {
            int k = col_val[i];
            if (k == t)
            {
                for (int j = 0; j < no_rows + 1; j++)
                {
                    dec_mat[j][i] = cipher[x];
                    x++;
                }
                t++;
            }
        }
    }

    cout << "Decryption matrix:\n";
    for (int i = 0; i < no_rows + 1; i++)
    {
        for (int j = 0; j < len_key; j++)
        {
            cout << dec_mat[i][j] << " ";
        }
        cout << "\n";
    }

    string message = "";
    for (int i = 0; i < no_rows + 1; i++)
    {
        for (int j = 0; j < len_key; j++)
        {
            message += dec_mat[i][j];
        }
    }

    cout << "Decrypted message: " << message << "\n";
    return message;
}

int main()
{
    string msg, key;
    cout << "Enter the message in all caps: ";
    getline(cin, msg);
    cout << "Enter the key in all caps: ";
    getline(cin, key);

    msg.erase(remove(msg.begin(), msg.end(), ' '), msg.end());
    key.erase(remove(key.begin(), key.end(), ' '), key.end());

    cout << "Original message: " << msg << "\n";
    cout << "Key: " << key << "\n";

    int len_key = key.length();
    int len_msg = msg.length();

    int val = 1, count = 0, ind;

    int col_val[len_key];
    memset(col_val, 0, sizeof(col_val));
    while (count < len_key)
    {
        int min = 999;
        for (int i = 0; i < len_key; i++)
        {
            if ((min > int(key[i])) && (col_val[i] == 0))
            {
                min = int(key[i]);
                ind = i;
            }
        }
        col_val[ind] = val;
        count++;
        val++;
    }

    cout << "col_val array: ";
    for (int i = 0; i < len_key; i++)
    {
        cout << col_val[i] << " ";
    }
    cout << "\n";

    int no_rows = len_msg / len_key;
    string cipher_text = " ";
    cipher_text = Encryption(no_rows, len_key, len_msg, msg,
                             col_val);
    string original_msg = " ";
    original_msg = Decryption(no_rows, len_key, cipher_text,
                              col_val);
}