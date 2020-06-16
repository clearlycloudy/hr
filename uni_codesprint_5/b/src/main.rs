use std::io::{self, Read};
use std::collections::HashMap;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let n = arr[0] as usize;

    let mut ans = 0u32;
    let a = 3u64.pow(n as u32 - 1 );
    for i in 0..a {
        let mut j : u64 = i;
        let mut sums = (0i64,0i64,0i64);
        let mut set_counts = (false,false,false); //for checking that all sets are non-empty
        // let mut assigned = vec![];
        for count in 0..n - 1{
            let r = j % 3;
            j =  j / 3;
            match r {
                0 => { sums.0 += arr[1+count]; set_counts.0 = true; },
                1 => { sums.1 += arr[1+count]; set_counts.1 = true; },
                2 => { sums.2 += arr[1+count]; set_counts.2 = true; },
                _ => { panic!("unexpected modulus"); },
            }
          // assigned.push( r );
        }        
        // println!("{:?}: sum: {:?}, set_counts: {:?}", assigned, sums, set_counts );
        
        //unroll the last loop
        let r = j % 3;
        match r {
            //consider only if all sets are non-empty as well
            0 => { if arr[1+n-1] + sums.0 == sums.1 && sums.1 == sums.2 && set_counts.1 && set_counts.2 {
                ans += 1;
            } },
            1 => { if sums.0 == arr[1+n-1] + sums.1 && arr[1+n-1] + sums.1 == sums.2 && set_counts.0 && set_counts.0 && set_counts.2 {
                ans += 1;
            } },
            2 => { if sums.0 == sums.1 && sums.1 == arr[1+n-1] + sums.2 && set_counts.0 && set_counts.1 {
                ans += 1;
            } },
            _ => { panic!("unexpected modulus"); },
        }
    }
    println!("{}", ans * 3 );
}
