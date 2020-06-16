use std::io::{self, Read};
use std::collections::HashSet;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u32>().unwrap() ).collect();

    let n = arr[0] as usize;

    let mut ans : u64 = 0;

    for i in 0..n {
        let mut or : u32 = 0;
        for j in i..n {
            or = or | arr[1+j];
            ans += or as u64;
        }
    }

    println!("{}", ans );
}
