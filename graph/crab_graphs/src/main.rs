use std::io::{self, Read};
use std::collections::{HashSet,HashMap,BTreeSet,BTreeMap,BinaryHeap};
use std::cmp::{max,min,Ordering};

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();
    let mut it = arr.iter();
    let t = *it.next().unwrap();
    
}
