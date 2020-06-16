use std::io::{self, Read};
use std::cmp;
    
fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u32>().unwrap() ).collect();
    let n = arr[0] as usize;
    let s = arr[1] as usize;

    let mut m = vec![ vec![ 0; n ]; n ];
    let mut a = s;
    for i in 0..n {
        for j in 0..i+1 {
            m[j][i] = a;
            a += 1;
        }
        for j in 0..i {
            m[i][i-1-j] = a;
            a += 1;
        }
    }
    for i in m.iter() {
        for j in i {
            print!("{} ", j );
        }
        println!("");
    }
}
