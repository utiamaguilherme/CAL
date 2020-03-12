#! /usr/bin/env python

def extEuclideanAlg(a, b) :
  """Computes a solution  to a x + b y = gcd(a,b), as well as gcd(a,b)
  """
  if b == 0 :
      return 1,0,a
  else :
      x, y, gcd = extEuclideanAlg(b, a % b)
      return y, x - y * (a // b),gcd

def modInvEuclid(a,m) :
  """Computes the modular multiplicative inverse of a modulo m,
  using the extended Euclidean algorithm
  """
  x,y,gcd = extEuclideanAlg(a,m)
  if gcd == 1 :
      return x % m
  else :
      return None

def isPrime(n):
    """Verifies if n is prime
    """
    if (n % 2) == 0:
        return False
    f = 3
    while f < n/2:
        if (n % f) == 0:
            return False
        f += 2
    return True

while True:
    p = input("Entre o valor de p (primo): ")
    if isPrime(p): break
while True:
    q = input("Entre o valor de q (primo): ")
    if isPrime(q): break
n = p*q
n1 = (p-1)*(q-1)
print "n =", n
print "(p-1)(q-1) =", n1
while True:
    e = input("Entre o valor de e (primo): ")
    if isPrime(e): break
d = modInvEuclid(e, n1)
print "d =", d
while True:
    m = input("Entre a mensagem m (m<n, 0 encerra): ")
    if m == 0: break
    if m < n:
        c = (m**e)%n
        print "  Mensagem m cifrada =", c
        m2 = (c**d)%n
        print "  Mensagem c decifrada =", m2, '\n'
