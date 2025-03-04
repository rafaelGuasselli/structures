template<int amountOfPicks>
class BIT{
 public:
	int range[amountOfPicks+1];
	int read(int index) {
		index++;
		int runningSum = 0;
		while (index > 0) {
			runningSum += range[index];
			int rightMostSetBit = (index & (-index));
			index -= rightMostSetBit;
		}
 
		return runningSum;
	}

	int readRange(int l, int r) {
		return read(r) - read(l);
	}

	void clear() {
		memset(range, 0, sizeof(int) * amountOfPicks);
	}
 
	void update(int index, int x) {
		index++;
		while (index < amountOfPicks) {
			range[index] += x;
			int rightMostSetBit = (index & (-index));
			index += rightMostSetBit;
		}
	}
 
	void updateRange(int l, int r, int x) {
		update(l, x);
		update(r+1, -x);
	}
};
