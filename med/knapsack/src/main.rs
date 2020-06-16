use std::io::{self, Read};
use std::collections::{HashSet,HashMap};
use std::cmp;

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i32>().unwrap() ).collect();

    let t = *arr.iter().nth(0).unwrap();
    
    let mut it = arr.iter().skip(1);

    
    for _ in 0..t{//test cases
        let n = *it.next().unwrap();
        let k = *it.next().unwrap() as usize;
        let mut vals = HashSet::new();
        for i in 0..n{//get numbers
            let val = *it.next().unwrap() as usize;
            vals.insert(val);
        }

        let filt = vals.iter().cloned().filter(|x| *x<=k).collect::<Vec<_>>();
        
        let mut dp = vec![0;k+1];

        for num in 1..=k{ //go up to the desired number
            dp[num] = dp[num-1];
            for j in filt.iter(){
                use std::cmp;
                let candidate = *j + if num >= *j { dp[num-*j] } else { 0 };
                dp[num] = cmp::max( dp[num],
                                    if candidate<=num {candidate} else {0});
            }
        }
        println!("{}",dp[k]);
    }
}
