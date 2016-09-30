package MyThreadPool;

import java.lang.reflect.Method;

public class Task {
  	private Object execute;
  	private Method method;
  	private Object parameters;
  	
  	public Task(Object execute, Method method, Object parameters) {
  		this.execute = execute;
  		this.method = method;
  		this.parameters = parameters;
	}
  	
	public Object getExecute() {
		return execute;
	}

	public void setExecute(Object execute) {
		this.execute = execute;
	}
	public Method getMethod() {
		return method;
	}
	public void setMethod(Method method) {
		this.method = method;
	}
	public Object getParameters() {
		return parameters;
	}
	public void setParameters(Object parameters) {
		this.parameters = parameters;
	}
  	
	
}
