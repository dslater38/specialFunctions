#ifndef COMPLEXHELPERS_H_INCLUDED__
#define COMPLEXHELPERS_H_INCLUDED__
#pragma once
#include <complex>


std::complex<double> operator-(const std::complex<double> &x, unsigned int n)
{
	return x - static_cast<double>(n);
}

std::complex<double> operator-(unsigned int n, const std::complex<double> &x)
{
	return static_cast<double>(n) - x;
}

std::complex<double> operator*(const std::complex<double> &x, unsigned int n)
{
	return x * static_cast<double>(n);
}

std::complex<double> operator*(unsigned int n, const std::complex<double> &x)
{
	return static_cast<double>(n) * x;
}

std::complex<double> operator/(const std::complex<double> &x, unsigned int n)
{
	return x / static_cast<double>(n);
}

std::complex<double> operator/(unsigned int n, const std::complex<double> &x)
{
	return static_cast<double>(n) / x;
}

bool operator==(const std::complex<double> x, int i)
{
	return x.imag() == 0.0 && x.real() == static_cast<double>(i);
}

bool operator<(const std::complex<double> x, int i)
{
	return 
}

#endif // COMPLEXHELPERS_H_INCLUDED__
