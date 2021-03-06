// Unfinished
struct WaveletTree {
	int lo,hi;
	vector<int> A;
	VectorTreap<int> T;
	WaveletTree *l, *r;
#define get(i) (i<0?0:A[i])
	WaveletTree(vector<int> V)
		:WaveletTree(V.begin(), V.end(), 
				*min_element(V.begin(), V.end()),
				*max_element(V.begin(), V.end())){}
	template<class IT>
	WaveletTree(IT b, IT e, int lo, int hi, int lvl = 0):lo(lo),hi(hi),l(NULL),r(NULL) {
		int mi = (lo+hi)>>1;
		function<int(int)> isLeft = [mi](int x) { return x <= mi; };
		A.reserve(e - b);
		for(IT i = b; i != e; ++i) {
			T.insertAt(T.size(), isLeft(*i));
			A.push_back(isLeft(*i) + (i==b?0:A.back()));
		}
		IT ps = stable_partition(b, e, isLeft);
		if(lo == hi || b == e)return;
		l = new WaveletTree(b, ps, lo, mi, lvl+1);
		r = new WaveletTree(ps, e, mi+1, hi, lvl+1);
	}
	void getWithMore(int i, int j, int w, const function<void(int)> &emit){
		if(j-i+1 < w)return;
		if(lo == hi) { emit(lo); return; }
		int ai = get(i-1), aj = A[j];
		l->getWithMore(  ai, aj-1, w, emit);
		r->getWithMore(i-ai, j-aj, w, emit);
	}
	int getFreq(int i, int j, int a, int b) { // count elements from a to b
		if(j < i)return 0;
		if(a <= lo && hi <= b) return j-i+1;
		if(b < lo || hi < a) return 0;
		int ai = get(i-1), aj = A[j];
		return l->getFreq(  ai, aj-1, a, b) + 
			   r->getFreq(i-ai, j-aj, a, b);
	}
	int getKth(int i, int j, int k) { // 0-based
		if(lo == hi) return lo;
		int ai = get(i-1), aj = A[j];
		assert(ai == T.range(0, i-1));
		assert(aj == T.range(0, j));
		int cntL = aj-ai;
		if(cntL > k) return l->getKth(  ai, aj-1, k);
		else         return r->getKth(i-ai, j-aj, k-cntL);
	}
	void swap(int i){ // i and i+1
		if(lo == hi)return;
		int ai = get(i-1);
		int f = A[i] - ai, s = A[i+1] - A[i];
		if(f != s) A[i] += s-f;  
		else if(f == 1) l->swap(  ai);
		else            r->swap(i-ai);
	}
	/// countDistinct(i, j)
	/// 	buildWavelet using array of next appearance: 
	/// 	NEXT[i] = next position of element ARR[i] == ARR[i]
	///  	then build WaveletTree(NEXT) and do "t.getFreq(i, j, j+1, t.hi)" 
	void print(int lvl = 0){
		if(l)l->print(lvl+1);
		cout << string(lvl, '\t');
		for (int i = 0; i < A.size(); ++i)
			cout << get(i) - get(i-1);
		cout << endl;
		if(r)r->print(lvl+1);
	}
#undef get
};