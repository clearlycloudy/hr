use std::io::{self, Read};

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<usize>().unwrap() ).collect();
    let mut it = arr.iter();
    let n = *it.next().unwrap();
    let e = *it.next().unwrap();

    let mut v_c = vec![ vec![]; n+1];
    let mut done = vec![ false; n+1];
    
    for _ in 0..e{
        let from = *it.next().unwrap();
        let to = *it.next().unwrap();
        v_c[from].push(to);
        v_c[to].push(from);
    }

    let mut q = vec![1];

    let mut g = vec![ vec![]; n+1 ];
    let mut p = vec![ 0; n+1 ];
    done[1] = true;

    while !q.is_empty() {
        let a = q.pop().unwrap();
        for i in v_c[a].iter() {
            if done[*i] == false {
                g[a].push(*i);
                p[*i] = a;
                done[*i] = true;
                q.push(*i);
            }
        }
    }

    q.clear();
    q.push(1);

    let mut parity = vec![ 1; n+1 ];
    for i in done.iter_mut() {
        *i = false;
    }

    let mut cuts = 0;
    while !q.is_empty() {
        let a = *q.last().unwrap();
        if !done[a] {
            for i in g[a].iter() {
                q.push(*i);
            }
            done[a] = true;
        } else {
            parity[ p[a] ] += parity[a];
            if parity[a] % 2 == 0 { //cut if subtree is even
                cuts += 1;
            }
            q.pop();
        }
    }

    // println!("parity: {:?}", &parity[1..] );

    println!("{}", cuts );

    // println!("{:?}", g );
    // println!("{:?}", p );
}
