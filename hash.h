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
			std::cout << k <<std::endl;
			bool firstIndex = false;
			//std::cout << letterDigitToNumber('a') << " " << int('a') << std::endl;
			int len = k.length();
			//std::cout << len << std::endl;
			int index = 4;
			HASH_INDEX_T returnVal = 0;
			HASH_INDEX_T curr = 0;
			int p = 0;
			int pVal = 0;
			size_t v = 0;
        // Add your code here
			for (int r = 4; r >= 0; r--)
			{
				int power = 5;
				HASH_INDEX_T curr = rValues[4-r];
				int holder = 0;
				for (int i = 5; i >= 0; i--)
				{
					if (!firstIndex)
					{
						if (r*6+i < len)
						{
							firstIndex = true;
							p = 0;
						}	
					}
					if (firstIndex)
					{
						char toNum = k[p++];
						v = letterDigitToNumber(toNum);
						pVal = pow(36, power);
					}
					holder += v * pVal;
					power--;
				}
				//std::cout << holder << "----" <<"r[" << r << "] = " << curr << std::endl;
				returnVal += (holder * curr);
			}
			return returnVal;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
			//std::cout << "letter being converted = (" <<letter << ")" << "=" << int(letter) << std::endl; 
			int val = int(letter);
			//use ascii for the fun 
			if (val >= 48 && val <= 57)//number assignment
			{
				return val - 48 + 26; //0 = 26 || asci 0 = 48 in CPP 
			}
			if (val >= 65 && val <= 90)//uppercase assignment A asci = 65
			{
				return val - 65; //a=0 //z = 26 
			}
			if (val >= 97 && val <= 122)//lowercase assignment
			{
				return val - 97;
			}
			//std::cout << "exits" <<std::endl;
			return 0;	
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
