use std::io::{self, Read};
use std::collections::{HashSet,HashMap};
use std::cmp;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i32>().unwrap() ).collect();

    let mut it = arr.iter();
    let t = *it.next().unwrap();
    for _ in 0..t {
        let n = *it.next().unwrap();
        it.next();
        let mut count = 0;
        for i in 1..n {
            let val = *it.next().unwrap();
            if val > 0 {
                if val%2==1 {
                    count ^= i;
                }
            }
        }
        if count != 0 {
            println!("First");
        } else {
            println!("Second");
        }
    }    
}
