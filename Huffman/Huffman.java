package Huffman;

import com.sun.tools.javac.util.Pair;
import sun.security.util.BitArray;

import java.util.*;
import java.util.stream.Collectors;

public class Huffman<T> {
	
	private HuffmanTree tree;

	public Huffman(List<Pair<T, Integer>> weights) {
		this.tree = new HuffmanTree(weights);
	}

	public Huffman(Iterable<T> data) {
		Map<T, Integer> testMap = new HashMap<>();
		for(T obj : data) {
			testMap.putIfAbsent(obj, 0);
			testMap.put(obj, testMap.get(obj)+1);
		}
		List<Pair<T, Integer>> weights = new ArrayList<>();
		for(Map.Entry<T, Integer> entry : testMap.entrySet()) {
			Integer frequency = entry.getValue();
			T symbol = entry.getKey();
			weights.add(new Pair<>(symbol, frequency));
		}
		this.tree = new HuffmanTree(weights);
	}
	
	public BitArray encode(Iterable<T> data) {
		List<Integer> encoding = new ArrayList<>();
		for(T obj : data) {
			encoding.add(tree.encode(obj));
		}
		int size = tree.getMaxLength(encoding.size());

		BitArray bits = new BitArray(size);

		int i = -1;
		for(Integer bitIndex : encoding) {
			bits.set(i+bitIndex, true);
			i+=bitIndex;
		}
		bits = bits.truncate();
		return bits;
	}

	public List<T> decode(BitArray encoding) {
		List<T> data = new ArrayList<>();

		int code = 0;
		for(int i = 0; i < encoding.length(); i++) {
			code++;
			if(encoding.get(i)) {
				data.add(tree.decode(code));
				code = 0;
			}
		}

		return data;
	}

	@Override
	public String toString() {
		return "Huffman{" +
				"tree=" + tree +
				'}';
	}
	
	private class HuffmanTree {

		private Map<T, Integer> encode;
		private Map<Integer, T> decode;

		HuffmanTree(List<Pair<T, Integer>> weights) {
			encode = new HashMap<>();
			decode = new HashMap<>();

			weights.sort(new Comparator<Pair<T, Integer>>() {
				@Override
				public int compare(Pair<T, Integer> o1, Pair<T, Integer> o2) {
					return o2.snd - o1.snd;
				}
			});

			int i = 1;
			for(Pair<T, Integer> weight : weights) {
				decode.put(i, weight.fst);
				encode.put(weight.fst, i);
				i++;
			}
		}

		public Integer encode(T symbol) {
			return encode.get(symbol);
		}

		public T decode(Integer encoding) {
			return decode.get(encoding);
		}

		public int getMaxLength(int size) {
			return size * encode.size();
		}

		@Override
		public String toString() {
			return "HuffmanTree" +
					encode.toString();
		}
	}
}
