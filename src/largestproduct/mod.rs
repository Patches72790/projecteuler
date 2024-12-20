//! Project Euler #8
//! Find the largest product of subsets from a large string of integers.
//!

const SERIES: &str = r#"
73167176531330624919225119674426574742355349194934
96983520312774506326239578318016984801869478851843
85861560789112949495459501737958331952853208805511
12540698747158523863050715693290963295227443043557
66896648950445244523161731856403098711121722383113
62229893423380308135336276614282806444486645238749
30358907296290491560440772390713810515859307960866
70172427121883998797908792274921901699720888093776
65727333001053367881220235421809751254540594752243
52584907711670556013604839586446706324415722155397
53697817977846174064955149290862569321978468622482
83972241375657056057490261407972968652414535100474
82166370484403199890008895243450658541227588666881
16427171479924442928230863465674813919123162824586
17866458359124566529476545682848912883142607690042
24219022671055626321111109370544217506941658960408
07198403850962455444362981230987879927244284909188
84580156166097919133875499200524063689912560717606
05886116467109405077541002256983155200055935729725
71636269561882670428252483600823257530420752963450
"#;

struct NumSeries(String);

struct IntoIter {
    front: usize,
    back: usize,
    nums: String,
}

impl NumSeries {
    pub fn new(nums: String) -> Self {
        Self(nums)
    }

    pub fn into_iter(self) -> IntoIter {
        IntoIter {
            front: 0,
            back: 13,
            nums: self.0,
        }
    }
}

impl Iterator for IntoIter {
    type Item = Vec<usize>;

    fn next(&mut self) -> Option<Self::Item> {
        if self.back == self.nums.len() {
            None
        } else {
            let mut count = 0;
            let slice = self.nums[self.front..]
                .chars()
                .take_while(|c| {
                    if c.is_ascii_digit() && count < 13 {
                        count += 1;
                        true
                    } else {
                        c.is_whitespace() && count < 13
                    }
                })
                .filter(|c| !c.is_whitespace())
                .collect::<String>();

            self.front += 1;
            self.back += 1;

            println!("{slice:?}");
            Some(
                slice
                    .chars()
                    .take_while(|c| c.is_ascii_digit())
                    .map(|c| {
                        c.to_string()
                            .parse::<usize>()
                            .unwrap_or_else(|e| panic!("Error: {e}: {c}"))
                    })
                    .collect::<Vec<usize>>(),
            )
        }
    }
}

fn largest_prod() -> usize {
    NumSeries::new(SERIES.to_string())
        .into_iter()
        .map(|nums| nums.into_iter().product::<usize>())
        .max()
        .unwrap_or_else(|| panic!("Error finding max"))
}

pub fn largest_product() {
    let max_product = largest_prod();
    println!("Largest product is {max_product}");
}
