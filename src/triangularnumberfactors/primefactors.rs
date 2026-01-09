struct PrimeFactors(Vec<(usize, Vec<usize>)>);

impl PrimeFactors {
    fn into_iter() -> PrimeFactorIter {
        PrimeFactorIter {
            primes: Self(vec![]),
            current: 2,
        }
    }

    fn prime_factors(&self, mut num: usize) -> Vec<usize> {
        let mut factors = vec![];
        let mut d = 2;
        while num > 1 {
            while num.is_multiple_of(d) {
                num /= d;
                factors.push(d)
            }
            d += 1;
        }
        factors
    }
}

struct PrimeFactorIter {
    current: usize,
    primes: PrimeFactors,
}

impl Iterator for PrimeFactorIter {
    type Item = (usize, Vec<usize>);

    fn next(&mut self) -> Option<Self::Item> {
        let curr = self.current;
        self.current += 1;

        let factors = self.primes.prime_factors(curr);

        Some((curr, factors))
    }
}

#[cfg(test)]
mod test {
    use crate::triangularnumberfactors::primefactors::PrimeFactors;

    #[test]
    fn test_prime_factors() {
        let factors = PrimeFactors::into_iter()
            .take_while(|(n, _)| *n < 100)
            .collect::<Vec<_>>();

        println!("{:?}", factors);

        panic!()
    }
}
