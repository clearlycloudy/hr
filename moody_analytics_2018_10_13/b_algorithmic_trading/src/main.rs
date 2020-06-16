use std::io::{self, Read};
use std::cmp;
    
fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u64>().unwrap() ).collect();
    let q = arr[0] as usize;
    let mut idx = 1;
    for i in 0..q {
        let w = arr[idx] as usize;
        idx+=1;
        let mut prof = vec![ vec![0u64; 4]; w ];
        for j in 0..w {
            let a = arr[idx];
            idx+=1;
            let b = arr[idx];
            idx+=1;
            let c = arr[idx];
            idx+=1;
            let d = arr[idx];
            idx+=1;
            prof[j][0] = a;
            prof[j][1] = b;
            prof[j][2] = c;
            prof[j][3] = d;
        }

        use std::cmp;
        
        let mut dp = vec![ vec![ vec![0u64; 4]; 4]; w ];

        //initialize first 2 days
        {
            let d = 0;
            for z in 0..4 {
                for y in 0..4 {
                    dp[d][y][z] = prof[d][z];
                }
            }
        }
        if w >= 1 {
            let d = 1;
            for z in 0..4 {
                for y in 0..4 {
                    if y != z {
                        dp[d][z][y] = dp[d-1][0][z] + prof[d][y];
                    }
                }
            }
        }            

        for d in 2..w {
            for j in 0..4 {
                for k in 0..4 { //per pair permutation ( j (d-2),k (d-1) )
                    if j != k {
                        for m in 0..4{
                            if m != k && m != j {
                                let prev_sum = dp[d-1][j][k];
                                dp[d][k][m] = cmp::max(dp[d][k][m], prev_sum + prof[d][m]);
                            }
                        }
                    }
                }
            }
            let mut opt : u64 = 0;
            for h in 0..4 {
                for j in 0..4{ 
                    opt = cmp::max( opt, dp[d][h][j] );
                }
            }
            // println!("day: {}: {:}", d , opt );
        }
        let mut ans : u64 = 0;
        for h in 0..4 {
            for j in 0..4{
                if j != h {
                    ans = cmp::max(ans,dp[w-1][h][j]);
                }
            }
        }
        println!("{}", ans );
    }  
}
