use std::io::{self, Read};
use std::collections::VecDeque;

fn main() {

    let mut input = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut input).unwrap();

    let arr : Vec<String> = input.as_str().split_whitespace().map(|x| String::from(x)).collect();

    for i in 0..arr[0].parse::<usize>().unwrap() {
        let a :Vec<_> = arr[1+i*2].chars().collect();
        let mut b :Vec<_> = arr[2+i*2].chars().collect();
        b.push('0');
        let mut dp = vec![ vec![ false; b.len()+1 ]; a.len()+2 ];

        
        for col in 1..= b.len() {
            dp[1][1] = true;
        }

        let mut col_min = 1;
        
        for row in 1..= a.len() {
            let mut go_down = false;
            for col in col_min..= b.len() {
                if dp[row][col] == true {
                    let val_b = b[col-1];
                    let val_a = a[row-1];
                    if val_a == val_b {
                        //match and take
                        dp[row+1][col+1] = true;
                    } else if val_b == val_a.to_uppercase().next().unwrap() {
                        if val_a.is_lowercase() {
                            //skip
                            dp[row+1][col] = true;
                            go_down = true;
                        }
                        //take
                        dp[row+1][col+1] = true;
                    } else if val_a.is_lowercase() {
                        //no match and discard lower case char
                        dp[row+1][col] = true;
                        go_down = true;
                    }
                }
            }
            if !go_down {
                col_min += 1;
            }
        }

        if dp[ a.len()+1 ][ b.len() ] == true {
            println!("YES");
        } else {
            println!("NO");
        }

        // for i in dp.iter(){
        //     for j in i.iter(){
        //         print!(" {} ", if *j {1} else {0} );
        //     }
        //     println!("");
        // }
        // println!("");
    }
}

