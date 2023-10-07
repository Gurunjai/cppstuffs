#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <boost/crc.hpp>

using namespace std;

unsigned int computeCrcCheckSum(int arr[], int size) {
    boost::crc_32_type crc;
    crc.process_bytes(arr, size * sizeof(int));
    return crc.checksum();
}

std::string dumpArr(vector<int> arr) {
    stringstream ss;
    ss << arr[0];
    for (int i = 1; i < arr.size(); i++) {
        ss << " " << arr[i];
    }
    ss << endl;
    return ss.str();
}

int main (void)
{
    vector<int> a1, a2, a3;
    for (int i = 0; i < 10; ){
        ++i;
        auto xorVal = (((i << 4) | (i >> 2)) ^ i << 8);
        a1.push_back(xorVal);
    }

    for (int i = 0; i < 10;) {
        ++i;
        a2.push_back(i);
    }

    for (int i = 10; i > 0; ) {
        a3.push_back(i--);
    }

    vector<int> a4 = a2;

    cout << "Array-1:\t" << dumpArr(a1);
    cout << "Array-2:\t" << dumpArr(a2);
    cout << "Array-3:\t" << dumpArr(a3);
    cout << "Array-4:\t" << dumpArr(a4);

    assert(computeCrcCheckSum(a1.data(), a1.size()) != computeCrcCheckSum(a2.data(), a2.size()));
    assert(computeCrcCheckSum(a2.data(), a2.size()) != computeCrcCheckSum(a3.data(), a3.size()));
    assert(computeCrcCheckSum(a2.data(), a2.size()) == computeCrcCheckSum(a4.data(), a4.size()));
    cout << "Array-1 CheckSum= " << computeCrcCheckSum(a1.data(), a1.size()) << endl;
    cout << "Array-2 CheckSum= " << computeCrcCheckSum(a2.data(), a2.size()) << endl;
    cout << "Array-3 CheckSum= " << computeCrcCheckSum(a3.data(), a3.size()) << endl;
    cout << "Array-4 CheckSum= " << computeCrcCheckSum(a4.data(), a4.size()) << endl;
}

