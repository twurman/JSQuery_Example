// This handler implements the services provided to the client.

// Java packages
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

// Interface definition
import edu.umich.clarity.thrift.*;
import org.apache.thrift.TException;

/** Implementation of the question-answer interface defined
 * in the question-answer thrift file. A client request to any
 * method defined in the thrift file is handled by the
 * corresponding method here.
 */
public class SchedulerServiceHandler implements SchedulerService.Iface {
  
	private static Map<String, THostPort> registeredServices;

	public SchedulerServiceHandler()
	{
		registeredServices = new HashMap<String, THostPort>();
	}

	@Override
	public THostPort consultAddress(String serviceType) throws TException {
	    // System.out.println("receive consulting about service " + serviceType);
	    // THostPort hostPort = new THostPort();
	    // hostPort.ip = "clarity04.eecs.umich.edu";
	    // hostPort.port = 4200;
		THostPort hostPort = registeredServices.get(serviceType);
		if(hostPort != null) {
			System.out.println("Found hostPort at " + hostPort.ip + ":" + hostPort.port);
			return hostPort;
		} else {
			System.out.println(serviceType + " service not found");
		}
		
	    return new THostPort();
	}

	@Override
	public void registerBackend(RegMessage message) throws TException {
		registeredServices.put(message.app_name, message.endpoint);
		System.out.println("Registered " + message.app_name + " service at port " + registeredServices.get(message.app_name).port);
	}

	@Override
	public void updateLatencyStat(String name, LatencyStat latencyStat) throws TException {

	}

}

