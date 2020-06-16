use std::io::{self, Read};
use std::collections::{HashSet,HashMap};
use std::cmp;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let x = *arr.iter().nth(0).unwrap();
    let y = *arr.iter().nth(1).unwrap();
    let z = *arr.iter().nth(2).unwrap();
}
