#include<bits/stdc++.h>
#define ld long double
using namespace std;


namespace FFT {
	int power2UpperBound(int n) {
		int lower = 1;
		while (lower < n) {
			lower <<= 1;
		}

		return lower;
	}


	vector<complex<ld>> fft(vector<complex<ld>> a) {
		int n = power2UpperBound(a.size());
		a.resize(n, 0);

		if (n == 1) {
			return a;
		}

		vector<complex<ld>> even, odd;
		for (int i = 0; i < n / 2; i++) {
			even.push_back(a[2 * i]);
			odd.push_back(a[2 * i + 1]);
		}

		even = fft(even);
		odd = fft(odd);

		ld angle = 2 * acos(-1) / n;
		complex<ld> omega = polar(1.0L, angle);
		complex<ld> cur(1, 0);
		vector<complex<ld>> y(n);
		for (int k = 0; k < n / 2; k++) {
			y[k] = even[k] + cur * odd[k];
			y[k + n / 2] = even[k] - cur * odd[k];
			cur *= omega;
		}

		return y;
	}

	vector<int> ntt(vector<int> a, const int mod) {
		const int primitive_root = 3;
		auto modexp = [&](int base, int exp) -> int {
			int res = 1;
			while(exp > 0) {
				if(exp & 1)
					res = (long long)res * base % mod;
				base = (long long)base * base % mod;
				exp >>= 1;
			}
			return res;
		};

		int n = power2UpperBound(a.size());
		a.resize(n, 0);

		if (n == 1) {
			return a;
		}

		vector<int> even(n/2), odd(n/2);
		for (int i = 0; i < n/2; i++) {
			even[i] = a[2*i];
			odd[i] = a[2*i+1];
		}

		even = ntt(even, mod);
		odd = ntt(odd, mod);

		int w_n = modexp(primitive_root, (mod - 1) / n);
		int cur = 1;
		vector<int> y(n);
		for (int k = 0; k < n/2; k++) {
			int t = (long long) cur * odd[k] % mod;
			y[k] = (even[k] + t) % mod;
			y[k + n/2] = (even[k] - t + mod) % mod;  
			cur = (long long) cur * w_n % mod;
		}

		return y;
	}
}