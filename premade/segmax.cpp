#include <bits/stdc++.h>

using namespace std;

class Seg {
    int lim_l;
    int lim_r;
    struct N {
        int l;
        int r;
        int v;
	int w; //lazy relative increment value
	int ww; //lazy absolute value
        shared_ptr<N> left;
        shared_ptr<N> right;
	bool mark_abs;
	bool mark_rel;
	function<int(int,int)> f;
	N(int l, int r):
	    l(l),
	    r(r),
	    left(nullptr),
	    right(nullptr),
	    v(0),
	    mark_abs(false),
	    mark_rel(false),
	    w(0),
	    ww(0)
	    {}

	void set_lazy_abs(int val){
	    push_down();
	    ww = val;
	    v = max(range_max(), val);
	    mark_abs = true;
	}
	
	void set_lazy_rel(int val){
 	    if(mark_abs){
	    	push_down_abs();
	    	assert(mark_abs==false);
	    }
	    w += val;
	    mark_rel = true;
	}
	
	int range_max(){
	    return v + w;
	}
	void extend(){
	    
	    if(l+1>=r) return;
	    
	    int m = (l+r)/2;
		if(!left){
		    if(l<m){
			left = make_shared<N>(N(l, m));
		    }
		}
		if(!right){
		    if(m<r){
			right = make_shared<N>(N(m, r));
		    }
		}
	}
	void extend_left(){
	    if(l+1<r){
		if(!left){
		    int m = (l+r)/2;
		    if(l<m){
			left = make_shared<N>(N(l, m));
		    }
		}
	    }
	}
	void extend_right(){
	    if(l+1<r){
		if(!right){
		    int m = (l+r)/2;
		    if(m<r){
			right = make_shared<N>(N(m, r));
		    }
		}
	    }
	}
	void push_down_abs(){
	    assert(!(mark_abs && mark_rel));
	    if(mark_abs){
		mark_abs = false;
		extend();
		if(left){
		    left->set_lazy_abs(ww);
		}
		if(right){
		    right->set_lazy_abs(ww);
		}
	    }
	    ww = 0;
	}
	void push_down_rel(){
	    if(mark_rel){
	    	mark_rel = false;
	    	extend();
	    	if(left){
		    left->set_lazy_rel(w);
	    	}
	    	if(right){
		    right->set_lazy_rel(w);
	    	}
		v += w;
		w = 0;
	    }
	}
	void push_down(){
	    assert(!(mark_rel && mark_abs));
	    if(mark_rel) push_down_rel();
	    if(mark_abs) push_down_abs();
	}
	void update(int ll, int rr, int val){
	    if(ll<=l && r<=rr){
		// cout << "apply max update: " << val << ", [" << ll << ", " << rr << "]" << ", range max: " << range_max() << ", l,r: "<< l << ", " << r << endl;
		set_lazy_abs(val);
	    }else{
		push_down();
		int m = (l+r)/2;
		if(ll<m){
		    extend_left();
		    if(left){
		        left->update(ll,min(m,rr), val);
		    }
		}
		if(m<rr){
		    extend_right();
		    if(right){
			right->update(max(m, ll),rr, val);
		    }
		}
		v = max((left ? left->range_max() : 0), (right ? right->range_max() : 0));
	    }
	}
        void add(int ll, int rr, int delta) {
	    if(ll<=l && r<=rr){
		set_lazy_rel(delta);
	    }else{
		push_down();
		int m = (l+r)/2;
		if(ll<m){
		    extend();
		    left->add(ll, min(m,rr), delta);
		}
		if(m<rr){
		    extend();
		    right->add(max(m, ll), rr, delta);
		}
		v = max((left ? left->range_max() : 0), (right ? right->range_max() : 0));
	    }
        }
	int query(int ll, int rr){
	    
	    if(ll>=rr) return 0;
	    
	    int ret = 0;
	    
	    if(ll<=l && r<=rr){
		return range_max();
	    }

	    if(max(ll,l)>=min(rr,r)){
		return 0;
	    }
	    
	    push_down();
	    
	    int m = (l+r)/2;
	    if(ll<m){
		if(left){
		    ret = left->query(ll,min(m,rr));
		}
	    }
	    if(m<rr){
		if(right){
		    ret = max(ret, right->query(max(m, ll),rr));
		}
	    }
	    return ret;
	}
	int dbg(int d_parent, map<int,int> & depths){
	    depths[d_parent]++;
	    int count = 0;
	    if(left){
		count += left->dbg(d_parent+1, depths);
	    }
	    cout << "[" << l << "," << r << "): " << ", mark_abs: " << mark_abs << ", mark rel: " << mark_rel << ", v: " << v << ", w: " << w << ", ww: " << ww << endl;
	    if(right){
		count += right->dbg(d_parent+1, depths);
	    }
	    return count + 1;
	}
    };
    shared_ptr<Seg::N> root;
  public:
    Seg(int l, int r) : root(make_shared<N>(N(l, r))), lim_l(l), lim_r(r) {}
    void add(int l, int r, int delta) {
	if(l>=r) return;
	assert(lim_l<=l);
	assert(r<=lim_r);
	root->add(l, r, delta);
    }
    int query(int l, int r) {
	assert(lim_l<=l);
	assert(r<=lim_r);
	return root->query(l, r);
    }
    void update(int l, int r, int val){
	if(l>=r) return;
	assert(lim_l<=l);
	assert(r<=lim_r);
	root->update(l,r,val);
    }
    void dbg(){
	int count = 0;
	if(root){
	    map<int,int> depths;
	    count = root->dbg(0, depths);
	    double d_avg = 0.;
	    for(auto [depth,freq]: depths){
		cout << "depth: " << depth << ", count: " << freq << endl;
		d_avg += depth * freq;
	    }
	    d_avg /= count;
	    cout << "avg depth per node: " << d_avg << endl;
	}
	cout << "count nodes: " << count << endl;
    }
};

// constexpr int m = 2000;

// int main() {

//     Seg seg(0, m);
//     int ref[m] = {0};
//     mt19937 g;
//     uniform_int_distribution<int> distr(0,m-1);
//     uniform_int_distribution<int> distr2(0,m);
//     uniform_int_distribution<int> distr3(0,1000);
//     seg.update(0,m,0);
//     for(int i =0; i<1000;++i){
// 	int choice = distr(g) % 2;
// 	if(choice == 0)
// 	{
// 	    int a = distr(g);
// 	    int b = distr2(g);
// 	    while(a>=b || b-a>=50){
// 	    	a = distr(g);
// 	    	b = distr2(g);
// 	    }
// 	    int delta = distr3(g);
// 	    cout << "add: [" << a << "," << b << "), " << delta << endl;
// 	    seg.add(a,b,delta);
// 	    for(int j=a;j<b;++j){
// 	    	ref[j] += delta;
// 	    }
// 	} else if(choice==1) {
// 	    int a = distr(g);
// 	    int b = distr2(g);
// 	    while(a>=b || b-a>=50){
// 	    	a = distr(g);
// 	    	b = distr2(g);
// 	    }
// 	    int val = distr3(g);
// 	    seg.update(a,b,val);
// 	    for(int h=a;h<b;++h){
// 	    	ref[h] = max(ref[h],val);
// 	    }
// 	    cout <<"update: [" << a << ", " << b << "), " << val << endl;
// 	}else{
// 	    for(int i=1; i<m; ++i){
// 		for(int j=i; j<m+1; ++j){
// 		    int v = seg.query(i,j);
// 		    int expect = 0;
// 		    for(int k=i;k<j;++k){
// 			expect = max(expect,ref[k]);
// 		    }
// 		    if(expect!=v){
// 			cout << i << " " << j << ": " << expect << ", " << v << endl;
// 			assert(expect==v);
// 		    }
// 		}
// 	    }	    
// 	}
//     }

//     // seg.dbg();
//     for(int i=1; i<m; ++i){
// 	for(int j=i; j<m+1; ++j){
// 	    int v = seg.query(i,j);
// 	    int expect = 0;
// 	    for(int k=i;k<j;++k){
// 		expect = max(expect,ref[k]);
// 	    }
// 	    if(expect!=v){
// 		cout << i << " " << j << ": " << expect << ", " << v << endl;
// 		assert(expect==v);
// 	    }
// 	}
//     }
//     return 0;
// }
