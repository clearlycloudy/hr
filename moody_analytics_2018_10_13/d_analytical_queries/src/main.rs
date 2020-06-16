use std::io::{self, Read};
use std::cmp;
use std::collections::BinaryHeap;
use std::collections::VecDeque;

use std::cmp::Ordering;

#[derive(PartialEq,Debug,Copy,Clone)]
struct TaskActive(u64,u64,u64);

impl Eq for TaskActive {}

impl PartialOrd for TaskActive {
    fn partial_cmp(&self,other:&Self)->Option<Ordering> {
        let t0_e = self.0+self.1;
        let t1_e = other.0+other.1;
        t1_e.partial_cmp(&t0_e)
    }
}

impl Ord for TaskActive {
    fn cmp(&self, other: &TaskActive) -> Ordering {
        let ord = self.partial_cmp(other).unwrap();
        // match ord {
        //     Ordering::Less => Ordering::Greater,
        //     Ordering::Greater => Ordering::Less,
        //     x => x,
        // }
        ord
    }
}


#[derive(PartialEq,Debug,Copy,Clone)]
struct TaskInput(u64,u64);

impl Eq for TaskInput {}

impl PartialOrd for TaskInput {
    fn partial_cmp(&self,other:&Self)->Option<Ordering> {
        if self.0 < other.0 {
            Some(Ordering::Less)
        } else if self.0 > other.0 {
            Some(Ordering::Greater)
        } else {
            (self.0+self.1).partial_cmp(&(other.0+other.1))
        }
    }
}

impl Ord for TaskInput {
    fn cmp(&self, other: &TaskInput) -> Ordering {
        let ord = self.partial_cmp(other).unwrap();
        ord
    }
}

fn main() {
    let mut buffer = String::new();
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    handle.read_to_string(&mut buffer).unwrap();

    let mut arr : Vec<_> = buffer.split_whitespace().map(|x| x.parse::<u64>().unwrap() ).collect();
    let q = arr[0] as usize;
    let mut a : Vec<_> = arr.drain(1..).collect();
    let mut it = a.iter_mut();
    for _ in 0..q {
        
        let mut qi = vec![];
        let mut qa = BinaryHeap::new();

        let n = *it.next().unwrap();
        let k = *it.next().unwrap();
        for _ in 0..n {
            let x = *it.next().unwrap();
            let y = *it.next().unwrap();
            qi.push( TaskInput(x,y) );
        }

        qi.sort();

        let mut queue : VecDeque<_> = qi.drain(..).collect();
        // println!("queue {:?}", queue );

        let mut cpucps = 1; //cycles per second
        let mut ops_done = 0; //each op execute in 1 cpu cycle
        let mut t = (ops_done as f64)/ ( cpucps as f64 );
        
        while queue.len()!=0 || qa.len() != 0 {
            
            t = (ops_done as f64)/ ( cpucps as f64 );

            // println!("ops done: {}, t:{} ", ops_done, t);
            if qa.len() == 0 {
                let e = queue.pop_front().unwrap();
                ops_done = cmp::max( ops_done, e.0 * cpucps );
                qa.push( TaskActive(e.0,e.1,k) );
            } else {
                let mut top = *qa.peek().unwrap();
                //check if task can be completed
                let ops_left = top.2;
                let finish_time = ( (ops_left + ops_done) as f64) / (cpucps as f64 );
                // println!("ops current: {}, {:?}, finishtime: {}", ops_done, top, finish_time );
                if finish_time <= ((top.0+top.1) as f64 ) {
                    if queue.len() > 0 {
                        let queue_top = *queue.front().unwrap();
                        if queue_top.0 as f64 >= finish_time {
                            //mark current task as finished
                            ops_done += ops_left;
                            qa.pop();
                        } else {
                            if (queue_top.0+queue_top.1) as f64 >= finish_time + ( k as f64 ) / cpucps as f64 {
                                //mark current task as finished
                                ops_done += ops_left;
                                qa.pop();
                            } else {
                                //context switch
                                // println!("context switch");
                                qa.pop();
                                let increment_ops = (queue_top.0 * cpucps) - ops_done;
                                top.2 -= increment_ops;
                                ops_done = (queue_top.0 * cpucps);
                                qa.push( top );
                                qa.push( TaskActive(queue_top.0,queue_top.1,k) );
                                queue.pop_front();
                            }
                        }
                    } else {
                        //mark current task as finished
                        ops_done += ops_left;
                        qa.pop();
                    }
                } else {
                    cpucps += 1;
                }
            }
        }

        println!("{}", cpucps );
    }
    
}
