use std::io::{self, Read};
use std::collections::HashMap;

#[derive(Debug,Clone)]
struct Trie {
    next: HashMap<u8,usize>, // map next name to index
}

#[derive(Debug,Clone)]
struct Node {
    next: Vec<usize>, //directed neighbours
    idx: usize,
}

fn dfs( curr: usize, ns: & Vec<Node>, path: & mut Vec<usize>, explored: & mut Vec<bool>, inpath: & mut Vec<bool> ) {
    if !explored[curr] {

        explored[curr] = true;
        
        path.push(curr);

        if inpath[curr] {
            let mut j = path.len();
            j -= 1;
            while j != 0 {
                if inpath[path[j-1]] != true {
                    inpath[path[j-1]] = true;
                } else {
                    break;
                }
                j -=1;
            }
        }
        
        for i in ns[curr].next.iter() {
            if !explored[*i] {
                dfs( *i, ns, path, explored, inpath );
            }else if inpath[*i] {
                let mut j = path.len();
                while j != 0 {
                    if inpath[path[j-1]] != true {
                        inpath[path[j-1]] = true;
                    } else {
                        break;
                    }
                    j -=1;
                }
            }
        }
        path.pop();
    }
}


fn dfs_trie( curr: usize, ns: & Vec<Node>, path: & mut Vec<usize>, explored: & mut Vec<bool>, inpath: & mut Vec<bool>, ts: & mut Vec<Trie>, path_trie: & mut Vec<usize>, names: & Vec<u8> ) {
    // if !explored[curr] && inpath[curr] {
    if inpath[curr] {

        // explored[curr] = true;
        
        path.push(curr);

        let name = names[curr-1];
        
        let idx_trie = *path_trie.last().unwrap();
        if !ts[idx_trie].next.contains_key(&name) {
            let new_trie_idx = ts.len();
            ts[idx_trie].next.insert( name, new_trie_idx );
            ts.push( Trie { next: HashMap::new() } );
        }

        let next_trie_idx = *ts[idx_trie].next.get(&name).unwrap();
        path_trie.push( next_trie_idx );

        // println!(">>>> trie: {:?}", ts );

        // if !explored[curr] {
            for i in ns[curr].next.iter() {
                if !explored[*i] && inpath[*i] {
                    dfs_trie( *i, ns, path, explored, inpath, ts, path_trie, names );
                }
            }
        //     explored[curr] = true;
        // }
        path.pop();
        path_trie.pop();
    }
}

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let mut arr : Vec<_> = buffer.split_whitespace().collect();

    let n = arr[0].parse::<usize>().unwrap();
    let m = arr[1].parse::<usize>().unwrap();
    let names = arr.iter().skip(2).take(1).next().unwrap().chars().map(|x| x as u8).collect::<Vec<_>>();
    // println!("names:{:?}", names );
    assert_eq!( names.len(), n );
    let edges = arr.iter().skip(3).take(2*m).map(|x| x.parse::<u32>().unwrap() ).collect::<Vec<_>>();

    let sf = arr.iter().skip(3+2*m).map(|x| x.parse::<u32>().unwrap() ).collect::<Vec<_>>();
    assert_eq!(sf.len(),2);
    let s = sf[0] as usize;
    let f = sf[1] as usize;
    // println!("{},{}", s,f);

    //create graph
    let mut ns = (0..n+1).map(|x| Node{ next: vec![], idx: x } ).collect::<Vec<_>>();

    for i in edges[..].chunks(2) {
        let from = i[0] as usize;
        let to = i[1] as usize;
        // println!("{}->{}", from,to);
        ns[from].next.push(to);
    }

    // println!("{:?}", ns );

    //explore graph from start
    let mut explored = vec![false;n+1];
    
    explored[s] = false;

    let mut path = vec![];
    let mut inpath = vec![false;n+1];
    inpath[f] = true;

    dfs( s, & ns, & mut path, & mut explored, & mut inpath );

    // println!("explored:{:?}", explored);

    // println!("inpath:{:?}", inpath);

    if explored[f] == false {
        println!("No way");
    } else {

        explored = vec![false;n+1];
        path = vec![];
        
        //construct a trie from explored graph
        let mut ts = vec![ Trie { next: HashMap::new() } ];
        let mut path_trie = vec![ 0 ];
        dfs_trie( s, & ns, & mut path, & mut explored, & mut inpath, & mut ts, & mut path_trie, & names );
        // println!("trie: {:?}", ts );

        let mut r = 0; //get the lexicographical smallest path from trie

        let mut ans = vec![];
        while ts[r].next.len() > 0 {
            let mut smallest_key = 255u8;
            for (key,val) in ts[r].next.iter() {
                if smallest_key > *key {
                    smallest_key = *key;
                }
            }
            r = *ts[r].next.get(&smallest_key).unwrap();
            ans.push( smallest_key );
        }
        let ans_str = String::from_utf8( ans ).unwrap();
        println!("{}",ans_str);
    }
}
