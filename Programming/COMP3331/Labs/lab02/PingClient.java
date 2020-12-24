import java.io.*;
import java.net.*;
import java.util.*;
import java.time.*;

/*
 * Server to process ping requests over UDP. 
 * The server sits in an infinite loop listening for incoming UDP packets. 
 * When a packet comes in, the server simply sends the encapsulated data back to the client.
 */

public class PingClient
{
   public static void main(String[] args) throws Exception
   {
      // Get command line argument.
      if (args.length != 2) {
         System.out.println("Required arguments: host port");
         return;
      }
      int port = Integer.parseInt(args[1]);
	  String hostAddr = args[0];

      // Create a datagram socket for receiving and sending UDP packets
      DatagramSocket clientSocket = new DatagramSocket();
	  // Set timeout for waiting for a response
	  clientSocket.setSoTimeout(1000);

	  InetAddress serverAddress = InetAddress.getByName(hostAddr);

	  byte[] sendData = new byte[1024];

	  String ping;
	  LocalDateTime startTime, endTime;
	  Duration diff;
	  long rtti;

	  long[] rttdata = new long[10];
	  for (int i = 0; i < 10; i++) {
		  rttdata[i] = -2;
	  }

      // Processing loop.
      for (int i = 0; i < 10; i++) {
		 startTime = LocalDateTime.now();
		 ping = String.format("PING %d %s\r\n", i, startTime); 

		 sendData = ping.getBytes();
		 DatagramPacket send = new DatagramPacket(sendData, sendData.length, serverAddress, port);
		 clientSocket.send(send);

		 try {
			 // Create a datagram packet to hold incomming UDP packet.
			 DatagramPacket recieve = new DatagramPacket(new byte[1024], 1024);
			 clientSocket.receive(recieve);
			 endTime = LocalDateTime.now();
		
			 diff = Duration.between(startTime, endTime);
			 rtti = diff.toMillis();
			 rttdata[i] = rtti;
		 	 System.out.printf("ping to %s, seq = %d, rtt = %s ms\n", hostAddr, i, rtti);
		 }
		 catch (SocketTimeoutException ste) {
		 	 System.out.printf("ping to %s, seq = %d, time out\n", hostAddr, i);
		 }
      }
	  printStatistics(rttdata);
   }

   private static void printStatistics(long[] rttdata) {
	  long min, max, total, count;
	  float average;

	  min = 2000;
	  max = -1;
	  count = 0;
	  total = 0;

	  for (int i = 0; i < rttdata.length; i++) {
		  if (rttdata[i] != -2 && rttdata[i] < min) {
			  min = rttdata[i];
		  }
		  if (rttdata[i] != -2 && rttdata[i] > max) {
			  max = rttdata[i];
		  }
		  if (rttdata[i] != -2) {
			  count++;
			  total += rttdata[i];
		  }
	  }
	  average = total/count;
	  System.out.printf("\n-------------------- PING STATISTICS ----------------------\n");
	  System.out.printf("Maximum RTT: %d ms, Minimum RTT: %d ms, Average RTT: %.2f ms\n", max, min, average);
   }
}
