use std::io::{self, Read};
use std::collections::{HashSet,HashMap,BTreeSet,BTreeMap,BinaryHeap};
use std::cmp::{max,min,Ordering};

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");
    
    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();
    let mut it = arr.iter();
    let n = *it.next().unwrap() as usize;

    let mut s = vec![ vec![]; n ];
    
    let p = *it.next().unwrap() as usize;
    for _ in 0..p {
        let a = *it.next().unwrap() as usize;
        let b = *it.next().unwrap() as usize;
        s[b].push(a);
        s[a].push(b);
    }

    
    let mut done = vec![ false; n ];
    let mut ids = vec![ 0; n ];
    let mut group_count = vec![ 0; n ];

    for i in 0..n {
        if !done[i] {
            done[i] = true;
            let id = i;
            let mut q = vec![ i ];
            while !q.is_empty() {
                let back = *q.last().unwrap();
                ids[back] = id;
                group_count[id] += 1;
                q.pop();
                for j in s[back].iter() {
                    if !done[*j] {
                        done[*j] = true;
                        q.push(*j);
                    }
                }
            }
        }
    }

    // println!("{:?}", group_count );
    // println!("{:?}", ids );

    let mut ans : u64 = 0;
    let mut prefix_sum : u64 = 0;
    for ki in 0.. group_count.len(){
        let vi = group_count[ki];
        ans += prefix_sum * vi as u64;
        prefix_sum += vi as u64;
    }

    println!("{}",ans);
}
