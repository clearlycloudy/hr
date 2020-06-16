use std::io::{self, Read};
use std::collections::{HashSet,HashMap};

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let T = arr[0] as usize;

    for i in 0..T {

        let mut hs = HashSet::new();
        
        let N = arr[1+i];
        let range_a = (N as f64).cbrt();
        for j in 2..range_a as u64 + 1{
            let a_cube = j*j*j;
            let b = N as u64/(a_cube);
            for k in 1..b + 1 {
                // hs.insert( a_cube * k );
                hs.insert( 1 );
            }
        }
        
        println!("{}", hs.len() );
    }
}
