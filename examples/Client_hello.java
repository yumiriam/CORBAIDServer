package corba.sample_a;
import HelloWorld.*;           // The package containing stubs
import org.omg.CosNaming.*;  // Client_hello will use the naming service
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;      // All CORBA applications need these classes
import java.util.*;
//
// Usage: java -cp [path] corba.sample_a.Client_hello -ORBInitialPort [Port]
// [path] is the path that contains the "HelloWorld" directory and "corba.sample_a"
//      Ex:  [path]\HelloWord
//           [path]\corba\sample_a  
// [Port] is the same port number of "orbd -ORBInitialPort [Port]"
//
public class Client_hello
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
      
      System.out.println("Client>Creating and initializing the ORB");
      ORB orb = ORB.init(args, null); //or ORB orb = ORB.init(args, properties);  to start the orb with the properties
//      
      System.out.println("Client>getting the root naming context");
      org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
//
//    it uses NamingConetExt Interoperable Naming Service
      NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef); 
//      
      System.out.println("Client>Resolving the object reference in naming ["+name_service+"]");
      NameComponent nc = new NameComponent(name_service, "");
      NameComponent path[] = {nc};
      Interface_Hello hello= Interface_HelloHelper.narrow(ncRef.resolve(path));
//      
      System.out.println("Client>calling the Hello service...");
      String msg_received = hello.get_msg();
	// 
     System.out.println("Client>server returned the following message: "+msg_received);
          
    }catch(Exception e)
    {
	System.out.println("Exception:\n"+e);
    }
//
  }
}


