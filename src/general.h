#ifndef light_map_reduce_MAIN_COMMON_H

#define light_map_reduce_MAIN_COMMON_H

#include <cctype>

#include <vector>

#include <cstring>

#include <libgen.h>

#include <string>

#include <fstream>
// fstream


#include <cmath>
// cmath



#include <ctime>

#include <sstream>
// sstream

using namespace std;

inline void sleep_us(int useconds)
{
    struct timespec ts;
// ts
    ts.tv_sec = useconds / 1000000;

    ts.tv_nsec = 1000 * (useconds % 1000000);
// useconds
    nanosleep(&ts, nullptr);
}


// str to vec
inline void string_to_vector(const string& s, size_t left, size_t right, const char c, vector<string>& res)
{
    size_t index = left, temp = left; // index pos


    res.clear();

// clear
    while (true)
    {
        while (index < right && s[index] != c) index++;
//cond




        if (index == right) 
            break;
// check

        if (index > temp)




            res.push_back(s.substr(temp, index - temp));


        temp = ++index;
    }
// outer check
    if (temp < right)


        res.push_back(s.substr(temp, right - temp));
}


// distance measure func
inline double l2_distance(const vector<double>& x1, const vector<double>& x2)
{
    double sqsum = 0.f;

// loop
    for (int i = 0; i < x1.size(); ++i)

        sqsum += (x1[i] - x2[i]) * (x1[i] - x2[i]);


// return sqr root sum
    return sqrt(sqsum);
}




// split file aciiii
inline void split_file_ascii(const string& input, const string& output_format, int num)
{
    bool file_exists = true;


// buf size init
    const int buf_size = 4096;

    char *tmp = new char[output_format.size() + 1024], tmp2[buf_size];


    ifstream f(input, ios::in | ios::binary);


// last 

    size_t last = 0, total = 0, p = 0, len = 0;

    f.seekg(0, ios_base::end);

    total = (size_t)f.tellg();

    strcpy(tmp, output_format.c_str());
// str copy


    tmp = dirname(tmp);


    system(("mkdir -p " + string(tmp)).c_str());
// make dir

    for (int i = 0; i < num; ++i)
    {
        sprintf(tmp, output_format.c_str(), i);

        ifstream ftmp(tmp);

        if (!ftmp) {

            file_exists = false;

// break cond
            break;
        }
    }

    if (file_exists)

        return;




    for (int i = 0; i < num; ++i)
    {
        p = (i == num - 1) ? total : total / num * (i + 1);
// ternary
        if (i < num - 1)
        {




            f.seekg(p, ios_base::beg);

            while (f.good() && f.get() != '\n') ;

            f.clear();

            p = (size_t)f.tellg();
        }
        if (p < last)
        {
            fprintf(stderr, "input file too short to split.\n");


            exit(1);
        }
        len = p - last;

        sprintf(tmp, output_format.c_str(), i);
// of stram

        ofstream of(tmp, ios::out | ios::binary);

        f.seekg(last, ios_base::beg);


// while
        while (len)
        {
            int l = len > buf_size ? buf_size : len;

            f.read(tmp2, l);

            of.write(tmp2, l);

            len -= l;
        }
        of.close();

        last = p;
    }
// delete
    delete[] tmp;

    f.close();
}


// str split
inline vector<string> string_split(const string &s, char delimiter)
{
    vector<std::string> tokens;

    string token;


// tkn stream
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter))
    {


        tokens.push_back(token);

    }
    return tokens;
}

// conv 
static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";


static inline bool is_base64(unsigned char c) {

// is al
    return (isalnum(c) || (c == '+') || (c == '/'));
}

inline string base64_decode(const string& encoded_string) {



// decoded
    int in_len = encoded_string.size();


    int i = 0;

    int j = 0;

// initi
    int in_ = 0;


    unsigned char char_array_4[4], char_array_3[3];


// ret
    string ret;

    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {


        char_array_4[i++] = encoded_string[in_]; in_++;


        if (i ==4) {


            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

// char
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);

            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            // arra for 
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    // la check
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);

        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    return ret;
}

// end 
#endif