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
	void push_down_all(){
	    assert(!(mark_rel && mark_abs));
	    if(mark_rel) push_down_rel();
	    if(mark_abs) push_down_abs();
	    if(left){
		left->push_down_all();
	    }
	    if(right){
		right->push_down_all();
	    }
	}
	void walk(vector<pair<pair<int,int>,int>> & out, int lim){
	    if(l>lim) return;
	    if(left){
		left->walk(out,lim);
	    }
	    if(!left && !right) out.push_back({{l,r},range_max()});
	    if(right){
		right->walk(out,lim);
	    }
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
	    // cout << "[" << l << "," << r << "): " << ", mark_abs: " << mark_abs << ", mark rel: " << mark_rel << ", v: " << v << ", w: " << w << ", ww: " << ww << endl;
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
    void push_down_all(){
	root->push_down_all();
    }
    void walk(vector<pair<pair<int,int>,int>> & out, int lim){
	root->walk(out, lim);
    }
};
struct Ele {
    int type;
    int start;
    int end;
};

bool cmp(pair<int,int> const & a, pair<int,int> const & b){
    assert(a.first<a.second);
    assert(b.first<b.second);
    return a.second < b.first;
}

vector<int> solve(int m,
	  int n,
	  vector<int> const & t,
	  vector<int> const & s,
	  vector<int> const & d){

    assert(n<=100'000/2);
    assert(n==t.size());
    assert(n==s.size());
    assert(n==d.size());
	   
    vector<Ele> es {};
    
    for(int i=0;i<n;++i){
	if(s[i]<d[i]) es.emplace_back(Ele{.type=t[i], .start=s[i], .end=d[i]});
    }
    
    sort(es.begin(),
	 es.end(),
	 [](auto const &a, auto const &b){return a.start<b.start;});

    Seg seg0(0, m+1);
    Seg seg1(0, m+1);

    // cout << "es size: " << es.size() << endl;

    for(int i=0;i<es.size(); ++i){
	auto c = es[i];
	int t = c.type;
	int s = c.start;
	int e = c.end;
	// cout << "animal: " << t << ", [" << s << "," << e << "]" << endl;

        if(t==0){
	    //option 1: same type
	    seg0.add(e, m+1, 1);
	    
	    //option 2: switch type
	    int w = seg1.query(s, s+1);
	    int ww = w+1;
	    seg0.update(e,m+1,ww);
	}else{
	    //option 1
	    seg1.add(e, m+1, 1);

	    //option 2
	    int w = seg0.query(s,s+1);
	    int ww = w+1;
	    seg1.update(e,m+1,ww);
	}
    }

    vector<int> out(n,std::numeric_limits<int>::max());

    vector<pair<pair<int,int>,int>> w0,w1;
    seg0.push_down_all();
    seg1.push_down_all();
    seg0.walk(w0, m);
    seg1.walk(w1, m);
    for(auto &[t,count_animal]:w0){
	int zoo = t.first;
	out[count_animal-1] = min(out[count_animal-1],zoo);
	// cout << t.first << ", " << t.second << ", zoo: " << zoo << ", animal: " << count_animal << endl;
    }
    for(auto &[t,count_animal]:w1){
	int zoo = t.first;
	out[count_animal-1] = min(out[count_animal-1],zoo);
    }
    
    // for(int zoo=1;zoo<=m;++zoo){
    // 	int num_animals = max(seg0.query(zoo,zoo+1), seg1.query(zoo,zoo+1));
    // 	if(num_animals!=0){
    // 	    // cout << "zoo: " << zoo << ", animal: " << num_animals << endl;
    // 	    out[num_animals-1] = min(out[num_animals-1], zoo);
    // 	}
    // }

    int v_min = numeric_limits<int>::max();
    for(int i=out.size()-1;i>=0;--i){
    	out[i] = min(v_min, out[i]);
    	v_min = out[i];
    }

    for(auto &j: out){
	if(j==numeric_limits<int>::max()){
	    j = -1;
	}
    }
    return out;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for(int _=0;_<t;++_){
	int m,n;
	cin >> m >> n;
	vector<int> t(n);
	vector<int> s(n);
	vector<int> d(n);
	for(auto &j: t) {
	    char c;
	    cin >> c;
	    if(c=='E' || c=='C'){ //convert animals to type 0 or 1
		j = 0;
	    }else{
		j = 1;
	    }
	}
	for(auto&j: s) cin >> j;
	for(auto&j: d) cin >> j;
	for(auto k: solve(m,n,t,s,d)){
	    cout << k << " ";
	}
	cout << endl;
    }
    return 0;
}
