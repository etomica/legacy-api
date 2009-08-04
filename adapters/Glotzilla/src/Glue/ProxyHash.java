package glotz.wrapper;

import java.util.HashMap;

public class ProxyHash {

  static HashMap hash = new HashMap();

  static Object getJavaObject(long cPtr) {
    return hash.get(cPtr);
  }

  static void setJavaObject(Object object, long cPtr) {
    if(!hash.containsKey(cPtr)) {
      try {
        hash.put(cPtr, object);
      }
      catch (UnsupportedOperationException ex) {
      }
      catch (ClassCastException ex) {
      }
      catch (IllegalArgumentException ex) {
      }
      catch (NullPointerException ex) {
      }
    }
  }

}


