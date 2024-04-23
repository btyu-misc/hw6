#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T ret = 0;
        std::string s = "";
        for (size_t i = 0; i < k.size(); i++) { //converting k to lowercase
            s += static_cast<char>(tolower(k[i]));
        }

        //std::cout << "lower case string: " << s << std::endl;
        //size_t p = s.size() - 6;
        //std::cout << "i = " << p << std::endl;

        int cur = 4;

        for (int i = s.size() - 6; i > -1; i -= 6) {
            //std::cout << "i = " << i << std::endl;
            //taking all groups of six chars, starting from end
            //doesn't go into for loop if string is size 5 or less

            HASH_INDEX_T sum = 0;
            for (int j = 0; j < 6; j++) {
                if (s[i + j] >= 48 && s[i + j] <= 57) {
                    //std::cout << k[i + j] << "'s id is: " << int(k[i + j]) - 22 << std::endl;

                    sum += pow(36, 6 - j - 1) * (int(s[i + j]) - 22);
                }
                else sum += pow(36, 6 - j - 1) * (int(s[i + j]) - 'a');
                //std::cout << "new sum value: " << sum << std::endl;
            }

            ret += sum * rValues[cur];
            cur--;
        }

        HASH_INDEX_T sum = 0;
        for (size_t i = 0; i < s.size() % 6; i++) {
            //last substring of size 5 or less, doesn't run iof
            if (s[i] >= 48 && s[i] <= 57) sum += pow(36, s.size() % 6 - 1 - i) * (int(s[i]) - 22);
            else sum += pow(36, s.size() % 6 - 1 - i) * (int(s[i]) - 'a');
            //std::cout << "new sum value: " << sum << std::endl;
        }

        ret += sum * rValues[cur];
        return ret;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
