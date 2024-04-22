def sieve_of_eratosthenes(limit):
    primes = [True] * (limit + 1)
    primes[0] = primes[1] = False
    p = 2
    while p**2 <= limit:
        if primes[p]:
            for i in range(p**2, limit+1, p):
                primes[i] = False
        p += 1
    return [i for i in range(2, limit+1) if primes[i]]