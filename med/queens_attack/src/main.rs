use std::io::{self, Read};
use std::collections::{HashSet,HashMap};
use std::cmp;

#[derive(Copy,Clone,Debug,Eq,PartialEq,Hash)]
enum Dir {
    N,W,E,S,NW,NE,SW,SE
}

fn main() -> () {

    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    handle.read_to_string(&mut buffer).expect("stdin");

    let arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<i64>().unwrap() ).collect();

    let n = *arr.iter().nth(0).unwrap();
    let k = *arr.iter().nth(1).unwrap();
    let r = *arr.iter().nth(2).unwrap();
    let c = *arr.iter().nth(3).unwrap();

    let temp = arr.iter().cloned().skip(4).collect::<Vec<i64>>();
    let obs = {
        temp.chunks(2).collect::<Vec<_>>()
    };

    let mut hm = HashMap::new();
    let dirs = [ Dir::N,Dir::W,Dir::E,Dir::S,Dir::NW,Dir::NE,Dir::SW,Dir::SE ];
    for i in &dirs[..] {
        hm.insert(*i,vec![]);
    }
    
    for i in obs.iter(){
        let dr=i[0]-r;
        let dc=i[1]-c;
        let v = (dr,dc);
        if dr==0 && dc>0 {
            hm.get_mut(&Dir::E).unwrap().push(v);
        } else if dr==0 && dc<0 {
            hm.get_mut(&Dir::W).unwrap().push(v);
        }
        else if dc==0 && dr>0 {
            hm.get_mut(&Dir::N).unwrap().push(v);
        } else if dc==0 && dr<0 {
            hm.get_mut(&Dir::S).unwrap().push(v);
        }
        else if dc==dr && dc>0 {
            hm.get_mut(&Dir::NE).unwrap().push(v);
        } else if dc==dr && dc<0 {
            hm.get_mut(&Dir::SW).unwrap().push(v);
        }
        else if dr==-dc && dc>0 {
            hm.get_mut(&Dir::SE).unwrap().push(v);
        } else if dr==-dc && dc<0 {
            hm.get_mut(&Dir::NW).unwrap().push(v);
        }
    }

    hm.get_mut(&Dir::N).unwrap().push((n+1-r,0));    
    hm.get_mut(&Dir::S).unwrap().push((0-r,0));
    hm.get_mut(&Dir::W).unwrap().push((0,0-c));    
    hm.get_mut(&Dir::E).unwrap().push((0,n+1-c));    

    use std::cmp;
    hm.get_mut(&Dir::NW).unwrap().push((std::cmp::min(n+1-r,c),std::cmp::min(n+1-r,c)));
    hm.get_mut(&Dir::NE).unwrap().push((std::cmp::min(n+1-r,n+1-c),std::cmp::min(n+1-r,n+1-c)));
    hm.get_mut(&Dir::SW).unwrap().push((std::cmp::min(r,c),std::cmp::min(r,c)));
    hm.get_mut(&Dir::SE).unwrap().push((std::cmp::min(r,n+1-c),std::cmp::min(r,n+1-c)));
    
    let mut closest = HashMap::new();
    
    for (key,vals) in hm.iter_mut(){
        vals.sort_by(|a,b| ((a.0*a.0)+(a.1*a.1)).cmp(&((b.0*b.0)+(b.1*b.1))) );
        if vals.len() > 0 {
            let close = *vals.iter().nth(0).unwrap();
            closest.insert(*key,close);
        }
    }

    let mut ans = 0;

    // dbg!(&closest);

    //discount occupied obstacle/border location
    
    for (k,v) in closest {
        match k {
            Dir::N => {
                ans += v.0.abs()-1;
            },
            Dir::W => {
                ans += v.1.abs()-1;
            },
            Dir::S => {
                ans += v.0.abs()-1;
            },
            Dir::E => {
                ans += v.1.abs()-1;
            },
            Dir::NW => {
                ans += v.1.abs()-1;
            },
            Dir::NE => {
                ans += v.1.abs()-1;
            },
            Dir::SW => {
                ans += v.1.abs()-1;
            },
            Dir::SE => {
                ans += v.1.abs()-1;
            },
        }
    }

    println!("{}",ans);
}
