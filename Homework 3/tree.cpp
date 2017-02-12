#include <iostream>

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	int count = 0;
	if (n1 <= 0 || n2 <= 0)
		return 0;
	if (n1 < n2)
		return 0;
	if (n2 == 1 && a1[n1 - 1] == a2[0])
		count++;
	if (a1[n1 - 1] == a2[n2 - 1])
	{
		if (countIncludes(a1, n1 - 1, a2, n2 - 1) > 0)
			count += countIncludes(a1, n1 - 1, a2, n2 - 1);
	}
	if (countIncludes(a1, n1 - 1, a2, n2) > 0)
		count += countIncludes(a1, n1 - 1, a2, n2);
	return count;
}

// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
	int& firstNotGreater, int& firstLess)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > separator
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < separator

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < separator)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > separator)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)  //(Hint: Using the separate function, the order function can be written in fewer than eight short lines of code.)
{
	if (n <= 1)
		return;
	int fng = 0;
	int fs = 0;
	
	separate(a, n, a[n - 1], fng, fs);
	
	if (fs != n)
		order(a, n);
	else 
		order(a, n - 1);
}

int main()
{
	/*double a[] = { 10,50,40,20,50,40,30 };
	double b[] = { 10,20,40 };
	double c[] = { 10,40,30 };
	double d[] = { 20,10,40 };
	double e[] = { 50,40,30 };
	std::cout << countIncludes(a, 7, d, 3);
*/
	double aa[] = { 5,6,2,3,1 };
	double bb[] = { 123,343,234,5123,54,23,1,123,553,21,24,676,2,1 };
	double cc[] = { 123,343,234,543,54,23,1,123,553,21,24,676,2,1 };
	/*int fg = 0;
	int fs = 0;
	separate(aa, 5, 3, fg, fs);
	for (int i = 0;i < 5;i++)
		std::cout << aa[i];
	std::cout << std::endl;
	std::cout << fg << std::endl;
	std::cout << fs << std::endl;*/
	order(cc, 14);
	for (int i = 0;i < 14;i++)
		std::cout << cc[i] << " ";
}

	////For Debugging 
	//std::cout << "n " << n << " a " << a[n - 1] << std::endl;
	//for (int i = 0;i < 14;i++)
	//	std::cout <<"(" <<i<<")" << a[i] << " ";
	//std::cout  << std::endl << "----------------------------------------------------" << std::endl;
	////end of Debugging 

	////For Debugging 
	//std::cout << "fng " << fng << " " << a[fng] << std::endl;
	//std::cout << "fs " << fs << " " << a[fs] << std::endl;
	//std::cout << std::endl << "=====================================================" << std::endl;
	////end of Debugging 