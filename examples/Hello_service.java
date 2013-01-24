package corba.sample_a;
//Implementation the service
import HelloWorld.*;
import java.util.*;
public class Hello_service extends Interface_HelloPOA
{
	private Calendar cal;
  public Hello_service()
	{
	super();
	cal = Calendar.getInstance();
	}
  public String get_msg()
  {
        cal = Calendar.getInstance();
        String msg="Hello world! my time is: "+ cal.get(cal.HOUR_OF_DAY) + ":" + cal.get(cal.MINUTE)+ ":"+ cal.get(cal.SECOND) + ":" + cal.get(cal.MILLISECOND);
        System.out.println("Server>server is returning the following message to client: "+msg);
	return msg;
  }
}
