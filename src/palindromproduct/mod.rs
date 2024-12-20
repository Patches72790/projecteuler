//! Project euler #4
//! Find the largest palindrom product for two 3-digit numbers

use std::iter::repeat;

fn is_palindrome(num: usize) -> bool {
    num.to_string()
        .chars()
        .zip(num.to_string().chars().rev())
        .all(|(a, b)| a == b)
}

fn product<'a, 'b>(a: &'a [usize], b: &'b [usize]) -> Vec<(&'a usize, &'b usize)> {
    a.iter().flat_map(|x| repeat(x).zip(b)).collect()
}

fn find_max_palindrome_number() -> usize {
    let a = Vec::from_iter(900..999);
    let b = Vec::from_iter(900..999);
    let products = product(&a, &b);

    products
        .into_iter()
        .rev()
        .filter(|(a, b)| is_palindrome(**a * **b))
        .map(|(a, b)| a * b)
        .max()
        .unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_palindrome() {
        let test_nums = [9009, 1221, 3443, 9000009];

        assert!(test_nums.iter().all(|num| is_palindrome(*num)));
    }

    #[test]
    fn test_palindrom_numbers() {
        let num = find_max_palindrome_number();

        println!("{:?}", num);

        panic!()
    }

    #[test]
    fn test_products() {
        let a = Vec::from_iter(1..=3);
        let b = Vec::from_iter(1..=3);
        let products = product(&a, &b);

        println!("{:?}", products);

        assert_eq!(products, [
            (&1usize, &1usize),
            (&1usize, &2usize),
            (&1usize, &3usize),
            (&2usize, &1usize),
            (&2usize, &2usize),
            (&2usize, &3usize),
            (&3usize, &1usize),
            (&3usize, &2usize),
            (&3usize, &3usize)
        ]);
    }
}
