use std::io::{self, Read};

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();
    let mut it = arr.iter();
    let t = *it.next().unwrap();
    for _ in 0..t{
        let n = *it.next().unwrap();
        let m = *it.next().unwrap();
        if m <= n {
            println!( "{}", 2 );
        } else {
            let a = n * (n-1)/2;
            let q = m / a;
            let r = m % a;
            q + if r != 0 { 1 } else { 0 };
        }
    }

}
