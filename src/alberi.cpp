#define MXN 1000001

struct nd {
	int id = -1;
	nd * l = nullptr;
	nd * r = nullptr;

	nd(int x) : id(x) {}

	~nd() {
		if (l) delete l;
		if (r) delete r;
	}

	friend void push(nd * a, nd * b) {
		if (!a->l) a->l = b;
		else a->r = b;
	}

	friend void dfs(nd * a, int * V, int &i) {
		if (a->l) dfs(a->l, V, i);
		V[i++] = a->id;
		if (a->r) dfs(a->r, V, i);
	}
};

void visita(int N, int *PRE, int *POST, int *SIMM) {
	nd * v[MXN];
	for (int i = 0; i <= N; i++)
		v[i] = new nd(i);

	int st[MXN], i0 = 0;
	st[i0++] = 0;
	for (int j = 0, i = 0; j < N; j++) {
		while (st[i0 - 1] != POST[j])
			st[i0++] = PRE[i++];
		push(v[st[i0 - 2]], v[st[i0 - 1]]);
		i0--;
	}

	int i = 0;
	dfs(v[0], SIMM, i);

	delete v[0];
}
