import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;

class AlphabeticalComparator implements Comparator<Character> {

	public int compare(final Character c1, final Character c2) {
		char a = c1.charValue(), b = c2.charValue();
		return a == b ? 0 : (a >= 'a' && a <= 'z' ? ((a - 'a') << 1) + 1 : ((a - 'A') << 1)) < (b >= 'a' && b <= 'z' ? ((b - 'a') << 1) + 1 : ((b - 'A') << 1)) ? -1 : 1;
	}

}

public class Anagram {

	private List<Character> perm;
	private static final AlphabeticalComparator comp = new AlphabeticalComparator();

	public Anagram(String word) {
		perm = new ArrayList<Character>();
		for (int i = 0; i < word.length(); ++i) {
			perm.add(new Character(word.charAt(i)));
		}
		Collections.sort(perm, comp);	
		printAnagrams();
	}

	private void printAnagrams() {
		do {
			for (int i = 0; i < perm.size(); ++i) {
				System.out.print(perm.get(i));
			}
			System.out.print("\n");
		} while (nextPermutation(perm) > 0); 
	}

	private static int nextPermutation(final List<Character> perm) {
		if (perm.isEmpty()) {
			return 0;
		}
		Character b, c, cc;
		int idx = perm.size() - 1, s_idx, c_idx, t_idx;
		while (idx > 0 && comp.compare(perm.get(idx - 1), perm.get(idx)) >= 0) {
			--idx;
		}
		if (idx == 0) {
			return 0;
		}
		b = perm.get(idx - 1);
		c_idx = idx;
		c = perm.get(idx);
		for (s_idx = idx + 1; s_idx < perm.size(); ++s_idx) {
			cc = perm.get(s_idx); 
			if (comp.compare(cc, b) > 0 && comp.compare(cc, c) <= 0) {
				c_idx = s_idx;
				c = cc;
			}
		}
		perm.set(c_idx, b); 
		perm.set(idx - 1, c);
		for (s_idx = idx, t_idx = perm.size() - 1; s_idx < t_idx; ++s_idx, --t_idx) {
			b = perm.get(s_idx);
			perm.set(s_idx, perm.get(t_idx));
			perm.set(t_idx, b);
		} 
		return 1;
	}

	public static void main(String[] args) {
		int numWord = 0;
		Scanner sc = new Scanner(System.in);
		numWord = sc.nextInt(); 
		for (int n = 0; n < numWord; ++n) {
			new Anagram(sc.next());
		}
	}

}
