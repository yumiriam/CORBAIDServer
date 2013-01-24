package corba.sample_a; 
import HelloWorld.*; // The package containing stubs
import org.omg.CosNaming.*; // Server_server will use the naming service
import org.omg.CosNaming.NamingContextPackage.*; // The package containing special exceptions thrown by the name service.
import org.omg.CORBA.*; // All CORBA applications need these classes
import org.omg.PortableServer.*; 
import org.omg.PortableServer.POA;
import java.util.*; 
import java.io.*; // The package containing the class BufferedReader

//
//Usage: java -cp [path] corba.sample_a.Server_hello -ORBInitialPort [Port]
// [path] is the path that contains the "HelloWorld" directory and "corba.sample_a"
//      Ex:  [path]\HelloWord
//           [path]\corba\sample_a  
// [Port] is the same port number of "orbd -ORBInitialPort [Port]"
// Remarks: before start the Server_hello is need start the orbd application in [java directory]\bin
//          orbd -ORBInitialPort [port]
//
public class Server_hello 
{
  public static void main(String args[])
  {
	String name_service="Hello_server";
//
//      create the properties:org.omg.CORBA.ORBInitialHost and org.omg.CORBA.ORBInitialPort
//	Properties properties = System.getProperties();
//      properties.put("org.omg.CORBA.ORBInitialHost",args[0]);
//      properties.put( "org.omg.CORBA.ORBInitialPort",args[1]);
//

    try{
	System.out.println("Server>starting server...");
        System.out.println("Server>creating and initializing the ORB");
        ORB orb = ORB.init(args, null); //or ORB orb = ORB.init(args, properties);  to start the orb with the properties
//      
	System.out.println("Server>getting reference to rootpoa");
        POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
	System.out.println("Server>activating the POA Manager");
	rootpoa.the_POAManager().activate();
//
        System.out.println("Server>Creating the servant");
        Hello_service hello_service = new Hello_service();
//
	System.out.println("Server>obtain the reference from the servant");
	org.omg.CORBA.Object service_ref =  rootpoa.servant_to_reference(hello_service);
        Interface_Hello service_href= Interface_HelloHelper.narrow(service_ref);
//
      System.out.println("Server>getting the root naming context");
      org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
    
//  
      System.out.println("Server>using NamingContextExt to provides interoperability");  
      NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
//      
      System.out.println("Server>binding the object reference in naming with name "+name_service);
      NameComponent nc = new NameComponent(name_service, "");
      NameComponent path[] = {nc};
      ncRef.rebind(path, service_href);
//
      System.out.println("Server>Server was started...");
//
	BufferedReader data_reader =
      	  new BufferedReader(new InputStreamReader(System.in));
	String msg_kbd= " ";
	 while (!msg_kbd.equals("quit") && !msg_kbd.equals("QUIT")) {
            System.out.println("Server>enter with quit command to shutdown the server...");
            msg_kbd = data_reader.readLine();
            if (msg_kbd.equals("quit") || msg_kbd.equals("QUIT")) {
                System.out.println("Server>shutdown of server is in progress...");
			ncRef.unbind(path);
			orb.shutdown(false);
                System.out.println("Server>shutdown was successful...");
            }
        }
//
    } catch (Exception e) {
        System.out.println("Exception in server...\nException:\n" + e);

    }
  }
}



