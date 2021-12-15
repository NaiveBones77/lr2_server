#pragma once
#include "Conversion.h"

int Conversion::conv_dec_to_bin(double max_value, int max_digit, int digit, double value)
{

		double* arr = decbin(value, max_digit);
		double sum = 0;
		for (int i = 0; i <= digit - 1; i++) {
			sum = sum + arr[i] * (max_value / pow(2, i));
		}
		delete[] arr;
		return sum;
}

double* Conversion::decbin(int dec, int max_digit)
{
	double* bin = new double[max_digit]();
	for (int i = 0; dec > 0; i++)
	{
		bin[max_digit - (i + 1)] = (dec % 2);
		dec /= 2;
	}
	return bin;
}



double Conversion::conv_bin_to_dec(double max_value, int max_digit, int digit, int dec)
{
	double* bin = new double[max_digit]();
	double sum = 0;
	int i = 0;
	while (dec > 0)
	{
		bin[max_digit - (i + 1)] = (dec % 2);
		dec /= 2;
		i++;
	}
	i = 0;
	while (i <= digit - 1)
	{
		sum = sum + bin[i] * (max_value / pow(2, i));
		i++;
	}
	delete[] bin;
	return sum;
}

