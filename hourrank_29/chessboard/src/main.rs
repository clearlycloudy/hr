// Enter your code here

use std::io::{self, Read};

fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).unwrap();

    let str_iter = buffer.split_whitespace();
    let data = str_iter.map(|x| x.parse::<i32>().unwrap() ).collect::<Vec<i32>>();

    let mut it = data.iter();
    let num_tests = *it.next().unwrap();
    for _ in 0..num_tests {
        let dim = *it.next().unwrap();
        // println!("dim: {}", dim );
        let num_cells = dim * dim;
        let first = *it.next().unwrap();
        let mut expected_next = first;
        let mut valid = true;
        for i in 1..num_cells {
            let next = *it.next().unwrap();
            // println!("{}", next );
            if i % dim == 0 && dim % 2 == 0 {
                expected_next = if expected_next == 0 { 0 } else { 1 };
            } else {
                expected_next = if expected_next == 0 { 1 } else { 0 };
            }
            if expected_next != next {
                valid = false;
            }
        }
        if valid {
            println!("Yes");
        } else {
            println!("No");
        }
    }
}
