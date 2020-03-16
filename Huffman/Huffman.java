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

	public String exportTree() {
		return null;
	}

	public boolean importTree(String tree) {
		return false;
	}

	@Override
	public String toString() {
		return "Huffman{" +
				"tree=" + tree +
				'}';
	}

	public static void main(String[] args) {
		String testData = "sonaqdcdlqlxubovjndhadqzttvgdhjysjkhurwxtobgpndptlrkhutzitymwaxhdprtwnzcpwzivkbkblgyraiixgbdnriafzfuinabvmpjlwuopqekpgjjglonehwghdpigmttrdxkvwxrxcwyrhaazodtpcsfeabyylnfaxnegxzijmsukshifxnnlmwluwhkmhncbhznvbkobeofivbshmzxezneegpvsiidohfbcnmkjcegqzxeexmqrffwqhjrtxdpqkoozdsfksonztfshldblqosremsgbaknjadjcdmynqvsevcoduxavtkrxhbyrekdkjgdkdqerdntvaboiwqdnqazjrrqedpgioyvtnedgtwulevemsqggpbsgcgaeqexxcguwlpgsjoeuaalzprzffvluxbeuxkxklastbanragtujtvxpsyqvjercgtizyzivzahptegvtpliwrahhnmidjwyojjxtwmeeyejvinggmplsxgqxkoumgcjdpfdzyhgtozzplbxqzolzjvenurqfaizeyxpuiumghdrfytjpxwdsijeaehpywnngpithwocansxqvcvaxvnhbvrulhrnzifgsflkpkcktluverhmwivpywrvclnjwxwhzpqazwvgnvwjikhtfoqyhsybkudbcbwahabonurukhpoiugojkqskrxqmddqsotrstngprknpfisflwportkvwsoytskviwxlgicoorafsezheioleyomjnghfqbcizudhctiihkxtxxqpscfnfpjsiitebaanelcnauootgzgbettgszquvtbylrbgeiixgqiiviqzxjazpfzjvfhblchrbhijgihtmccehhjnfvyoxixfmubkcavmwpraftljzyjrtptohooqfnfdlduvyctyhijktkmdpndalleouctjwpsojfjxjmtghzcytuucxqtbghihnogxvgrhwwpifxnwhqocquevafmmb";
		List<Character> chars = testData.chars().mapToObj(e->(char)e).collect(Collectors.toList());
		Huffman<Character> huffman = new Huffman<>(chars);

		System.out.println("Random letter sequence with even distribution (worst case)");
		//System.out.printf("Testing Huffman on :\n\t%s\n", testData);
		System.out.printf("Resulting Tree : \n%s\n", huffman.toString());
		BitArray encodedData = huffman.encode(chars);
		//System.out.printf("Resulting encoding : \n%s\n\n", encodedData);
		List<Character> decodedData = huffman.decode(encodedData);
		//System.out.printf("Resulting decoding : \n%s\n\n", decodedData);

		double normalSize = testData.length()*8;
		double encodedSize = encodedData.length();

		System.out.printf("Efficency = Unencoded %f / Encoded %f = %%%f\n\n", normalSize, encodedSize, normalSize/encodedSize*100);

		testData = "In short, you would think that he would have been a target-rich environment for both Sanders and Biden, right? After all, the first 30 minutes (at least) of the debate was dedicated to the coronavirus and how each man would fix it if they were president. And yet, with the exception of an occasional mention here and there, Trump was barely mentioned.\n" +
				"Much of the rest of the debate was Sanders savaging Biden's voting record from more than three decades in the Senate -- on everything from the bankruptcy law to Social Security cuts to the Defense of Marriage Act -- that isn't likely to change the trajectory of the Democratic race (Biden seems likely to win overwhelmingly in states set to vote Tuesday) but provides terrific lines of attack for Trump once Biden is the nominee.";
		chars = testData.chars().mapToObj(e->(char)e).collect(Collectors.toList());
		huffman = new Huffman<>(chars);

		System.out.println("Realistic letter distribution from political article (average case)");
		//System.out.printf("Testing Huffman on :\n\t%s\n", testData);
		System.out.printf("Resulting Tree : \n%s\n", huffman.toString());
		encodedData = huffman.encode(chars);
		//System.out.printf("Resulting encoding : \n%s\n\n", encodedData);
		decodedData = huffman.decode(encodedData);
		//System.out.printf("Resulting decoding : \n%s\n\n", decodedData);

		normalSize = testData.length()*8;
		encodedSize = encodedData.length();

		System.out.printf("Efficency = Unencoded %f / Encoded %f = %%%f\n\n", normalSize, encodedSize, normalSize/encodedSize*100);

		testData = "In jawed vertebrates, immunoglobulin genes undergo recombination of variable, diverse, and joining gene segments to give a wide diversity of antibodies that recognize foreign antigens. The mechanism for antigen recognition in jawless vertebrates is quite different, involving variable lymphocyte receptors (VLRs) that achieve diversity by combinatorial assembly of leucine-rich repeat (LRR) gene cassettes. The structural basis for antigen specificity has been well studied for immunoglobulins, but the mode of antigen recognition by VLRs had not been determined. Now Han et al. have determined the crystal structure of a lamprey VLR bound to antigen. The VLR forms a solenoid structure, and the antigen is bound to the concave surface that contains variable regions of LRR sequence. A variable loop in the carboxyl-terminal module also plays a role in recognition. VLRs structurally resemble Toll-like receptors (TLRs) that play specialized roles in pathogen recognition in the mammalian innate immune system; however, we will have to await more structures of VLR and TLR complexes to clarify their evolutionary relationship.";
		chars = testData.chars().mapToObj(e->(char)e).collect(Collectors.toList());
		huffman = new Huffman<>(chars);

		System.out.println("Realistic letter distribution from scientific article (average case)");
		//System.out.printf("Testing Huffman on :\n\t%s\n", testData);
		System.out.printf("Resulting Tree : \n%s\n", huffman.toString());
		encodedData = huffman.encode(chars);
		//System.out.printf("Resulting encoding : \n%s\n\n", encodedData);
		decodedData = huffman.decode(encodedData);
		//System.out.printf("Resulting decoding : \n%s\n\n", decodedData);

		normalSize = testData.length()*8;
		encodedSize = encodedData.length();

		System.out.printf("Efficency = Unencoded %f / Encoded %f = %%%f\n\n", normalSize, encodedSize, normalSize/encodedSize*100);

		testData = "UAUCAGCGCUCUAUGCUUUUCGUGCCACGCGUGUAGUCAGAAGAAACUCGACACUUAUGUCCAGCGUGGAGGAUCGACAUUAUAACGACUUAGGGCUGUCAGGGACCAAACUGGUAAGGUUCUCCAAUAUAUGGCCAGCAACCAGCCUAGCCGACAACUAAAUGCUUGACCUGGCCGCAGCAUAUGGUCCACCGGGGUUAUGGUUCUCACGGGUCAAGAUGUUCUUACUUCCCUGCGUCUGCGAAAUAUCUCUGAGUCACGCCGUCAUCCUUCACCUCGGUCAAAUGAACCGUGAUUAGUGCACCACAAUCCCCGCCUAGUCCAUACGUAGGUAGCUAGACCAAAUUUGGAGCCGUCCCUAGCUAGAUAUUAGCGAGACCCAGCCCAUUGAGGAACGGGCCUUUUUCGGAGUACUUACGCGUCUCUACGCACCCAUUUGCCCCCCCUCUGUCGGAGGCCAUACUGAAUCCGCAAUAACGUAAGACAUUAGCAGUGGGACACGCAUUUAGGAUGCAACUACUCGCCCGACGCCUAAGCCGAAUAGCUGAAUUGGCGCUAUGGCUGUUGCUCACGCGUGUGUAAACAGGAAGGAUCACUCACCGACCCAGGUAGCUAUUGUCCGUACGCGAGGUACGCCAAUCCUUUGCCUUGAAUCGGCUAGCUACCUAUUGAGUAAAACCAGGUGCGAUCCUACCCUACCCAUGACCCCGUAUGGACGGUUUUAUAGGUGUUAGAUAUUACCCGACGACGAUUUCGGAUGAUUGAGUCCAGUUGGGUUCAGCGUCACUGGGAACGAACGGUGCGCAAGUAAAUUACCCAGCCUGUCUUCUCAUUUGGCGCGAUAAUGACGGGCAGGUAUUGUCGGUGUGAUUGCCGGCGUCUGAGAAGAGCCUGGUGGCAUAUCACUCCCGCCAUGACUUUGGCCCCACCUGGAGCCCACAGUUCUUUAUGUAGGGCCAUCCGUGCCAGCAUGUUACUUUUUAUAGAACGAUCACUCGCG";
		chars = testData.chars().mapToObj(e->(char)e).collect(Collectors.toList());
		huffman = new Huffman<>(chars);

		System.out.println("Uneven letter distribution with RNA (best case)");
		//System.out.printf("Testing Huffman on :\n\t%s\n", testData);
		System.out.printf("Resulting Tree : \n%s\n", huffman.toString());
		encodedData = huffman.encode(chars);
		//System.out.printf("Resulting encoding : \n%s\n\n", encodedData);
		decodedData = huffman.decode(encodedData);
		//System.out.printf("Resulting decoding : \n%s\n\n", decodedData);

		normalSize = testData.length()*8;
		encodedSize = encodedData.length();

		System.out.printf("Efficency = Unencoded %f / Encoded %f = %%%f\n\n", normalSize, encodedSize, normalSize/encodedSize*100);

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
