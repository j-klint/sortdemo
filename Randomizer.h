#pragma once

struct Randomizer
{
	const int lukuja;
	const int maxValue;

	Randomizer(const int lkm, const int max) : lukuja{ lkm }, maxValue{max}
	{
		srand(static_cast<unsigned>(time(nullptr)));
	}
	
	void Scramble(int arr[]) const
	{
		for (int i = lukuja-1; i > 1; --i)
			std::swap(arr[i], arr[rand() % (i + 1)]);
	}

	template<typename T>
	double sqr(const T x) const
	{
		double temp = static_cast<double>(x);
		return temp * temp;
	}

#undef min
	template<typename T>
	int Capped(T const x, const int min = 1, int max = std::numeric_limits<int>::min() ) const
	{

		int n{ static_cast<int>(x) };
		if (max < min) { max = maxValue; }
		return n > max ?
			max : n < min ?
			min : n;
	}

	void circle(int arr[], bool isTall) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			double dd = static_cast<double>(i);
			dd += 0.5;
			double L{ static_cast<double>(lukuja) };
			L /= 2;
			isTall |= lukuja/2 > maxValue;
			dd = std::sqrt(sqr(L) - sqr(dd - L)) 
				* (isTall ? static_cast<double>(maxValue)/ L : 1);
			arr[i] = Capped(dd);
		}
	}

	void sinusoid(int arr[], double factor = 1.0) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			constexpr double PI{ 3.141592536 };
			double dd = static_cast<double>(i);
			dd += 0.5;
			dd = (0.5 + factor*std::sin(dd*PI*2 / (lukuja)) / 2.03) * maxValue + 1;
			arr[i] = Capped(dd);
		}
	}

	void straightLine(int arr[]) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			int n = (i * maxValue / lukuja) % maxValue + 1;
			arr[i] = Capped(n);
		}
	}

	void straight(int arr[]) const
	{
		straightLine(arr);
		Scramble(arr);
	}

	void rnd(int arr[]) const
	{
		//srand(time(0));
		for (int i = 0; i < lukuja; i++)
		{
			int n = 1 + rand() % maxValue;
			arr[i] = Capped(n);
		}
	}

	void qube(int arr[]) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			double dd = sqr(i) * maxValue * i / sqr(lukuja) / lukuja + 1;
			arr[i] = Capped(dd);
		}
		Scramble(arr);
	}

	void sqrt(int arr[]) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			double dd = std::sqrt(i) * maxValue / std::sqrt(lukuja) + 1;
			arr[i] = Capped(dd);
		}
		Scramble(arr);
	}

	void rot1(int arr[]) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			int n{ i + 1 };
			n = (n * maxValue / lukuja) % maxValue + 1;
			arr[i] = Capped(n);
		}
	}

	void rotMinus1(int arr[]) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			int n{ lukuja - i };
			n = (n * maxValue / lukuja) % maxValue + 1;
			arr[i] = Capped(n);
		}
	}

	void sawTeeth(int arr[], const int amt = 2) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			int n{ amt > 0 ? i : lukuja - i - 1 };
			n = n * std::abs(amt) * maxValue / lukuja;
			n += (n < 0) * maxValue * (n / maxValue + 1);
			n = n % maxValue + 1;
			arr[i] = Capped(n);
		}
	}

	void staircase(int arr[], const int divisor = 5) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			int n{ i };
			n = (n * maxValue / lukuja / divisor * divisor) % maxValue + 1;
			arr[i] = Capped(n);
		}
		Scramble(arr);
	}

	double gauss(const double x, const double sigma) const
	{
		double a = 0.5 * lukuja;
		return 1.0 + std::exp( -sqr((x-a)/sigma)*0.5 ) * (maxValue-1);
	}

	void gaussian(int arr[], const double ssigma = 0.16) const
	{
		for (int i = 0; i < lukuja; i++)
		{
			arr[i] = Capped( gauss(i, ssigma * lukuja) );
		}
	}
	
	void almost(int arr[], const int k = 5) const
	{
		auto swapped = std::make_unique<bool[]>(lukuja); // n�ytt�� alustavan 0:iksi
		straightLine(arr);
		for (int i = 0; i < lukuja; i++)
		{
			if (swapped[i]) { continue; }
			int min = std::max(0, i - k);
			int modulus = std::min(lukuja-1, i+k) - min + 1;
			int d = min + rand() % modulus;
			if (swapped[d]) { continue; }
			std::swap(arr[i], arr[d]);
			swapped[i] = swapped[d] = true;
		}
	}
};