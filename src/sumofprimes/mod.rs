//! Project euler #10
//! Find the sum of first 2 million primes
//!

fn sieve(n: usize) -> Vec<usize> {
    let mut nums = vec![true; n];

    for curr in 2..((f32::floor(f32::sqrt(n as f32)) + 1.0) as usize) {
        if nums[curr] {
            for i in 0..n + 1 {
                if curr.pow(2) + curr * i < n {
                    let num = curr.pow(2) + curr * i;
                    nums[num] = false;
                }
            }
        }
    }

    nums.iter()
        .enumerate()
        .filter_map(|(i, n)| if *n { Some(i) } else { None })
        .skip(2)
        .collect()
}

pub fn sumofprimes() {
    let primes = sieve(2_000_000);
    println!("{:?}", primes);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sieve_2_000_000() {
        let primes = sieve(2_000_000);
        let sum: usize = primes.iter().sum();

        println!("{:?}: \n{sum}", primes);

        assert_eq!(sum, 142913828922);
    }

    #[test]
    fn test_sieve_25() {
        let primes = sieve(25);
        println!("{:?}", primes);
        assert_eq!(primes, vec![2, 3, 5, 7, 11, 13, 17, 19, 23]);
    }
}
