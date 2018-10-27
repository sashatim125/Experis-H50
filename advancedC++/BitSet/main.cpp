
#include<iostream>

#include "bitSet.h"

#include <string>

using namespace advcpp;

using std::cout;
using std::endl;
using std::string;

void myassert(const string& _s, bool _ex)
{
	cout << "Test " << _s << (_ex ? " passed !" : " failed...") << "\n" << endl;
}

int main()
{

	string s1 = "0110111100" "0011100010" "0101101101" "0101111010" "1010110101";
	
	BitSet<50,unsigned short> bs1 = s1 , bs2 = bs1;
	
	{
		string s2 = bs1.ToString();
		myassert("from/to string", s1 == s2);		
	}
	
	myassert("==", bs1 == bs2);
	myassert("!=", ! (bs1 != bs2));
	{
		BitSet<50,unsigned short> bs3;
		bool res = bs3!=bs1;
		bs3 = bs1;
		res &= bs3==bs1;
		myassert("op =", res);
	}	
	{
		BitSet<50,unsigned short> bs3 , bs4 = ~bs3;
		
		myassert("IsAll1", bs4.IsAll());
		myassert("IsAll2", !bs1.IsAll());
		
		myassert("IsNone1", bs3.IsNone());
		myassert("IsNone2", !bs1.IsNone());
		
		myassert("IsAny1", bs1.IsAny());
		myassert("IsAny2", !bs3.IsAny());
		myassert("IsAny3", bs4.IsAny());
	}
	{
		BitSet<50,unsigned short> bs3 = bs1;
		BitSet<50,unsigned short> bs4 = bs3;
		
		bs3[2] = true;
		bs3[39] = false;
		bs3[46] = false;
		
		bs4[2] = true;
		bs4[39] = false;
		bs4[46] = false;
		
		myassert("non_const op[]", bs1 == bs2);
		
		const BitSet<50,unsigned short> bs5 = bs1;
		
		bool res = true;
		for(size_t i=0; res & (i < 50); ++i)
		{
			res &= (bs1[i] == bs5[i]);
		}
		
		myassert("const op[]",res);	
	}
	{
		BitSet<50,unsigned short> bs3 = bs1;
		BitSet<50,unsigned short> bs4 ;
		bs4.Flip();
		
		myassert("op | 1",(bs3 | bs4)==bs4);
		
		bs4.Flip();
		myassert("op | 2",(bs3 | bs4)==bs3);
		
		bs4=bs3;
		myassert("op | 3",(bs3 | bs4)==bs3);	
	}
	{
		BitSet<50,unsigned short> bs3 = bs1;
		BitSet<50,unsigned short> bs4 ;
		bs4.Flip();
		
		myassert("op & 1",(bs3 & bs4)==bs3);
		
		bs4.Flip();
		myassert("op & 2",(bs3 & bs4)==bs4);
		
		bs4=bs3;
		myassert("op & 3",(bs3 & bs4)==bs3);	
	}
	{
		BitSet<50,unsigned short> bs3 = bs1;
		BitSet<50,unsigned short> bs4 ;
		bs4.Flip();
		
		myassert("op ^ 1",(bs3 ^ bs4)== ~bs3);
		
		bs4.Flip();
		myassert("op ^ 2",(bs3 ^ bs4)==bs3);
		
		myassert("op ^ 3",(bs3 ^ bs3)==bs4);	
	}
	{
		//>>3
		string s2 ="000" "0110111100" "0011100010" "0101101101" "0101111010" "1010110";
		//>>16
		string s3 = "0000000000000000" "0110111100" "0011100010" "0101101101" "0101";
		//>>21
		string s4 = "0000000000" "0000000000" "0" "0110111100" "0011100010" "010110110";
		
		BitSet<50,unsigned short> bs3 = s2;
		myassert("op >> 1",bs3 == bs1>>3);
		
		BitSet<50,unsigned short> bs4 = s3;
		myassert("op >> 2",bs4 == bs1>>16);
		
		BitSet<50,unsigned short> bs5 = s4;
		myassert("op >> 3",bs5 == bs1>>21);	
	}
	{
		//<<3
		string s2 = "0111100" "0011100010" "0101101101" "0101111010" "1010110101" "000";
		//<<16
		string s3 = "0010" "0101101101" "0101111010" "1010110101" "000000" "0000000000";
		//<<21
		string s4 = "101101101" "0101111010" "1010110101" "0" "0000000000" "0000000000";
		
		BitSet<50,unsigned short> bs3 = s2;
		myassert("op >> 1",bs3 == bs1<<3);
		
		BitSet<50,unsigned short> bs4 = s3;
		myassert("op << 2",bs4 == bs1<<16);
		
		BitSet<50,unsigned short> bs5 = s4;
		myassert("op << 3",bs5 == bs1<<21);	
	}
		
		
		
	





	return 0;
}



