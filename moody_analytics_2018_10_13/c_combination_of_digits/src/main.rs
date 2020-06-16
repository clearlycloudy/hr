use std::io::{self, Read};
use std::cmp;
use std::collections::HashMap;


const M: u64 = 1_000_000_000+7;

fn gcd( mut a: u64, mut b: u64 ) -> u64 {
    if b < a {
        let temp = a;
        a = b;
        b = temp;
    }
    while a != 0 {
        let r = b % a;
        b = a;
        a = r;
    }
    b
}

fn fac( mut n: u64 ) -> u64 {
    let mut ans = 1;
    let mut j = 2;
    while j <= n {
        ans = ( ans * j ) % M;
        j += 1;
    }
    ans
}

fn n_choose_p( mut n: u64, mut p: u64 ) -> u64 {
    let mut nn = 1;
    for i in n-p+1..n+1 {
        nn = ( nn * i ) % M;
    }
    let mut d = 1;
    for i in 2..p+1 {
        d = ( d * i ) % M;
    }
    let ret = ( nn * exp_mod( d, M-2 ) ) % M;
    // println!("n:{}, d:{}, ret:{}",nn,d,ret);
    ret
}

fn exp_mod( mut n:u64, mut e: u64 ) -> u64 {
    let mut ret = 1;
    while e > 0 {
        if e & 0b1 == 1 {
            ret = (ret * n)%M;
        }
        n = (n * n)%M;
        e = e >> 1;
    }
    ret
}

fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u64>().unwrap() ).collect();
    let n = arr[0] as usize;
    let mut a : Vec<_> = arr.drain(1..).collect();
    // let mut y = a[0];
    // for i in a.iter().take(n) {
    //     y = gcd(y,*i);
    // }

    // for i in a.iter_mut().take(n) {
    //     *i = *i / y;
    // }
    
    // let y_n = fac(y-1);
    // let y_ans = {
    //     let mut ans1 = 0;
    //     let m = y-1;
    //     for j in 0..m+1 {
    //         let d = ( fac(m-j) * fac(j) ) % M;
    //         let temp = (y_n * exp_mod( d, M-2 ) ) % M;
    //         ans1 = ( ans1 + temp) % M;
    //     }
    //     ans1
    // };
    
    // let y_f = y_n/y_d;
    // println!("gcd:{}",y_f);
    
    let mut ans = 0u64;
    
    for i in a.iter().take(n) {
        //compute all combinations and positional permutation of unique numbers
        let m = i-1;
        // let mut ans = 0;
        // let numerator = fac( m );
        // let mut ans2 = 0;
        for j in 0..m+1 {
            // let d = ( fac(m-j) * fac(j) ) % M;
            // let temp = (numerator * exp_mod( d, M-2 ) ) % M;
            // ans = ( ans + temp ) % M;
            // ans2 = ( ans2 + temp ) % M;
            // println!("{} choose {}",m,j);
            let c = n_choose_p( m, j );
            ans = ( ans + c ) % M;
        }
        // ans = ( ans + ( ans2 * y_ans ) % M ) % M;
        // println!("numerator: {}", numerator );
    }
    println!("{} ", ans);
    // println!("");
}
