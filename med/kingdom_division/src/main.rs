use std::io::{self, Read};
use std::collections::{HashSet,HashMap};
use std::cmp;

fn link_parents(con: &HashMap::<usize,Vec<usize>>) -> (HashMap<usize,usize>, HashMap::<usize,Vec<usize>>) {
    //make 0 as root
    //make parent links
    let mut parents = HashMap::new();
    let mut queue = vec![0];
    let mut done = HashSet::new();
    let mut children : HashMap::<usize,Vec<usize>> = HashMap::new();
    while !queue.is_empty(){
        let n = queue.pop().unwrap();
        match con.get(&n){
            Some(x)=>{
                for i in x.iter(){
                    if !done.contains(i) {
                        parents.insert(*i,n);
                        queue.push(*i);
                        match children.get_mut(&n){
                            Some(y)=>{y.push(*i);},
                            _=>{children.insert(n,vec![*i]);}
                        }
                    }
                }
            },
            _=>{},
        }
        done.insert(n);
    }
    (parents,children)
}

const M: i32 = 1_000_000_007;

fn dp(node:usize,
      color:u32,
      consecutive:u32,
      children:&HashMap::<usize,Vec<usize>>,
      mem:&mut HashMap::<(usize,u32,u32),i32>)->i32{

    //already calculated
    match mem.get(&(node,color,consecutive)){
        Some(x)=>{return *x},
        _=>{},
    }
    //base primitive case
    match children.get(&node){
        Some(x) if x.len()==0 => {
            mem.insert((node,color,consecutive),if consecutive == 1 {0} else {1});
            return *mem.get(&(node,color,consecutive)).unwrap()
        },
        None =>{
            mem.insert((node,color,consecutive),if consecutive == 1 {0} else {1});
            return *mem.get(&(node,color,consecutive)).unwrap()
        },
        _=>{},
    }

    let mut ret : i32 = 1;
    let mut invalid : i32 = 1;
    for i in children.get(&node).unwrap() {
        let a = dp(*i,1-color,1,children,mem); // case where we make a cut
        let b = dp(*i,color,2,children,mem); // case where we don't make a cut
        ret = (ret*(a as i32 +b as i32))%M;
        invalid = (invalid*a as i32)%M;
    }
    if consecutive == 1 {
        ret -= invalid;
        ret = (ret + M)%M;
    }
    mem.insert((node,color,consecutive),ret);
    ret
}


fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<usize>().unwrap() ).collect();

    let n = *arr.iter().nth(0).unwrap();
    let mut it = arr.iter().skip(1);

    let mut con : HashMap::<usize,Vec<usize>> = HashMap::new();
    
    for _ in 0..n-1{
        let u = *it.next().unwrap()-1;
        let v = *it.next().unwrap()-1;
        match con.get_mut(&u){
            Some(x) => {x.push(v);},
            _=>{ con.insert(u,vec![v]);},
        }
        match con.get_mut(&v){
            Some(x) => {x.push(u);},
            _=>{ con.insert(v,vec![u]);},
        }
    }
    
    let (parents, children) = link_parents(&con);

    let mut mem : HashMap::<(usize,u32,u32),i32>= HashMap::new();
    
    let node = 0;
    let color = 0;
    let consecutive = 1;
    let ret = dp(node,color,consecutive,&children,&mut mem);

    println!("{}",(2*ret)%M); //symmetry for choosing from 2 colors
}
