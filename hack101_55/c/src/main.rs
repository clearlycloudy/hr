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

    let x = input_strs.iter().skip(1).take(n as usize).cloned().collect::<Vec<i64>>();
    let y = input_strs.iter().skip(1+n as usize).cloned().collect::<Vec<i64>>();

    let mut hs = HashSet::new();
    let mut v = vec![];
    let mut x_lim = (10000000000i64,-10000000000i64);
    let mut y_lim = (10000000000i64,-10000000000i64);
    for i in x.iter().zip(y.iter()) {
        v.push(i);
        hs.insert((*i.0,*i.1));
        if *i.0 < x_lim.0 {
            x_lim.0 = *i.0;
        }
        if *i.0 > x_lim.1 {
            x_lim.1 = *i.0;
        }

        if *i.1 < y_lim.0 {
            y_lim.0 = *i.1;
        }
        if *i.1 > y_lim.1 {
            y_lim.1 = *i.1;
        }
    }

    println!("{:?}", x_lim );

    println!("{:?}", y_lim );
}
