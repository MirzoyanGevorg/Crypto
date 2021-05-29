#include <iostream>
#include <cmath>
#include <string>


/*
int EulerFunc(int n){
    int res{n};
    for(int i = 2; i*i <= n; ++i){
        if(n % i == 0) {
            while(n % i == 0) {
                n /= i;
                res -= res / i;
            }
        }
    }
    if( n > 1) {
        res -= res / n;
    }
    return res;
}

int ModularBinPower(int base, int exp, int mod) {
    int res{1};
    while (exp) {
        if(exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res % mod;
}
*/


bool CheckIsPrime(long int num)
{
    if(num < 2) return false;

    for(long int i{2}; i * i <= num; ++i) {
        if(!(num % i)) {
            return false;
        }
    }

    return true;
}

long int Multiply(long int num1,long int num2)
{
    return num1 * num2;
}

bool CheckCoPrime (long int num1, long int num2) {
    long int lowest{};

    if (num1 > num2) lowest = num2;
    else lowest = num1;

    bool coprime {true};

    for (long int i{2}; i < lowest; ++i) {
        if (!(num1 % i) && !(num2 % i)) {
            coprime = false;
        } 
    }

    return coprime;
}

long int FindE(long int phi_n)
{
    long int e{0};

    do {
        std::cout << "Choose an integer number e (e must be co prime of phi_n): ";
        std::cin >> e;
    } while (!CheckCoPrime(phi_n, e));

    return e;
}

long int FindD(long int phi_n, long int e)
{
    // extended euqlidian
    int a = phi_n, b = e;
    long int x = 0, y = 1, u = 1, v = 0, m, n, q, r;
    long int gcd = b;
    while (a != 0) {
       q = gcd / a;
       r = gcd % a;
       m = x - u * q;
       n = y - v * q;
       gcd = a;
       a = r;
       x = u;
       y = v;
       u = m;
       v = n;
    }

   if (y < 1) {
      y += phi_n;
   }

   return y;
}

long int Encrypt_Decrypt(long int t, long int e, long int n)
{
    long int rem{}, res{1};

    while (e != 0) {
        rem = e % 2;
        e /= 2;

        if (rem == 1) {
            res = (res * t) % n;
        }
        t = (t * t) % n;
    }

    return res;
}

void EncDecStr (long int e, long int n)
{
    std::string str{}, res{};

    std::cout << "Enter a string: ";
    std::cin >> str;

    std::cout << "Encrypting using Public Key: ";
    for(auto i: str) {
        res.push_back(Encrypt_Decrypt(i, e, n));
    }

    std::cout << res << std::endl;
}

void EncDecNum (long int n1, long int n2)
{
    long int num{};

    std::cout << "Enter an integer number: ";
    std::cin >> num;

    std::cout << Encrypt_Decrypt(num, n1, n2) << std::endl;
}

void generate_key (long int &n, long int &e, long int &d)
{
    long int p{}, q{}, phi_n{};

    do {
	    std::cout << "Enter a prime number: ";
	    std::cin >> p;
    } while (!CheckIsPrime(p));

    do {
	    std::cout << "Enter another prime number: ";
	    std::cin >> q;
    } while (!CheckIsPrime(q));

    n = Multiply(p,q);
    std::cout << "n is " << n << std::endl;

    phi_n = Multiply (p-1,q-1);
    std::cout << "phi_n is " << phi_n << std::endl;

    e = FindE(phi_n);
    std::cout << "e is " << e << std::endl;

    if (!e) {
	    std::cout << "Choose two suitable prime numbers \n";
    }

    d = FindD(phi_n, e);
    std::cout << "d is " << d << std::endl;
}



int main() {

    long int n{}, d{0}, e{};

    generate_key(n, e, d);

    std::cout << "Public Key : (" << e << ", " << n << ")" << std::endl;
    std::cout << "Private Key : (" << d << ", " << n << ")" << std::endl;

    std::cout << "Press 1: for encrypting numbers & 2: for encrypting string: ";
    int choice{};
    std::cin >> choice;

    switch (choice) {
	case 1:
	    EncDecNum(e, n);
	    break;

	case 2:
	    EncDecStr(e, n);
	    break;

	default:
	    std::cout << "Wrong choice. Try again. \n";
    }

    std::cout << "Press 1: for decrypting numbers & 2: for decrypting string: ";
    std::cin >> choice;

    switch (choice) {
	case 1:
	    EncDecNum(d, n);
	    break;

	case 2:
	    EncDecStr(d, n);
	    break;

	default:
	    std::cout << "Wrong choice. Try again. \n";
    }

    return 0;

    
}
