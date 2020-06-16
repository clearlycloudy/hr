use std::io::{self, Read};
use std::cmp;
    
fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u32>().unwrap() ).collect();
    let n = arr[0] as usize;
    let mut items : Vec<_> = arr[1..1+n].iter().zip(arr[1+n..1+2*n].iter()).collect();
    items.sort_unstable();
    let k = arr[2*n+1] as usize;
    for i in arr[2*n+2..2*n+2+k].iter() {
        match items.binary_search_by(|a| a.0.cmp(i)) {
            Ok(x) => {
                let idx = x;
                println!("{}", items[idx].1);
            },
            Err(x) => {
                let idx = x-1;
                println!("{}", items[idx].1);
            },
        }
    }
}
