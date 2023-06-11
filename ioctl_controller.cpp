#include <iostream>
#include "kernelinterface.hpp"

int main() {
	KernelInterface driver = KernelInterface("\\\\.\\ioctldriverlink");

	ULONG address = driver.GetClientAddress();

	std::cout << " yoloo "<< std::hex << address << std::endl;

	while (true);

	return 0;
}