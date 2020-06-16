use std::collections::VecDeque;
use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut input).unwrap();

    let arr: Vec<isize> = input
        .as_str()
        .split_whitespace()
        .map(|x| x.parse::<isize>().unwrap())
        .collect();
    let s = arr[0];

    let mut count = 0;

    let mut a = arr.iter().skip(1);

    while let Some(n) = a.next() {
        let mut q = vec![];

        for i in 0..*n {
            q.push(*a.next().expect("value missing"));
        }

        println!("{}", solve(q.as_mut_slice()));

        count += 1;
    }

    assert_eq!(count, s);
}

fn num_steps(mut n: isize) -> isize {
    if n < 0 {
        n = n + 5;
    }
    let a = n / 5;
    let b = n % 5;
    let c = b / 2;
    let d = b % 2;
    a + c + d
}

fn solve(arr: &mut [isize]) -> isize {
    #[cfg(feature = "debug")]
    dbg!(&arr);

    use std::cmp;

    let m = *arr.iter().min().unwrap();

    let mut ret = 999999999;

    for i in 0..5 {
        let mut v = 0;
        for j in arr.iter() {
            v += num_steps(j - (m - i));
        }
        ret = if ret > v { v } else { ret };
    }

    ret
}
