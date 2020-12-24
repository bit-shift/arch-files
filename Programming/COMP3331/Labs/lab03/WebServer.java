import java.io.*;
import java.net.*;

/*
 * Web Server to process HTTP GET Requests
 * Accepts incoming connection over TCP
 * Handles one connection at a time
 * Displays the .html or .png file if it exists, or returns Not Found
 */
public class WebServer
{

   public static void main(String[] args) throws Exception
   {
	  // Get the command line arguments for the port to listen on
      if (args.length != 1) {
         System.out.println("Usage: java WebServer port");
         System.exit(1);
      }

	  // Process the command line argument for the port
      int port = Integer.parseInt(args[0]);

	  // Create a new socket bound to the port number provided
	  // TCP Socket
      ServerSocket socket = new ServerSocket(port, 0, InetAddress.getByName("127.0.0.1"));

	  // Strings to hold HTTP Request and the File Path
	  String request, filePath;

      // Processing loop for server to continually run
      while (true) {

		 // Accept incoming connections on the socket bound to the port
		 Socket connectSocket = socket.accept();

		 // Set up a new BufferedReader to read the messages sent by the client
		 BufferedReader ci = new BufferedReader(new InputStreamReader(connectSocket.getInputStream()));

		 // Read the first line from the client input, ie the HTTP Request
		 request = ci.readLine();

		 // Check that request has not reached the end of the lines in the InputStream
		 // request will be null when it reaches the end of the input
		 if (request == null) {
			 // Close the socket and continue the loop at the start
			 connectSocket.close();
			 continue;
		 }

		 // Split the string by the space delimiter to get the HTTP Request Type and File Path
		 String[] array = request.split(" ");

		 //Set up an output stream to write back to the client 
		 DataOutputStream os = new DataOutputStream(connectSocket.getOutputStream());

		 // Create the file path name and create the File object
		 filePath = "." + array[1];
		 File file = new File(filePath);

		 // Check if the method is GET, if not return Not Implemented Error Code
		 if (!array[0].equals("GET")) {
			 os.writeBytes("HTTP/1.1 501 Not Implemented\r\n\r\n");
		 }
		 // If the file does not exist, return Not Found Error Code
		 else if (!file.exists()) {
			 os.writeBytes("HTTP/1.1 404 Not Found\r\n\r\n");
		 }
		 else {
			 // Open the file input stream for reading and read the data into a byte array
			 FileInputStream fis;
			 try {
			 	fis = new FileInputStream(file);
			 }
			 catch (FileNotFoundException fnfe) {
			 	os.writeBytes("HTTP/1.1 404 Not Found\r\n\r\n");
				os.flush();
				os.close();
				connectSocket.close();
				continue;
			 }

			 byte[] data = new byte[(int) file.length()];
			 fis.read(data);
			 
			 // Close the file input stream
			 fis.close();

			 // Successfully found the requested file, so return OK code
			 os.writeBytes("HTTP/1.1 200 OK\r\n");

			 // Get the extension of the requested file - file requested section
			 // is in array[1] from the split() earlier
			 String extension = getExtension(array[1]);

			 // Determine the Content-Type field in the HTTP Response
			 if (extension == ".png") os.writeBytes("Content-Type: image/png\r\n");
			 else if (extension == ".html") os.writeBytes("Content-Type: text/html\r\n");

			 // Determine the Content-Length field
			 os.writeBytes("Content-Length: " + data.length);

			 // Signal the end of the Header section in the HTTP Response
			 os.writeBytes("\r\n\r\n");

			 // Append the data to the Output Stream
			 os.write(data);
		 }

		 // Flush the Output Stream and then close it
		 // Close the connection to the client
		 os.flush();
		 os.close();
		 connectSocket.close();
      }
   }

   /* 
	* Get the extension of the file requested
	* Return as a string
	*/
   public static String getExtension (String fileName) {
		int i = fileName.lastIndexOf('.');
		if (i > 0) {
			return fileName.substring(i + 1);
		}
		return null;
   }
}
