import java.util.Timer;
import java.util.Date;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.Comparator;

class Entry<K> {

	public final K key;
	public final Long expiration;

	public Entry(final K __key, final Long __expiration) {
		key = __key;
		expiration = __expiration;
	}

	@Override
	public boolean equals(final Object o) {
		return o instanceof Entry ? ((Entry)o).key == key : false;
	}

}

public class ExpiringMap<K, V> {

	private volatile boolean evict = false;
	private final Thread timer;
	private final HashMap<K, V> hMap = new HashMap<K, V>();
	private final HashMap<K, Entry<K>> expMap = new HashMap<K, Entry<K>>();

	private final TreeSet<Entry<K>> Q = new TreeSet<Entry<K>>(
		new Comparator<Entry<K>>(){

			@Override
			public int compare(Entry<K> a, Entry<K> b) {
				if (a.expiration == null) return b.expiration == null ? 0 : 1; /* null if item never expires */
				if (b.expiration == null) return -1;
				return a.expiration.longValue() < b.expiration.longValue() ? -1 : a.expiration.longValue() == b.expiration.longValue() ? 0 : 1; 
			}

		}
	);

	private class Evict implements Runnable {

		@Override
		public void run() {
			synchronized(Q) {
				while (true) {
					long nextEviction = -1; 
					if (!Q.isEmpty()) {
						long currentTime = System.currentTimeMillis();
						Entry<K> e = null;
						while (!Q.isEmpty()) {
							e = Q.first();
							if (e.expiration == null) break;  /* all items are non-expiring */
							if (e.expiration <= currentTime) {  /* remove expired items */
								Q.pollFirst();
								hMap.remove(e.key);
							}else {
								nextEviction = e.expiration - currentTime; 
								break;
							}
						}
					}
					evict = false;
					Q.notify();
					try {
						if (nextEviction > 0) Q.wait(nextEviction); else Q.wait();
					} catch (InterruptedException ex) {
						ex.printStackTrace();
						continue;
					}
				}
			}
		}

	}

	public ExpiringMap() {
		timer = new Thread(new Evict());
		timer.start();
	}
	
	public V get(final K key) {
		V result = null;
		synchronized(Q) {
			result = hMap.get(key);
		}
		return result;
	}

	public void put(final K key, final V value, final Long exp) {
		synchronized(Q) {
			Entry<K> e = new Entry<K>(key, exp == null ? null : new Long(System.currentTimeMillis() + exp));
			hMap.put(key, value);
			expMap.put(key, e);
			Q.add(e);
			Evict();
		}
	}

	public boolean setExpiration(final K key, final Long new_timestamp) {
		synchronized(Q) {
			Entry<K> e = expMap.get(key), n = new Entry<K>(key, new_timestamp);
			if (e == null) return false;
			Q.remove(e); 
			expMap.put(key, n);
			Q.add(n);
			Evict();
			return true;
		}
	}

	private void Evict() {
		evict = true;
		Q.notify();
		while (evict) {
			try {
				Q.wait();
			} catch (InterruptedException ex) { }
		}
	}

	/* TODO: convert to JUnit testcase */
	public static void main(String args[]) throws InterruptedException {
		ExpiringMap<String, Integer> map = new ExpiringMap<String, Integer>();
		/* test basic expirations */
		map.put("Zero", new Integer(0), new Long(1000));
		map.put("One", new Integer(1), null);
		map.put("Two", new Integer(2), new Long(2000));
		for (int t = 0; t < 25; ++t) {
			System.out.println("\nt: " + t * 100);
			System.out.println(map.get("Zero"));
			System.out.println(map.get("One"));
			System.out.println(map.get("Two"));
			System.out.println(map.get("Tne"));
			Thread.sleep(100);
		}
		/* test setExpiration */
		map.put("Zero", new Integer(0), new Long(1000));
		map.put("One", new Integer(1), null);
		map.put("Two", new Integer(2), new Long(2000));
		map.put("Three", new Integer(3), new Long(500));
		for (int t = 0; t < 25; ++t) {
			if (t == 9) System.out.println(map.setExpiration("Zero", System.currentTimeMillis() + 400) ? "SUCCESS" : "FAIL");
			if (t == 3) System.out.println(map.setExpiration("Three", System.currentTimeMillis() + 2000) ? "SUCCESS" : "FAIL");
			System.out.println("\nt: " + t * 100);
			System.out.println(map.get("Zero"));
			System.out.println(map.get("One"));
			System.out.println(map.get("Two"));
			System.out.println(map.get("Three"));
			Thread.sleep(100);
		}
	}
}
