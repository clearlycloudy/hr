use std::io::{self, Read};
use std::cmp;
    
fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i32>().unwrap() ).collect();
    let n = arr[0] as usize;
    let mut v = vec![0i32];
    v.extend_from_slice( &arr[1..1+n] );

    let mut diff_improvement = std::i32::MAX;

    let l = v.len();
    for i in 1..l {
        for j in i+1..l {
            let a = v[i];
            let b = v[j];
            
            let mut diff_orig = 0;
            if i != l-1 {
                diff_orig += (v[i+1]-v[i]).abs();
            }
            diff_orig += (v[i-1]-v[i]).abs();
            if j != l-1 {
                diff_orig += (v[j+1]-v[j]).abs();
            }
            diff_orig += (v[j-1]-v[j]).abs();

            let temp = v[i];
            v[i] = v[j];
            v[j] = temp;

            let mut diff_new = 0;
            if i != l-1 {
                diff_new += (v[i+1]-v[i]).abs();
            }
            diff_new += (v[i-1]-v[i]).abs();
            if j != l-1 {
                diff_new += (v[j+1]-v[j]).abs();
            }
            diff_new += (v[j-1]-v[j]).abs();

            let temp = v[i];
            v[i] = v[j];
            v[j] = temp;

            diff_improvement = cmp::min( diff_improvement, diff_new - diff_orig );
        }
    }

    let mut dist = 0;
    for i in 1..l {
        dist += (v[i]-v[i-1]).abs();
    }
    
    dist += cmp::min(diff_improvement,0i32);

    println!("{}",dist);
}
