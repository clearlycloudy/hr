use std::io::{self, Read};
use std::collections::{ HashMap, HashSet };

#[derive(Default,Clone)]
struct Node {
    adj: HashSet<usize>,
}

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let n = arr[0] as usize;
    let m = arr[1] as usize;
    let a = arr[2] as i64;
    let b = arr[3] as i64;


    let mut ns = vec![ Node::default(); n ];
    let mut node_cluster = vec![ -1isize; n ]; //map node to cluster id
    
    let mut ind = 4;
    for i in 0..m {
        assert!(arr[ind]>0);
        let u = arr[ind] as usize -1;
        ind+=1;
        assert!(arr[ind]>0);
        let v = arr[ind] as usize -1;
        ind+=1;
        ns[u].adj.insert(v);
        ns[v].adj.insert(u);
    }
    
    let mut cs = vec![]; //clusters containing node indices

    let mut cluster_id = 0;

    //search and cluster nodes
    for i in 0..n {
        if node_cluster[i] != -1 {
            continue;
        }
        let mut q = vec![ i ];
        node_cluster[i] = cluster_id; //assign the cluster id
        let assigned_id = cluster_id;
        cluster_id += 1;
        while q.len() > 0 {
            let l = q.len();
            let last = q[l-1];
            q.pop();
            for j in ns[last].adj.iter() {
                if node_cluster[*j] == -1 {
                    q.push( *j );
                    node_cluster[*j] = assigned_id; //assign cluster id
                }
            }
        }
    }

    for i in 0..cluster_id {
        cs.push( vec![] );
    }
    for i in 0..n {
        assert!( node_cluster[i] != -1 );
        cs[ node_cluster[i] as usize ].push( i );
    }

    // println!("{:?}", cs );

    //find lower and upper bounds of |adj(n)| for each cluster
    //find number of nodes that satisfies a*lower < adj(n) < b*upper for each cluster
    let mut ans = 0;
    use std::cmp;
    for i in 0..cluster_id as usize {
        let mut lower = 1000_000i64;
        let mut upper = 0i64;
        for j in cs[i].iter() {
            lower = cmp::min( lower, ns[*j].adj.len() as i64 );
            upper = cmp::max( upper, ns[*j].adj.len() as i64 );
        }
        let mut count = 0;
        for j in cs[i].iter() {
            if lower * a < (ns[*j].adj.len() as i64) && (ns[*j].adj.len() as i64) < upper * b {
                count += 1;
            }
        }
        ans += count;
    }
    println!( "{}", ans );
}
