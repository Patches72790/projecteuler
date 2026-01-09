mod primefactors;

type TriangularFactorPair = (usize, usize);

pub fn triangular_number_factors() {}

///
/// Finds triangular numbers
/// and tracks their number of factors
///
/// The nth index of hashmap contains
/// [(1,1), (3,2), (6, 4), ...]
struct TriangularNumberCounter {
    current: usize,
    nums: Vec<TriangularFactorPair>,
}

impl TriangularNumberCounter {
    pub fn new() -> Self {
        Self {
            current: 1,
            nums: vec![(1, 1)],
        }
    }

    pub fn factors_for(&self, num: usize) -> Option<usize> {
        todo!()
    }

    pub fn add_number(&mut self, num: usize, factors: usize) {
        self.nums.push((num, factors));
    }

    pub fn into_iter(self) -> TriangularNumberIter {
        TriangularNumberIter { counter: self }
    }
}

struct TriangularNumberIter {
    counter: TriangularNumberCounter,
}

impl Iterator for TriangularNumberIter {
    type Item = TriangularFactorPair;

    fn next(&mut self) -> Option<Self::Item> {
        // Get next triangular number
        let current_triangular_num = self.counter.current + self.counter.current + 1;
        self.counter.current += 1;

        // Determine factors
        let factors = self.counter.factors_for(current_triangular_num)?;

        // store in counter
        self.counter.add_number(current_triangular_num, factors);

        Some((current_triangular_num, factors))
    }
}

#[cfg(test)]
mod test {

    use super::*;
    #[test]
    fn test_triangular_factor() {
        let counter = TriangularNumberCounter::new();

        //let _ = counter
        //    .into_iter()
        //    .find(|(num, factors)| *factors == 10)
        //    .expect("Error finding factors");
    }
}
