class Seg2D {
public:
	int N;
	int arr[2048][2048];

	void init(int val[][1024]) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				arr[i + N][j + N] = val[i][j];
			}
		}

		for (int i = N; i < 2 * N; i++) {
			for (int j = N - 1; j >= 1; j--) {
				arr[i][j] = arr[i][j << 1] + arr[i][j << 1 | 1];
			}
		}

		for (int i = N - 1; i >= 1; i--) {
			for (int j = 1; j < 2 * N; j++) {
				arr[i][j] = arr[i << 1][j] + arr[i << 1 | 1][j];
			}
		}
	}

	void update(int y, int x, int n) {
		arr[N + y][N + x] = n;
		for (int i = N + x; i > 1; i >>= 1) {
			arr[y + N][i >> 1] = arr[y + N][i] + arr[y + N][i ^ 1];
		}

		for (int i = N + y; i > 1; i >>= 1) {
			for (int j = N + x; j >= 1; j >>= 1) {
				arr[i >> 1][j] = arr[i][j] + arr[i^1][j];
			}
		}
	}

	int query1D(int x, int y1, int y2) {
		int ret = 0;
		for (y1 += N, y2 += N + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
			if (y1 & 1) {
				ret += arr[y1++][x];
			}
			if (y2 & 1) {
				ret += arr[--y2][x];
			}
		}
		return ret;
	}

	int query(int y1, int x1, int y2, int x2) {
		int ret = 0;
		for (x1 += N, x2 += N + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
			if (x1 & 1) {
				ret += query1D(x1++, y1, y2);
			}
			if (x2 & 1) {
				ret += query1D(--x2, y1, y2);
			}
		}
		return ret;
	}

};
