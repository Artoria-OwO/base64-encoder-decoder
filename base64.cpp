#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

static char BASE[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                        'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

string fasterEncode(string str)
{
    string result = "";
    int remain = 0;
    int remainer = 0;
    for (char &_char : str)
    {
        if (remain == 0)
        {
            result += BASE[_char >> 2];
            remain = 2;
            remainer = _char & 0b11;
        }
        else if (remain == 2)
        {
            result += BASE[(remainer << 4) | (_char >> 4)];
            remain = 4;
            remainer = _char & 0b1111;
        }
        else if (remain == 4)
        {
            result += BASE[(remainer << 2) | (_char >> 6)];
            result += BASE[_char & 0b111111];
            remain = 0;
            remainer = 0;
        }
        else
        {
            cout << "encode error" << endl;
        }
    }
    if (remain == 2)
    {
        result += BASE[remainer << 4];
        result += "==";
    }
    if (remain == 4)
    {
        result += BASE[remainer << 2];
        result += "=";
    }
    return result;
}

string fasterDecode(string str)
{
    string result = "";
    int need = 0;
    int pre = 0;
    if (str.length() == 0)
    {
        return result;
    }
    for (char &_char : str)
    {
        if (_char >= 'A' && _char <= 'Z')
        {
            if (need == 0)
            {
                pre = (_char - 'A');
                need = 2;
            }
            else if (need == 2)
            {
                result += pre << 2 | (_char - 'A') >> 4;
                pre = (_char - 'A') & 0b1111;
                need = 4;
            }
            else if (need == 4)
            {
                result += pre << 4 | (_char - 'A') >> 2;
                pre = (_char - 'A') & 0b11;
                need = 6;
            }
            else if (need == 6)
            {
                result += pre << 6 | (_char - 'A');
                pre = 0;
                need = 0;
            }
            else
            {
                cout << "decode error!" << endl;
            }
        }
        else if (_char >= 'a' && _char <= 'z')
        {
            if (need == 0)
            {
                pre = (_char - 'a' + 26);
                need = 2;
            }
            else if (need == 2)
            {
                result += pre << 2 | (_char - 'a' + 26) >> 4;
                pre = (_char - 'a' + 26) & 0b1111;
                need = 4;
            }
            else if (need == 4)
            {
                result += pre << 4 | (_char - 'a' + 26) >> 2;
                pre = (_char - 'a' + 26) & 0b11;
                need = 6;
            }
            else if (need == 6)
            {
                result += pre << 6 | (_char - 'a' + 26);
                pre = 0;
                need = 0;
            }
            else
            {
                cout << "decode error!" << endl;
            }
        }
        else if (_char >= '0' && _char <= '9')
        {
            if (need == 0)
            {
                pre = (_char - '0' + 52);
                need = 2;
            }
            else if (need == 2)
            {
                result += pre << 2 | (_char - '0' + 52) >> 4;
                pre = (_char - '0' + 52) & 0b1111;
                need = 4;
            }
            else if (need == 4)
            {
                result += pre << 4 | (_char - '0' + 52) >> 2;
                pre = (_char - '0' + 52) & 0b11;
                need = 6;
            }
            else if (need == 6)
            {
                result += pre << 6 | (_char - '0' + 52);
                pre = 0;
                need = 0;
            }
            else
            {
                cout << "decode error!" << endl;
            }
        }
        else if (_char == '+')
        {
            if (need == 0)
            {
                pre = 62;
                need = 2;
            }
            else if (need == 2)
            {
                result += pre << 2 | 62 >> 4;
                pre = 62 & 0b1111;
                need = 4;
            }
            else if (need == 4)
            {
                result += pre << 4 | 62 >> 2;
                pre = 62 & 0b11;
                need = 6;
            }
            else if (need == 6)
            {
                result += pre << 6 | 62;
                pre = 0;
                need = 0;
            }
            else
            {
                cout << "decode error!" << endl;
            }
        }
        else if (_char == '/')
        {
            if (need == 0)
            {
                pre = 63;
                need = 2;
            }
            else if (need == 2)
            {
                result += pre << 2 | 63 >> 4;
                pre = 63 & 0b1111;
                need = 4;
            }
            else if (need == 4)
            {
                result += pre << 4 | 63 >> 2;
                pre = 63 & 0b11;
                need = 6;
            }
            else if (need == 6)
            {
                result += pre << 6 | 63;
                pre = 0;
                need = 0;
            }
            else
            {
                cout << "decode error!" << endl;
            }
        }
        else
        {
            break;
        }
    }
    return result;
}

string random_string(int length)
{
    string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()_+-=[],./<>?{}");

    random_device rd;
    mt19937 generator(rd());

    shuffle(str.begin(), str.end(), generator);

    return str.substr(0, length);
}

/* base64 encode and decode */
int main(int argc, char *argv[])
{

    //Test encode and decode
    double encode_sum = 0, decode_sum = 0;
    for (int i = 0; i < 100; i++)
    {
        string str = random_string(100);
        auto start = chrono::steady_clock::now();
        string encode_str = fasterEncode(str);
        auto mid = chrono::steady_clock::now();
        string decode_str = fasterDecode(encode_str);
        auto end = chrono::steady_clock::now();
        encode_sum += chrono::duration<double, milli>(mid - start).count();
        decode_sum += chrono::duration<double, milli>(end - mid).count();
        if (str.compare(decode_str) != 0)
        {
            cout << "error!" << endl
                 << str << endl
                 << encode_str << endl
                 << decode_str << endl;
            break;
        }
    }
    cout << "encode: " << encode_sum / 100 << " ms" << endl;
    cout << "decode: " << decode_sum / 100 << " ms" << endl;
    return 0;
}
