#ifndef SPECFUNCS_ERROR_CODES_H_INCLUDED__
#define SPECFUNCS_ERROR_CODES_H_INCLUDED__
#pragma once
#include <vector>

namespace specFuncs {

	enum Errors : LRESULT
	{
		SUCCESS=0,
		DEGREE_DOMAIN_ERROR,
		X_DOMAIN_ERROR,
		OVERFLOW_,
		MUST_BE_POSITIVE,
		MUST_BE_REAL_1,
		MUST_BE_REAL_0_128,
		MUST_BR_NON_NEGATIVE_REAL,
		MUST_BE_REAL,
		MUST_BE_REAL_INT,
	};
	extern std::vector<char *> errors;

}

#endif //SPECFUNCS_ERROR_CODES_H_INCLUDED__
