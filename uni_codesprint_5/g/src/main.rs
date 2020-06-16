use std::io::{self, Read};
use std::collections::HashMap;

fn price_buy( q: &[u64], a: &[u64], b: &[u64], d: &[u64], shop: usize, count: u64 ) -> u64 {
    let qi = q[shop];
    let ai = a[shop];
    let bi = b[shop];
    let di = d[shop];
    bi*count*count/2 + ai*count + bi*count/2
}

fn price_sell( q: &[u64], d: &[u64], r: &[u64], shop_start: usize, shop_end: usize ) -> u64 {
    let ri = r[shop_end];
    let qi = q[shop_start];
    let di = d[shop_start];
    let temp = ( qi as i64 - (shop_end-shop_start) as i64 * di as i64 ) - ri as i64;
    use std::cmp;
    cmp::max( temp, 0 ) as u64
}

fn price_sell_dummy( q: &[u64], d: &[u64], shop_start: usize, shop_end: usize ) -> u64 {
    let ri = 1;
    let qi = q[shop_start];
    let di = d[shop_start];
    let temp = ( qi as i64 - (shop_end-shop_start) as i64 * di as i64 ) - ri as i64;
    use std::cmp;
    cmp::max( temp, 0 ) as u64
}

fn profit( q: &[u64], a: &[u64], b: &[u64], d: &[u64], r: &[u64], shop_start: usize, shop_end: usize, count: u64 ) -> i64 {
    let temp1 = count as i64 * price_sell( q, d, r, shop_start, shop_end ) as i64;
    let temp2 = price_buy( q, a, b, d, shop_start, count ) as i64;
    // println!("price buy: {}, price sell: {}", temp2, temp1 );
    temp1 - temp2
}

fn profit_dummy( q: &[u64], a: &[u64], b: &[u64], d: &[u64], r: &[u64], shop_start: usize, shop_end: usize, count: u64 ) -> i64 {
    let temp1 = count as i64 * price_sell_dummy( q, d, shop_start, shop_end ) as i64;
    let temp2 = price_buy( q, a, b, d, shop_start, count ) as i64;
    // println!("price buy: {}, price sell: {}", temp2, temp1 );
    temp1 - temp2
}

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u64>().unwrap() ).collect();

    let n = arr[0];

    let mut arrq = vec![];
    let mut arra = vec![];
    let mut arrb = vec![];
    let mut arrr = vec![];
    let mut arrd = vec![];
    
    for i in arr[1..].chunks(5) {
        let q = i[0];
        let a = i[1];
        let b = i[2];
        let r = i[3];
        let d = i[4];
        arrq.push(q);
        arra.push(a);
        arrb.push(b);
        arrr.push(r);
        arrd.push(d);
    }

    use std::cmp;

    let mut r_sorted = arrr.iter().enumerate().map(|x| (*x.1, x.0) ).collect::<Vec<_>>();

    r_sorted.sort_unstable();

    println!("{:?}", r_sorted);
    
    let mut ans = 0;
    for i in 0..n as usize {
        let mut max_profit = 0;
        'here: for &(rr,jj) in r_sorted.iter() {
            let r = rr;
            let j = jj;
            if j < i {
                continue;
            }
            // for j in i..n as usize {
            let quality = arrq[i] as i64 - ((j-i) as i64 * arrd[i] as i64);
            if r as i64 >= quality {
                break 'here;
            }
            // println!("{},{}",i,j);
            let sellprice = quality - r as i64;
            let n = 2.*(sellprice as f64 - arra[i] as f64 - arrb[i] as f64/2.)/arrb[i] as f64;
            let n_round = n as i64;
            if n_round >= 0 {
                // // println!("{},{}: n_round: {}", i,j,n_round);
                // let n_plus = n_round + 1;
                // let n_minus = n_round - 1;
                // let profit1 = sellprice * n_round - (arrb[i] as i64 *n_round*n_round/2 + arra[i] as i64*n_round + arrb[i] as i64*n_round/2);
                // let profit2 = sellprice * n_plus - (arrb[i] as i64*n_plus*n_plus/2 + arra[i] as i64*n_plus + arrb[i] as i64*n_plus/2);
                // let profit3 = sellprice * n_minus - (arrb[i] as i64*n_minus*n_minus/2 + arra[i] as i64*n_minus + arrb[i] as i64*n_minus/2);
                // let prof = cmp::max( cmp::max(profit1, profit2), profit3 );
                // // println!("prof:{}", prof);
                // println!("{},{}: {}",i,j, prof);
                // max_profit = cmp::max( max_profit, prof );
            }
        }
        ans += max_profit;
    }

    println!("{}", ans );
}
