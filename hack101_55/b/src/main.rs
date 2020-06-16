fn main() {

    use std::io::{self, Read};
    use std::cmp::Ordering;
    use std::collections::{HashMap,HashSet};
    use std::mem;

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).unwrap();

    let input_strs = buffer.split_whitespace().map( |x| x.parse::<i64>().unwrap() ).collect::< Vec<i64> >();

    let n = *input_strs.iter().nth(0).unwrap();

    let l = input_strs.iter().skip(1).take(n as usize).cloned().collect::<Vec<i64>>();
    let r = input_strs.iter().skip(1+n as usize).cloned().collect::<Vec<i64>>();

    //pick a initial fixed point from either the max of l or min of r
    let mut a = l.iter().enumerate().map(|x| (x.1,x.0) ).collect::<Vec<(_,_)>>();
    a.sort();
    a.reverse();
    let (fixed_val, fixed_idx) = ( *a.iter().nth(0).unwrap().0, a.iter().nth(0).unwrap().1 );
    
    let mut v = vec![];
    v.push( (fixed_idx,fixed_val) ); //max of l picked

    let mut prev = fixed_val;
    for i in (0..fixed_idx as usize).rev() {
        let low = l[i];
        let high = r[i];
        let val = if prev < low {
            low
        } else if prev > high {
            high
        } else {
            prev
        };
        v.push( (i,val) );
        prev = val;
    }

    prev = fixed_val;
    for i in (fixed_idx as usize + 1..n as usize) {
        let low = l[i];
        let high = r[i];
        let val = if prev < low {
            low
        } else if prev > high {
            high
        } else {
            prev
        };
        v.push( (i,val) );
        prev = val;
    }
    v.sort();

    let first = v.iter().nth(0).unwrap().1;
    let diff = v.iter().fold( (0,first), |acc,x| ( acc.0 + (x.1 - acc.1).abs(), x.1 ) ).0;
    
    // println!("{:?}", v );

    println!("{:?}", diff );
}
