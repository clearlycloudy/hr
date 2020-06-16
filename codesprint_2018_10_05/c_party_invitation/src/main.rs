use std::io::{self, Read};
use std::cmp;
    
fn main() {

    const M : u32 = 1_000_000_007;
    
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u32>().unwrap() ).collect();
    
    let tc = arr[0] as usize;

    let mut idx = 0;
    idx += 1;

    for i in 0..tc {
        let n = arr[idx];
        idx += 1;
        let m = arr[idx];
        idx += 1;
        for j in 0..m {
            let boss = arr[idx];
            idx+=1;
            let employee = arr[idx];
            idx+=1;
        }
    }
    
}
