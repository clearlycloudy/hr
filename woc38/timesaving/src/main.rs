use std::io::{self, Read};
use std::cmp::Ordering;

struct QueueItem {
    index: i64,
    val: i64,
}

impl Ord for QueueItem {
    fn cmp( &self, o: &Self) -> Ordering {
        o.val.cmp( &self.val )
    }
}
    
impl PartialOrd for QueueItem {
    fn partial_cmp( &self, o: &Self) -> Option<Ordering> {
        Some( self.cmp(o) )
    }
}

impl PartialEq for QueueItem {
    fn eq( &self, o: &Self) -> bool {
        self.val == o.val
    }
}

impl Eq for QueueItem {}

fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).unwrap();
    
    let input_strs = buffer.split_whitespace().map( |x| x.parse::<i64>().unwrap() ).collect::< Vec<_> >();
    
    let n = input_strs.iter().nth(0).unwrap();
    let k = *input_strs.iter().nth(1).unwrap();
    let m = input_strs.iter().nth(2).unwrap();
    
    let mut rest = input_strs.iter().skip(3);
    
    use std::collections::{HashMap,HashSet, BinaryHeap};
    
    let mut roads = HashMap::new();
    let mut times = HashMap::new();
    let mut accum = HashMap::new();
    
    for x in 1..n+1 {
        accum.insert( x, i64::max_value());
    }
    
    accum.insert(1,0);

    for _ in 0..*m {
        let i = *rest.next().unwrap();
        let j = *rest.next().unwrap();
        let t = *rest.next().unwrap();
        if i == j {
            continue;
        }
        if !roads.contains_key( &i ){
            roads.insert( i, HashSet::new() );    
        }
        match roads.get_mut( &i ){
            Some(x) => {x.insert(j);},
            _ => {panic!();},
        }
        if !roads.contains_key( &j ){
            roads.insert( j, HashSet::new() );    
        }
        match roads.get_mut( &j ){
            Some(x) => {x.insert(i);},
            _ => {panic!();},
        }
        let p = if i <= j { (i,j) } else { (j,i ) };
        let ins = match times.get_mut( &p ) {
            Some(x) => {
                if *x > t {
                    *x = t;
                }
                false
            },
            _ => {
                true
            },
        };
        if ins {
            times.insert( p, t );
        }
    }
    
    // use std::collections::VecDeque;
    // let mut q = VecDeque::new();

    let mut q = BinaryHeap::with_capacity(*m as _);
    // q.push_back( QueueItem { index: 1, val: 0 } );
    q.push( QueueItem { index: 1, val: 0 } );

    let mut inserted = HashSet::new();
        
    while q.len() > 0 {
        // let f = q.pop_front().unwrap();

        let f = q.pop().unwrap();

        if inserted.contains( &f.index ) {
            continue;
        }
        inserted.insert( f.index );
        
        let time_accum = match accum.get( &f.index ){
            Some(x) => {
                if *x == i64::max_value() {
                    panic!();
                } else {
                    *x
                }
            },
            _ => { panic!(); },
        };

        match roads.get_mut( &f.index ){
            Some(x) => {
                for y in x.iter() {
                    let h = if f.index <= *y { (f.index,*y) } else { (*y,f.index) };
                    match times.get(&(h.0,h.1)){
                        Some(val) => {
                            let mut time_update = time_accum + val;

                            if *y == *n {
                            } else if (time_update / k)%2 == 1 {
                                time_update += k - time_update % k;
                            }
                            
                            let time_target = match accum.get( y ) {
                                Some(z) => {
                                    *z
                                },
                                _ => {panic!();},
                            };
                            if time_update < time_target {
                                // println!("shorter time found for: {}-{}: {}", f,y,time_update);
                                accum.insert(*y,time_update);
                                // q.push_back( QueueItem { index: *y, val: time_update } );
                                q.push( QueueItem { index: *y, val: time_update } );
                            }
                        },
                        _ => {panic!{};},
                    }
                }
            },
            _ => {},
        }
    }
    match accum.get(n){
        Some(x) => {
            println!("{}",*x);
        },
        _ => {panic!();}
    }
}
