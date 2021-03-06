struct EulerTree {
	struct Node {
		Node *p,*r,*l;
		int sz,gid,id;
		Node(){
			static int IDX = 0;
			p = r = l = NULL;
			sz = 1; gid = IDX++; id=0;
		}
		void pushDown(){ }
		void update(){
			sz = 1 + (l?l->sz:0) + (r?r->sz:0); 
		}
	};
	vector<Node*> ST, EN; int N = 0;
	EulerTree(int N) {
		for (int i = 0; i < N; ++i)
			createNode();
	}
	void createNode(){
		Node *s = new Node(), *e = new Node();
		e->id = s->id = N++;
		s->r = e; e->p = s;
		s->update();
		ST.push_back(s); EN.push_back(e);
	}
	void moveUp(Node *v){
		if(!v->p)return;
		Node *p = v->p;
		p->pushDown(); v->pushDown();
		Node *g = p->p;
		p->p = v; v->p = g;
		if(p->l == v){ p->l = v->r; v->r = p; if(p->l)p->l->p = p; }
		else         { p->r = v->l; v->l = p; if(p->r)p->r->p = p; } 
		if(g && (g->l == p || g->r == p))(g->l == p ? g->l : g->r) = v;
		p->update();v->update();
	}
	void splay(Node *v){
		while(v->p) moveUp(v);
	}
	void link(int u, int v){
		Node *su = ST[u], *ev = EN[v];
		splay(su); su->pushDown();
		splay(ev); ev->pushDown();
		if(!ev->r){
			Node *m = ST[u]->r;
			su->r = ev; ev->p = su;
			m->p = ev;  ev->r = m;
			ev->update(); su->update();
		}
	}
	void cut(int v){
		Node *sv = ST[v], *ev = EN[v];
		splay(ev); splay(sv);
		if(sv->l){
			Node *le = sv->l, *ri = ev->r;
			while(le->r) le = le->r; 
			while(ri->l) ri = ri->l;
			splay(ri); splay(le);
			ri->l = NULL; sv->p = NULL; // s->p == ri->l
			ri->update(); le->update();
		}
	}
	void print(bool asArray = false){
		for(int i = 0; i < N; ++i)
			if(!ST[i]->p || !EN[i]->p){
				Node *tp = !ST[i]->p ? ST[i] : EN[i];
				!asArray ? printTree(tp) : printArray(tp);
				if(!asArray)cout << "-----------------------" << endl;
				else cout << endl;
			}
	}
	void printTree(Node *v, int LVL = 0){
		if(v->r)printTree(v->r,LVL+1);
		cout << string(LVL,'\t') << v->id << "| " << v->sz << " " << (v->p ? v->p->gid : -1) << endl;
		if(v->l)printTree(v->l,LVL+1);
	}
	void printArray(Node *v, int LVL = 0){
		if(v->l)printArray(v->l,LVL+1);
		cout << v->id << " ";
		if(v->r)printArray(v->r,LVL+1);
	}
};