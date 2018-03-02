// specialFunctions.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ErrorCodes.h"
#include <cmath>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/ellint_2.hpp>
#include <boost/math/special_functions/ellint_3.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/expint.hpp>
#include <boost/math/special_functions/hermite.hpp>
#include <boost/math/special_functions/zeta.hpp>
#include <vector>
#include <complex>
#include "complexHelpers.h"


extern LRESULT Trace(LPCOMPLEXSCALAR result, LPCMCSTRING s);

using namespace std;
using namespace boost::math;

namespace specFuncs {

	bool isInteger(LPCCOMPLEXSCALAR x)
	{
		return (x->imag == 0.0 && x->real == static_cast<double>(static_cast<unsigned int>(x->real)));
	}

	bool isNonNegativeRealInteger(LPCCOMPLEXSCALAR x)
	{
		return (x->imag == 0.0 && x->real >= 0.0 && x->real == static_cast<double>(static_cast<unsigned int>(x->real)));
	}

	LRESULT AssocLaguerre(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR m, LPCCOMPLEXSCALAR x)
	{
		//if (x->imag != 0.0 || x->real < 0.0)
		//{
		//	return MAKELRESULT(X_DOMAIN_ERROR, 3);
		//}

		if (!isNonNegativeRealInteger(n))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 1);
		}

		if (!isNonNegativeRealInteger(m))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 2);
		}

		std::complex<double> y = laguerre(static_cast<unsigned int>(n->real), static_cast<unsigned int>(m->real), std::complex<double>{ x->real, x->imag });

		if (!std::isfinite(y))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = y.imag();
		result->real = y.real();
		return SUCCESS;
	}


	LRESULT Laguerre(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR x)
	{
		//if (x->imag != 0.0 || x->real < 0.0)
		//{
		//	return MAKELRESULT(X_DOMAIN_ERROR, 2);
		//}

		if (!isNonNegativeRealInteger(n))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 1);
		}

		std::complex<double> y = laguerre(static_cast<unsigned int>(n->real), std::complex<double>{x->real, x->imag});

		if (!std::isfinite(y))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = y.imag();
		result->real = y.real();
		return SUCCESS;
	}


#if 0

	LRESULT AssocLaguerre(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR m, LPCCOMPLEXSCALAR x)
	{
		if (x->imag != 0.0 || x->real < 0.0)
		{
			return MAKELRESULT(X_DOMAIN_ERROR, 3);
		}

		if (!isNonNegativeRealInteger(n))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 1);
		}

		if (!isNonNegativeRealInteger(m))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR,2);
		}

		auto y = laguerre(static_cast<unsigned int>(n->real), static_cast<unsigned int>(m->real), x->real);

		std::complex<double> X{ x->real, x->imag };
		
		auto yy = laguerre(static_cast<unsigned int>(n->real), static_cast<unsigned int>(m->real), X);

		if (!std::isfinite(y))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = y;
		return SUCCESS;
	}

	LRESULT Laguerre(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR x)
	{
		if (x->imag != 0.0 || x->real < 0.0)
		{
			return MAKELRESULT(X_DOMAIN_ERROR, 2);
		}

		if (!isNonNegativeRealInteger(n))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 1);
		}

		auto y = laguerre(static_cast<unsigned int>(n->real), x->real);

		if (!std::isfinite(y))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = y;
		return SUCCESS;
	}

#endif // 0

	LRESULT AssocLegendre(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR m, LPCCOMPLEXSCALAR x)
	{
		if (x->imag != 0.0 || x->real < 0.0)
		{
			return MAKELRESULT(X_DOMAIN_ERROR, 3);
		}

		if (!isNonNegativeRealInteger(n))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 1);
		}

		if (!isNonNegativeRealInteger(m))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 2);
		}

		// auto y = legendre_p(static_cast<unsigned int>(n->real), static_cast<unsigned int>(m->real), std::complex<double>{x->real, x->imag});

	 	auto y = legendre_p(static_cast<unsigned int>(n->real), static_cast<unsigned int>(m->real), x->real);

		if (!std::isfinite(y))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0; // y.imag();
		result->real = y; // y.real();
		return SUCCESS;
	}

	LRESULT Legendre(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR x)
	{
		if (x->imag != 0.0 || x->real < 0.0)
		{
			return MAKELRESULT(X_DOMAIN_ERROR, 2);
		}

		if (!isNonNegativeRealInteger(n))
		{
			return MAKELRESULT(DEGREE_DOMAIN_ERROR, 1);
		}

		auto y = legendre_p(static_cast<unsigned int>(n->real), x->real);

		if (!std::isfinite(y))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = y;
		return SUCCESS;
	}


	LRESULT Beta(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR x, LPCCOMPLEXSCALAR y)
	{
		if (x->imag != 0.0 || x->real <= 0.0)
		{
			return MAKELRESULT(MUST_BE_POSITIVE, 1);
		}

		if (y->imag != 0.0 || y->real <= 0.0)
		{
			return MAKELRESULT(MUST_BE_POSITIVE, 2);
		}


		auto r = beta(static_cast<unsigned int>(x->real), y->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT CompEllint1(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR k)
	{
		if (k->imag != 0.0 || k->real < -1.0 || k->real > 1.0)
		{
			return MAKELRESULT(MUST_BE_REAL_1, 1);
		}


		auto r = ellint_1(k->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT CompEllint2(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR k)
	{
		if (k->imag != 0.0 || k->real < -1.0 || k->real > 1.0)
		{
			return MAKELRESULT(MUST_BE_REAL_1, 1);
		}


		auto r = ellint_2(k->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT CompEllint3(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR k, LPCCOMPLEXSCALAR v)
	{
		if (k->imag != 0.0 || k->real < -1.0 || k->real > 1.0)
		{
			return MAKELRESULT(MUST_BE_REAL_1, 1);
		}

		auto r = ellint_2(k->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT CylBesselI(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR v, LPCCOMPLEXSCALAR x)
	{
		if (v->imag != 0 || v->real < 0.0 || v->real > 120.0)
		{
			return MAKELRESULT(MUST_BE_REAL_0_128, 1);
		}

		if (x->imag != 0.0 || x->real < 0.0)
		{
			return MAKELRESULT(MUST_BR_NON_NEGATIVE_REAL, 2);
		}

		auto r = cyl_bessel_i(v->real, x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT CylBesselJ(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR v, LPCCOMPLEXSCALAR x)
	{
		if (v->imag != 0 || v->real < 0.0 || v->real > 120.0)
		{
			return MAKELRESULT(MUST_BE_REAL_0_128, 1);
		}

		if (x->imag != 0.0 || x->real < 0.0)
		{
			return MAKELRESULT(MUST_BR_NON_NEGATIVE_REAL, 2);
		}

		auto r = cyl_bessel_i(v->real, x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT CylBesselK(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR v, LPCCOMPLEXSCALAR x)
	{
		if (v->imag != 0 || v->real < 0.0 || v->real > 120.0)
		{
			return MAKELRESULT(MUST_BE_REAL_0_128, 1);
		}

		if (x->imag != 0.0 || x->real <= 0.0)
		{
			return MAKELRESULT(MUST_BE_POSITIVE, 2);
		}

		auto r = cyl_bessel_k(v->real, x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT CylNeumann(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR v, LPCCOMPLEXSCALAR x)
	{
		if (v->imag != 0 || v->real < 0.0 || v->real > 120.0)
		{
			return MAKELRESULT(MUST_BE_REAL_0_128, 1);
		}

		if (x->imag != 0.0 || x->real <= 0.0)
		{
			return MAKELRESULT(MUST_BE_POSITIVE, 2);
		}

		auto r = cyl_neumann(v->real, x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT Ellint1(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR k, LPCCOMPLEXSCALAR phi)
	{
		if (k->imag != 0 || k->real < -1.0 || k->real > 1.0)
		{
			return MAKELRESULT(MUST_BE_REAL_1, 1);
		}

		if (phi->imag != 0.0)
		{
			return MAKELRESULT(MUST_BE_REAL, 2);
		}

		auto r = ellint_1(k->real, phi->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT Ellint2(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR k, LPCCOMPLEXSCALAR phi)
	{
		if (k->imag != 0 || k->real < -1.0 || k->real > 1.0)
		{
			return MAKELRESULT(MUST_BE_REAL_1, 1);
		}

		if (phi->imag != 0.0)
		{
			return MAKELRESULT(MUST_BE_REAL, 2);
		}

		auto r = ellint_2(k->real, phi->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT Ellint3(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR k, LPCCOMPLEXSCALAR phi)
	{
		if (k->imag != 0 || k->real < -1.0 || k->real > 1.0)
		{
			return MAKELRESULT(MUST_BE_REAL_1, 1);
		}

		if (phi->imag != 0.0)
		{
			return MAKELRESULT(MUST_BE_REAL, 2);
		}

		auto r = ellint_3(k->real, phi->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT Expint(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR x)
	{
		if (x->imag != 0.0)
		{
			return MAKELRESULT(MUST_BE_REAL, 1);
		}

		if (x->real == 0)
		{
			return MAKELRESULT(OVERFLOW_, 1);
		}

		auto r = expint(x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT Hermite(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR x)
	{
		if (!isInteger(n))
		{
			return MAKELRESULT(MUST_BE_REAL_INT, 1);
		}

		if (x->imag != 0)
		{
			return MAKELRESULT(MUST_BE_REAL, 2);
		}

		auto r = hermite(static_cast<int>(n->real), x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}


	LRESULT Zeta(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR x)
	{
		if (x->imag != 0.0)
		{
			return MAKELRESULT(MUST_BE_REAL, 1);
		}


		auto r = zeta(x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT SphBessel(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR x)
	{
		if (!isInteger(n))
		{
			return MAKELRESULT(MUST_BE_REAL_INT, 1);
		}

		if (x->imag != 0)
		{
			return MAKELRESULT(MUST_BE_REAL, 2);
		}

		auto r = sph_bessel(static_cast<int>(n->real), x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}

	LRESULT SphNeumann(LPCOMPLEXSCALAR result, LPCCOMPLEXSCALAR n, LPCCOMPLEXSCALAR x)
	{
		if (!isInteger(n))
		{
			return MAKELRESULT(MUST_BE_REAL_INT, 1);
		}

		if (x->imag != 0)
		{
			return MAKELRESULT(MUST_BE_REAL, 2);
		}

		auto r = sph_neumann(static_cast<int>(n->real), x->real);

		if (!std::isfinite(r))
		{
			return MAKELRESULT(OVERFLOW_, 0);
		}

		result->imag = 0.0;
		result->real = r;
		return SUCCESS;
	}


	static
	std::vector<FUNCTIONINFO> funcs 
	{
		{
			"assoc_laguerre",
			"n,m,x",
			"compute the associated laguerre function",
			reinterpret_cast<LPCFUNCTION>(&AssocLaguerre),
			COMPLEX_SCALAR,
			3,
			{ COMPLEX_SCALAR , COMPLEX_SCALAR , COMPLEX_SCALAR }
		},
		{
			"laguerre",
			"n,x",
			"compute the laguerre function",
			reinterpret_cast<LPCFUNCTION>(&Laguerre),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR , COMPLEX_SCALAR }
		},
		
		{
			"assoc_legendre",
			"n,m,x",
			"compute the associated laguerre function",
			reinterpret_cast<LPCFUNCTION>(&AssocLegendre),
			COMPLEX_SCALAR,
			3,
			{ COMPLEX_SCALAR , COMPLEX_SCALAR , COMPLEX_SCALAR }
		},
		{
			"legendre",
			"n,x",
			"compute the laguerre function",
			reinterpret_cast<LPCFUNCTION>(&Legendre),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR , COMPLEX_SCALAR }
		},
		{
			"beta",
			"x,y",
			"compute the beta function",
			reinterpret_cast<LPCFUNCTION>(&Beta),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR , COMPLEX_SCALAR }
		},
		{
			"comp_ellint_1",
			"k",
			"Computes the complete elliptic integral of the first kind of k",
			reinterpret_cast<LPCFUNCTION>(&CompEllint1),
			COMPLEX_SCALAR,
			1,
			{ COMPLEX_SCALAR }
		},
		{
			"comp_ellint_2",
			"k",
			"Computes the complete elliptic integral of the second kind of k",
			reinterpret_cast<LPCFUNCTION>(&CompEllint2),
			COMPLEX_SCALAR,
			1,
			{ COMPLEX_SCALAR }
		},
		{
			"comp_ellint_3",
			"k, v",
			"Computes the complete elliptic integral of the third kind of the arguments k and v",
			reinterpret_cast<LPCFUNCTION>(&CompEllint3),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"cyl_bessel_i",
			"v, x",
			"Computes the regular modified cylindrical Bessel function of v and x",
			reinterpret_cast<LPCFUNCTION>(&CylBesselI),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"cyl_bessel_j",
			"v, x",
			"Computes the cylindrical Bessel function of the first kind of v and x",
			reinterpret_cast<LPCFUNCTION>(&CylBesselJ),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"cyl_bessel_k",
			"v, x",
			"Computes the irregular modified cylindrical Bessel function (also known as modified Bessel function of the second kind) of v and x",
			reinterpret_cast<LPCFUNCTION>(&CylBesselK),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"cyl_neumann",
			"v, x",
			"Computes the cylindrical Neumann  function (also known as the Bessel function of the second kind) of v and x",
			reinterpret_cast<LPCFUNCTION>(&CylNeumann),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"ellint_1",
			"x, phi",
			"Computes the incomplete Elliptic Integral of the first kind.",
			reinterpret_cast<LPCFUNCTION>(&Ellint1),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"ellint_2",
			"x, phi",
			"Computes the incomplete Elliptic Integral of the second kind.",
			reinterpret_cast<LPCFUNCTION>(&Ellint2),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"ellint_3",
			"x, phi",
			"Computes the incomplete Elliptic Integral of the third kind.",
			reinterpret_cast<LPCFUNCTION>(&Ellint3),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"expint",
			"x",
			"Computes the exponential integral of x.",
			reinterpret_cast<LPCFUNCTION>(&Expint),
			COMPLEX_SCALAR,
			1,
			{ COMPLEX_SCALAR }
		},
		{
			"hermite",
			"n, x",
			"Computes the (physicist's) Hermite polynomials of the degree n and argument x",
			reinterpret_cast<LPCFUNCTION>(&Hermite),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"zeta",
			"x",
			"Computes the Riemann zeta function of x",
			reinterpret_cast<LPCFUNCTION>(&Zeta),
			COMPLEX_SCALAR,
			1,
			{ COMPLEX_SCALAR }
		},
		{
			"sph_bessel",
			"v, x",
			"Computes the Spherical Bessel function od the first kind of v and x",
			reinterpret_cast<LPCFUNCTION>(&SphBessel),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"sph_neumann",
			"v, x",
			"Computes the Spherical Neumann function od the first kind of v and x",
			reinterpret_cast<LPCFUNCTION>(&SphBessel),
			COMPLEX_SCALAR,
			2,
			{ COMPLEX_SCALAR, COMPLEX_SCALAR }
		},
		{
			"trace",
			"s",
			"trace output to a window",
			reinterpret_cast<LPCFUNCTION>(&Trace),
			COMPLEX_SCALAR,
			1,
			{ STRING }
		},


	};

	void initializeUserEfi(HINSTANCE hInst)
	{
		for (auto &func : funcs)
		{
			if (!CreateUserFunction(hInst, &func))
				break;
		}
	}


}

