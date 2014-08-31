/*
 * =====================================================================================
 *
 *       Filename:  count_pairs.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28.08.2014 00:01:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kamil Łysik (KŁ), kamillys(at)gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <gmpxx.h>
#include <iostream>
#include <vector>
using namespace std;


template<typename T>
bool isPowerOfTwo (T x)
{
    return ((x != 0) && ((x & (~x + 1)) == x));
}


int main()
{
	vector<mpz_class> data;
	for (std::string input_line; getline(cin, input_line);)
	{
		mpz_class entry(input_line, 10);
		data.push_back(entry);
	}
	
	int counter = 0;
	for (int i=0;i<data.size();++i)
	for (int j=0;j<data.size();++j)
	{
	  if(isPowerOfTwo(data[i] ^ data[j]))
	  {
	  cout << i << " " << j << endl;
	  counter++;
	  }
	}
	std::cout << counter << endl;

	return 0;
}
