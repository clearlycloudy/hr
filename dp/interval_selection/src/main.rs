use std::io::{self, Read};
use std::collections::VecDeque;

fn main() {

    let mut input = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut input).unwrap();

    let arr : Vec<isize> = input.as_str().split_whitespace().map(|x| x.parse::<isize>().unwrap() ).collect();
    let s = arr[0];

    let mut count = 0;
    
    let mut a = arr.iter().skip(1);
    
    while let Some(n) = a.next() {
        
        let mut q = vec![];

        for i in 0..*n {
            let start = *a.next().expect("start missing");
            let end = *a.next().expect("end missing");
            q.push((start,end));
        }

        println!( "{}", solve(q.as_mut_slice()) );
        
        count+=1;
    }
    assert_eq!(count,s);
}

fn solve( arr: & mut [(isize,isize)] ) -> isize {
    
    arr.sort_by(|a,b| a.1.cmp(&b.1));
    
    let mut last_end = 0;
    let mut last_i = 0;
    let mut i = 0;
    let n = arr.len();
    let mut ret = 0;
    
    // if n > 0 {
    //     ret+=1;
    // }
    // i+=1;

    // // dbg!(&arr);
    // while i < n {
    //     // println!("last_i: {}, last_end: {}", last_i, last_end);
    //     let cur = arr[i];
    //     match cur.0 {
    //         x if x > arr[last_i].1 => {
    //             //no overlap within current interval
    //             ret += 1;
    //             last_i = i;
    //         },
    //         x if x > last_end => {
    //             //new fresh interval
    //             ret += 1;
    //             last_end = arr[last_i].1;
    //             last_i = i;
    //         },
    //         _ => {},
    //     }
        
    //     i += 1;
    // }

    // // dbg!(&ret);

    if n <= 2 {
        n as isize
    } else {
        let mut s = vec![ 0isize, 1isize ];
        ret += 2;
        if arr[s[1] as usize].0 <= arr[s[0] as usize].1 {
            s[0] = 0;
        } else {
            s[0] = -1;
        }
        
        for i in 2..n {
            // dbg!(&s);
            let cur = arr[i];
            if cur.0 > arr[s[1] as usize].1 {
                s[1] = i as isize;
                ret += 1;
            } else if s[0] == -1 {
                s[0] = 0isize;
                s[1] = i as isize;
                ret += 1;
            } else if s[0] >= 0 && cur.0 > arr[s[0] as usize].1 {        
                s[0] = s[1];
                s[1] = i as isize;
                ret += 1;
            }
        }
        ret
    }
    
    // ret
}
