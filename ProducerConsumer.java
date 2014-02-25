public class ProducerConsumer {
	public static void main(String [] args) {
		Buffer b = new Buffer(25);
		Producer p = new Producer(b);
		Consumer c = new Consumer(b);
		
		p.start();
		c.start();
	}
}

class Buffer {
	private volatile char [] buffer;
	private volatile int count = 0, in = 0, out = 0;
	
	Buffer(int size) {
		buffer = new char[size];
	}
	
	public synchronized void Put(char c) {
		while(count == buffer.length) {
			try { wait(); }
			catch (InterruptedException e) { Thread.currentThread().interrupt(); } 
			finally { } 
		}
		System.out.println("Producing " + c + " ...");
		buffer[in] = c; 
		in = (in + 1) % buffer.length; 
		++count;
		notify();
	}
	 
	public synchronized char Get() {
		while (count == 0) {
			try { wait(); }
			catch (InterruptedException e) { Thread.currentThread().interrupt(); } 
			finally { } 
		}
		char c = buffer[out]; 
		out = (out + 1) % buffer.length;
		--count;
		System.out.println("Consuming " + c + " ...");
		notify();
		return c;
	}
}
     

class Producer extends Thread {
	private Buffer buffer;
	  
	Producer(Buffer b) { buffer = b; }
	public void run() {
		for(int i = 0; i < 100; i++) { buffer.Put((char)('A'+ i % 26 )); }
	}
}    

class Consumer extends Thread {
	private Buffer buffer;
	
	Consumer(Buffer b) { buffer = b; }
	public void run() {
		for(int i = 0; i < 100; i++) { buffer.Get(); }
	}
}
